#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include "operations.hpp"

/**
 *  Enum class containing possible functionalities of this program
 */
enum flags{
    newlines, digits, numbers, chars, words, words_length, sorted, reverse_sorted, sorted_length, reverse_sorted_length, anagrams, palindromes
};
/**
 * Structure used to return errors and store error message
 */
struct my_exception : std::exception{
private:
    std::string message;
public:
    my_exception(std::string input) : message(std::move(input)){}
    /**
     * Prints error message
     */
    void what() {
        std::cout << message;
    }
};
/**
 * Shows all flags and theirs functionality
 */
void show_help(){
    std::cout
            << "App: PJAText2\n"
            << "Version 1.0\n"
            << "Allows to get specified data regarding content of specified text file (ASCII only)\n"
            << "\"\"    or \"--help\" - shows list of possible flags\n"
            << "\"-f\"  or \"--file\" [path] - specifies program's input file\n"
            << "\"-n\"  or \"--newlines\" - returns number of newlines\n"
            << "\"-d\"  or \"--digits\" - returns number of digits\n"
            << "\"-dd\" or \"--numbers\" - returns number of numbers\n"
            << "\"-c\"  or \"--chars\" - returns number of chars\n"
            << "\"-w\"  or \"--words\" - returns number of groups of chars separated by white spaces\n"
            << "\"-wl\" or \"--words-length\" - returns average word length \n"
            << "\"-s\"  or \"--sorted\" - returns all \"words\" sorted alphabetically\n"
            << "\"-rs\" or \"--reverse-sorted\" - returns all \"words\" sorted alphabetically from z to a\n"
            << "\"-l\"  or \"--by-length\" - should be used after \"-s\" or \"-rs\" sorts \"words\" by length instead\n"
            << "\"-a\"  or \"--anagrams\" [list of arguments separated with whitespace] - should be the last flag, returns all anagrams from file specified in list\n"
            << "\"-o\"  or \"--output\" [path] - redirects program output to specified file and overrides content\n"
            << "\"-p\"  or \"--palindromes\" [list of arguments separated with whitespace] - should be the last flag, returns all palindromes from file specified in list\n"
            << "\"-i\"  or \"--input\" [path] - specifies program's input file and takes flags from first line of file instead\n";
}
/**
 *  Transforms a vector of strings into corresponding value from enum class flags and removes inappropriate used flags
 *
 *  @param args - vector of strings
 *  @return result - vector of enum class flags based on args
 */
std::vector<flags> transform(const std::vector<std::string>* args){
    auto result = std::vector<flags>();
    bool rm = false;
    bool last = false;
    std::string last_name;
    for (const auto& s : *args){
        if (s == "-n" or s == "--newlines")
            result.push_back(newlines);
        else if (s == "-d" or s == "--digits")
            result.push_back(digits);
        else if (s == "-dd" or s == "--numbers")
            result.push_back(numbers);
        else if (s == "-c" or s == "--chars")
            result.push_back(chars);
        else if (s == "-w" or s == "--words")
            result.push_back(words);
        else if (s == "-wl" or s == "--words-length")
            result.push_back(words_length);
        else if (s == "-s" or s == "--sorted")
            result.push_back(sorted);
        else if (s == "-rs" or s == "--reverse-sorted")
            result.push_back(reverse_sorted);
        else if (s == "-a" or s == "--anagrams") {
            result.push_back(anagrams);
            last = true;
            if (last_name.empty()) last_name = s;
        }
        else if (s == "-p" or s == "--palindromes"){
            result.push_back(palindromes);
            last = true;
            if (last_name.empty()) last_name = s;
        }
        else if (s == "-l" or s == "--by-length"){
            if (!result.empty()) {
                if (result.at(result.size() - 1) == sorted) {
                    result.pop_back();
                    result.push_back(sorted_length);
                } else if (result.at(result.size() - 1) == reverse_sorted) {
                    result.pop_back();
                    result.push_back(reverse_sorted_length);
                }
            }
        }
        else {
            if (!result.empty() and (result.at(result.size() - 1) == anagrams or result.at(result.size() - 1) == palindromes))
                rm = false;
            else if (s == "--help"){
                show_help();
                return std::vector<flags>();
            }
            else
                throw my_exception("Flag not found: " + s + '\n' + "Program execution halted\n");
        }
        if (last){
            if (rm)
                throw my_exception("Flag: " + last_name + " wasn't specified as last flag\n");
            else
                rm = true;
        }
    }
    return result;
}
/**
 * Core of the program. Runs all of correctly specified flags.
 *
 * @param std::vector<flags>& args - vector containing flags to run
 * @param std::string* path_in - path to source file
 * @param std::string* path_out - path to output file (if null send to std::cout)
 * @param bool was_it_i - parameter specifying if we need to omit first line (result of flag -i)
 * @param std::vector<std::string>* list - vector containing untranslated flags as strings
 */
