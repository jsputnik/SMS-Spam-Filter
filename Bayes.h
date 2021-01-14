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
    vector <string> spamWords;
    vector <string> hamWords;
    vector <int> spamCounter;
    vector <int> hamCounter;

    vector<Data> testData; //
    vector<Attribute> attributes;
    int wordsCounter;
public:
    void loadData(Data data); //read one set of data
    void readData();
    void print();
    void printA(vector <Attribute> x);
};
#endif // BAYES_H_INCLUDED
