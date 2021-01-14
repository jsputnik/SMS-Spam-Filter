#include "Bayes.h"
#include "Attribute.h"
#include "Data.h"

void Bayes::readData()
{
    //Attribute attribute();
    int l=0;
    fstream data;
    bool stop1, stop2 = 0;
    bool added = 0;
    data.open("spam.csv", ios::in);
    string type, word, tmp1, tmp2;
    getline(data, type, '\n');
    while(true)
    {
        type.clear();
        getline(data, type, ',');
        if(type.size() == 0)
            break;
        getline(data, tmp1, '\n');

        while(!(tmp1[tmp1.size()-1] == ',' && tmp1[tmp1.size()-2] == ',' && tmp1[tmp1.size()-3] == ','))
        {
            getline(data, tmp2, '\n');
            tmp1+=tmp2;
        }
        stringstream line(tmp1);

        while(!stop2)
        {
            added = 0;
            line>>word;
            if(word[word.size()-1] == ',' && word[word.size()-2] == ',')
                stop2 = 1;
            while(word[word.size()-1] == ',' || word[word.size()-1] == '.' || word[word.size()-1] == '\n')
            {
                word.pop_back();
            }
            for(unsigned int i=0; i < attributes.size(); i++)
            {
                if(word == attributes[i].getWord())
                {
                    if(type == "spam")
                        attributes[i].incSpamCounter();
                    else
                        attributes[i].incHamCounter();
                    added = 1;
                    break;
                }
            }
            if(!added)
            {
                Attribute newAtr;
                newAtr.getWord() = word;
                if(type == "spam")
                    newAtr.incSpamCounter();
                else
                    newAtr.incHamCounter();
                attributes.push_back(newAtr);
            }
        }
        stop2 = 0;
        if(l%100 == 0)
        cout<<l<<endl;
        l++;
    /*  if(l==2000)
        break;*/
    }
    print();
    data.close();
}

//void Bayes::print()
//{
//    cout<<"Spam List"<<endl;
//    printS(spamWords);
//    cout<<"Spam Counter"<<endl;
//    printI(spamCounter);
//    cout<<"Ham List"<<endl;
//    printS(hamWords);
//    cout<<"Ham Counter"<<endl;
//    printI(hamCounter);
//
//}
//
//void Bayes::printA(vector <Attribute> x)
//{
//    vector<string>::iterator it;
//    for(it = x.begin(); it != x.end(); it++)
//    {
//        cout<<*it<<" ";
//    }
//    cout<<endl;
//}
//
