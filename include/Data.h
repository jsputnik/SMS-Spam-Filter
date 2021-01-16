#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <iostream>
#include <vector>

class Data {
private:
    std::string actual_type;
    std::string type;
    float hamProb;
    float spamProb;
    std::vector<std::string> words;
public:
    Data(std::string actual_type);
    void print();
    void setType();
    void addWord(std::string word) {words.push_back(word);}
};

#endif // DATA_H_INCLUDED

