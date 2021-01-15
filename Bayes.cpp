#include "Bayes.h"
#include "Attribute.h"
#include "Data.h"

void Bayes::printAttributes() {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        cout << attributes[i].getWord() << ", ham: " << attributes[i].getHamCounter() << ", spam: " << attributes[i].getSpamCounter() << endl;
    }
}

//load type of msg into type, text of the msg into msg
bool Bayes::loadMessage(fstream& file, string& type, string& msg) {
    string tmp;
    getline(file, type, ','); //because of structure
    if(type.empty()) {
        return false;
    }
    //load one message (until ,,,)
    while(!(msg[msg.size()-1] == ',' && msg[msg.size()-2] == ',' && msg[msg.size()-3] == ',')) {
        getline(file, tmp, '\n');
        msg += tmp;
    }
    return true;
}

//load one test data
bool Bayes::loadData(fstream& file) {
    string type, msg;
    if (!loadMessage(file, type, msg)) {
        return false;
    }
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
            }
        }
    }
    cout << "original msg: " << msg << endl;
    data.print();
    return true;
}

//load all learning data into attributes
bool Bayes::loadAttributes(fstream& file) {
    int k = 0;
    //while(!file.eof()) {
    while (k < 500) {
        string type, msg, tmp;
        if (!loadMessage(file, type, msg)) { //fix
            cerr << "Error in loadMessage()" << endl;
            return false;
        }
        if (type != "ham" && type != "spam") {
            cerr << "Wrong type read in loadAttributes()" << endl;
            return false;
        }
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
                    ++wordsCounter;
                }
            }
        }
        ++k;
    }
    return true;
}

//void Bayes::loadAttributes()
//{
//    int l=0;
//    fstream data;
//    bool stop2 = 0;
//    bool added = 0;
//    data.open("spam.csv", ios::in);
//    string type; //ham or spam in file
//    string word, tmp1, tmp2;
//    getline(data, type, '\n'); //cleaning 1st line
//    //for each data
//    while(true)
//    {
//        type.clear();
//        getline(data, type, ','); //because of structure
//        if(type.size() == 0)
//            break;
//        getline(data, tmp1, '\n');
//
//        while(!(tmp1[tmp1.size()-1] == ',' && tmp1[tmp1.size()-2] == ',' && tmp1[tmp1.size()-3] == ',')) //until ,,,
//        {
//            getline(data, tmp2, '\n');
//            tmp1+=tmp2;
//        }
//        stringstream line(tmp1); //contains all words in data
//
//        while(!stop2)
//        {
//            added = 0;
//            line>>word;
//            if(word[word.size()-1] == ',' && word[word.size()-2] == ',')
//                stop2 = 1;
//            while(word[word.size()-1] == ',' || word[word.size()-1] == '.' || word[word.size()-1] == '\n') //remove . ,
//            {
//                word.pop_back();
//            }
//            //check if the word already occurred
//            for(unsigned int i=0; i < attributes.size(); i++)
//            {
//                if(word == attributes[i].getWord())
//                {
//                    if(type == "spam")
//                        attributes[i].incSpamCounter();
//                    else
//                        attributes[i].incHamCounter();
//                    added = 1;
//                    break;
//                }
//            }
//            //if not in vector attributes
//            if(!added)
//            {
//                Attribute newAtr;
//                newAtr.setWord(word);
//                if(type == "spam") {
//                    newAtr.incSpamCounter();
//                    attributes.push_back(newAtr);
//                }
//
//                else if (type == "ham") {
//                    newAtr.incHamCounter();
//                    attributes.push_back(newAtr);
//                }
//            }
//            incWordsCounter();
//        }
//        stop2 = 0;
//        if(l%100 == 0)
//        cout<<l<<endl;
//        l++;
//    }
//    //print();
//    data.close();
//    cout << "wordscounter: " << wordsCounter << endl;
//}

