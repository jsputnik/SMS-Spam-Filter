#include <iostream>
#include "Bayes.h"

using namespace std;

int main()
{
    Bayes x;
    int k = 7; //5572 / 7 = 796
    fstream file;
    //counting data and words
    file.open("spam.csv", ios::in);
    x.count(file);
    file.close();
    int testDataQuantity = x.getDataCounter() / k;
    int learningDataQuantity = x.getDataCounter() - testDataQuantity;
    for (int i = 0; i < k; ++i) {
        ;
    }
    file.open("spam.csv", ios::in);
    string firstLine; //1st line v1,v2
    getline(file, firstLine, '\n'); //cleaning 1st line v1,v2
    cout << "Learning..." << endl;
    x.loadAttributes(file);
    x.printAttributes();
    cout << endl;
    int i = 0;
    while (x.loadData(file) && i < 10/*!file.eof()*/) {
        cout << "i: " << i << endl << endl;
        ++i;
    }
    file.close();
    cout << endl << "Words counter: " << x.getWordsCounter() << endl;
    cout << "Data counter: " << x.getDataCounter() << endl;
    cout << "testDataQuantity: " << testDataQuantity << endl;
    cout << "learningDataQuantity: " << learningDataQuantity << endl;
    cout << endl << "End" << endl;
    return 0;
}
