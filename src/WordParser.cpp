
#include "WordParser.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>  // absolute value
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>  // pair, make_pair
#include <vector>

namespace WordParser {

void WordParser::check_if_vowel_or_consonant(const char &letter)
/*
 * Check if character is a vowel or consonant.
 * Append to "this->vowel_count" or "this->consonant_count".
 *
 * NOTE: this DOES modify both of the above.
 */
{
    // ignore digits and spaces
    if (std::isdigit(letter) || std::isspace(letter)) {
        return;
    }
    for (const char &vowel : this->vowels) {
        if (letter == vowel) {
            ++this->vowel_count;
            return;
        }
    }
    ++this->consonant_count;
}

const std::string WordParser::remove_punctuation()
/*
 * Remove punctuation and turn "this->text" string lowercase.
 *
 * NOTE: this does NOT modify "this->text".
 */
{
    std::string r;
    for (char &letter : this->text) {
        letter = tolower(letter);  // turn lowercase
        // check if punctuation does not contain the iterator char
        if (this->PUNCTUATION.find(letter) == std::string::npos) {
            // if true, we are dealing with a letter (i.e., NOT PUNCTUATION)
            r += letter;
            this->check_if_vowel_or_consonant(letter);
        }
        else {
            // std::cout << "DEBUG: removing punctuation: '" << letter << "'.\n";
        }
    }
    return r;
}

const vec_words_t WordParser::split_into_words()
/*
 * Return "this->text" without punctuation as a vector of words.
 *
 * NOTE: this modifies "this->word_count" and will set it to the amount of separate (but repeating) words.
 * NOTE: this does NOT modify "this->text".
 */
{
    // get "this->text" without punctuation
    const std::string text_no_punct = this->remove_punctuation();
    vec_words_t vec_words;
    std::string buffer;
    std::stringstream ss(text_no_punct);  // insert text into stream
    while (ss >> buffer) {
        vec_words.push_back(buffer);
    }
    vec_words.shrink_to_fit();            // shrink capacity to size
    this->word_count = vec_words.size();  // set instance variable
    return vec_words;
}

const unord_map_freq_t WordParser::get_unsorted_frequency()
/*
 * Return "this->text" without punctuation as an unordered map of "word:frequency".
 *
 * NOTE: this does NOT modify "this->text".
 */
{
    const vec_words_t words_vec = this->split_into_words();
    unord_map_freq_t freq_map;
    for (const auto &word : words_vec) {
        freq_map[word] += 1;
    }
    return freq_map;
}

template <typename T, typename Y>
struct greater_second {
    typedef std::pair<T, Y> type;
    bool operator()(type const &a, type const &b) const
    {
        return a.second > b.second;
    }
};

const ord_pair_freq_t WordParser::get_sorted_frequency()
/*
 * Return "this->text" without punctuation as an ordered vector of "word:frequency" pairs.
 *
 * NOTE: this modifies "this->frequency" and will return it as cache.
 * NOTE: this does NOT modify "this->text".
 */
{
    // if not already cached, run now
    if (this->frequency.empty()) {
        const unord_map_freq_t freq_map = this->get_unsorted_frequency();
        // create vector from map
        ord_pair_freq_t vec_sorted_pairs(freq_map.begin(), freq_map.end());
        // sort vector by the value of each pair, from biggest to smallest
        std::sort(vec_sorted_pairs.begin(), vec_sorted_pairs.end(), greater_second<std::string, unsigned>());
        // shrink capacity to size, then overwrite instance variable
        vec_sorted_pairs.shrink_to_fit();
        this->frequency = vec_sorted_pairs;
    }
    return this->frequency;
}

float WordParser::get_uint_percentage(const unsigned &x, const unsigned &y) const
/*
 * Get the percentage of two unsigned integers as absolute float rounded to two digits.
 * E.g., 55 out of 120 (x = 55, y = 120).
 *
 * NOTE: this does NOT modify the "x" and "y".
 */
{
    // cast to floating point (can't get percentage with ints)
    const float first = static_cast<float>(x);
    const float second = static_cast<float>(y);
    const float r = (first / second) * 100;
    // round to 2 digits
    return std::fabs(std::round(r * 100.0) / 100.0);
}

WordParser::WordParser(const std::string &s)
{
    /* Class constructor. */
    this->text = s;
}

void WordParser::run(ord_pair_freq_t::size_type amount_to_print)
/*
 * Count the number of occurrences for each individual word and print them to console.
 * If "amount_to_print" exceeds the maximum amount of words, it will be clamped.
 */
{
    const ord_pair_freq_t vec_frequency = this->get_sorted_frequency();
    ord_pair_freq_t::size_type len = vec_frequency.size();
    if (len < amount_to_print) {  // we don't have enough words available
        std::cout << "WARNING: requested amount to print '" << amount_to_print
                  << "' exceeds the amount of individual words '" << len
                  << "' available, setting amount to '" << len << "'.\n";
        amount_to_print = len;
    }
    for (ord_pair_freq_t::size_type i = 0; i < amount_to_print; ++i) {
        const auto pair = vec_frequency.at(i);
        std::cout << i + 1 << ". " << pair.first << " (" << pair.second << ") \n";
    }

    std::cout << "\nNumber of unique words: " << len
              << ".\nTotal number of words: " << this->word_count
              << ".\nUnique-to-total word ratio: " << get_uint_percentage(len, this->word_count)
              << "%.\n\nNumber of vowels: " << this->vowel_count
              << ".\nTotal number of consonants: " << this->consonant_count
              << ".\nVowel-to-consonant ratio: " << get_uint_percentage(this->vowel_count, this->consonant_count)
              << "%.\n";
}

}  // namespace WordParser
