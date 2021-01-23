#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <iostream>
#include <vector>

class Data {
private:
    std::string actual_type;
    std::string type;
    float hamProb = 1; //P(C=HAM|x1,x2,x3,...) where x1, x2, x3 are attributes (words) that are in the test data
    float spamProb = 1; //P(C=SPAM|x1,x2,x3,...) where x1, x2, x3 are attributes (words) that are in the test data
    std::vector<std::string> words;
public:
    Data(std::string actual_type);
    std::string getWord(int index) {return words[index];};
    std::vector<std::string>& getWords() {return words;}
    void print();
    void addWord(std::string word) {words.push_back(word);}
    void updateProb(float probForHam, float probForSpam);//multiplies hamProb and spamProb by probIfHam, probIfSpam
    bool classify(); //returns true if test data was classified correctly
};

#endif // DATA_H_INCLUDED

