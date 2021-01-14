#include "Data.h"

Data::Data() {
    type = "none";
    hamProb = 0;
    spamProb = 0;
}

void Data::setType() {
    if (hamProb >= spamProb) {
        type = "ham";
    }
    else {
        type = "spam";
    }
}
