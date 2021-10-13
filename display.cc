
#include "display.h"
#include "table.h"
using namespace std;


// Ctor
Display::Display(shared_ptr<Table> theTable): theTable{theTable} {}

// Dtor
Display::~Display() {}


// Prints out each of the table's heads
void Display::printHeads() const {
    int curId = 0;
    string curCard = "";
    int curHeadLen = 0;
    int headTotal = theTable->getHeadCount();

    cout << "Heads:" << endl;

    // Go through all heads
    for (int h = 0; h < headTotal; ++h) {
        curId = theTable->getHeadId(h);
        curCard = theTable->getTopCardHead(curId);
        curHeadLen = theTable->getHeadLen(curId);

        cout << curId << ": " << curCard << " (" << curHeadLen << ")";
        cout << endl;
    }
    cout << endl;
}


// Prints players, their cards & discards
// Also prints cards currently in hand
void Display::printPlayers() const {
    shared_ptr<Player> pTemp = nullptr;
    int pNum = theTable->getPlayerCount();

    cout << "Players:" << endl;
    for (int i = 0; i < pNum; ++i) {
        pTemp = theTable->getPlayer(i+1);
        cout << *pTemp;

        // Extra stuff
        int handCount = pTemp->getHand().size();
        if (handCount != 0) {
            cout << " + 1 in hand, ";
            cout << handCount - 1 << " remaining, ";

            int reserveCount = 0;
            if (pTemp->getReserve() != "") {
                reserveCount = 1;
            }
            cout << reserveCount << " in reserve";
        } else {
            if (pTemp->getReserve() != "") {
                cout << ", 1 in reserve";
            }
        }
        cout << endl;
    }
    cout << endl;
}


// Prints dialogue for round
void Display::printRound() const {
    printHeads();
    printPlayers();
}

// Prints dialogue for one player's turn
void Display::printTurn(int pId) const {
    cout << endl;
    cout << "Player " << pId << ", it is your turn. Input any character to continue." << endl;
    string confirm;
    cin >> confirm;
}

// Tells the player their current card, asks for their move
// Returns chosen head
int Display::playMove(int pId, string card) const {
    cout << "Player " << pId << ", you are holding a ";
    cout << card << ". Your move?" << endl;

    int headChosen;
    while (true) {
        cin >> headChosen;
        if ( cin.fail()  ||  (!(theTable->headExists(headChosen))) ) {
            if (cin.eof()) break;
            if ((!cin.fail()) && headChosen == 0) return headChosen;
            cout << "Please choose a valid head." << endl;
            cin.clear();
            cin.ignore();
        } else {
            return headChosen;
        }
    }    
}

// Handles updating the Joker
string Display::handleJoker() const {
    string val;
    
    cout << "Joker value?" << endl;

    // Get a valid character
    while (true) {
        if ( !(cin >> val) ) {
            if (cin.eof()) break;
            cout << "Please enter a valid rank." << endl;
            cin.clear();
            cin.ignore();
        } else {
            if (!isValidRank(val)) {
                cout << "Please enter a valid rank." << endl;
            } else {
                return val + "J";
            }
        }
    }
}


// True if c is a valid rank
bool Display::isValidRank(string c) const {
    for (int i = 0; i < 13; ++i) {
        if (c == RANK[i]) {
            return true;
        }
    }
    return false;
}


// Prints out winner
void Display::printWinner(int pId) const {
    cout << "Player " << pId << " wins!" << endl;
}
