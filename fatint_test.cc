// fatint_test: test fatint functions.
//
// (C) Sean Brennan 2017
//
// Mit License.


#include <string>
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
    return error;

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


  int run() {
    equality_tests();
    multiply_tests();
    add_tests();
    subtract_tests();
    divide_tests();
    mod_tests();
    shift_tests();
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
