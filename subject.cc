
#include "subject.h"
using namespace std;


// Dtor
Subject::~Subject() {}


// Adds o to the end of the observer vector
void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}

// Removes o from the observer vector
// If o not in vector, does nothing
void Subject::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}

// Notifies observers that the subject has played a card
void Subject::playCard(int headId, std::string card) const {
    for (auto ob: observers) {
        ob->cardPlayed(headId, card);
    }
}
