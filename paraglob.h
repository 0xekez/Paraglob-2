#ifndef PARAGLOB_H
#define PARAGLOB_H

// #include "aho_corasick.hpp"
#include "AhoCorasickPlus.h"

#include <vector>


#include <string>
#include <unordered_map>
#include <set>
#include <cstddef>      // std::size_t
#include <fnmatch.h>


class Paraglob {
private:
  AhoCorasickPlus my_ac;
  std::unordered_map<std::string, std::string> meta_to_pattern_words;
  std::vector<std::string> meta_words;
  /*
  Get a vector of the meta-words in the pattern.
  Meta-words are strings that must be inside a string in order for
  it to match a pattern.
  ex:
  pattern       meta words
  *dog      ->  [dog]
  fish*dog  ->  [fish, dog]
  cat       ->  [cat]
  */
  std::vector<std::string> get_meta_words(std::string pattern);
  std::vector<std::string> split_on_brackets(std::string in);
public:
  Paraglob() = default;
  // Initialize a paraglob from a vector of patterns
  Paraglob(std::vector<std::string> &patterns);
  // Add a pattern to the paraglob
  void add(std::string pattern);
  // Compile the paraglob
  void compile();
  // Get a vector of the patterns that match the input string
  std::vector<std::string> get(std::string text);
};

#endif
