// Fatint.cc fat integer implementation.

// (C) 2017 Sean Brennan
//
// MIT Licence.

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

#include "fatint.h"

using namespace std;

// stored as vector of unsigned 32 bit integers.  least significant is index 0.

namespace com_zettix {

Fatint::Fatint()  {
  vec_.push_back(0);
}

Fatint::Fatint(const Fatint &rhs) {
  vec_.clear();
  vec_.insert(vec_.begin(), rhs.vec_.begin(), rhs.vec_.end());
  positive = rhs.positive;
}

Fatint::Fatint(long long int value) {
  if (value < 0) {
    positive = false;
    value = -value;
  }
  uint32_t x = (value & 0xffffffff);
  vec_.push_back(x);
  x = ((value & 0xffffffff00000000) >> 32);
  vec_.push_back(x);
  remove_leading_zeros_();
}

long long int Fatint::get_value() const {
  long long int result = (long long int) vec_[0];
  long long int multiplier =  (long long int) vec_[1] << 32;
  multiplier &= 0x7fffffff00000000;  // 2's complement likes bit 63 for neg.
  result += multiplier;
  if (! positive) {
    result = -result;
  }
  return result;
}

int Fatint::get_digit_(char c, int base) {
  int value = -1;
  if (c >= '0' && c <= '9') {
    value = (c - '0');
  } else if (c >= 'a' && c <= 'z') {
    value = (c - 'a') + 10;
  } else if (c >= 'A' && c <= 'z') {
    value = (c - 'A') + 10;
  }
  if (value > base) {
    return -1;
  }
  return value;
}

Fatint::Fatint(const string &rhs, int base) {
  int ctr = 0;
  uint32_t subt = 0;
  int start = 0;
  if (rhs[0] == '-') {
    positive = false;
    start = 1;
  }
  if (base == 16) {
    for (int j = rhs.length() - 1; j >= start; j--) {
      char c = rhs[j];
      int digval = get_digit_(c, base);
      if (digval >= 0) {
        ctr++;
      } else {
        cerr << "Illegal character in base 16: " << c << " returning ZERO"
             << endl;
        vec_.push_back(0);
        return;
      }
      subt += digval << ((ctr - 1) * 4);
      if (ctr == 8) {
        vec_.push_back(subt);
        subt = 0;
        ctr = 0;
      }
    }
    if (subt != 0 || vec_.size() == 0) {
      vec_.push_back(subt);
    }
  } else {
   if (base > 1) {
     Fatint accum;
     Fatint base_f(base);
     Fatint base_scaler(ONE);  // base ^ 0 = 1.
     for (int j = rhs.length() - 1; j >= start; j--) {
        char c = rhs[j];
        int digval = get_digit_(c, base);
        if (digval < 0) {
          cerr << "Illegal character in base " << base << ": " 
               << c << " returning ZERO" << endl;
          vec_.push_back(0);
          return;
        }
        accum += Fatint(digval) * base_scaler;
        base_scaler *= base_f;
      }
      vec_.clear();
      vec_.insert(vec_.begin(), accum.vec_.begin(), accum.vec_.end());
      positive = accum.positive;
    } else {
      cerr << "Illegal base: " << base << endl;
      vec_.push_back(0);
    }
  }
}

Fatint & Fatint::operator=(const Fatint &rhs) {
  vec_.clear();
  vec_.insert(vec_.begin(), rhs.vec_.begin(), rhs.vec_.end());
  positive = rhs.positive;
  return *this;
}

istream& operator>>(istream &din, Fatint &x) {
  string s;
  din >> s;
  x = Fatint(s);
  return din;
}

ostream& operator<<(ostream &dout, const Fatint &x) {
  dout << x.to_string();
  return dout;
}


string Fatint::to_string(int base) const {
  stringstream ss;
  if (!positive) {
    ss << "-";
  }
  if (base != 16) {
    string special_return = special_to_string_(base);
    ss << special_return;
  } else {
    for (int j = vec_.size() - 1; j >= 0; j--) {
      uint32_t num = vec_[j];
      stringstream tmp_ss;
      tmp_ss << hex << num;
      if (j != vec_.size() - 1) {
        for (int i = 8 - tmp_ss.str().length(); i > 0; i--) {
          ss << "0";
        }
      }
      ss << tmp_ss.str();
    }
  }
  return ss.str();
}

bool Fatint::get_bit(int index) const {
  int skip = index / BIT_WIDTH;
  int mask = 1 << (index % BIT_WIDTH);
  if ((skip + 1) > vec_.size()) {
    return false;
  }
  uint32_t item = vec_[skip];
  if ((item & mask) > 0) {
    return true;
  }
  return false;
}

void Fatint::set_bit(int index) {
  int skip = index / BIT_WIDTH;
  int mask = 1 << (index % BIT_WIDTH);
  if ((skip + 1) > vec_.size()) {
    vec_.resize(skip + 1);
  }
  uint32_t item = vec_[skip];
  vec_[skip] = item | mask;
}

void Fatint::clear_bit(int index) {
  int skip = index / BIT_WIDTH;
  int mask = 1 << (index % BIT_WIDTH);
  mask = ~mask;
  if ((skip + 1) > vec_.size()) {
    vec_.resize(skip + 1);
  }
  uint32_t item = vec_[skip];
  vec_[skip] = item & mask;
  remove_leading_zeros_();
}


/** fastmultiply(): multiply two Fatint numbers faster than nxm adds.

For a calculation a x b, we consider decomposing the smaller number
into its binary form, and then performing the add on the digits. For example,
9 x 5 = 1001 x 101.  9 is longer so we decompose 5. we then see:
9 x 5 = 9 x (100) + 9 x (000) + 9 x (001)
by masking 5 one bit at a time, resulting in 3 adds instead of 5.
This is log2(n) or linear in the number of digits.  */
Fatint & Fatint::fastmultiply_(const Fatint &rhs) {
  bool me_bigger = compare_to(rhs, true) > 0;
  const Fatint &aref = (me_bigger)? *this : rhs;
  const Fatint &bref = (me_bigger)? rhs : *this;

  Fatint result = ZERO;

  // a is bigger than b. iterate over b's binary digits.
  // Find first 1....
  int num_packets = bref.vec_.size();
  uint32_t last_packet = bref.vec_.back();
  int first_one = 31;
  while (first_one >= 0) {
    uint32_t testbit = 1 << first_one;
    if (testbit & last_packet) {
      break;
    }
    first_one--;
  }
  int num_bits = (num_packets - 1) * BIT_WIDTH + first_one + 1;
  Fatint tmpa = aref;

  for (int b = 0; b < num_bits; b++) {
    if (bref.get_bit(b)) {
      result += tmpa;
    }
    if (b < num_bits - 1) {
      tmpa.shift(1);
    }
  }
  *this = result;
  return  *this;
}


/** fastmod(): find remainder of x / y or x modulo y aka x % y.

@see fastdivide() for more details.
*/
Fatint & Fatint::fastmod_(const Fatint &rhs) {
  if (rhs == ZERO) {
    cerr << "MOD BY ZERO ERROR!!!!!!!!!!!!!!!!!" << endl;
    *this = ZERO;  // TODO(sean): what is a NaN and do I want one?
    return *this;  // or do I throw an exception.  In c++??
  }
  Fatint multiple = rhs;
  int bitcount = 0;
  while (multiple <= *this) {  // shift up to bignuts.
    multiple.shift(1);
    bitcount++;
  }
  for (int i = bitcount - 1; i >= 0; i--) {
    multiple.shift(-1);
    if (*this >= multiple) {
      *this -= multiple;
    }
  }
  return *this;
}


/** fastdivide(): divide two Fatint numbers faster than n subracts.

For a calculation a / b, we test multiples of b util we hit a.
We then test each multiple as we whittle down a.  The multiples
are 2 to the n and reflect the binary form of the resulting quotient.

We considered caching values but this could be prohibitive.
A million digit binary number would have a million cached multiples.
Storage of n^2 is no good.
*/


Fatint & Fatint::fastdivide_(const Fatint &divisor) {
  Fatint result = ZERO;
  if (divisor == ZERO) {
    cerr << "DIVIDE BY ZERO ERROR!!!!!!!!!!!!!!!!!" << endl;
    *this = ZERO;  // TODO(sean): what is a NaN and do I want one?
    return *this;  // or do I throw an exception.  In c++??
  }
  if (divisor == ONE) {
    return *this;
  }
  Fatint multiple = divisor;
  int bitcount = 0;
  while (multiple <= *this) {  // shift up to bignuts.
    multiple.shift(1);
    bitcount++;
  }
  for (int i = bitcount - 1; i >= 0; i--) {
    multiple.shift(-1);
    if (*this >= multiple) {
      *this -= multiple;
      result.set_bit(i);
    }
  }
  *this = result;
  return *this;
}

string Fatint::special_to_string_(int base) const {
  static char base_buff[37] = "0123456789"
                              "abcdefghij"
                              "klmnopqrst"
                              "uvwxyz";

  if (base > 36 || base < 2) {
      return "[ERROR: Invalid base]";
  }
  
  Fatint tmp = *this;
  Fatint basecount = ONE;
  Fatint fatbase(base);
  stringstream ss;
  
  // Size up number of digits of base whatever.
  int mulcount = 0;
  while (tmp > basecount) {
    basecount *= fatbase;
    mulcount++;
  }
  int mulcount_max = mulcount;

  basecount /= fatbase;
  // Divide with remainder to get digits.
  while (tmp >= ZERO && basecount >= ONE) {
    Fatint doggo = tmp / basecount;
    if (doggo < fatbase) {
      int i = doggo.get_value();
      char c = base_buff[i];
      ss << c;
    } else {
      return "[ERROR: BAD SPECIAL CONVERSION";
    }
    tmp -= doggo * basecount;  // the remainder.
    basecount /= fatbase;
    mulcount--;
    if (tmp < ZERO) {
      ss << "Tmp: " << tmp << endl;
      ss << "[ERROR: CODE SPECIAL CONVERSION";
      return ss.str();
    }
  }
  return ss.str();
}


Fatint & Fatint::operator+=(const Fatint &rhs) {
  if (positive != rhs.positive) {
    bool me_bigger = compare_to(rhs, true) > 0;
    if (me_bigger) {   // a - b, -a + b: |a| > |b|.
      this->negate(); //  negate to fool subtract into thinking same sign.
      *this -= rhs;
      this->negate(); // fix up sign.
      return *this;
    } else {          //  a - b, -a + b: |a| < |b|.
      this->negate(); //  negate to fool subtract into thinking same sign.
      *this = rhs - *this;
      return *this;   // leave sign reversed.
    }
  }
  uint64_t a, b, carry = 0;
  int a_end = vec_.size();
  int b_end = rhs.vec_.size();
  int longest = a_end;
  if (b_end > longest) {
    longest = b_end;
  }
  for (int i = 0; i < longest; i++) {
    if (i < a_end) {
      a = (uint64_t) vec_[i];
    } else {
      a = 0;
    }
    if (i < b_end) {
      b = (uint64_t) rhs.vec_[i];
    } else {
      b = 0;
    }
    a += b + carry;
    carry = a >> 32;
    uint32_t result = a & 0xffffffff;
    if (i < a_end) {
      vec_[i] = result;
    } else {
      vec_.push_back(result);
    }
  }

  if (carry > 0) {
    vec_.push_back(carry);
  }

  return *this;
}

void Fatint::remove_leading_zeros_() {
  // remove leading zeros. but leave at least 1 digit.
  int newsize = vec_.size();
  for (int j = vec_.size() - 1; j > 0; j--) { 
    if (vec_[j] == 0) {
      newsize--;
    } else {
      break;
    }
  }
  if (newsize != vec_.size()) {
   vec_.resize(newsize);
  }
  if (newsize == 1) {
    if (vec_.back() == 0) {
      positive = true;
    }
  }
}

Fatint & Fatint::operator-=(const Fatint &rhs) {
  if (positive != rhs.positive) {
    // -a - b, a - -b: just add.
    this->negate(); //  negate to fool add into thinking same sign.
    *this += rhs;
    this->negate(); // fix up sign.
    return *this;
  }

  uint64_t a, b, tmpres = 0, borrow = 0;
  int a_end = vec_.size();
  int b_end = rhs.vec_.size();
  bool a_morethan_b = compare_to(rhs, true) > 0;
  const Fatint &a_ref =  (a_morethan_b)? *this : rhs;
  const Fatint &b_ref =  (a_morethan_b)? rhs : *this;
  int longest = (a_morethan_b)? a_end : b_end;
  positive = (a_morethan_b)? positive: !positive;

  for (int i = 0; i < longest; i++) {
    if (i < a_end) {
      a = (uint64_t) a_ref.vec_[i];
    } else {
      a = 0;
    }
    if (i < b_end) {
      b = (uint64_t) b_ref.vec_[i];
    } else {
      b = 0;
    }
    uint32_t res;
    if (a >= (b + borrow)) {
      tmpres = a - b - borrow;
      res = tmpres & 0xFFFFFFFF;
      borrow = 0;
    } else {
      tmpres = 0x100000000; //  1 << 32;
      tmpres +=  a - b - borrow;
      res = tmpres & 0xFFFFFFFF;
      borrow = 1;
    }
    if (i < a_end) {
      vec_[i] = res;
    } else {
      vec_.push_back(res);
    }
  }
  remove_leading_zeros_();
  return *this;
}

Fatint & Fatint::operator%=(const Fatint &rhs) {
  fastmod_(rhs);
  return *this;
}

Fatint & Fatint::operator<<=(int bits) {
  shift(bits);
}

Fatint & Fatint::operator>>=(int bits) {
  shift(-bits);
}

Fatint & Fatint::operator/=(const Fatint &rhs) {
  fastdivide_(rhs);
  return *this;
}

bool Fatint::is_positive() const {
  return positive;
}

bool Fatint::negate() {
  positive = !positive;
  return positive;
}

Fatint & Fatint::operator*=(const Fatint &rhs) {
  fastmultiply_(rhs);
  return *this;
}
  
Fatint operator+(const Fatint &lhs, const Fatint &rhs) {
  Fatint tmp = lhs;
  tmp += rhs;
  return tmp;
}

Fatint operator+(const Fatint &lhs) {
  Fatint tmp = lhs;
  return tmp;
}

Fatint operator-(const Fatint &lhs, const Fatint &rhs) {
  Fatint tmp = lhs;
  tmp -= rhs;
  return tmp;
}

Fatint operator-(const Fatint &lhs) {
  Fatint tmp = lhs;
  tmp.negate();
  return tmp;
}

Fatint operator*(const Fatint &lhs, const Fatint &rhs) {
  Fatint tmp = lhs;
  tmp *= rhs;
  return tmp;
}

Fatint operator/(const Fatint &lhs, const Fatint &rhs) {
  Fatint tmp = lhs;
  tmp /= rhs;
  return tmp;
}

Fatint operator%(const Fatint &lhs, const Fatint &rhs) {
  Fatint tmp = lhs;
  tmp %= rhs;
  return tmp;
}


Fatint operator>>(const Fatint &lhs, int bits) {
  Fatint tmp = lhs;
  tmp.shift(-bits);
  return tmp;
}

Fatint operator<<(const Fatint &lhs, int bits) {
  Fatint tmp = lhs;
  tmp.shift(bits);
  return tmp;
}


int Fatint::compare_to(const Fatint &rhs, bool abs) const {
  // <, ==, > ? -int, 0, +int.
  int a_end = vec_.size();
  int b_end = rhs.vec_.size();

  bool this_p = (abs)? true : positive;
  bool rhs_p = (abs)? true : rhs.positive;
  int result = 0;

  if (a_end != b_end) {
    if (a_end < b_end) {
        return (this_p)? -1 : 1;
    }
    if (b_end < a_end) {
      return (rhs_p)? 1 : -1;
    }
  }
  if (this_p != rhs_p) {
    // same number of buckets from above if. if one bucket both zero, sign
    // does not matter. -0 === 0. Fixes all kinds of addition/multiply/shift
    // resulting in a negative number becoming zero.
    if (a_end == 1) {
      if (vec_.back() == 0) {
         if (rhs.vec_.back() == 0) {
           return 0;
         }
      }
    }
    result =  (this_p)? 1: -1;
  } else {
    for (int j = b_end - 1; j >= 0; j--) {
      bool d = vec_[j] > rhs.vec_[j];
      bool e = vec_[j] < rhs.vec_[j];
      if (! (d | e)) {
        continue;
      }
      if (d) {
        result = (this_p)? 1: -1;
        break;
      } else {
        result = (this_p)? -1: 1;
        break;
      }
    }
  }
  return result;
}

Fatint & Fatint::shift(int bits) {
  vector<uint32_t> res;
  bool left = true;
  if (bits < 0) {
    bits = -bits;
    left = false;
  }

  int cell_shifts = bits / BIT_WIDTH;
  int cell_offset = bits % BIT_WIDTH;
  int mask =  32 - cell_offset;
  int new_size = 0;

  if (left) {
    for (int i = 0; i < cell_shifts; i++) {
      res.push_back(0);
      new_size++;
    }
    uint32_t old_in = 0;
      for (int i = 0; i < vec_.size(); i++) {
        if (cell_offset != 0 ) {  // 32 does nada.
          uint32_t new_in = vec_[i] << cell_offset;
          new_in |= old_in;
          res.push_back(new_in);
          old_in = vec_[i] >> mask;
        } else {
           res.push_back(vec_[i]);
        }
        new_size++;
      }
      if (old_in > 0) {
        res.push_back(old_in);
        new_size++;
      }
  } else {  // shift right
    // remove least significant cells.
    uint32_t old_in = 0;
    for (int i =  vec_.size() - 1; i >= cell_shifts; i--) {
      uint32_t new_in;
      if (cell_offset != 0) {
        new_in = vec_[i] >> cell_offset;
      } else {
        new_in = vec_[i];
      }
      new_in |= old_in;
      res.insert(res.begin(), new_in);
      if (cell_offset != 0) {
        old_in = vec_[i] << mask;
      } else {
        old_in = vec_[i];
      }
      new_size++;
    }
  }

  vec_.clear();

  if (new_size > 1) {
    const vector<uint32_t>::iterator last_index = (res.back() == 0)? res.end() - 1 : res.end();
    vec_.insert(vec_.begin(), res.begin(), last_index);
  } else {
    if (new_size == 0) {
      vec_.push_back(0);
      positive = true;
    } else {
      vec_.push_back(res.back());
    }
  }

  return *this;
}

bool operator<(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) < 0);
}

bool operator>(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) > 0);
}

bool operator<=(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) <= 0);
}

bool operator>=(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) >= 0);
}

bool operator==(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) == 0);
}

bool operator!=(const Fatint &lhs, const Fatint &rhs) {
  return (lhs.compare_to(rhs) != 0);
}

} // namespace
