#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#ifndef PJATEXT2_OPERATIONS_HPP
#define PJATEXT2_OPERATIONS_HPP
/**
 * Counts number of new lines and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void newlinesF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Counts number of digits and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void digitsF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Counts number of numbers and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void numbersF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Counts number of chars and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void charsF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Counts number of groups of chars separated by whitespaces ("words") and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void wordsF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Calculates average length of word and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(result, path_out)
 */
void words_lengthF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Sorts all "words" alphabetically and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(results, path_out)
 */
void sortedF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Sorts all "words" alphabetically from z to a and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(results, path_out)
 */
void reverse_sortedF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Sorts all "words" from shortest to longest then alphabetically and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(results, path_out)
 */
void sorted_lengthF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Sorts all "words" from longest to shortest then alphabetically and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @return print(results, path_out)
 */
void reverse_sorted_lengthF(const std::string* path_in, const std::string* path_out, bool was_it_i);
/**
 * Searches for all "words" that are anagrams of words specified in arguments and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out - path to output file (can be empty)
 * @param was_it_i - if flags were loaded from file equals true
 * @param arguments - vector of arguments (words) to check
 * @return print(results, path_out)
 */
void anagramsF(const std::string* path_in, const std::string* path_out, bool was_it_i, const std::vector<std::string>* arguments);
/**
 * Searches for all "words" that are palindromes of words specified in arguments and sends result to print function
 *
 * @param path_in  - path to input file
 * @param path_out -
 * @param was_it_i - if flags were loaded from file equals true
 * @param arguments - vector of arguments (words) to check
 * @return print(results, path_out)
 */
void palindromesF(const std::string* path_in, const std::string* path_out, bool was_it_i, const std::vector<std::string>* arguments);
/**
 * Checks if word is a palindrome
 *
 * @param word - string containing one word
 * @return true if word is palindrome
 */
bool is_palindrome(const std::string *word);
/**
 *
 * @tparam T - standard container
 * @param data - results of specific functions returning containers
 * @param path_out - path to output file if empty results are shown in cmd
 */
template <typename T>
void print(const std::string &header, T* data, const std::string* path_out);
/**
 *
 * @tparam T - standard numeric variable
 * @param data - result of specific function returning numeric variable
 * @param path_out - path to output file if empty results are shown in cmd
 */
template <typename T>
void print(const std::string &header, T data, const std::string* path_out);
#endif //PJATEXT2_OPERATIONS_HPP
