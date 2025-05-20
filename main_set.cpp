// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream file1(argc[1]);
  ifstream file2(argc[2]);
  string line;

  if (file1.fail() || file2.fail()){
    cout << "Could not open file " << argc[2] << endl;
    return 1;
  }

  set<Card> p1cards;
  set<Card> p2cards;

  while (getline(file1, line) && (line.length() > 0)) {
    string suit = line.substr(0,1);
    string rank = line.substr(1);
    p1cards.insert(Card(suit, rank));
  }
  file1.close();

  while (getline(file2, line) && (line.length() > 0)) {
    string suit = line.substr(0,1);
    string rank = line.substr(1);
    p2cards.insert(Card(suit, rank));
  }
  file2.close();

  set<Card>::iterator it1 = p1cards.begin();
  while (it1 != p1cards.end()) {
    if (p2cards.find(*it1) != p2cards.end()) {
      cout << "Alice picked matching card " << it1->toString() << endl;
      p2cards.erase(*it1);
      it1 = p1cards.erase(it1);
    } else {
      ++it1;
    }
  }

  set<Card>::reverse_iterator rit2 = p2cards.rbegin();
  while (rit2 != p2cards.rend()) {
    if (p1cards.find(*rit2) != p1cards.end()) {
      cout << "Bob picked matching card " << rit2->toString() << endl;
      p1cards.erase(*rit2);
      rit2 = set<Card>::reverse_iterator(p2cards.erase(next(rit2).base()));
    } else {
      ++rit2;
    }
  }

  cout << endl << "Alice's remaining cards:" << endl;
  for (set<Card>::iterator it = p1cards.begin(); it != p1cards.end(); it++) {
    cout << it->toString() << endl;
  }

  cout << endl << "Bob's remaining cards:" << endl;
  for (set<Card>::iterator it = p2cards.begin(); it != p2cards.end(); it++) {
    cout << it->toString() << endl;
  }

  return 0;
}
