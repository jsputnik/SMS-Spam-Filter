#include "Data.h"

using namespace std;

Data::Data(string actual_type) {
    this->actual_type = actual_type;
    type = "none";
    hamProb = 0;
    spamProb = 0;
}

void Data::print() {
    cout << "Actual type: " << actual_type << endl;
    cout << "Assigned type: " << type << endl;
    cout << "Message: " << endl;
    for(vector<string>::iterator it = words.begin(); it != words.end(); it++) {
        cout << *it << "|";
    }
    cout << endl << endl;
}

void Data::updateProb(float probForHam, float probForSpam) {
    if (probForHam == 0) {
        probForHam = 0.001;
    }
    if (probForSpam == 0) {
        probForSpam = 0.001;
    }
    hamProb *= probForHam;
    spamProb *= probForSpam;
}

bool Data::classify() {
    if (hamProb >= spamProb) {
        type = "ham";
    }
    else {
        type = "spam";
    }
    return (actual_type == type);
}
