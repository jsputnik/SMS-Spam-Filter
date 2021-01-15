#include <iostream>
#include "Bayes.h"

using namespace std;

int main()
{
    Bayes x;
    fstream file;
    file.open("spam.csv", ios::in);
    string type; //ham or spam in file
    getline(file, type, '\n'); //cleaning 1st line v1,v2
    cout << "Learning..." << endl;
    x.loadAttributes(file);
    x.printAttributes();
    cout << endl;
    int i = 0;
    while (x.loadData(file) && i < 2) {
        cout << "i: " << i << endl << endl;
        ++i;
    }
    file.close();
    cout << endl << "End" << endl;
    return 0;
}
