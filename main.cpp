// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
// Do not include set in this file

using namespace std;

int main(int argv, char** argc) {
  if (argv < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << argc[2] << endl;
    return 1;
  }

  CardList player1;
  CardList player2;

  while (getline(cardFile1, line) && !line.empty()) {
    string suit = line.substr(0, 1);
    string rank = line.substr(1);
    Card c(suit, rank);
    player1.insert(c);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && !line.empty()) {
    string suit = line.substr(0, 1);
    string rank = line.substr(1);
    Card c(suit, rank);
    player2.insert(c);
  }
  cardFile2.close();

  CardList::iterator it = player1.begin();
  while (it != player1.end()) {
    if (player2.find(*it)) {
      cout << "Alice picked matching card " << it->toString() << endl;
      player2.erase(*it);
      it = player1.erase(it);
    } else {
      ++it;  // increment properly
    }
  }

  CardList::reverse_iterator rit = player2.rbegin();
  while (rit != player2.rend()) {
    if (player1.find(*rit)) {
      cout << "Bob picked matching card " << rit->toString() << endl;
      player1.erase(*rit);

      // Erase element correctly with reverse iterator
      auto baseIt = rit.base();
      --baseIt;
      baseIt = player2.erase(baseIt);
      rit = CardList::reverse_iterator(baseIt);
    } else {
      ++rit;
    }
  }

  cout << endl << "Alice's remaining cards:" << endl;
  for (CardList::iterator it2 = player1.begin(); it2 != player1.end(); ++it2) {
    cout << it2->toString() << endl;
  }

  cout << endl << "Bob's remaining cards:" << endl;
  for (CardList::iterator it2 = player2.begin(); it2 != player2.end(); ++it2) {
    cout << it2->toString() << endl;
  }

  return 0;
}
