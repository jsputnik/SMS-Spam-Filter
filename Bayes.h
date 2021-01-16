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
    int wordsCounter = 0;
    int dataCounter = 0;
public:
    bool loadMessage(fstream& file, string& type, string& msg); //read one set of data
    bool loadData(fstream& file);
    bool loadAttributes(fstream& file);
    void incWordsCounter() {++wordsCounter;}
    void incDataCounter() {++dataCounter;}
    void printAttributes();
    void printA(vector <Attribute> x);
    void count(fstream& file);
    int getWordsCounter() {return wordsCounter;}
    int getDataCounter() {return dataCounter;}
};
#endif // BAYES_H_INCLUDED

