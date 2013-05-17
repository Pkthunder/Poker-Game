//Programmer: Jared Perreault
//Date: Apr 29, 2013
//Complete verison of the 5-card draw poker game
//Compiles: "g++ final_game.cc player.cc dealer.cc game.cc hand.cc card.cc"

#include <stdlib.h> //srand()
#include "game.h"
#include "hand.h"
#include "card.h"

int main()
{
  srand( time(NULL) );
  Game b;
  b.performTurn();
  b.simulateTurn();
  b.determine_winner();

  return 0;
}
