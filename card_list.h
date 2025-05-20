#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class CardList {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Card& c) : card(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void destroy(Node* node);
    Node* copy(Node* node);
    Node* insert(Node* node, const Card& c);
    Node* remove(Node* node, const Card& c, bool& removed);

    Node* findMin(Node* node);
    Node* findMax(Node* node) const;
    void inorderPrint(Node* node) const;

    Node* getSuccessorNode(Node* node) const;
    Node* getPredecessorNode(Node* node) const;

public:
    class Iterator {
    private:
        Node* current;
        const CardList* tree;
        bool reverse;

    public:
        Iterator(Node* node, const CardList* t, bool rev = false)
            : current(node), tree(t), reverse(rev) {}

        const Card& operator*() const {
            return current->card;
        }

        const Card* operator->() const {
            return &(current->card);
        }

        Iterator& operator++() {
            if (reverse) {
                current = tree->getPredecessorNode(current);
            } else {
                current = tree->getSuccessorNode(current);
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            if (reverse) {
                current = tree->getSuccessorNode(current);
            } else {
                current = tree->getPredecessorNode(current);
            }
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    CardList();
    CardList(const CardList& other);
    ~CardList();

    CardList& operator=(const CardList& other);

    void insert(const Card& c);
    bool remove(const Card& c);
    bool contains(const Card& c) const;
    void print() const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

void playGame(CardList& alice, CardList& bob);

#endif
