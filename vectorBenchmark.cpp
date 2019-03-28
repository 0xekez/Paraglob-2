
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

#include <cstdint>
#include <cstring>
#include "vector.h"

class Timer{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
  Timer() {
    start = std::chrono::high_resolution_clock::now();
  }
  void printTime() {
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  }
};

// @source: https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

DECLARE_VECTOR(strings, std::string, uint64_t)

int main() {
  /*
  adds 100,000 random strings that are n chars long to each set & reports the
  time.
  in this case I default the initialization to 8 items/ default, becase
  in general we will not know how many things we'd like to put into the
  vectors
  */
  size_t n = 8;
  int n_items = 100000;

  std::cout << "testing vector.h \n";
  std::cout << "add test..\n";
  Timer t;
  vec_strings* vs = vec_strings_create(8);
  for (int i = 0; i < n_items; i++) {
    std::string temp = random_string(16);
    vec_strings_append(vs, temp);
    if (i%20000 == 0) {
      std::cout << "--------\ntime for " << i << " items:\n";
      t.printTime();
    }
  }
  std::cout << "********\nTOTAL TIME: ";
  t.printTime();

  std::cout << "testing std::vector\n";
  std::cout << "add test..\n";
  Timer t2;
  std::vector<std::string> v;
  for (int i = 0; i < n_items; i++) {
    std::string temp = random_string(16);
    v.push_back(temp);
    if (i%20000 == 0) {
      std::cout << "--------\ntime for " << i << " items:\n";
      t2.printTime();
    }
  }
  std::cout << "********\nTOTAL TIME: ";
  t2.printTime();
}
