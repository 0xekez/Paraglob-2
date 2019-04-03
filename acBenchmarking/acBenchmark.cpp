#include <string>
#include <fstream>
#include <iostream>

#include "sfutil/bnfa_search.h"


int main() {
  bnfa_struct_t * bnfa;
  bnfa = bnfaNew();
  std::fstream in("20190328-0910.dbl");
  std::string is;
  while (std::getline(in, is)) {
    std::cout << is << "\n";
  }
  in.close();
}
