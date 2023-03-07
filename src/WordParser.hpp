#pragma once

// libraries
#include <string>
#include <unordered_map>
#include <vector>

// custom namespace
namespace WordParser {

// types
using vec_words_t = std::vector<std::string>;
using unord_map_freq_t = std::unordered_map<std::string, unsigned>;
using ord_pair_freq_t = std::vector<std::pair<std::string, unsigned>>;

// literals
// print top 10 most common words
#define AMOUNT_OF_WORDS_TO_PRINT 10

// prototypes
class WordParser {
  private:
    // types
    // NOTE: C++ 2011 is required for initialization in header
    inline static const std::string PUNCTUATION = R"('!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~')";
    inline static const std::string vowels = "aeiou";

    // variables
    std::string text;
    ord_pair_freq_t frequency;
    unsigned vowel_count = 0;
    unsigned consonant_count = 0;
    unsigned word_count;

    void check_if_vowel_or_consonant(const char &letter);
    const std::string remove_punctuation();
    const vec_words_t split_into_words();
    const unord_map_freq_t get_unsorted_frequency();
    const ord_pair_freq_t get_sorted_frequency();
    float get_uint_percentage(const unsigned &x, const unsigned &y) const;

  public:
    WordParser(const std::string &s);
    void run(ord_pair_freq_t::size_type amount_to_print = AMOUNT_OF_WORDS_TO_PRINT);
};

}  // namespace WordParser
