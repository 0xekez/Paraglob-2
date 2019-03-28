
#include <iostream>
#include <set>
#include <chrono>
#include <string>
#include <algorithm> //generate_n

#include <cstdint>
#include "set.h"

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

int compare_strings(std::string a, std::string b) {
  return a.compare(b);
}

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

DECLARE_SET(strings, std::string, uint64_t, compare_strings);

int main() {
  /*
  adds 100,000 random strings that are n chars long to each set & reports the
  time.
  */
  size_t n = 8;
  int n_items = 100000;

  std::cout << "testing set.h \n";
  std::cout << "add test..\n";
  Timer t;
  set_strings* hhhh = set_strings_create(8);
  for (int i = 0; i < n_items; i++) {
    std::string temp = random_string(16);
    set_strings_insert(hhhh, temp);
    if (i%20000 == 0) {
      std::cout << "--------\ntime for " << i << " items:\n";
      t.printTime();
    }
  }
  std::cout << "********\nTOTAL TIME: ";
  t.printTime();

  std::cout << "testing set\n";
  std::cout << "add test..\n";
  Timer t2;
  std::set<std::string> s;
  for (int i = 0; i < n_items; i++) {
    std::string temp = random_string(16);
    s.insert(temp);
    if (i%20000 == 0) {
      std::cout << "--------\ntime for " << i << " items:\n";
      t2.printTime();
    }
  }
  std::cout << "********\nTOTAL TIME: ";
  t2.printTime();
}
