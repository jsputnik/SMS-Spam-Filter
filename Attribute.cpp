#include "Attribute.h"

using namespace std;

Attribute::Attribute() {
    hamCounter = 0;
    spamCounter = 0;
    hamProb = 0;
    spamProb = 0;
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
