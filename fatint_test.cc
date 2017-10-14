// fatint_test: test fatint functions.
//
// (C) Sean Brennan 2017
//
// Mit License.


#include <string>
#include <sstream>
#include <iostream>
#include "fatint.h"

using namespace std;
using namespace com_zettix;

class Test {
  public:

  bool equality_tests() {
    Fatint a("0");
    Fatint b("0");
    assert(a == b, "Zero equals zero. 1");
    assert(!(a != b), "Zero equals zero. 2");
    a = -a;
    assert(a == b, "A-Zero equals zero. 3");
    assert(!(a != b), "A-Zero equals zero. 4");
    assert(ZERO == b, "B-Zero equals zero. 5");
    assert(!(ZERO != b), "B-Zero equals zero. 6");
    assert(a == ZERO, "C-Zero equals zero. 7");
    a = Fatint("1");
    b = Fatint("1");
    assert(a == b, "ONE equals ONE. 8");
    assert(!(a != b), "ONE equals ONE. 9");
    assert(ONE == b, "ONE equals ONE. 10");
    assert(!(ONE != b), "ONE equals ONE. 11");
    assert(a == ONE, "ONE equals ONE. 12");
    assert(!(a != ONE), "ONE equals ONE. 13");
    b = Fatint("-1");
    assert(! (a == b), "-ONE does not equal ONE. 14");
    assert((a != b), "-ONE does not equal ONE. 15");
    log(a, b);
    a = Fatint("-1");
    assert( (a == b), "Minus ONE does equal Minus ONE. 16");
    assert( !(a != b), "Minus ONE does equal Minus ONE. 17");
    a = ZERO - ZERO - ONE;
    assert( (a == b), "Minus ONE does equal Minus ONE. 18");
    assert( !(a != b), "Minus ONE does equal Minus ONE. 19");

    a = Fatint("4");
    b = Fatint("5");
    assert( !(a == b), "4 is not 5. 20");
    assert( (a != b), "4 is not 5. 21");
    assert( !(a > b), "4 is !> 5. 22");
    assert( (a < b), "4 is < 5. 23");
    assert( !(a >= b), "4 is !>= 5. 24");
    assert( (a <= b), "4 is <= 5. 25");
    a = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
               "2643302198588690069095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");
    assert( !(a == b), "X is not 5.");
    assert( (a != b), "X is not 5.");
    assert( (a > b), "X is > 5.");
    assert( !(a < b), "X is !< 5.");
    assert( (a >= b), "X is >= 5.");
    assert( !(a <= b), "X is !<= 5.");
    b = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
      /* f */  "264330219858869006f095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");  //       ^f^
    assert( !(a == b), "A != B.");
    assert( (a != b), "A != B.");
    assert( !(a > b), "A is !> B.");
    assert( (a < b), "A is < B.");
    assert( !(a >= b), "A is !>= B.");
    assert( (a <= b), "A is <= B.");

    return error;
  }

  bool multiply_tests() {
    Fatint a("2");
    Fatint b("4");
    Fatint c("8");
    assert(  ((a * b) == c), "MUL  1");
    a = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
               "2643302198588690069095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");
    b = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
               "264330219858869006f095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");
    c = Fatint("581f3e00e4925470596fb28507a89d913e5298e870cb9b8f4f24ed8c602e4"
               "9fa261dcb9b4aa7f23768540c8a764b2745b92278389d821a51d81255fb83"
               "4578ee35f8f9102e6fd5355c5312ded7e65e67639e6aa5fe3569770e22a7d"
               "3b0561631340c5c9785b140c3ea16c3c4bd3c59dc8f8e2f972288f81c3150"
               "622d580a0673a355a874964184cfb5ae8f8740398c8a1d072d0efcf1ff1ea"
               "8bf95b251b0384dd59fd47785159e39a1ab16f0ee9e7ce8ef325e6af23f62"
               "6eaaf85c0c0e6a550ad5ec8ae5248b419db9603ebfd58a40e89dad86aa2ae"
               "52abbf07d613dc08e29088bd3adbd3f37faf908a104c070c8f1f57fccdda7"
               "297e5a46b2d5bc6d92a6ecda1e40910cf012d58fffcce571b6161b7e3a373"
               "46cc4e31c300808aacf040c753b73c693f30cd44bf1a6b6844930058ed4bc"
               "53cc10");

    assert(  ((a * ZERO) == ZERO), "MUL  2");
    assert(  ((ZERO * b) == ZERO), "MUL  3");
    assert(  ((a * b) == c), "MUL  4");

    return error;
  }

  bool add_tests() {
    Fatint a("3");
    Fatint b("5");
    Fatint c("8");
    assert( ((a + b) == c), "ADD  1");
    a = Fatint("892d26e28b03c4515d10e33f67f45d54bded9703303fd041962e222e1220e"
               "246f2bebe56fbbccc9d7a252a58ddeef0c2db01a7faf80388f157987fb5b9"
               "b37ec476c5da0d755cc40ce2c387b7a4a558b0f198b894e2f2e3b7dd34ba7"
               "f1452aeb388b66e70a2feb2a1abe4c843e46ed0ee3aedd2be181d16e478ae"
               "087af28288d0");
    b = Fatint("449693714581e228ae88719fb3fa2eaa5ef6cb81981fe820cb17111709107"
               "123795f5f2b7dde664ebd12952c6ef778616d80d3fd7c01c478abcc3fdadc"
               "d9bf623b62ed06baae62067161c3dbd252ac5878cc5c4a717971dbee9a5d3"
               "f8a295759c45b3738517f5950d5f26421f23768771d");

    c = Fatint("892d26e28b03c4515d10e33f67f45d9954810848b221f8f01e9fc1e20c4f8"
               "ca5e98a3fef1ba4ed6891364161ee60143c3a60d378d669d7ae6a2dac24b1"
               "2be031f799d78977213cb8af0362947e64baec5485bf4f9154ea293ef8965"
               "166ff072c5512b8e21c708e90464207ce0dc62ab296250b0f977667ba6b12"
               "2a6d29eaffed");
    assert( ((a + b) == c), "ADD  2");
    a = Fatint("2");
    b = Fatint("-6");
    c = Fatint("-4");
    assert(  ((a + b) == c), "ADD  3");
    
    return error;
  }

  bool subtract_tests() {
    Fatint a("6");
    Fatint b("2");
    Fatint c("4");
    assert(  ((a - b) == c), "SUB  1");
    a = Fatint("2");
    b = Fatint("6");
    c = Fatint("-4");
    assert(  ((a - b) == c), "SUB  2");
    a = Fatint("2");
    b = Fatint("-6");
    c = Fatint("8");
    assert(  ((a - b) == c), "SUB  3");
    a = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
               "2643302198588690069095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");
    b = Fatint("9632852611732543622711844548873460233693638956995191673400822"
               "2649022340246261565018450302926049200390837709989475142731032"
      /* f */  "264330219858869006f095107378187188328824724138482659042912276"
               "5646765838930896103467735777528120126927593571602462645634450"
               "9693254786357341666290157781830471973979728215988144242675583"
               "184");  //       ^f^
    c = Fatint("-600000000000000000000000000000000000000000000000000000000000"
               "0000000000000000000000000000000000000000000000000000000000000"
               "00000000000000000000000000000000000000000000000");
    assert(  ((a - b) == c), "SUB  4");
    
    return error;
  }

  bool divide_tests() {
    Fatint a("8");
    Fatint b("2");
    Fatint c("4");
    assert(  ((a / b) == c), "DIV  1");
    a = Fatint("892d26e28b03c4515d10e33f67f45d54bded9703303fd041962e222e1220e"
               "246f2bebe56fbbccc9d7a252a58ddeef0c2db01a7faf80388f157987fb5b9"
               "b37ec476c5da0d755cc40ce2c387b7a4a558b0f198b894e2f2e3b7dd34ba7"
               "f1452aeb388b66e70a2feb2a1abe4c843e46ed0ee3aedd2be181d16e478ae"
               "087af28288d0");
    b = Fatint("449693714581e228ae88719fb3fa2eaa5ef6cb81981fe820cb17111709107"
               "123795f5f2b7dde664ebd12952c6ef778616d80d3fd7c01c478abcc3fdadc"
               "d9bf623b62ed06baae62067161c3dbd252ac5878cc5c4a717971dbee9a5d3"
               "f8a295759c45b3738517f5950d5f26421f23768771d");
    c = Fatint("2000000000000000000000000000000");
    assert(  ((a / b) == c), "DIV  2");
    
    assert(  ((a / ONE) == a), "DIV  3");

    // rut-roh:
    assert(  ((a / ZERO) == ZERO), "DIV  4");

    a = Fatint("3b9aca00");
    b = Fatint("a");
    assert (( a / b) > ZERO, "DIV 5");

    return error;
  }

  bool mod_tests() {
    Fatint a("3");
    Fatint b("8");
    Fatint c("3");
    assert(  ((a % b) == c), "MOD  1");
    a = Fatint("449693714581e228ae88719fb3fa2eaa5ef6cb81981fe820cb17111709107"
               "123795f5f2b7dde664ebd12952c6ef778616d80d3fd7c01c478abcc3fdadc"
               "d9bf623b62ed06baae62067161c3dbd252ac5878cc5c4a717971dbee9a5d3"
               "f8a295759c45b3738517f5950d5f26421f23768771d");
    b = Fatint("892d26e28b03c4515d10e33f67f45d54bded9703303fd041962e222e1220e"
               "246f2bebe56fbbccc9d7a252a58ddeef0c2db01a7faf80388f157987fb5b9"
               "b37ec476c5da0d755cc40ce2c387b7a4a558b0f198b894e2f2e3b7dd34ba7"
               "f1452aeb388b66e70a2feb2a1abe4c843e46ed0ee3aedd2be181d16e478ae"
               "087af28288d0");
    c = Fatint("449693714581e228ae88719fb3fa2eaa5ef6cb81981fe820cb17111709107"
               "123795f5f2b7dde664ebd12952c6ef778616d80d3fd7c01c478abcc3fdadc"
               "d9bf623b62ed06baae62067161c3dbd252ac5878cc5c4a717971dbee9a5d3"
               "f8a295759c45b3738517f5950d5f26421f23768771d");
    assert(  ((a % b) == c), "MOD  2");

    a =Fatint("8f404561fd0662fe095443780783ba2cea33d5");
    b =Fatint("1ffffff");
    c =Fatint("b682ab");
    assert(  ((a % b) == c), "MOD  3");
    assert(  ((a % ZERO) == ZERO), "MOD  4");  // ERROR, cannot mod 0.
    
    return error;
  }

  bool shift_tests() {
    Fatint a("2");
    // Fatint b("4");
    Fatint c("20");  // hex.
    assert(  ((a << 4) == c), "SHIFT  1");
    a = Fatint("1234567890abcdef");
    c = Fatint("2468acf121579bde0000000000000000000");
    assert(  ((a << 77) == c), "SHIFT  2");
    a = Fatint("892d26e28b03c4515d10e33f67f45d54bded9703303fd041962e222e1220e"
               "246f2bebe56fbbccc9d7a252a58ddeef0c2db01a7faf80388f157987fb5b9"
               "b37ec476c5da0d755cc40ce2c387b7a4a558b0f198b894e2f2e3b7dd34ba7"
               "f1452aeb388b66e70a2feb2a1abe4c843e46ed0ee3aedd2be181d16e478ae"
               "087af28288d0");
    c = Fatint("449693714581e228ae88719fb3fa2eaa5ef6cb81981fe820cb17111709107"
               "123795f5f2b7dde664ebd12952c6ef778616d80d3fd7c01c478abcc3fdadc"
               "d9bf623b62ed06baae62067161c3dbd252ac5878cc5c4a717971dbee9a5d3"
               "f8a295759c45b3738517f5950d5f26421f23768771d");
    assert(  ((a >> 121) == c), "SHIFT  3");
    assert(  ((a >> 6000) == ZERO), "SHIFT  4");
    return error;
  }

  bool bit_tests() {
    Fatint a("ffffffff0000000010000000");
    //                       876543210
    //                       digit is 4 bits.
    assert(!(a.get_bit(27)), "BIT 1");
    assert( (a.get_bit(28)), "BIT 2");
    assert(!(a.get_bit(29)), "BIT 3");
    a.set_bit(27);
    assert( (a.get_bit(27)), "BIT 4");
    assert( (a.get_bit(28)), "BIT 5");
    assert(!(a.get_bit(29)), "BIT 6");
    a.clear_bit(28);
    assert( (a.get_bit(27)), "BIT 7");
    assert(!(a.get_bit(28)), "BIT 8");
    assert(!(a.get_bit(29)), "BIT 9");
    return error;
  }

  bool stream_tests() {
    string s = "deadbeef1234567890";
    Fatint a(s);
    stringstream ss;
    ss << a;
    string sb = ss.str();
    assert( (s.compare(sb) == 0), "STREAM 1");
    Fatint b;
    ss >> b;
    assert( (a == b), "STREAM 2");
    return error;
  }

  bool long_long_tests() {
    long long int a = 9223372036854775807;
    Fatint fa(a);
    fa = -fa;
    a = -a;
    assert( (a == fa.get_value()), "LONG 1");

    return error;

  }

  bool anybase_tests() {
   Fatint a = Fatint("", 10);
   assert( (a == ZERO), "BASE 1");
   string b16 = "892d26e28b03c4515d10e33f67f45d54bded9703303fd041962e222e1220"
                "e246f2bebe56fbbccc9d7a252a58ddeef0c2db01a7faf80388f157987fb5"
                "b9b37ec476c5da0d755cc40ce2c387b7a4a558b0f198b894e2f2e3b7dd34"
                "ba7f1452aeb388b66e70a2feb2a1abe4c843e46ed0ee3aedd2be181d16e4"
                "78ae087af28288d0";
   string b10 = "963285261173254362271184454887346023369363895699519167340082"
                "226490223402462615650184503029260492003908377099894751427310"
                "322643302198588690069095107378187188328824724138482659042912"
                "276564676583893089610346773577752812012692759357160246264563"
                "445096932547863573416662901577818304719739797282159881442426"
                "75583184";
   string b8 = "1044551156121300742121272103431766376427252275733134031403772"
                "020313056104270221016110674537276255756746311657211225130673"
                "673606055540151775370007043612571417755334663375421666135501"
                "535256304031613034173364451254260743142704516136270733735151"
                "351770505125654704266334702427753124152762310207621566416707"
                "27335127606016426710742560207536240504320";
   Fatint f16(b16, 16);
   Fatint f10(b10, 10);
   Fatint f8(b8, 8);
   assert( (f16 == f10), "BASE 2");
   assert( (f16 == f8), "BASE 3");
   Fatint fq("Gobblydygook", 4);
   assert( (fq == ZERO), "BASE 4");

   string s8 = f8.to_string(10);
   assert( (s8.compare(b10) == 0), "Base 5");

   return error;
  }


  bool logic_tests() {
    Fatint a("f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
    Fatint b("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0");
    Fatint o("fffffffffffffffffffffffffffffffffff");
    Fatint z("00000000000000000000000000000000000");
    
    Fatint d("fffff0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0");

    assert( ((a | b) == o), "LOGIC 1");

    Fatint c = a & b;
    assert( ((a & b) == z), "LOGIC 2");

    c = a ^ b;
    assert( ((a ^ b) == o), "LOGIC 3");

    c = ~a;
    b = ~c;
    assert( (a == b), "LOGIC 5");
    return error;
  }
    

  int run() {
    equality_tests();
    multiply_tests();
    add_tests();
    subtract_tests();
    divide_tests();
    mod_tests();
    shift_tests();
    bit_tests();
    stream_tests();
    long_long_tests();
    anybase_tests();
    logic_tests();
    if (error) {
      cout << "Failures! " << serror << endl;
    } else {
      cout << "Success! " << serror << endl;
    }
    return error;
  }

  void assert(bool state, string msg) {
    if (!state) {
      cout << "Fail! " << msg << endl;
      error = true;
      serror += " " + msg;
    } else {
      cout << "OK: " << msg << endl;
    }
  }

  void log(const Fatint &a, const Fatint &b) {
    cout << "a:" << a << " b" << b << endl;
  }

 private:
  bool error = false;
  string serror;
};


int main(int argc, char **argv) {
  Test t;
  return t.run();
}
