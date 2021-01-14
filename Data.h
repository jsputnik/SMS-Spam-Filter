#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <iostream>
#include <vector>

class Data {
private:
    std::string type;
    float hamProb;
    float spamProb;
    std::vector<std::string> words;
public:
    Data();
    void print();
    void setType();
};

#endif // DATA_H_INCLUDED
