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
    void incHamCounter() {++hamCounter;}
    void incSpamCounter() {++spamCounter;}
    void calcHamProb();
    void calcSpamProb();
};
#endif // ATTRIBUTE_H_INCLUDED
