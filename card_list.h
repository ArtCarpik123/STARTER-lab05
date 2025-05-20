// card_list.h
// Author: Artem Karpik
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardList {
private: 
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node(const Card& c): card(c), left(nullptr), right(nullptr) {}

    };

    Node* root;

    void destroy(Node*node);
    Node* copy(Node* node);
    Node* insert(Node* node, const Card& c);
    Node* remove(Node* node, const Card& c, bool& removed);
    Node* findMin(Node* node);
    void inorderPrint(Node* node);

    public:
    CardList();
    CardList(const CardList& other);
    ~CardList();

    CardList& operator=(const CardList& other);

    void insert(const Card& c);
    bool remove(const Card& c);
    bool contains(const Card& c);
    void print();
};


#endif
