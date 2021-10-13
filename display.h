
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <memory>
class Table;

class Display {
    private:
        std::shared_ptr<Table> theTable;

    public:
        Display(std::shared_ptr<Table> theTable);
        ~Display();

        // Prints out each of the heads
        void printHeads() const;
        // Prints players, their cards, discards
        // May also print for player currently playing turn
        void printPlayers() const;

        // Prints dialogue for round
        void printRound() const;
        // Prints current player turn
        void printTurn(int pId) const;
        // Prompts player for action with card
        int playMove(int pId, std::string card) const;
        // Handles updating the joker
        std::string handleJoker() const;

        // True if c is a valid rank
        bool isValidRank(std::string c) const;

        // Prints the winner
        void printWinner(int pId) const;
        
};

#endif
