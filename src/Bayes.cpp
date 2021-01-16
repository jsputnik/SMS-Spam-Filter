#include "Bayes.h"
#include "Attribute.h"
#include "Data.h"

Bayes::Bayes(int wordsCounter, int dataCounter) {
    this->wordsCounter = wordsCounter;
    this->dataCounter = dataCounter;
}

void Bayes::loadIntoMemory(fstream& file, vector<string>& messages, int& wordsCounter, int& dataCounter) {
    string firstLine, type, msg, word;
    getline(file, firstLine, '\n'); //cleaning 1st line v1,v2
    while(loadMessage(file, type, msg)) {
        for (unsigned int i = 0; i < msg.size(); ++i) {
            if (isalpha(msg[i]) || isdigit(msg[i])) {
                word += msg[i];
            }
            else {
                if (!word.empty()) {
                    word.clear();
                    ++wordsCounter;
                }
            }
        }
        messages.push_back(type + "," + msg);
        ++dataCounter;
        type.clear();
        msg.clear();
    }
}

void Bayes::printCounters() {
     cout << "WordsCounterLearningData: " << wordsCounterLearningData << endl;
     cout << "WordsCounter: " << wordsCounter << endl;
     cout << "DataCounter: " << dataCounter << endl;
}

void Bayes::printAttributes() {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        cout << attributes[i].getWord() << ", ham: " << attributes[i].getHamCounter() << ", spam: " << attributes[i].getSpamCounter() << endl;
    }
}

void Bayes::printTestData() {
    for (unsigned int i = 0; i < testData.size(); ++i) {
        testData[i].print();
    }
}

//load type of msg into type, text of the msg into msg from file
bool Bayes::loadMessage(fstream& file, string& type, string& msg) {
    getline(file, type, ','); //because of structure
    if(type.empty()) {
        return false;
    }
    //load one message (until \n)
    getline(file, msg, '\n');
    if(msg.empty()) {
        return false;
    }
    return true;
}

//load one test data from string
void Bayes::loadData(string testMessage) {
    string msg = testMessage;
    int typeIndex = msg.find(",");
    string type = msg.substr(0, typeIndex);
    msg = msg.substr(typeIndex + 1);
    Data data(type);
    string word;
    //divide into strings
    for (unsigned int i = 0; i < msg.size(); ++i) {
        if (isalpha(msg[i]) || isdigit(msg[i])) {
            word += msg[i];
        }
        else {
            if (!word.empty()) {
                data.addWord(word);
                word.clear();
                //++wordsCounterLearningData;
            }
        }
    }
    //cout << "original msg: " << msg << endl;
    //data.print();
    //cout << endl;
    testData.push_back(data);
}

//load all learning data into attributes from strings
void Bayes::loadAttributes(vector<string>& learningMessages) {
    for (unsigned int k = 0; k < learningMessages.size(); ++k) {
        string msg = learningMessages[k];
        int typeIndex = msg.find(",");
        string type = msg.substr(0, typeIndex);
        msg = msg.substr(typeIndex + 1);
        string word;
        //divide into strings
        for (unsigned int i = 0; i < msg.size(); ++i) {
            if (isalpha(msg[i]) || isdigit(msg[i])) {
                word += msg[i];
            }
            else {
                if (!word.empty()) {
                    //find if appeared in attributes
                    bool found = false;
                    for (unsigned int i = 0; i < attributes.size(); ++i) {
                        if(word == attributes[i].getWord()) {
                            attributes[i].incCounter(type);
                            found = true;
                            break;
                        }
                    }
                    //if not in attributes yet
                    if (!found) {
                        Attribute newAttr;
                        newAttr.setWord(word);
                        newAttr.incCounter(type);
                        attributes.push_back(newAttr);
                    }
                    word.clear();
                    ++wordsCounterLearningData;
                }
            }
        }
    }
}
