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
        learningMessages.erase(learningMessages.begin() + index, learningMessages.begin() + index + testDataQuantity); //filling learning data by removing test data from a copy of messages
        Bayes bayes;
        cout << "Learning..." << endl;
        bayes.loadAttributes(learningMessages); //fill attributes (learning data)
        bayes.calcProbabilities(learningDataQuantity); //calculate P(C = SPAM) and P(C = HAM)
        bayes.calcWordsCounterInSpamAndHam(); //purely for analytics
        bayes.calcConditionalProbabilitiesForLearningData(); //calculate P(xi|C = SPAM) and P(xi|C = HAM) for all attributes in X (attributes)
        cout << "Testing..." << endl;
        //load into testData vector all the test data
        for (unsigned int j = 0; j < testMessages.size(); ++j) {
            bayes.loadData(testMessages[j]);
        }
        bayes.calcConditionalProbabilitiesForTestData(); //calculate P(C=SPAM|x1,x2,x3,...) and P(C=HAM|x1,x2,x3,...)
        bayes.classify(); //assign class and grade model
        vector<Data> incorrectAssignments;
        bayes.createIncorrectAssignments(incorrectAssignments); //save incorrect assignments into Data vector

        models.push_back(bayes);
        //bayes.printAttributes();
        //bayes.printTestData();
        cout << "Incorrectly assigned test data: " << endl;
        for (unsigned int j = 0; j < incorrectAssignments.size(); ++j) {
            incorrectAssignments[j].print();
        }
        cout << "Incorrectly assigned test data size: " << incorrectAssignments.size() << endl << endl;
        cout << "Model stats: " << endl;
        bayes.print();

//        /******************************************************
//        * vv comment this section if dont want any interaction
//        ******************************************************/
//        string command;
//        cout << "Next?" << endl << "y/n/q" << endl;
//        cin >> command;
//        while (command != "y" && command != "q") {
//            command.clear();
//            cout << "Next?" << endl << "y/n/q" << endl;
//            cin >> command;
//        }
//        if (command == "q") {
//            break;
//        }
//        /******************************************************
//        * ^^ comment this section if dont want any interaction
//        ******************************************************/
    }

    cout << endl;
    float average = 0;
    for (unsigned int i = 0; i < models.size(); ++i) {
        average += models[i].getSuccess();
        cout << models[i].getSuccess() * 100 << "%" << endl;
    }
    average = average * 100 / k;
    cout << "Average success: " << average << "%" << endl;
    cout << endl << "End" << endl;
    return 0;
}
