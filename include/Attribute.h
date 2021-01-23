#ifndef ATTRIBUTE_H_INCLUDED
#define ATTRIBUTE_H_INCLUDED
#include <iostream>

class Attribute {
private:
    std::string word;
    int hamCounter = 0; //how many times in ham msgs with repeats in the same msg, NOT USED IN ALGORITHM
    int spamCounter = 0; //how many times in spam msgs with repeats in the same msg, NOT USED IN ALGORITHM
    int occurrenceInHam = 0; //how many times in ham msgs without repeats in the same msg
    int occurrenceInSpam = 0; //how many times in spam msgs without repeats in the same msg
    float probIfHam = 0; //probability of word provided it's in ham P(x|C=HAM)
    float probIfSpam = 0; //probability of word provided it's in spam P(x|C=SPAM)
public:
    std::string getWord() {return word;}
    void setWord(std::string word) {this->word = word;}
    int getHamCounter() {return hamCounter;}
    int getSpamCounter() {return spamCounter;}
    float getProbIfHam() {return probIfHam;}
    float getProbIfSpam() {return probIfSpam;}
    void print();
    void incCounter(std::string type);
    void incOccurrence(std::string type);
    void calcHamAndSpamProb(int hamMsgsNumber, int spamMsgsNumber); //calculate conditional probabilities P(x|C=HAM) and P(x|C=SPAM) where x is the attribute
};
#endif // ATTRIBUTE_H_INCLUDED
