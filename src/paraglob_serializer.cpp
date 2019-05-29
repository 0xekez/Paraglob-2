// See the file "COPYING" in the main distribution directory for copyright.

#include "paraglob_serializer.h"

std::unique_ptr<std::vector<uint8_t>>
  paraglob::ParaglobSerializer::serialize(const std::vector<std::string>& v) {
    std::unique_ptr<std::vector<uint8_t>> ret (new std::vector<uint8_t>);
    add_int(v.size(), *ret);

    for (const std::string &s: v) {
      add_int(s.length(), *ret);
      for (const uint8_t &c : s) {
        ret->push_back(c);
      }
    }

    return ret;
  }

// ret -> [<n_strings><len_1><str_1>, <len_2><str_2>, ... <len_n><str_n>]
std::vector<std::string> paraglob::ParaglobSerializer::unserialize
  (const std::unique_ptr<std::vector<uint8_t>>& vsp) {
    std::vector<std::string> ret;
    // Serialized empty vector.
    if (vsp->size() == 0) {
      return ret;
    }

    std::vector<uint8_t>::iterator vsp_it = vsp->begin();
    uint64_t n_strings = get_int_and_move(vsp_it);
    // Reserve space ahead of time rather than resizing in loop.
    ret.reserve(n_strings);

    while (vsp_it < vsp->end()) {
      uint64_t l = get_int_and_move(vsp_it);
      ret.emplace_back(vsp_it, vsp_it + l);
      std::advance(vsp_it, l);
    }

    return ret;
  }

void paraglob::ParaglobSerializer::add_int
  (uint64_t a, std::vector<uint8_t> &target) {
    uint8_t* chars = reinterpret_cast<uint8_t*>(&a);
    target.insert(target.end(), chars, chars + sizeof(uint64_t));
}

uint64_t paraglob::ParaglobSerializer::get_int_and_move
  (std::vector<uint8_t>::iterator &start) {
    uint64_t ret = static_cast<uint64_t>(*start);
    std::advance(start, sizeof(uint64_t));
    return ret;
}
