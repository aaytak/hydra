
#ifndef _TABLE_H_
#define _TABLE_H_

#include <algorithm>
#include <map>
#include <memory>
#include <random>
#include "player.h"

// Important consts for cards
const std::string RANK[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
const std::string SUIT[4] = { "C", "D", "H", "S" };

class Table: public Observer {
    private:
        int playerCount = 0;
        int allHeadsSoFar = 0;
        std::map<int, std::vector<std::string>> heads;
        std::vector<std::shared_ptr<Player>> players;

    public:
        Table();
        ~Table();

        // Retrieves player count
        int getPlayerCount() const;
        // Counts total heads (that are alive)
        int getHeadCount() const;
        // Returns the nth head's id (based on position)
        int getHeadId(int index) const;
        // Returns the nth head (NOT BASED ON ID)
        const std::vector<std::string>& getHead(int index) const;
        // Returns the head BASED ON ID
        const std::vector<std::string>& getHeadWId(int id) const;
        // Returns the top card of the head with id
        std::string getTopCardHead(int id) const;
        // Returns the length of the head with id
        int getHeadLen(int id) const;
        // Returns player with given id
        std::shared_ptr<Player> getPlayer(int pId) const;

        // Sets up the table, players, deals cards
        void setupTable();
        // Adds player to the table
        void addPlayer(std::shared_ptr<Player> p);
        // Deals out cards; need playerCount > 1
        void dealCards();
        
        // True if head with this ID exists
        bool headExists(int id) const;
        // Checks whether card can be played on head
        // 0 == false, 1 == true, 2 == true (same card)
        int isValidPlay(int headId, std::string card) const;
        // Each of the players plays their turn?
        //void playTurn(int whichHead, int pId);
        // OBSERVER METHOD
        // Card has been played
        void cardPlayed(int headId, std::string cardPlayed) override;

        // Makes a new head
        void makeNewHead(std::string card);
        // Removes head with id, gives it to player
        // True if successful
        bool cutOffHead(int id, int player);

        // True if one of the players has won
        bool isGameOver() const;
};

#endif
