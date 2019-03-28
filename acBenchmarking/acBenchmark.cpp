#include <string>
#include <fstream>
#include <iostream>

int main() {
  std::fstream in("20190328-0910.dbl");
  std::string is;
  while (std::getline(in, is)) {
    std::cout << is << "\n";
  }
  in.close();
}
