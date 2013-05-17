#include <iostream>
#include <string>
#include <stdlib.h> //srand()
#include "card.h"
#include "hand.h"
#include "game.h"
using namespace std;

//including BubbleSort from hand.cc
void BubbleSort( Card h[5] );

//Additional memeber functions of Hand for the purposes of game.cc
//Additional constructor
Hand::Hand( OWNER o )
{
  owner = o;
  hand_value = unchecked;
  high_pair = 0;
  low_pair = 0;
}
//Additional setter
void Hand::setHand( Card arr[5] )
{
  BubbleSort( arr );
  for ( int i=0; i<5; i++ )
    hand.push_back( arr[i] );
  check_list();
}

Game::Game() : players_hand(player), computers_hand(computer)
{
  cout << "\033[2J\033[1;1H";
  game_deck.Shuffle();
  Card players[5], computers[5];

  for ( int i=0; i<5; i++ )
    {
      players[i] = game_deck.dealCard();
      computers[i] = game_deck.dealCard();
    }
  players_hand.setHand( players );
  computers_hand.setHand( computers );
}

void Game::determine_winner()
{
  int p = players_hand.getHandValue();
  int c = computers_hand.getHandValue();
  string arr[8] = { "unchecked", "high card", "pair", "two pair",
  	    "three of a kind", "straight", "flush", "four of a kind" };

  cout << "\nplayer: " << arr[p] << "\ncomputer: " << arr[c] << endl;

  if ( p > c )
    cout << "player wins\n" << endl;

  else if ( p < c )
    cout << "computer wins\n" << endl;

  else if ( p == c )
    {
      vector<int> p_high = players_hand.getHighest();
      vector<int> c_high = computers_hand.getHighest();
      cout << "same hand" << endl;
      
      //straights, flushes
      if ( p == 5 || p == 6 )
	{
	  if ( p_high[0] > c_high[0] )
	    cout << "player wins!" << endl << endl;
	  else
	    cout << "computer wins!" << endl << endl;
	}
      
      //four and three of a kind, and pair
      else if ( p != 5 && p != 6 )
	{
	  //determines winner by high card if pair(s) are equal
	  if ( players_hand.getHighPair() == computers_hand.getHighPair() &&
	       players_hand.getLowPair() == players_hand.getLowPair() )
	    {
	      while ( p_high.back() == c_high.back() )
		{
		  p_high.pop_back();
		  c_high.pop_back();
		}
	      if ( p_high.back() > c_high.back() )
		cout << "player wins, high card" << endl << endl;
	      else
		cout << "computer wins, high card" << endl << endl;
	    }
	  //determines winner by high pair
	  else if ( players_hand.getHighPair() > computers_hand.getHighPair() )
	    cout << "player wins, higher pair (" << players_hand.getHighPair() << " over " << computers_hand.getHighPair() << ")" << endl << endl;
	  else if ( players_hand.getHighPair() < computers_hand.getHighPair() )
	    cout << "computer wins, higher pair (" << computers_hand.getHighPair() << " over " << players_hand.getHighPair() << ")" << endl << endl;
	  //determines winner by low pair if high pairs are equal
	  else if ( players_hand.getLowPair() > computers_hand.getLowPair() )
	    cout << "player wins, highest 2nd pair (" << players_hand.getLowPair() << " over " << computers_hand.getLowPair() << ")" << endl << endl;
	  else if ( players_hand.getLowPair() < computers_hand.getLowPair() )
	    cout << "computer wins, highest 2nd pair (" << computers_hand.getLowPair() << " over " << players_hand.getLowPair() << ")" << endl << endl;
	}
    }
}
