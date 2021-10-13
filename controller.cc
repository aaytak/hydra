
#include "controller.h"
using namespace std;


Controller::Controller(bool testingMode) : testingMode{testingMode} {
    theTable = make_shared<Table>();
    theDisplay = make_unique<Display>(theTable);
}

Controller::~Controller() {}


// Returns the round number
int Controller::getRoundNum() const {
    return roundNum;
}

// Setup table
void Controller::setupGame() {
    theTable->setupTable();
}


// Starts the game
// Called after setup
void Controller::startGame() {
    string firstCard = "";
    shared_ptr<Player> curPlayer = theTable->getPlayer(1);

    // Player 1 creates first head
    curPlayer->drawCards(1);
    firstCard = curPlayer->getFirstHand();
    theTable->makeNewHead(firstCard);

    // Next player is player 2
    curPlayerId = 2;

    // Print current results
    printTable();
}

void Controller::playGame() {
    bool gameOver = false;

    // Play rounds until game done
    while (!gameOver) {
        gameOver = playRound();
        if (gameOver) break;
        // Reset current player id to 1
        curPlayerId = 1;
    }

    theDisplay->printWinner(curPlayerId);
}

// One round of the game
// Each player plays once
// TRUE if game over
bool Controller::playRound() {
    bool result = false;

    // Current turn CHECK FOR WIN
    int pCount = theTable->getPlayerCount();

    // Each player plays their turn
    for (int i = curPlayerId - 1; i < pCount; ++i) {
        curPlayerId = i + 1;
        result = playerTurn();

        // Player has won
        if (result) return true;
    }
    
    return false;
}

// One player's turn
bool Controller::playerTurn() {
    string curCard = "";
    shared_ptr<Player> curPlayer = theTable->getPlayer(curPlayerId);

    // Check if player has won
    if (curPlayer->hasWon()) return true;

    // Turn message
    theDisplay->printTurn(curPlayerId);
    // Player draws required cards
    int headCount = theTable->getHeadCount();
    curPlayer->drawCards(headCount);

    // Could not draw enough cards; must use reserve
    // THIS ENDS TURN
    int handSize = curPlayer->getHand().size();
    if (handSize < headCount) {
        string pReserve = curPlayer->getReserve();
        if (pReserve == ""  &&  handSize == 0) { // Player wins
            return true;
        }
        // If have reserve, move it to hand
        if (pReserve != "") {
            cout << "Moving reserve to draw pile; turn over." << endl;
            curPlayer->drawReserve();
            curPlayer->returnHand();
            theDisplay->printRound();
            return false;            
        }
    }

    theDisplay->printRound();

    // Player must do something with each card
    int headChosen, playResult;
    while(! curPlayer->handEmpty() ) {
        curCard = curPlayer->getFirstHand();

        // Ask player what they want to do
        headChosen = theDisplay->playMove(curPlayerId, curCard);

        // head is 0 -> put card in reserve
        // Loop to enable swapping back
        bool skipToNext = false;
        while (headChosen == 0) {
            curCard = curPlayer->swapReserve(curCard);
            // If reserve was empty AND hand empty, turn ends
            if (curCard == "" && curPlayer->handEmpty()) {
                theDisplay->printRound();
                return false;
            } else if (curCard == "") {
                skipToNext = true;
                break;
            } else {
                headChosen = theDisplay->playMove(curPlayerId, curCard);
            }
        }
        if (skipToNext) continue;

        // Handle joker
        if (curCard == "Joker") {
            curCard = theDisplay->handleJoker();
        }

        // What will happen once card is played?
        playResult = theTable->isValidPlay(headChosen, curCard);
        // Play card on head
        curPlayer->playCard(headChosen, curCard);

        // 0 == player takes head, hand discarded
        if (playResult == 0) {
            curPlayer->returnHand();
            bool addedHeads = theTable->cutOffHead(headChosen, curPlayerId);
            if (!addedHeads) {     // Could not add heads; player has no more cards
                return true;    // Player wins
            }
            break;
        }
        // 2 == same card as head; turn ends
        else if (playResult == 2) {
            curPlayer->returnHand();
            if (curPlayer->hasWon()) return true;
            break;
        }
        // ELSE playResult == 1; turn continues
        else {
            if (!curPlayer->handEmpty()) {
                theDisplay->printRound();
            }
        }

        // check if player has won
        if (curPlayer->hasWon()) return true;
    }

    theDisplay->printRound();
    return false;
}


// Prints out the heads of the table & players
void Controller::printTable() const {
    theDisplay->printHeads();
    theDisplay->printPlayers();
}
