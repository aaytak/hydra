
#include "player.h"
using namespace std;


// Ctor
Player::Player(int id) : id{id} {}

// Dtor
Player::~Player() {}


// Retrieves player id
int Player::getId() const {
    return id;
}

// Returns the player's reserve card
string Player::getReserve() const {
    return reserve;
}

// Retrieves cards in player's hand
const vector<string>& Player::getHand() const {
    return hand;
}

// Retrieves reference to player cards
const vector<string>& Player::getCards() const {
    return cards;
}

// Retrieves ref to player discards
const vector<string>& Player::getDiscards() const {
    return discards;
}


// Adds card to cards pile
void Player::receiveCard(string card) {
    cards.emplace_back(card);
}


// Player draws cards from top of cards
// If not enough cards, discard pile moved to cards.
// If still not enough, reserve drawn
// CLEARS PREVIOUS HAND
void Player::drawCards(int howMany) {
    string tempCard = "";

    // Clear previous hand
    hand.clear();

    // Draw required amount of cards
    for (int i = 0; i < howMany; ++i) {
        // If no more cards, discards made into card pile
        if (cards.empty()) {
            moveDiscards();

            // If still none, stop
            if (cards.empty()) break;
        }

        tempCard = cards.at(0);
        cards.erase(cards.begin());
        hand.emplace_back(tempCard);
    }
}

// Adds reserve to hand (only if there is one)
void Player::drawReserve() {
    if (reserve != "") {
        hand.emplace_back(reserve);
        reserve = "";
    }
}

// Adds card to discard pile
void Player::discardCard(string card) {
    discards.emplace_back(card);
}

// Moves discards to card pile
void Player::moveDiscards() {
    for (auto it = discards.begin(); it != discards.end(); ++it) {
        cards.emplace_back(*it);
    }
    discards.clear();
}

// Hand returned to card pile and cleared
void Player::returnHand() {
    int handLen = hand.size();
    // Put cards back in cards pile in order
    for (int i = handLen - 1; i >= 0; --i) {
        cards.insert(cards.begin(), hand.at(i));
    }

    hand.clear();
}

// Switches card with card in reserve;
// Returns current reserve
string Player::swapReserve(string card) {
    string temp = reserve;
    reserve = card;
    return temp;
}


// Assigns value to joker
// ASSUMES VALUE IS VALID
string Player::assignJoker(string value) const {
    return value + "J";
}


// True if the player has:
// NO cards && NO discards && NO reserve
bool Player::hasWon() const {
    return ( hand.empty()  &&  cards.empty()  &&  discards.empty()  &&  reserve == "" );
}


// Returns the FIRST card in hand
// Also removes it from hand
string Player::getFirstHand() {
    string c = hand.at(0);
    hand.erase(hand.begin());
    return c;
}

// True if no more cards in hand (all played)
bool Player::handEmpty() const {
    return hand.empty();
}


// OUTPUT OPERATOR OVERLOAD
// Prints the player in format:
// PlayerX: CARDCOUNT (CARDS draw, DISCARDS discard)
ostream& operator<<(ostream& out, const Player& p) {
    int numCards = p.cards.size();
    int numDiscards = p.discards.size();
    // Calculate total card amount
    int totalCards = numCards + numDiscards;

    out << "Player " << p.getId() << ": " << totalCards << " ";
    out << "(" << numCards << " draw, " << numDiscards << " discard)";

    // More may be added after outside of this function

    return out;
}
