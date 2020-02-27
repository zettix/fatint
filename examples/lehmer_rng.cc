// Example Lehmer random number generator using Fatint objects.

#include <string>
#include <iostream>
#include "fatint.h"


namespace com_zettix {

class Lehmer {
 public:
   Lehmer(const Fatint &seed, int type=1) : seed_(seed) {
  
   Fatint f_("5"); 
   switch (type) {
     case 1:
       n_ = Fatint("1ffffffff");  // 2 << 31 - 1 Merseene prime.
       g_ = Fatint("41a7"); // 7 ** 5  16,807. primitive root.
       break;
     case 2:
       n_ = ONE << 128; 
       g_ = Fatint("12e15e35b500f16e2e714eb2b37916a5");
       break;
     case 3:
       n_ = Fatint("f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f1");  // Aime' Ferrier.
       g_ = Fatint("5"); 
       for (int i = 0; i < 62; i++) {
         g_ *= f_;
         int p = i * 100 / 62;
         std::cout << "Generating g term: " << p << "%" << std::endl;
       }
       break;
     default:
       n_ = ONE;
       g_ = ONE;
       std::cout << "Please pick a Lehmer type." << endl;
       break;
     }
   }
   Fatint next() {
     Fatint result = (g_ * seed_);
     result %= n_;
     seed_ = result;
     return result;
   };

 private:
  Fatint g_, n_, seed_;
};

} // namespace


int main(int argc, char **argv) {
  int type = 3;

  com_zettix::Fatint seed("12345678901ac1");
  com_zettix::Lehmer l(seed, type);

  std::cout << "Lehmer random number generator type " << type << 
      "." << std::endl <<
      "based on https://en.wikipedia.org/wiki/Lehmer_random_number_generator"
       << std::endl;
  for (int i = 0; i < 100; i++) {
     if (i < 10) std::cout << " ";
     std::cout << i << " " << l.next() << std::endl;
  }
}
