#ifndef CARD_H_
#define CARD_H_

#include <string>
#include <vector>
using namespace std;

class Card
{
private:
  int suit;
  int value;
  string face_name;
  string suit_name;
public:
  Card();
  Card( int s, int v );
  Card( const Card &Source );
  Card& operator= ( const Card &Source );
  friend bool operator== ( Card &C1, Card &C2 );
  friend bool operator!= ( Card &C1, Card &C2 );
  int getSuit();
  int getValue();
  string toString();
};

class DeckOfCards
{
private:
  vector<Card> deck;
  int currentCard;
public:
  DeckOfCards();
  void Shuffle();
  Card dealCard();
  bool moreCards();
};

#endif
