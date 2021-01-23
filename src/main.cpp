#include <iostream>
#include "Bayes.h"
//change so there are words in single spam or ham count
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
    vector<Bayes> models;
    for (int i = 0; i < k; ++i) {
        vector<string> testMessages;
        vector<string> learningMessages;
        int index = i * testDataQuantity; //starting index in messages where test data begins
        testMessages.insert(testMessages.end(), messages.begin() + index, messages.begin() + index + testDataQuantity); //adding test data
        learningMessages = messages;
        learningMessages.erase(learningMessages.begin() + index, learningMessages.begin() + index + testDataQuantity); //removing test data from a copy of messages
        Bayes bayes;
        cout << "Learning..." << endl;
        bayes.loadAttributes(learningMessages); //fill attributes (learning data)
        bayes.calcProbabilities(learningDataQuantity); //calculate P(C = SPAM) and P(C = HAM)
        bayes.calcWordsCounterInSpamAndHam(); //purely for analytics
        bayes.calcConditionalProbabilitiesForLearningData(); //calculate P(xi|C = SPAM) and P(xi|C = HAM) for all attributes in X (attributes)
        cout << "Testing..." << endl;
        for (unsigned int j = 0; j < testMessages.size(); ++j) {
            bayes.loadData(testMessages[j]);
        }
        bayes.calcConditionalProbabilitiesForTestData(); //calculate P(C=SPAM|x1,x2,x3,...) and P(C=HAM|x1,x2,x3,...)
        bayes.classify(); //assighn class and grade model
        models.push_back(bayes);
        //bayes.printAttributes();
        //bayes.printTestData();
        bayes.print();

//        cout << "Learning messages: " << endl;
//        for (unsigned int i = 0; i < learningMessages.size(); ++i) {
//            cout << learningMessages[i] << endl;
//        }
//
//        cout << "Test messages: " << endl;
//        for (unsigned int l = 0; l < testMessages.size(); ++l) {
//            cout << testMessages[l] << endl;
//        }
//        cout << "Index: " << index << endl;
//        cout << "Learning messages size: " << learningMessages.size() << endl;
//        cout << "Test messages size: " << testMessages.size() << endl;
//        cout << "Attributes quantity: " << bayes.getAttributes().size() << endl;
//        cout << "Test data quantity: " << bayes.getTestData().size() << endl;

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

    cout << endl << "Words counter: " << wordsCounter << endl;
    cout << "Data counter: " << dataCounter << endl;
    cout << "testDataQuantity: " << testDataQuantity << endl;
    cout << "learningDataQuantity: " << learningDataQuantity << endl << endl;
    cout << "Models success: " << endl;
    for (unsigned int i = 0; i < models.size(); ++i) {
        cout << models[i].getSuccess() * 100 << "%" << endl;
    }
    cout << endl << "End" << endl;
    return 0;
}
