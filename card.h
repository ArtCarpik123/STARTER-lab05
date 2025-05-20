// card.h
// Author: Artem Karpik
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
private:
    char r; // rank
    char s; // suit
    
    // Helper method to convert suit to numeric value for comparison
    int getSuitRank() const {
        switch (s) {
            case 'c': return 1; // clubs
            case 'd': return 2; // diamonds
            case 's': return 3; // spades
            case 'h': return 4; // hearts
            default: return 0;
        }
    }
    
    // Helper method to convert rank to numeric value for comparison
    int getRankValue() const {
        if (r == 'a') return 1;  // ace
        else if (r == 'j') return 11; // jack
        else if (r == 'q') return 12; // queen
        else if (r == 'k') return 13; // king
        else return r - '0'; // numeric 2-10
    }

public:
    Card(char rr = '0', char ss = '0') {
        r = rr;
        s = ss;
    }

    char getRank() const {
        return r;
    }

    char getSuit() const {
        return s;
    }

    // Changed to sort by suit first, then rank (as per assignment requirements)
    bool operator<(const Card& othercard) const {
        if (getSuitRank() != othercard.getSuitRank()) {
            return getSuitRank() < othercard.getSuitRank();
        } else {
            return getRankValue() < othercard.getRankValue();
        }
    }

    bool operator==(const Card& othercard) const {
        return (r == othercard.r && s == othercard.s);
    }
    
    std::string toString() const {
        return std::string(1, s) + " " + std::string(1, r);
    }
};

std::ostream& operator<<(std::ostream& out, const Card& c);

#endif