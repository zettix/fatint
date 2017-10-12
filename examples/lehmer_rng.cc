// Example Lehmer random number generator using Fatint objects.

#include <string>
#include <iostream>
#include "fatint.h"


namespace com_zettix {

class Lehmer {
 public:
   Lehmer(const Fatint &seed) : seed_(seed) {
     n_ = Fatint("1ffffffff");  // 2 << 31 - 1 Merseene prime.
     g_ = Fatint("41a7"); // 7 ** 5  16,807. primitive root.
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
  com_zettix::Fatint seed("12345678901ac1");
  com_zettix::Lehmer l(seed);

  std::cout << "Lehmer random number generator." << std::endl <<
      "based on https://en.wikipedia.org/wiki/Lehmer_random_number_generator"
       << std::endl;
  for (int i = 0; i < 100; i++) {
     std::cout << i << " " << l.next() << std::endl;
  }
}
