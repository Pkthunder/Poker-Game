#include <iostream>
#include <string>
#include <stdlib.h>
#include "card.h"
#include "hand.h"
using namespace std;

Hand::Hand() {}

void BubbleSort( Card h[5] )
{
  int i, j;
  for ( i=0; i<4; i++ )
    {
      for ( j=0; j < 4-i; j++ )
  {
	  if ( h[j].getValue() > h[j+1].getValue() )
	    {
	      //swaps values
	      Card temp = h[j];
	      h[j] = h[j+1];
	      h[j+1] = temp;
	    }
	}
    }
}

Hand::Hand( DeckOfCards a, OWNER o )
{
  Card temp[5];
 
  for ( int i=0; i<5; i++ )
    temp[i] = a.dealCard();
  BubbleSort( temp );
  for ( int i=0; i<5; i++ )
    hand.push_back( temp[i] );

  //sets the owner of the hand, either player or computer
  owner = o;
  hand_value = unchecked;
}

vector<int> Hand::getHighest()
{ return high_list; }

int Hand::getHighPair()
{ return high_pair; }

int Hand::getLowPair()
{ return low_pair; }

HAND_VALUE Hand::getHandValue()
{ return hand_value; }

void Hand::printHand( string s )
{
  if ( owner == player )
    cout << "\nPlayer";
  else
    cout << "\nComputer";

  cout << "'s " << s << " Hand:\n";
  for ( int i=0; i<5; i++ )
    cout << hand[i].toString() << endl;
}

//additional function for game.cc
void Hand::determine_high_card()
{
  //error checking
  if ( hand_value == 0 )
    {
      cout << "\nError, hand_value was never checked/updated\n";
      return;
    }

  //straight and flushes
  else if ( hand_value == 5 || hand_value == 6 )
    {
      //checks for straight with Ace as low card
      if ( hand_value == 5 && hand[4].getValue() == 14 )
	high_list.push_back( hand[3].getValue() );
      else
	high_list.push_back( hand[4].getValue() );
    }
  //pair, two pair, three of a kind, four of a kind
  else if ( hand_value < 5 || hand_value == 7 )
    {
      for ( int i=0; i<5; i++ )
	{
	  //pushes non-used card into the vector first
	  if ( hand[i].getValue() != high_pair && hand[i].getValue() != low_pair )
	      high_list.push_back( hand[i].getValue() );
	}
    }
}

void Hand::check_list()
{
  if ( four_kind_check() )
    hand_value = four_kind;
  else if ( flush_check() )
    hand_value = a_flush;
  else if ( straight_check() )
    hand_value = a_straight;
  else if ( three_kind_check() )
    hand_value = three_kind;
  else if ( two_pair_check() )
    hand_value = two_pair;
  else if ( pair_check() )
    hand_value = one_pair;
  else
    hand_value = high_card;

  determine_high_card();
}

bool Hand::pair_check()
{
  for ( int i=0; i<5; i++ )
    {
      for ( int j=0; j<5; j++ )
	{
	  if ( i != j )
	    {
	      if ( hand[i].getValue() == hand[j].getValue() )
		{
		  high_pair = hand[i].getValue();
		  return true;
		}
	    }
	}
    }
  return false;
}

bool Hand::two_pair_check()
{
  Card first_card, second_card; //stores first pair (obviously two cards)
  int i, j;

  for ( i=0; i<5; i++ )
    {
      for ( j=0; j<5; j++ )
        {
          if ( i != j )
	    if ( hand[i].getValue() == hand[j].getValue() )
	      {
		first_card = hand[i];
		second_card = hand[j];
	      }
        }
    }

  for ( i=0; i<5; i++ )
    {
      for ( j=0; j<5; j++ )
        {
          if ( i != j )
            {
              if ( hand[i].getValue() == hand[j].getValue() )
		if ( hand[i] != first_card && hand[j] != first_card &&
		     hand[i] != second_card && hand[j] != second_card )
		  {
		    if ( hand[i].getValue() > first_card.getValue() )
		      {
			high_pair = hand[i].getValue();
			low_pair = first_card.getValue();
		      }
		    else
		      {
			high_pair = first_card.getValue();
			low_pair = hand[i].getValue();
		      }
		    return true;
		  }            
	    }
        }
    }
  return false;
}

bool Hand::three_kind_check()
{
  //123
  if ( hand[0].getValue() == hand[1].getValue() && 
       hand[1].getValue() == hand[2].getValue() )
    {
      high_pair = hand[2].getValue();
      return true;
    }
  //234
  if ( hand[1].getValue() == hand[2].getValue() &&
       hand[2].getValue() == hand[3].getValue() )
    {
      high_pair = hand[3].getValue();
      return true;
    }
  //345
  if ( hand[2].getValue() == hand[3].getValue() &&
       hand[3].getValue() == hand[4].getValue() )
    {
      high_pair = hand[4].getValue();
      return true;
    }

  return false;
}

bool Hand::four_kind_check()
{
  if ( (hand[1].getValue() == hand[2].getValue()) && 
       (hand[2].getValue() == hand[3].getValue()) )
    {
      if ( hand[0].getValue() == hand[1].getValue() )
	{	
	  high_pair = hand[2].getValue();
	  return true;
	}
      if ( hand[4].getValue() == hand[1].getValue() )
	{
	  high_pair = hand[2].getValue();
	  return true;
	}
    }
  
  return false;
}

bool Hand::flush_check()
{
  if ( hand[0].getSuit() == hand[1].getSuit() &&
       hand[0].getSuit() == hand[2].getSuit() &&
       hand[0].getSuit() == hand[3].getSuit() &&
       hand[0].getSuit() == hand[4].getSuit() )
    return true;
  return false;
}

bool Hand::straight_check()
{
  int temp = hand[0].getValue();
  
  //Checks for Ace,2,3,4,5
  if ( (hand[0].getValue() == 2) &&
       (hand[1].getValue() == 3) &&                                            
       (hand[2].getValue() == 4) &&                                            
       (hand[3].getValue() == 5) &&                                            
       (hand[4].getValue() == 14) )
    return true;

  //Checks for Sequential Straight
  if ( (hand[1].getValue() == temp+1) &&
       (hand[2].getValue() == temp+2) &&
       (hand[3].getValue() == temp+3) &&
       (hand[4].getValue() == temp+4) )
    return true;
  
  return false;
}
