#include <iostream>
#include <string>
#include <stdlib.h> //rand and srand
#include <time.h> // time()
#include <sstream> // stringstream
#include <vector>
#include "card.h"
using namespace std;

/****************************** Card ****************************/
Card::Card(){} //default constructor
Card::Card( int s, int v ) //constructor
{
  suit = s;
  value = v;
  
  if ( s == 0 )
    suit_name = "Hearts";
  else if ( s == 1 )
    suit_name = "Diamonds";
  else if ( s == 2 )
    suit_name = "Spades";
  else if ( s == 3 )
    suit_name = "Clubs";
  
  if ( v < 11 && v > 1 )
    {
      stringstream mystream;
      mystream << v;
      face_name = mystream.str();
    }
  else if ( v == 11 )
    face_name = "Jack";
  else if ( v == 12 )
    face_name = "Queen";
  else if ( v == 13 )
    face_name = "King";
  else if ( v == 1 )
    face_name = "Ace";

  if ( v == 1 ) //makes Aces high cards, Ace are only low in straights
    value = 14;
}

Card::Card( const Card &Source ) //copy constructor
{
  suit = Source.suit;
  value = Source.value;
  suit_name = Source.suit_name;
  face_name = Source.face_name;
}

Card& Card::operator= ( const Card &Source ) //assignment operator
{
  suit = Source.suit;
  value = Source.value;
  suit_name = Source.suit_name;
  face_name = Source.face_name;

  return *this;
}

bool operator== ( Card &C1, Card &C2 )
{
  return ( C1.value ==  C2.value &&
     C1.suit == C2.suit );
}

bool operator!= ( Card &C1, Card &C2 )
{
  return !( C1 == C2 );
}

int Card::getSuit() { return suit; }

int Card::getValue() { return value; }

string Card::toString() { return face_name + " of " + suit_name; }

/**************************** DeckOfCards *****************************/

DeckOfCards::DeckOfCards()
{
  int i, j=1, k=0;
  for ( i=0; i<52; i++ )
    {
      deck.push_back( Card(k,j) );
      j++;
      if ( j == 14 ) //checks for 13 created cards of 1 suit
	{
	    j = 1;
	    k++;
	}
    }
  
  currentCard = 0; //sets the "next card to be dealt" to vector position 0
}

void DeckOfCards::Shuffle()
{
  int i, j, Ran;
  Card temp;
  
  for ( j=0; j<2; j++ ) //iterates the deck twice to ensure good shuffle
    {
      for ( i=0; i<52; i++ )
	{
	  //generates random numbers between 0 to 51 
	  Ran = rand() % 52;
	  
	  //swaps the two cards picked by the random number and i
	  temp = deck[i];
	  deck[i] = deck[Ran];
	  deck[Ran] = temp;
	}
    }
}

Card DeckOfCards::dealCard() { return deck[currentCard++]; }

bool DeckOfCards::moreCards() { return ( currentCard < 52 ) ? true : false; }
