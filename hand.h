#ifndef HAND_H_
#define HAND_H_

#include <string>
#include "card.h"

using namespace std;

enum OWNER { player, computer };
enum HAND_VALUE { unchecked, high_card, one_pair, two_pair, 
  	  three_kind, a_straight, a_flush, four_kind };

class Hand
{
private:
  vector<Card> hand;
  OWNER owner;
  HAND_VALUE hand_value;
  //additional functionality used by game.cc
  vector<int> high_list;
  int high_pair;
  int low_pair;
public:
  Hand();
  Hand( DeckOfCards a, OWNER o );
  Hand( DeckOfCards a );
  Hand( string test_hand ); //for testing in test_hand.cc
  Hand( OWNER o ); //in game.cc
  HAND_VALUE getHandValue();
  vector<int> getHighest(); 
  int getHighPair();
  int getLowPair(); 
  void setHand( Card arr[5] ); //in game.cc
  void printHand( string s );
  void determine_high_card(); //in hand.cc for game.cc
  void check_list();
  bool pair_check();
  bool two_pair_check();
  bool three_kind_check();
  bool four_kind_check();
  bool flush_check();
  bool straight_check();
  void tradeCard( DeckOfCards &, int ); //in dealer.cc
  void playersTurn( DeckOfCards & ); //in player.cc
};

#endif
