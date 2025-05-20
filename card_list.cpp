#include "card_list.h"
#include <iostream>

CardList::CardList() : root(nullptr) {}

CardList::CardList(const CardList& other) : root(nullptr) {
    root = copy(other.root);
}

CardList::~CardList() {
    destroy(root);
}

CardList& CardList::operator=(const CardList& other) {
    if (this != &other) {
        destroy(root);
        root = copy(other.root);
    }
    return *this;
}

CardList::Node* CardList::copy(Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->card);
    newNode->left = copy(node->left);
    if (newNode->left) newNode->left->parent = newNode;
    newNode->right = copy(node->right);
    if (newNode->right) newNode->right->parent = newNode;

    return newNode;
}

void CardList::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void CardList::insert(const Card& c) {
    if (!root) {
        root = new Node(c);
    } else {
        root = insert(root, c);
        root->parent = nullptr;
    }
}

CardList::Node* CardList::insert(Node* node, const Card& c) {
    if (!node) return new Node(c);

    if (c < node->card) {
        node->left = insert(node->left, c);
        node->left->parent = node;
    } else if (node->card < c) {
        node->right = insert(node->right, c);
        node->right->parent = node;
    }
    return node;
}

bool CardList::remove(const Card& c) {
    bool removed = false;
    root = remove(root, c, removed);
    if (root) root->parent = nullptr;
    return removed;
}

CardList::Node* CardList::remove(Node* node, const Card& c, bool& removed) {
    if (!node) return nullptr;

    if (c < node->card) {
        node->left = remove(node->left, c, removed);
        if (node->left) node->left->parent = node;
    } else if (node->card < c) {
        node->right = remove(node->right, c, removed);
        if (node->right) node->right->parent = node;
    } else {
        removed = true;
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        } else if (!node->left) {
            Node* temp = node->right;
            temp->parent = node->parent;
            delete node;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            temp->parent = node->parent;
            delete node;
            return temp;
        } else {
            Node* succ = findMin(node->right);
            node->card = succ->card;
            node->right = remove(node->right, succ->card, removed);
            if (node->right) node->right->parent = node;
        }
    }
    return node;
}

CardList::Node* CardList::findMin(Node* node) {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

CardList::Node* CardList::findMax(Node* node) const {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

bool CardList::contains(const Card& c) const {
    Node* cur = root;
    while (cur) {
        if (c < cur->card) cur = cur->left;
        else if (cur->card < c) cur = cur->right;
        else return true;
    }
    return false;
}

void CardList::print() {
    inorderPrint(root);
    std::cout << std::endl;
}

void CardList::inorderPrint(Node* node) {
    if (!node) return;
    inorderPrint(node->left);
    std::cout << node->card << std::endl;
    inorderPrint(node->right);
}

CardList::Node* CardList::getSuccessorNode(Node* node) const {
    if (!node) return nullptr;

    if (node->right) return findMin(node->right);

    Node* p = node->parent;
    while (p && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}

CardList::Node* CardList::getPredecessorNode(Node* node) const {
    if (!node) return nullptr;

    if (node->left) return findMax(node->left);

    Node* p = node->parent;
    while (p && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p;
}

CardList::Iterator::Iterator(Node* n, const CardList* list, bool reverse)
    : current(n), tree(list), reverse(reverse) {}

CardList::Iterator& CardList::Iterator::operator++() {
    if (!reverse) current = tree->getSuccessorNode(current);
    else current = tree->getPredecessorNode(current);
    return *this;
}

CardList::Iterator CardList::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

CardList::Iterator& CardList::Iterator::operator--() {
    if (!reverse) {
        if (!current) current = tree->findMax(tree->root);
        else current = tree->getPredecessorNode(current);
    } else {
        if (!current) current = tree->findMin(tree->root);
        else current = tree->getSuccessorNode(current);
    }
    return *this;
}

CardList::Iterator CardList::Iterator::operator--(int) {
    Iterator tmp = *this;
    --(*this);
    return tmp;
}

const Card& CardList::Iterator::operator*() const {
    return current->card;
}

const Card* CardList::Iterator::operator->() const {
    return &(current->card);
}

bool CardList::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool CardList::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

CardList::Iterator CardList::begin() const {
    return Iterator(findMin(root), this, false);
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr, this, false);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(findMax(root), this, true);
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr, this, true);
}

void playGame(CardList& alice, CardList& bob) {
    bool matchFound = true;

    while (matchFound) {
        matchFound = false;

        for (CardList::Iterator it = alice.begin(); it != alice.end(); ++it) {
            const Card& aliceCard = *it;
            if (bob.contains(aliceCard)) {
                matchFound = true;
                std::cout << "Alice picked matching card " << aliceCard << std::endl;
                alice.remove(aliceCard);
                bob.remove(aliceCard);
                break;
            }
        }

        if (!matchFound) break;

        matchFound = false;

        for (CardList::Iterator it = bob.rbegin(); it != bob.rend(); --it) {
            const Card& bobCard = *it;
            if (alice.contains(bobCard)) {
                matchFound = true;
                std::cout << "Bob picked matching card " << bobCard << std::endl;
                alice.remove(bobCard);
                bob.remove(bobCard);
                break;
            }
        }
    }

    std::cout << "\nAlice's cards:" << std::endl;
    alice.print();

    std::cout << "Bob's cards:" << std::endl;
    bob.print();
}
