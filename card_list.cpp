// card_list.cpp
// Implementation of CardList class for a BST-based card game
// Author: Artem Karpik

#include "card_list.h"
#include <iostream>


CardList::CardList() : root(nullptr) {
}


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
    if (node == nullptr) {
        return nullptr;
    }
    
    Node* newNode = new Node(node->card);
    newNode->left = copy(node->left);
    if (newNode->left) newNode->left->parent = newNode;
    
    newNode->right = copy(node->right);
    if (newNode->right) newNode->right->parent = newNode;
    
    return newNode;
}


void CardList::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    
    destroy(node->left);
    destroy(node->right);
    delete node;
}


void CardList::insert(const Card& c) {
    if (root == nullptr) {
        root = new Node(c);
    } else {
        root = insert(root, c);
    }
}


CardList::Node* CardList::insert(Node* node, const Card& c) {
    if (node == nullptr) {
        return new Node(c);
    }
    
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
    return removed;
}


CardList::Node* CardList::remove(Node* node, const Card& c, bool& removed) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (c < node->card) {
        node->left = remove(node->left, c, removed);
        if (node->left) node->left->parent = node;
    } else if (node->card < c) {
        node->right = remove(node->right, c, removed);
        if (node->right) node->right->parent = node;
    } else {
        
        removed = true;
        
        
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        else {
            
            Node* successor = findMin(node->right);
            node->card = successor->card;
          
            node->right = remove(node->right, successor->card, removed);
            if (node->right) node->right->parent = node;
        }
    }
    
    return node;
}


CardList::Node* CardList::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}


CardList::Node* CardList::findMax(Node* node) const {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}


bool CardList::contains(const Card& c) const {
    Node* current = root;
    
    while (current) {
        if (c < current->card) {
            current = current->left;
        } else if (current->card < c) {
            current = current->right;
        } else {
            return true; 
        }
    }
    
    return false; 
}

void CardList::print() {
    inorderPrint(root);
    std::cout << std::endl;
}


void CardList::inorderPrint(Node* node) {
    if (node == nullptr) {
        return;
    }
    
    inorderPrint(node->left);
    std::cout << node->card << std::endl;
    inorderPrint(node->right);
}

// Get the successor node for a given node
CardList::Node* CardList::getSuccessorNode(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    // If right subtree exists, successor is the leftmost node in right subtree
    if (node->right != nullptr) {
        return findMin(node->right);
    }
    
    // Otherwise, go up until we find a parent whose left child contains our node
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    
    return parent;
}

// Get the predecessor node for a given node
CardList::Node* CardList::getPredecessorNode(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    
    // If left subtree exists, predecessor is the rightmost node in left subtree
    if (node->left != nullptr) {
        return findMax(node->left);
    }
    
    // Otherwise, go up until we find a parent whose right child contains our node
    Node* parent = node->parent;
    while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    
    return parent;
}

// Iterator methods

// Begin iterator (points to smallest card)
CardList::Iterator CardList::begin() const {
    return Iterator(findMin(root), this);
}

// End iterator (points to nullptr)
CardList::Iterator CardList::end() const {
    return Iterator(nullptr, this);
}

// Reverse begin iterator (points to largest card)
CardList::Iterator CardList::rbegin() const {
    return Iterator(findMax(root), this, true);
}

// Reverse end iterator (points to nullptr)
CardList::Iterator CardList::rend() const {
    return Iterator(nullptr, this, true);
}

// Game logic implementation
void playGame(CardList& alice, CardList& bob) {
    bool matchFound = true;
    
    // Continue until no matching cards are found
    while (matchFound) {
        matchFound = false;
        
        // Alice's turn - checks cards in ascending order
        for (CardList::Iterator it = alice.begin(); it != alice.end(); ++it) {
            const Card& aliceCard = *it;
            
            // If Bob has the same card
            if (bob.contains(aliceCard)) {
                matchFound = true;
                std::cout << "Alice picked matching card " << aliceCard << std::endl;
                
                // Remove the matching card from both hands
                alice.remove(aliceCard);
                bob.remove(aliceCard);
                break;
            }
        }
        
        if (!matchFound) {
            break;  // No match found, game over
        }
        
        matchFound = false;
        
        // Bob's turn - checks cards in descending order
        for (CardList::Iterator it = bob.rbegin(); it != bob.rend(); --it) {
            const Card& bobCard = *it;
            
            // If Alice has the same card
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