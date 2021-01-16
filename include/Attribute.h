#ifndef ATTRIBUTE_H_INCLUDED
#define ATTRIBUTE_H_INCLUDED
#include <iostream>

class Attribute {
private:
    std::string word;
    long hamCounter;
    long spamCounter;
    float hamProb;
    float spamProb;
public:
    Attribute();
    void print();
    void incCounter(std::string type);
    void calcHamProb();
    void calcSpamProb();
    std::string getWord() {return word;}
    void setWord(std::string word) {this->word = word;}
    float getHamCounter() {return hamCounter;}
    float getSpamCounter() {return spamCounter;}
};
#endif // ATTRIBUTE_H_INCLUDED
