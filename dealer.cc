#include <iostream>
#include <string>
#include "card.h"
#include "hand.h"
#include "game.h"
using namespace std;

//using BubbleSort from hand.cc
void BubbleSort( Card h[5] );

void Hand::tradeCard( DeckOfCards &the_deck, int n )
{
  Card temp[5];

  for ( int i=0; i<5; i++ )
    {
      //draws the new card to replace the old one
      if ( hand[i].getValue() == n )
  temp[i] = the_deck.dealCard();
      else
	temp[i] = hand[i];
    }
  BubbleSort( temp );
  hand.clear();
  setHand( temp );
}

void Game::simulateTurn()
{
  int c = computers_hand.getHandValue();
  vector<int> extra = computers_hand.getHighest();

  computers_hand.printHand("Original");

  //pair, two pair, three of a kind, four of a kind
  if ( c != 1 || c != 5 || c != 6 )
    {
      for ( int i=0; i<extra.size(); i++ )
	{
	  if ( extra[i] < 10 )
	    computers_hand.tradeCard( game_deck, extra[i] );
	}
    }
  //high card, i.e. no hand yet
  else if ( c == 1 )
    {      
      //trades the 3 lowest cards
      if ( extra[0] < 10 )
	computers_hand.tradeCard( game_deck, extra[0] );
      if ( extra[1] < 10 )
	computers_hand.tradeCard( game_deck, extra[1] );
      if ( extra[2] < 10 )
	computers_hand.tradeCard( game_deck, extra[2] );
    }
  //if straight or flush, do nothing

  computers_hand.printHand("Current");
}
