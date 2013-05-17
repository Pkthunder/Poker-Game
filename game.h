#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "card.h"
#include "hand.h"
#include "game.h"

class Game
{
private:
  DeckOfCards game_deck;
  Hand players_hand;
  Hand computers_hand;
public:
  Game();
  void determine_winner();
  void simulateTurn(); //in dealer.cc
  void performTurn(); //in player.cc
};

#endif
