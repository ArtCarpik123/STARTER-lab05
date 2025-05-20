//Artem Karpik
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

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

    CardList alice;
    CardList bob;

    while (getline(cardFile1, line) && !line.empty()) {
        if (line.length() >= 2) {
            char rank = line[0];
            char suit = line[1];
            alice.insert(Card(rank, suit));
        }
    }
    cardFile1.close();

    while (getline(cardFile2, line) && !line.empty()) {
        if (line.length() >= 2) {
            char rank = line[0];
            char suit = line[1];
            bob.insert(Card(rank, suit));
        }
    }
    cardFile2.close();

    playGame(alice, bob);

    return 0;
}
