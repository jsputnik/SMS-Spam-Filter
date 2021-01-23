#include "Attribute.h"

using namespace std;

void Attribute::print() {
    cout << "Word: " << word << ", ";
    cout << "hamCounter: " << hamCounter << ", ";
    cout << "spamCounter: " << spamCounter << ", ";
    cout << "probIfHam: " << probIfHam << ", ";
    cout << "probIfSpam: " << probIfSpam << ", ";
    cout << "occurrenceInHam: " << occurrenceInHam << ", ";
    cout << "occurrenceInSpam: " << occurrenceInSpam << endl;
}

void Attribute::incCounter(string type) {
    if (type == "ham") {
        ++hamCounter;
    }
    else if (type == "spam") {
        ++spamCounter;
    }
    else {
        cerr << "Error in incCounter: undefined value for 'type'" << endl;
    }
}

void Attribute::incOccurrence(string type) {
    if (type == "ham") {
        ++occurrenceInHam;
    }
    else if (type == "spam") {
        ++occurrenceInSpam;
    }
    else {
        cerr << "Error in incOccurrence: undefined value for 'type'" << endl;
    }
}

void Attribute::calcHamAndSpamProb(int hamMsgsNumber, int spamMsgsNumber) {
    probIfHam = (float)occurrenceInHam / (float)hamMsgsNumber;
    probIfSpam = (float)occurrenceInSpam / (float)spamMsgsNumber;
}