auto run(const std::vector<flags>& args, const std::string* path_in, const std::string* path_out,const bool was_it_i, const std::vector<std::string>* list){
    auto arguments = std::vector<std::string>();
    if (args.at(args.size()-1) == anagrams or args.at(args.size()-1) == palindromes) {
        arguments.resize(list->size()-args.size());
        std::copy(list->begin()+args.size(), list->end(), arguments.begin());
    }
    for (const auto& element : args) {
        switch (element) {
            case newlines:
                newlinesF(path_in, path_out, was_it_i);
                break;
            case digits:
                digitsF(path_in, path_out, was_it_i);
                break;
            case numbers:
                numbersF(path_in, path_out, was_it_i);
                break;
            case chars:
                charsF(path_in, path_out, was_it_i);
                break;
            case words:
                wordsF(path_in, path_out, was_it_i);
                break;
            case words_length:
                words_lengthF(path_in, path_out, was_it_i);
                break;
            case sorted:
                sortedF(path_in, path_out, was_it_i);
                break;
            case reverse_sorted:
                reverse_sortedF(path_in, path_out, was_it_i);
                break;
            case sorted_length:
                sorted_lengthF(path_in, path_out, was_it_i);
                break;
            case reverse_sorted_length:
                reverse_sorted_lengthF(path_in, path_out, was_it_i);
                break;
            case anagrams:
                anagramsF(path_in, path_out, was_it_i, &arguments);
                break;
            case palindromes:
                palindromesF(path_in, path_out, was_it_i, &arguments);
                break;
            default:
                std::cout << "Flag not found enum: " << element;
        }
    }
}
/**
 * Finds index of specified flag and checks if there is correct path following it
 *
 * @param arguments - vector of strings with everything (before any transformation)
 * @param flags - table of strings representing specific flag
 * @return index of specified flag
 */
int where(const std::vector<std::string>* arguments, const std::array<std::string,2>& flags){
    auto where = std::distance(arguments->begin(),min(std::find(arguments->begin(),arguments->end(),flags[0]),std::find(arguments->begin(),arguments->end(),flags[1])));
    if (where < arguments->size()-1){
        std::fstream file;
        file.open(arguments->at(where+1));
        if (!file.fail())
            return where;
        }
    return arguments->size();
}
/**
 * Searches for output flag and file address or empty string if flag was not found. Throws exception if flag was present but there was no file address.
 *
 * @param arguments - vector of strings with everything (before any transformation)
 * @return path_out - address of file or empty string
 */
std::string add_path_out_if_exists(std::vector<std::string>* arguments){
    std::string path_out;
    auto where_o = std::distance(arguments->begin(),min(std::find(arguments->begin(),arguments->end(),"-o"),std::find(arguments->begin(),arguments->end(),"--output")));
    if (where_o < arguments->size() - 1) {
        path_out = arguments->at(where_o + 1);
        arguments->erase(arguments->begin() + where_o, arguments->begin() + where_o + 2);
    } else if (std::find(arguments->begin(), arguments->end(), "-o") < arguments->end() or std::find(arguments->begin(), arguments->end(), "--output") < arguments->end())
        throw my_exception("Output file was not found or couldn't be created.\nApplication terminated\n");
    std::fstream file;
    file.open(path_out,std::ios::out);
    return path_out;
}


int main(int args_count, const char* args[]) {
    std::string path_in;
    std::string path_out;
    auto arguments = std::vector<std::string>(args + 1, args + args_count);
    if (args_count == 1 or (args_count == 2 and arguments[0] == "--help"))
        show_help();
    else {
        // checking handling -i, -f, -o flags
        bool was_it_i = false;
        auto where_i = where(&arguments,{"-i","--input"});
        auto i_exception_help = std::distance(arguments.begin(),min(std::find(arguments.begin(),arguments.end(),"-i"),std::find(arguments.begin(),arguments.end(),"input")));
        if (args_count != 3 and i_exception_help < arguments.size()){
            try {
                throw my_exception("There were specified other flags with " + arguments.at(i_exception_help) + " \nApplication terminated\n");
            }
            catch (my_exception& e){
                e.what();
                return 1;
            }
        }
        if (where_i < arguments.size()) {
            path_in = arguments.at(where_i + 1);
            arguments.erase(arguments.begin() + where_i, arguments.begin() + where_i + 2);
            was_it_i = true;
        }
        if (arguments.size() > 1) {
            auto where_f = where(&arguments, {"-f", "--file"});
            if (where_f < arguments.size()) {
                path_in = arguments.at(where_f + 1);
                arguments.erase(arguments.begin() + where_f, arguments.begin() + where_f + 2);
            }
        }
        if (arguments.size() > 1) {
            try {
                path_out = add_path_out_if_exists(&arguments);
            }
            catch (my_exception& e) {
                e.what();
            }
        }
        // preparations before run()
        if (!path_in.empty()){
            if (!was_it_i) {
                try {
                    run(transform(&arguments), &path_in, &path_out, was_it_i, &arguments);
                }
                catch (my_exception& e) {
                    e.what();
                    return 1;
                }
            }
            else{
                std::ifstream in_file;
                std::string line;
                in_file.open(path_in);
                std::getline(in_file,line);
                std::istringstream tmp(line);
                std::vector<std::string> help ((std::istream_iterator<std::string>(tmp)),std::istream_iterator<std::string>());
                if (help.size() > 1) {
                    try {
                        path_out = add_path_out_if_exists(&help);
                    }
                    catch (my_exception& e) {
                        e.what();
                        return 1;
                    }
                }
                try {
                    // start cheat
                    if (help.size() > 1) {
                        auto where_f = where(&help, {"-f", "--file"});
                        if (where_f < help.size()) {
                            path_in = help.at(where_f + 1);
                            help.erase(help.begin() + where_f, help.begin() + where_f + 2);
                            was_it_i = false;
                        }
                    }
                    //end cheat
                    run(transform(&help), &path_in, &path_out, was_it_i, &help);
                }
                catch (my_exception& e) {
                    e.what();
                    return 1;
                }
            }
        }
        else {
            try {
                throw my_exception("Data file was not found. Application terminated\n");
            }
            catch (my_exception& e){
                e.what();
                return 1;
            }
        }
    }
    return 0;
}
