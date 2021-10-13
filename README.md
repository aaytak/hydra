# hydra
This is my implementation of the card game Hydra using C++.
Written by Kat Driscoll at the University of Waterloo for CS246 in Spring 2021.


<b>Game Rules:</b>
This game requires at least 2 players. You need one deck of cards per player (including jokers). These cards are all shuffled, then distributed evenly, face-down, between all players (i.e. each player starts with 54 cards). This is the player's <i><u>draw pile</u></i>.

The players each have 3 "piles" of cards:
1. The draw pile
2. The discard pile
3. The reserve (can only have 0 or 1 cards).

The card suits are irrelevant. Here are the card values, in increasing order:
ACE   TWO   THREE   FOUR   FIVE   SIX   SEVEN   EIGHT   NINE   TEN   JACK   QUEEN   KING

Player 1 creates the first <i>"head"</i> by drawing the first card from their draw pile and placing it, face up, in the centre of the table. If the card happens to be a joker, it takes the value 2 (see notes about jokers below). From there, the other players take turns clockwise. Each player draws and plays as many cards as there are heads.

Here are the ways in which players can play their cards:
<b>1.</b> If the drawn card's value is <u>strictly less</u> than the top card of any head, it may be played, face up, on that head.
<b>2.</b> If the drawn card's value is <u>equal</u> to that of the top card of any head, it may be played, face up, on that head. However, the player's turn ends immediately after this, and the rest of the player's drawn cards return to their draw pile.
<b>3.</b> If the top card of any head is an ace, and the drawn card is not, it may be played, face up, on that head.
<b>4.</b> If the player has nothing in their reserve, they may place their drawn card into reserve. The player must simply place the card, face down, in front of themselves.
<b>5.</b> If the player has something in their reserve, they may replace the drawn card with the one in reserve. Note that the reserve pile can have at most one card in it at any given time.

If a player cannot play a card following any of these rules (i.e. they are stuck playing a card with a greater value than any of the heads), they must <i>"cut off one of the heads"</i> by playing their card on the head, and adding all of the cards in that head into their <i><u>discard pile<u><i>.
  
Once a player runs out of cards in their <i>draw pile</i>, they must shuffle their <i>discard pile</i> and add it to their draw pile. If their discard pile is empty, they must play their reserve card.
  
A player wins when they have no cards left; i.e. when their draw pile, discard pile, and reserve are all empty.
  
<b>Note about Jokers:</b>
Jokers are a special card in this game. When a player draws a Joker, they choose a value to assign to it. In other words, the joker card can become any card the player wants. The obvious choice is to assign an ACE value to it, since aces are universal, but other options are available.
  
