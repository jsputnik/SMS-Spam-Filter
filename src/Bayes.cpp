#include "Bayes.h"
#include "Attribute.h"
#include "Data.h"

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

void Bayes::loadIntoMemory(fstream& file, vector<string>& messages, int& wordsCounter, int& dataCounter) {
    string firstLine, type, msg, word;
    getline(file, firstLine, '\n'); //cleaning 1st line v1,v2
    while (loadMessage(file, type, msg)) {
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

//load all learning data into attributes from strings
void Bayes::loadAttributes(vector<string>& learningMessages) {
    for (unsigned int k = 0; k < learningMessages.size(); ++k) {
        string text = learningMessages[k];
        int typeIndex = text.find(",");
        string type = text.substr(0, typeIndex);
        if (type == "ham") {
            ++hamCounter;
        }
        else if (type == "spam") {
            ++spamCounter;
        }
        else {
            cerr << "Unknown 'type' - neither HAM or SPAM" << endl;
            return;
        }
        text = text.substr(typeIndex + 1);
        string word;
        vector<string> wordsWithoutRepeats; //to check if same word repeated in one message
        //divide into strings
        for (unsigned int i = 0; i < text.size(); ++i) {
            if (isalpha(text[i]) || isdigit(text[i])) {
                word += text[i];
            }
            else {
                if (!word.empty()) {
                    //find if appeared in attributes
                    for (unsigned int i = 0; i < word.size(); ++i) {
                        word[i] = tolower(word[i]);
                    }
                    /***************************************
                    *check if link, tolower, check if number
                    ****************************************/
                    bool found = false;
                    for (unsigned int i = 0; i < attributes.size(); ++i) {
                        if (word == attributes[i].getWord()) {
                            bool repeated = false;
                            for (unsigned int j = 0; j < wordsWithoutRepeats.size(); ++j) {
                                if (wordsWithoutRepeats[j] == word) {
                                    repeated = true;
                                    break;
                                }
                            }
                            if (!repeated) {
                                wordsWithoutRepeats.push_back(word);
                                attributes[i].incOccurrence(type);
                            }
                            attributes[i].incCounter(type);
                            found = true;
                            break;
                        }
                    }
                    //if not in attributes yet
                    if (!found) {
                        wordsWithoutRepeats.push_back(word);
                        Attribute newAttr;
                        newAttr.setWord(word);
                        newAttr.incOccurrence(type);
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
                for (unsigned int i = 0; i < word.size(); ++i) {
                    word[i] = tolower(word[i]);
                }
                /***************************************
                *check if link, tolower, check if number
                ****************************************/
                data.addWord(word);
                word.clear();
            }
        }
    }
    //cout << "original msg: " << msg << endl;
    //data.print();
    //cout << endl;
    testData.push_back(data);
}

void Bayes::calcProbabilities(int learningDataQuantity) {
    spamProb = (float)spamCounter / (float)learningDataQuantity;
    hamProb = (float)hamCounter / (float)learningDataQuantity;
}

void Bayes::calcConditionalProbabilitiesForLearningData() {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        attributes[i].calcHamAndSpamProb(hamCounter, spamCounter);
    }
}

void Bayes::calcConditionalProbabilitiesForTestData() {
    for (unsigned int i = 0; i < testData.size(); ++i) {
        testData[i].updateProb(hamProb, spamProb);
        for (unsigned int j = 0; j < testData[i].getWords().size(); ++j) {
            bool found = false;
            for (unsigned int k = 0; k < attributes.size() && !found; ++k) {
                //if word appeared in learning data
                if (testData[i].getWord(j) == attributes[k].getWord()) {
                    testData[i].updateProb(attributes[k].getProbIfHam(), attributes[k].getProbIfSpam());
                    found = true;
                }
            }
            //if word didn't appear in learning data
            if (!found) {
                testData[i].updateProb(0, 0); //either this or skip
            }
        }
    }
}

void Bayes::classify() {
    int successfullAssignments = 0;
    int unsuccessfullAssignments = 0;
    for (unsigned int i = 0; i < testData.size(); ++i) {
        if (testData[i].classify()) {
            ++successfullAssignments;
        }
        else {
            ++unsuccessfullAssignments;
        }
    }
    success = (float)successfullAssignments / (float)(successfullAssignments + unsuccessfullAssignments);
}

void Bayes::print() {
    cout << "WordsCounterLearningData: " << wordsCounterLearningData << " - how many words are in learning data, NOT USED IN ALGORITHM" << endl;
    cout << "HamCounter: " << hamCounter << " - how many msgs are spam in x learning data" << endl;
    cout << "SpamCounter: " << spamCounter << " - how many msgs are spam in x learning data" <<endl;
    cout << "HamProb: " << hamProb << " - number of ham data / all data P(C=HAM)" << endl;
    cout << "SpamProb: " << spamProb << " - number of spam data / all data P(C=SPAM)" << endl;
    cout << "WordsCounterInHam: " << wordsCounterInHam << " - words with repeats in all ham data, NOT USED IN ALGORITHM" << endl;
    cout << "WordsCounterInSpam: " << wordsCounterInSpam << " - words with repeats in all spam data, NOT USED IN ALGORITHM" << endl;
    cout << "Success: " << success << " - % of successfull assignments" << endl;
}

void Bayes::printAttributes() {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
//      if (attributes[i].getSpamCounter() > 20 || attributes[i].getHamCounter() > 20) {
//          //cout << attributes[i].getWord() << ", ham: " << attributes[i].getHamCounter() << ", spam: " << attributes[i].getSpamCounter() << endl;
//          attributes[i].print();
//      }
        attributes[i].print();
    }
}

void Bayes::printTestData() {
    for (unsigned int i = 0; i < testData.size(); ++i) {
        testData[i].print();
    }
}

void Bayes::calcWordsCounterInSpamAndHam() {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        wordsCounterInHam += attributes[i].getHamCounter();
        wordsCounterInSpam += attributes[i].getSpamCounter();
    }
}
