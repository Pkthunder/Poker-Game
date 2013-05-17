#include <iostream>
#include <string>
#include "card.h"
#include "hand.h"
#include "game.h"
using namespace std;

//BubbleSort from hand.cc
void BubbleSort( Card h[5] );

int validateInput( bool zero )
{
  int n;
  bool pass =  false;
  while ( pass == false )
    {
      cin >> n;
      if ( zero == true )
  {
	  if ( n > -1 && n < 4 ) //include zero
	    pass = true;
	  else
	    cout << "Invalid Entry" << endl;
	}  
      if ( zero == false )
	{
	  if ( n > 0 && n < 6 ) //exclude zero
	    pass = true;
	  else
	    cout << "Invalid Entry" << endl;
	}
    }
  
  return n;
}

void Hand::playersTurn( DeckOfCards &the_deck )
{
  int n, pos[3] = { -1, -1, -1 };
  Card temp[5];

  cout << "\nHow many cards you would to trade?  ";
  n = validateInput(true);
  for ( int i=0; i<n; i++ )
    {
      cout << "Please enter the card's position\n(top card is 1, bottom card is 5):  ";
      pos[i] = validateInput(false) - 1;
    }
  for ( int j=0; j<5; j++ )
    {
      //check for position
      if ( (pos[0] != -1 && pos[0] == j) ||
	   (pos[1] != -1 && pos[1] == j) ||
	   (pos[2] != -1 && pos[2] == j) )
	temp[j] = the_deck.dealCard();
      else
	temp[j] = hand[j];
    }
  hand.clear();
  BubbleSort( temp );
  setHand( temp );
}

void Game::performTurn()
{
  players_hand.printHand("Original");
  players_hand.playersTurn( game_deck );
  players_hand.printHand("Current");
}
