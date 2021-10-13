
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "display.h"
#include "table.h"

class Controller {
    private:
        std::shared_ptr<Table> theTable;
        std::unique_ptr<Display> theDisplay;
        int roundNum = 0;
        int curPlayerId = 1;
        bool testingMode = false;

    public:
        Controller(bool testingMode);
        ~Controller();

        int getRoundNum() const;

        // Sets up the table/display
        void setupGame();

        // Starts the game
        void startGame();
        // Overall game handler
        void playGame();
        // Plays one round
        bool playRound();
        // One player's turn
        bool playerTurn();

        // Prints out the heads of the table
        void printTable() const;
};

#endif
