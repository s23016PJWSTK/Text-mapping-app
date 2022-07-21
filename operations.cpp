#include <regex>
#include <set>
#include "operations.hpp"

void newlinesF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    int result = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    while (getline(in_file,line))
        result++;
    return print("Newlines: ", result, path_out);
}

void digitsF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    int result = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    while (getline(in_file,line))
        result += std::count_if(line.begin(),line.end(),[](char s){ return (s >= '0' and s <= '9');});
    return print("Digits: ", result, path_out);
}
void numbersF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    int result = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::regex reg (R"(\b-?[^,][0-9]+(,[0-9]+)?\b)");
    while (getline(in_file,line))
        result += std::distance(std::sregex_iterator(line.begin(),line.end(),reg), std::sregex_iterator());
    return print("Numbers: ", result, path_out);
}
void charsF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    int result = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    while (getline(in_file,line))
        result += std::count_if(line.begin(),line.end(),[](const char& c){return !isspace(c);});
    return print("Chars: ",result, path_out);
}
void wordsF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    int result = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::regex reg (R"(\b[^\s]+\b)");
    while (getline(in_file,line))
        result += std::distance(std::sregex_iterator(line.begin(),line.end(),reg), std::sregex_iterator());
    return print("Words: ", result, path_out);
}
void words_lengthF(const std::string* path_in, const std::string* path_out, const bool was_it_i) {
    long double divider = 0;
    unsigned long int characters = 0;
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i) getline(in_file, line);
    std::regex reg(R"(\b[^\s]+\b)");
    while (getline(in_file, line)){
        divider += std::distance(std::sregex_iterator(line.begin(), line.end(), reg), std::sregex_iterator());
        characters += std::count_if(line.begin(), line.end(), [](const char &c) { return !isspace(c); });
    }
    return print("Average word length: ", characters/divider, path_out);
}
void sortedF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    std::for_each(data.begin(),data.end(),[](auto& s){std::transform(s.begin(),s.end(),s.begin(),[](char& c){ return tolower(c);});});
    std::sort(data.begin(),data.end());
    return print("All words sorted:\n", &data, path_out);
}
void reverse_sortedF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    std::for_each(data.begin(),data.end(),[](auto& s){std::transform(s.begin(),s.end(),s.begin(),[](char& c){ return tolower(c);});});
    std::sort(data.begin(),data.end(), [](const auto& first, const auto& second){return first > second;});
    return print("All words reverse sorted:\n", &data, path_out);
}
void sorted_lengthF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    std::for_each(data.begin(),data.end(),[](auto& s){std::transform(s.begin(),s.end(),s.begin(),[](char& c){ return tolower(c);});});
    std::sort(data.begin(),data.end(), [](const auto& first, const auto& second){
        if (first.size() == second.size())
            return first < second;
        else
            return first.size() < second.size();
    });
    return print("All words sorted by length:\n", &data, path_out);
}
void reverse_sorted_lengthF(const std::string* path_in, const std::string* path_out, const bool was_it_i){
    std::string line;
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    std::for_each(data.begin(),data.end(),[](auto& s){std::transform(s.begin(),s.end(),s.begin(),[](char& c){ return tolower(c);});});
    std::sort(data.begin(),data.end(), [](const auto& first, const auto& second){
        if (first.size() == second.size())
            return first < second;
        else
            return first.size() > second.size();
    });
    return print("All words reverse sorted by length:\n", &data, path_out);
}
void anagramsF(const std::string* path_in, const std::string* path_out, const bool was_it_i, const std::vector<std::string>* arguments){
    std::string line;
    auto results = std::set<std::string>();
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    for (auto compare : *arguments){
        std::transform(compare.begin(),compare.end(),compare.begin(),[](char c){ return std::tolower(c);});
        std::sort(compare.begin(), compare.end());
        for (const auto& s : data) {
            if (s.size() == compare.size()) {
                std::string tmp = s;
                std::transform(tmp.begin(),tmp.end(),tmp.begin(),[](char c){return tolower(c);});
                std::sort(tmp.begin(),tmp.end());
                if (tmp == compare)
                    results.insert(s);
            }
        }
    }
    return print("Anagrams:\n", &results, path_out);
}
void palindromesF(const std::string* path_in, const std::string* path_out, const bool was_it_i,const std::vector<std::string>* arguments){
    std::string line;
    auto results = std::set<std::string>();
    std::ifstream in_file;
    in_file.open(*path_in);
    if (was_it_i)  getline(in_file,line);
    std::vector<std::string> data ((std::istream_iterator<std::string>(in_file)),std::istream_iterator<std::string>());
    std::for_each(data.begin(),data.end(),[](auto& s){std::transform(s.begin(),s.end(),s.begin(),[](char& c){ return tolower(c);});});
    for (auto compare : *arguments){
        std::transform(compare.begin(),compare.end(),compare.begin(),[](char& c){return tolower(c);});
        if (is_palindrome(&compare)){
        if (std::find(data.begin(),data.end(),compare) < data.end())
            results.insert(compare);
        }
    }
    return print("Palindromes:\n", &results, path_out);
}

bool is_palindrome(const std::string *word) {
    for (int i = 0; i < word->size()/2; i++){
        if (word->at(i) != word->at(word->size()-i-1))
            return false;
    }
    return true;
}

template <typename T>
void print(const std::string &header, T* data, const std::string* path_out){
    if (!path_out->empty()){
        std::ofstream out_file;
        out_file.open(*path_out,std::ios::app);
        out_file << header;
        std::copy(data->begin(), data->end(), std::ostream_iterator<std::string> (out_file, " "));
        out_file << '\n';
    }
    else {
        std::cout << header;
        std::copy(data->begin(), data->end(), std::ostream_iterator<std::string>(std::cout, " "));
        std::cout << '\n';
    }
}
template <typename T>
void print(const std::string &header, T data, const std::string* path_out){
    if (!path_out->empty()){
        std::ofstream out_file;
        out_file.open(*path_out,std::ios::app);
        out_file << header;
        out_file << data << '\n';
    }
    else {
        std::cout << header;
        std::cout << data << '\n';
    }
}
