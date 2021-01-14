#include <iostream>
#include <fstream>
#include <string>
#include "Data.h"
#include "Attribute.h"
#include<bits/stdc++.h>
using namespace std;

void myGetLine();

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
    loadData(Data data); //read one set of data
    void print()
    {
        cout<<"Spam List"<<endl;
        printS(spamWords);
        cout<<"Spam Counter"<<endl;
        printI(spamCounter);
        cout<<"Ham List"<<endl;
        printS(hamWords);
        cout<<"Ham Counter"<<endl;
        printI(hamCounter);

    }

    void printS(vector <string> x)
    {
        vector<string>::iterator it;
        for(it = x.begin(); it != x.end(); it++)
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }
     void printI(vector <int> x)
    {
        vector<int>::iterator it;
        for(it = x.begin(); it != x.end(); it++)
        {
            cout<<*it<<" ";
        }
        cout<<endl;
    }

    void readData()
    {
        //Attribute attribute();
        int l=0;
        fstream data;
        bool stop1, stop2 = 0;
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
                line>>word;
                if(word[word.size()-1] == ',' && word[word.size()-2] == ',')
                    stop2 = 1;
                while(word[word.size()-1] == ',' || word[word.size()-1] == '.' || word[word.size()-1] == '\n')
                {
                    word.pop_back();
                }
                if(type == "spam")
                {
                    for(int i=0; i < spamWords.size(); i++)
                    {
                        if(word == spamWords[i])
                        {
                            spamCounter[i]++;
                            continue;
                        }
                    }
                    spamWords.push_back(word);
                    spamCounter.push_back(1);
                }
                else if(type == "ham")
                {
                    for(int i=0; i < hamWords.size(); i++)
                    {
                        if(word == hamWords[i])
                        {
                            hamCounter[i]++;
                            continue;
                        }
                    }
                    hamWords.push_back(word);
                    hamCounter.push_back(1);
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
};

int main()
{
    Bayes b;
    b.readData();

    return 0;
}
