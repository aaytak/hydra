
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include "subject.h"

class Player: public Subject {
    private:
        int id;
        std::string reserve = "";
        std::vector<std::string> hand;
        std::vector<std::string> cards;
        std::vector<std::string> discards;

    public:
        Player(int id);
        ~Player();

        // Retrieves player's id
        int getId() const;
        // Retrieves reserve
        std::string getReserve() const;
        // Retrieves cards in player's hand
        const std::vector<std::string>& getHand() const;
        // Retrieves player's cards
        const std::vector<std::string>& getCards() const;
        // Retrieves player's discards
        const std::vector<std::string>& getDiscards() const;
        
        // Adds card to cards pile
        void receiveCard(std::string card);

        // Draws top card from card deck
        // (Removes it from cards vector & adds to hand)
        void drawCards(int howMany);
        // Draws from reserve (only if there is one)
        void drawReserve();
        // Adds card to discard pile
        void discardCard(std::string card);
        // Discard pile moved to cards
        void moveDiscards();
        // Rest of hand added back to hand pile
        void returnHand();
        // Switches c with card in reserve
        // Returns current reserve
        std::string swapReserve(std::string card);

        // Assigns a value to the joker
        // Returns the updated string
        std::string assignJoker(std::string value) const;

        // True if player has no more cards/discards/reserve
        bool hasWon() const;

        // Removes first card from player's hand
        std::string getFirstHand();
        // True if player has played all cards in hand
        bool handEmpty() const;

        friend std::ostream& operator<<(std::ostream& out, const Player& p);
};

std::ostream& operator<<(std::ostream& out, const Player& p);

#endif
