#ifndef BAYES_H_INCLUDED
#define BAYES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
#include "Attribute.h"
#include<bits/stdc++.h>
using namespace std;

class Bayes
{
private:
    vector<Data> testData;
    vector<Attribute> attributes;
    int wordsCounterLearningData = 0; //how many words are in learning data, NOT USED IN ALGORITHM
    int hamCounter = 0; //how many msgs are spam in x learning data
    int spamCounter = 0; //how many msgs are ham in x learning data
    float hamProb = 0; //number of ham data / all learning data P(C=HAM)
    float spamProb = 0; //number of spam data / all learning data P(C=SPAM)
    int wordsCounterInHam = 0; //words with repeats in all ham data, NOT USED IN ALGORITHM
    int wordsCounterInSpam = 0; //words with repeats in all spam data, NOT USED IN ALGORITHM
    float success = 0; //% of successfull assignments
public:
    int getWordsCounterLearningData() {return wordsCounterLearningData;}
    int getSpamCounter() {return spamCounter;}
    int getHamCounter() {return hamCounter;}
    int getWordsCounterInSpam() {return wordsCounterInSpam;}
    int getWordsCounterInHam() {return wordsCounterInHam;}
    float getSuccess() {return success;}
    vector<Attribute>& getAttributes() {return attributes;}
    vector<Data>& getTestData() {return testData;}
    void incWordsCounterLearningData() {++wordsCounterLearningData;}

    static bool loadMessage(fstream& file, string& type, string& msg); //read one record of data from file
    static void loadIntoMemory(fstream& file, vector<string>& messages, int& wordsCounter, int& dataCounter); //saves all the data into memory without dividing to test and learning data
    void loadAttributes(vector<string>& learningMessages); //load all learning data transforming them into attributes
    void loadData(string testMessage); //load one data
    static bool isLink(string word);
    static bool isPhoneNumber(string word);

    void calcProbabilities(int learningDataCounter); //calculate spamProb and hamProb based on learning data size
    void calcConditionalProbabilitiesForLearningData(); //calculate probIfHam and probIfSpam for class Attribute
    void calcConditionalProbabilitiesForTestData(); //calculate spamProb and hamProb for class Data
    void classify(); //assigns type to Data class and grades model by calculating success
    void createIncorrectAssignments(vector<Data>& incorrectAssignments); //save incorrect assignments into Data vector

    void printAttributes();
    void printTestData();
    void print();

    void calcWordsCounterInSpamAndHam(); //currently not used in algorithm
};
#endif // BAYES_H_INCLUDED

