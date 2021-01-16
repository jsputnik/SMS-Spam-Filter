#include <iostream>
#include "Bayes.h"

using namespace std;

int main()
{
    int k = 7; //5572 / 7 = 796
    vector<string> messages; //each string is a whole message including ham/spam identifier
    fstream file;
    //counting data and words
    file.open("spam.csv", ios::in);
    int wordsCounter = 0;
    int dataCounter = 0;
    Bayes::loadIntoMemory(file, messages, wordsCounter, dataCounter);
    file.close();
    int testDataQuantity = dataCounter / k;
    int learningDataQuantity = dataCounter - testDataQuantity;
    for (int i = 0; i < k; ++i) {
        vector<string> testMessages;
        vector<string> learningMessages;
        int index = i * testDataQuantity; //starting index in messages where test data begins
        testMessages.insert(testMessages.end(), messages.begin() + index, messages.begin() + index + testDataQuantity); //adding test data
        learningMessages = messages;
        learningMessages.erase(learningMessages.begin() + index, learningMessages.begin() + index + testDataQuantity); //removing test data from a copy of messages
        Bayes x(wordsCounter, dataCounter);
        cout << "Learning..." << endl;
        x.loadAttributes(learningMessages);
        cout << "Testing..." << endl;
        for (unsigned int j = 0; j < testMessages.size(); ++j) {
            x.loadData(testMessages[j]);
        }
        //x.printAttributes();
        x.printTestData();
/*
        cout << "Learning messages: " << endl;
        for (unsigned int i = 0; i < learningMessages.size(); ++i) {
            cout << learningMessages[i] << endl;
        }*/
        /*
        cout << "Test messages: " << endl;
        for (unsigned int l = 0; l < testMessages.size(); ++l) {
            cout << testMessages[l] << endl;
        }*/
        cout << "Index: " << index << endl;
        cout << "Learning messages size: " << learningMessages.size() << endl;
        cout << "Test messages size: " << testMessages.size() << endl;
        cout << "Attributes quantity: " << x.getAttributes().size() << endl;
        cout << "Test data quantity: " << x.getTestData().size() << endl;
        x.printCounters();

        /******************************************************
        * vv comment this section if dont want any interaction
        ******************************************************/
        string command;
        cout << "Next model?" << endl << "y/n/q" << endl;
        cin >> command;
        while (command != "y" && command != "q") {
            command.clear();
            cout << "Next model?" << endl << "y/n/q" << endl;
            cin >> command;
        }
        if (command == "q") {
            break;
        }
        /******************************************************
        * ^^ comment this section if dont want any interaction
        ******************************************************/
    }

    for (unsigned int i = 0; i < messages.size(); ++i) {
        cout << messages[i] << endl;
    }

    cout << "Words counter: " << wordsCounter << endl;
    cout << "Data counter: " << dataCounter << endl;
    cout << "testDataQuantity: " << testDataQuantity << endl;
    cout << "learningDataQuantity: " << learningDataQuantity << endl;
    cout << endl << "End" << endl;
    return 0;
}
