#include "paraglob.h"

#include <iostream>

namespace ac = aho_corasick;
using trie = ac::trie;

int main() {
	std::vector<std::string> init_vec = {"*og", "do*", "cat", "fish"};
	Paraglob my_glob(init_vec);

	for (std::string a : my_glob.get("dog")) {
		std::cout << a << "\n";
	}
}
