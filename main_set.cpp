// main_set.cpp
// Feb 14: This file implements the game using std::set container class
// Does NOT include card_list.h

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

// Function to play the game with std::set<Card>
void playGame(set<Card>& alice, set<Card>& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;

        for (const Card& aliceCard : alice) {
            if (bob.find(aliceCard) != bob.end()) {
                matchFound = true;
                cout << "Alice picked matching card " << aliceCard << endl;

                alice.erase(aliceCard);
                bob.erase(aliceCard);
                break;
            }
        }

        if (!matchFound) {
            break;
        }

        matchFound = false;

        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
            const Card& bobCard = *it;

            if (alice.find(bobCard) != alice.end()) {
                matchFound = true;
                cout << "Bob picked matching card " << bobCard << endl;

                alice.erase(bobCard);
                bob.erase(bobCard);
                break;
            }
        }
    }

    cout << "\nAlice's cards:" << endl;
    for (const Card& c : alice) {
        cout << c << endl;
    }

    cout << "Bob's cards:" << endl;
    for (const Card& c : bob) {
        cout << c << endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    set<Card> alice;
    set<Card> bob;

    while (getline(cardFile1, line) && (line.length() > 0)) {
        if (line.length() >= 3) {
            char suit = line[0];
            char rank;
            if (line.length() >= 4 && line[2] == '1' && line[3] == '0') {
                rank = 't';
            }
            else {
                rank = line[2];
            }
            Card card(rank, suit);
            alice.insert(card);
        }
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        if (line.length() >= 3) {
            char suit = line[0];
            char rank;
            if (line.length() >= 4 && line[2] == '1' && line[3] == '0') {
                rank = 't';
            }
            else {
                rank = line[2];
            }
            Card card(rank, suit);
            bob.insert(card);
        }
    }
    cardFile2.close();

    playGame(alice, bob);

    return 0;
}