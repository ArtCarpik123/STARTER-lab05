#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class Card {
public:
    char suit;
    char rank;

    // Constructor expects chars, not strings
    Card(char s, char r) : suit(s), rank(r) {}
};

class CardList {
public:
    std::list<Card> cards;

    using iterator = std::list<Card>::iterator;
    using const_iterator = std::list<Card>::const_iterator;

    iterator begin() { return cards.begin(); }
    iterator end() { return cards.end(); }
    const_iterator begin() const { return cards.begin(); }
    const_iterator end() const { return cards.end(); }

    void push_back(const Card& card) { cards.push_back(card); }

    iterator find(const Card& card) {
        return std::find_if(cards.begin(), cards.end(), [&](const Card& c) {
            return c.suit == card.suit && c.rank == card.rank;
        });
    }

    void erase(iterator it) { cards.erase(it); }
};

int main() {
    CardList myCards;

    std::string suit = "H";  // Example input
    std::string rank = "A";

    // Pass chars, not strings
    myCards.push_back(Card(suit[0], rank[0]));

    auto it = myCards.find(Card(suit[0], rank[0]));
    if (it != myCards.end()) {
        myCards.erase(it);
    }

    for (auto& card : myCards) {
        std::cout << card.suit << card.rank << std::endl;
    }

    return 0;
}
