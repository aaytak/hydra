
#include "table.h"
using namespace std;


// Ctor
Table::Table() {}

// Dtor
Table::~Table() {}


// Retrieves player total
int Table::getPlayerCount() const {
    return playerCount;
}

// Counts total heads CURRENTLY ALIVE
// Aka length of heads map
int Table::getHeadCount() const {
    return heads.size();
}

// Returns the id of the head at position
// Based on INDEX
int Table::getHeadId(int index) const {
    auto it = heads.begin();
    advance(it, index);
    return it->first;
}

// Returns the head at position
// Not based on id, but on index
const vector<string>& Table::getHead(int index) const {
    // Iterator pointing to position
    auto it = heads.begin();
    advance(it, index);
    return it->second;
}

// Gets head based on id
const vector<string>& Table::getHeadWId(int id) const {
    return heads.at(id);
}

// Returns the TOP CARD of the head with id
string Table::getTopCardHead(int id) const {
    return heads.at(id).back();
}

// Returns the length of the head with id
int Table::getHeadLen(int id) const {
    return heads.at(id).size();
}

// Returns a shared_ptr to the player with given id
// If no such player exists, returns nullptr
shared_ptr<Player> Table::getPlayer(int pId) const {
    for (auto p: players) {
        if (p->getId() == pId) {
            return p;
        }
    }
    return nullptr;
}


// SETUP METHOD
// Gets players, deals cards
// Plays first card? (create first head)
void Table::setupTable() {
    int pCount = 0;

    // Prompt user for player count
    cout << "How many players?" << endl;
    while (true) {
        if ( !(cin >> pCount) ||  pCount < 2 ) {
            if (cin.eof()) break;
            cout << "Please enter a valid integer greater than 1." << endl;
            cin.clear();
            cin.ignore();
        } else {    // A proper number was provided
            playerCount = pCount;
            break;
        }
    }

    // Create desired amount of players
    for (int i = 0; i < pCount; ++i) {
        addPlayer(make_shared<Player>(i+1));
    }

    // Deal cards
    dealCards();
}

// Adds p to player vector
void Table::addPlayer(shared_ptr<Player> p) {
    p->attach(this);
    players.emplace_back(p);
}

// Deals out cards
// ASSUMES PLAYERCOUNT > 1
void Table::dealCards() {
    string tempCard = "";
    int max = getPlayerCount();

    // Add all decks to one big vector that includes all cards
    vector<string> allCards;
    for (int pCount = 0; pCount < max; ++pCount) {  // For each player
        for (int r = 0; r < 13; ++r) {                      // For each rank
            for (int s = 0; s < 4; ++s) {                   // For each suit
                tempCard = RANK[r] + SUIT[s];
                allCards.emplace_back(tempCard);
            }
        }
        // 2 Jokers per player
        allCards.emplace_back("Joker");
        allCards.emplace_back("Joker");
    }

    // Shuffle the cards
    unsigned seed = rand();
    std::default_random_engine rng{seed};
    std::shuffle( allCards.begin(), allCards.end(), rng );
    
    // Deal 54 cards to each player
    auto p = players.begin();
    int cardCounter = 0;
    for (auto c = allCards.begin(); c != allCards.end(); ++c) { // Go through cards
        if (p == players.end()) break;
        if (cardCounter == 54) {    // Reset counter & move to next player
            ++p;
            cardCounter = 0;
        }
        (*p)->receiveCard(*c);
        ++cardCounter;
    }
}


// True if head with id exists
bool Table::headExists(int id) const {
    auto h = heads.find(id);
    return (h != heads.end());  // iterator to end only returned if id not found
}

// 0 if NOT VALID
// 1 if VALID
// 2 if VALID: SAME CARD
// Must play less than top
// if top is ace, can play anything
int Table::isValidPlay(int headId, string card) const {
    char myRank = card[0];
    char top = (getTopCardHead(headId))[0];

    // SAME RANK
    if (top == myRank) return 2;

    // Aces are universal; can play anything on king
    if ( top == 'A' ||  myRank == 'A'  ||  top == 'K' ) {
        return 1;
    }
    // myRank is not an ace; cannot play on 2
    if (top == '2') return 0;

    // TOP: non-integer values
    // Queen: valid except K
    if ( top == 'Q'  &&  myRank != 'K' ) {
        return 1;
    }
    // Jack: valid except K, Q
    if ( top == 'J'  &&  myRank != ('K' || 'Q') ) {
        return 1;
    }

    // TOP: integer values
    if (myRank == ('K' || 'Q' || 'J')) return false;
    int numTop = top - '0';
    int numRank = myRank - '0';
    if (numTop == 1) numTop = 10;
    if (numRank == 1) numRank = 10;
    // compare the two ints
    return (numRank < numTop);
}

// OBSERVER METHOD
// Card has been played
void Table::cardPlayed(int headId, string card) {
    // Find head with given id
    auto it = heads.find(headId);
    // Add to END of head
    if (it != heads.end()) {
        it->second.emplace_back(card);
    }
}


// Makes a new head
void Table::makeNewHead(string card) {
    int headId = allHeadsSoFar + 1;
    allHeadsSoFar++;

    // Add empty head (like mine)
    heads.emplace(make_pair(headId, vector<string>()));

    // Add card to head
    cardPlayed(headId, card);
}

// Removes head with given id
// All cards are added to discard pile of player
bool Table::cutOffHead(int id, int player) {
    shared_ptr<Player> p = getPlayer(player);

    // Player adds all cards to discard pile
    vector<string>& theHead = heads.at(id);
    for (auto it = theHead.begin(); it != theHead.end(); ++it) {
        p->discardCard(*it);
    }

    // Clear head
    auto it = heads.find(id);
    if (it != heads.end()) {
        heads.erase(it);
    }

    // Player must make 2 new heads
    p->drawCards(2);
    // Use reserve if necessary
    if (p->getHand().size() < 2) {
        p->drawReserve();
        // If still not enough, player has won
        if (p->getHand().size() < 2) {
            return false;   // Could not make heads
        }
    }
    // Make heads
    string curCard;
    for (int i = 0; i < 2; ++i) {
        curCard = p->getFirstHand();
        // Prompt user if joker
        if (curCard == "Joker" ) {
            string val;
            cout << "One of the heads will be a Joker. Choose its value:" << endl;
            while (true) {
                if (! (cin >> val)) {
                    if (cin.eof()) break;
                    cout << "Please input a valid rank." << endl;
                    cin.clear();
                    cin.ignore();
                } else {
                    // Check if valid rank
                    bool isValidRank = false;
                    for (int i = 0; i < 13; ++i) {
                        if (val == RANK[i]) {
                            isValidRank = true;
                            break;
                        }
                    }

                    if (!isValidRank) {
                        cout << "Please input a valid rank." << endl;
                    } else {
			curCard = val + "J";
                        break;
                    }
                }
            }
        }
        makeNewHead(curCard);
    }
    return true;
}


// True if one of the players has won
bool Table::isGameOver() const {
    for (auto p: players) {
        if (p->hasWon()) {
            return true;
        }
    }
    return false;
}
