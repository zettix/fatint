// fat_int.h Manipulate really long integers.
//
// Inspired by Java's BigInteger class and C++'s fascination with overloading.
// (C) 2017 Sean Brennan
//
// Note: c++11 required due to the use of uint32_t and uint64_t.
//       Replacing with longs should not be difficult but you need
//       a native double width of a single bit packet, 64 for 32 in this case.
//
// MIT Licence.  I hear it's a good one.
//

#ifndef __COM_ZETTIX_FATINT_H__
#define __COM_ZETTIX_FATINT_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace com_zettix {

class Fatint {
 public:
  Fatint();
  Fatint(const Fatint &rhs);
  Fatint(const string &rhs, int base=16);
  Fatint(const long long int value);

  Fatint & operator=(const Fatint &rhs);
  Fatint & operator+=(const Fatint &rhs);
  Fatint & operator-=(const Fatint &rhs);
  Fatint & operator*=(const Fatint &rhs);
  Fatint & operator/=(const Fatint &rhs);
  Fatint & operator%=(const Fatint &rhs);
  Fatint & operator<<=(int bits);
  Fatint & operator>>=(int bits);
  Fatint & shift(int bits);
  int compare_to(const Fatint &rhs, bool abs=false) const;
  bool is_positive() const;
  bool negate();
  bool get_bit(int index) const;
  long long int get_value() const;  // get value masked with |long long|
  void set_bit(int index);
  void clear_bit(int index);
  string to_string(int base=16) const;
  friend bool operator<(const Fatint &lhs, const Fatint &rhs);
  friend bool operator>(const Fatint &lhs, const Fatint &rhs);
  friend bool operator<=(const Fatint &lhs, const Fatint &rhs);
  friend bool operator>=(const Fatint &lhs, const Fatint &rhs);
  friend bool operator==(const Fatint &lhs, const Fatint &rhs);
  friend bool operator!=(const Fatint &lhs, const Fatint &rhs);
  friend Fatint operator+(const Fatint &lhs, const Fatint &rhs);
  friend Fatint operator+(const Fatint &lhs);
  friend Fatint operator-(const Fatint &lhs, const Fatint &rhs);
  friend Fatint operator-(const Fatint &lhs);
  friend Fatint operator*(const Fatint &lhs, const Fatint &rhs);
  friend Fatint operator/(const Fatint &lhs, const Fatint &rhs);  // Divide by ZERO returns ZERO!
  friend Fatint operator%(const Fatint &lhs, const Fatint &rhs);  // Mod by ZERO returns ZERO!
  friend Fatint operator<<(const Fatint &lhs, int bits);
  friend Fatint operator>>(const Fatint &lhs, int bits);

 private:
  vector<uint32_t> vec_;
  bool positive = true;
  static const int BIT_WIDTH = 32;
  static int get_digit_(char c, int base);
  Fatint &fastmultiply_(const Fatint &rhs);
  Fatint &fastdivide_(const Fatint &rhs);
  Fatint &fastmod_(const Fatint &rhs);
  string special_to_string_(int base) const;
  void remove_leading_zeros_();
};

const Fatint ZERO = Fatint("0");
const Fatint ONE = Fatint("1");
const Fatint TWO = Fatint("2");

istream& operator>>(istream &din, Fatint &x);
ostream& operator<<(ostream &dout, const Fatint &x);
bool operator<(const Fatint &lhs, const Fatint &rhs);
bool operator>(const Fatint &lhs, const Fatint &rhs);
bool operator<=(const Fatint &lhs, const Fatint &rhs);
bool operator>=(const Fatint &lhs, const Fatint &rhs);
bool operator==(const Fatint &lhs, const Fatint &rhs);
bool operator!=(const Fatint &lhs, const Fatint &rhs);
Fatint operator+(const Fatint &lhs, const Fatint &rhs);
Fatint operator-(const Fatint &lhs, const Fatint &rhs);
Fatint operator*(const Fatint &lhs, const Fatint &rhs);
Fatint operator/(const Fatint &lhs, const Fatint &rhs);
Fatint operator%(const Fatint &lhs, const Fatint &rhs);
Fatint operator<<(const Fatint &lhs, int bits);
Fatint operator>>(const Fatint &lhs, int bits);

} // namespace

#endif
