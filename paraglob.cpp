#include "paraglob.h"

Paraglob::Paraglob(std::vector<std::string> &patterns): Paraglob() {
  for (std::string pattern : patterns) {
    this->add(pattern);
  }
}

void Paraglob::add(std::string pattern) {
  // Get the meta words
  std::vector<std::string> meta_words = this->get_meta_words(pattern);
  // Associate them with their patterns & add them to our AC
  for (std::string word : meta_words) {
    this->meta_to_pattern_words[word] = pattern;
    this->my_ac.insert(word);
  }
}

std::vector<std::string> Paraglob::get(std::string text) {
  // Narrow down to only the words which contain meta words
  std::vector<std::string> meta_matches;
  for (auto result : this->my_ac.parse_text(text)) {
    meta_matches.push_back(result.get_keyword());
  }

  // Check against their respective patterns
  std::set<std::string> patterns;
  for (std::string meta_word : meta_matches) {
    patterns.insert(this->meta_to_pattern_words.at(meta_word));
  }
  std::vector<std::string> successes;
  for (std::string pattern : patterns) {
    if (fnmatch(pattern.c_str(), text.c_str(), 0) == 0) {
      successes.push_back(pattern);
    }
  }

  return successes;
}

std::vector<std::string> Paraglob::get_meta_words(std::string pattern) {
  std::vector<std::string> meta_words;
  // Split the pattern
  // @source: https://stackoverflow.com/a/7621814
  std::size_t prev = 0, pos;
  while ((pos = pattern.find_first_of(this->supported_patterns, prev)) !=
  std::string::npos) {
    if (pos > prev) {
      meta_words.push_back(pattern.substr(prev, pos-prev));
    }
    prev = pos+1;
  }
  if (prev < pattern.length()) {
    meta_words.push_back(pattern.substr(prev, std::string::npos));
  }
  return meta_words;
}
