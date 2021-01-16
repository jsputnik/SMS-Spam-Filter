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
    int wordsCounterLearningData = 0;
    int wordsCounter;
    int dataCounter;
public:
    Bayes(int wordsCounter, int dataCounter);
    void incWordsCounterLearningData() {++wordsCounterLearningData;}
    void incDataCounter() {++dataCounter;}
    void printAttributes();
    void printTestData();
    void printCounters();
    int getWordsCounterLearningData() {return wordsCounterLearningData;}
    int getWordsCounter() {return wordsCounter;}
    int getDataCounter() {return dataCounter;}
    vector<Attribute>& getAttributes() {return attributes;}
    vector<Data>& getTestData() {return testData;}
    static bool loadMessage(fstream& file, string& type, string& msg); //read one set of data
    static void loadIntoMemory(fstream& file, vector<string>& messages, int& wordsCounter, int& dataCounter);
    void loadAttributes(vector<string>& learningMessages);
    void loadData(string testMessage);
};
#endif // BAYES_H_INCLUDED

