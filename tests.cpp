#include <iostream>
#include <string>
#include <cassert>
#include "card.h"
#include "card_list.h"

void testCardComparison() {
    std::cout << "Card comparison...\n";
    
    Card c1('a', 'c');
    Card c2('a', 'd');
    Card c3('a', 's');
    Card c4('a', 'h');
    
    assert(c1 < c2);
    assert(c2 < c3);
    assert(c3 < c4);
    
    Card c5('a', 'c');
    Card c6('2', 'c');
    Card c7('k', 'c');
    
    assert(c5 < c6);
    assert(c6 < c7);
    
    Card c8('q', 'h');
    Card c9('q', 'h');
    
    assert(c8 == c9);
    assert(!(c1 == c2));
    
    std::cout << "Card comparison tests passed!\n";
}

void testBSTInsert() {
    std::cout << "BST insert...\n";
    CardList bst;
    
    Card c1('a', 'c');
    bst.insert(c1);
    assert(bst.contains(c1));
    
    Card c2('k', 'h');
    Card c3('3', 's');
    Card c4('j', 'd');
    Card c5('7', 'c');
    
    bst.insert(c2);
    bst.insert(c3);
    bst.insert(c4);
    bst.insert(c5);
    
    assert(bst.contains(c2));
    assert(bst.contains(c3));
    assert(bst.contains(c4));
    assert(bst.contains(c5));
    
    Card c6('9', 'h');
    assert(!bst.contains(c6));
    
    std::cout << "Tests passed!\n";
}

void testBSTRemove() {
    std::cout << "Testing BST remove...\n";
    CardList bst;
    
    Card c1('a', 'c');
    Card c2('k', 'h');
    Card c3('3', 's');
    Card c4('j', 'd');
    Card c5('7', 'c');
    
    bst.insert(c1);
    bst.insert(c2);
    bst.insert(c3);
    bst.insert(c4);
    bst.insert(c5);
    
    assert(bst.remove(c3));
    assert(!bst.contains(c3));
    
    bst.insert(c3);
    bst.insert(Card('4', 's'));
    assert(bst.remove(c3));
    assert(!bst.contains(c3));
    assert(bst.contains(Card('4', 's')));
    
    CardList bst2;
    Card root('5', 'd');
    Card left('2', 'd');
    Card right('8', 'd');
    
    bst2.insert(root);
    bst2.insert(left);
    bst2.insert(right);
    
    assert(bst2.remove(root));
    assert(!bst2.contains(root));
    assert(bst2.contains(left));
    assert(bst2.contains(right));
    
    Card noCard('9', 'h');
    assert(!bst.remove(noCard));
    
    std::cout << "Tests passed!\n";
}

void testBSTContains() {
    std::cout << "BST contains...\n";
    CardList bst;
    
    Card c1('a', 'c');
    assert(!bst.contains(c1));
    
    bst.insert(c1);
    assert(bst.contains(c1));
    
    Card c2('k', 'h');
    Card c3('3', 's');
    Card c4('j', 'd');
    Card c5('7', 'c');
    
    bst.insert(c2);
    bst.insert(c3);
    bst.insert(c4);
    bst.insert(c5);
    
    assert(bst.contains(c2));
    assert(bst.contains(c3));
    assert(bst.contains(c4));
    assert(bst.contains(c5));
    
    Card c6('9', 'h');
    assert(!bst.contains(c6));
    
    std::cout << "Tests passed!\n";
}

void testBSTIterators() {
    std::cout << "BST iterators...\n";
    CardList bst;
    
    assert(bst.begin() == bst.end());
    assert(bst.rbegin() == bst.rend());
    
    bst.insert(Card('j', 'h'));
    bst.insert(Card('3', 's'));
    bst.insert(Card('a', 'c'));
    bst.insert(Card('k', 'd'));
    bst.insert(Card('7', 'h'));
    
    CardList::Iterator it = bst.begin();
    assert((*it).toString() == "c a");
    ++it;
    assert((*it).toString() == "s 3");
    ++it;
    assert((*it).toString() == "d k");
    ++it;
    assert((*it).toString() == "h 7");
    ++it;
    assert((*it).toString() == "h j");
    ++it;
    assert(it == bst.end());
    
    CardList::Iterator rit = bst.rbegin();
    assert((*rit).toString() == "h j");
    --rit;
    assert((*rit).toString() == "h 7");
    --rit;
    assert((*rit).toString() == "d k");
    --rit;
    assert((*rit).toString() == "s 3");
    --rit;
    assert((*rit).toString() == "c a");
    --rit;
    assert(rit == bst.rend());
    
    CardList::Iterator it2 = bst.begin();
    CardList::Iterator it3 = bst.begin();
    assert(it2 == it3);
    ++it3;
    assert(it2 != it3);
    
    std::cout << "Tests passed!\n";
}

void testPlayGame() {
    std::cout << "playGame function...\n";
    
    CardList alice1, bob1;
    alice1.insert(Card('3', 'h'));
    alice1.insert(Card('a', 'c'));
    alice1.insert(Card('5', 's'));
    bob1.insert(Card('a', 'c'));
    bob1.insert(Card('j', 'd'));
    
    std::cout << "Test 1: common cards\n";
    playGame(alice1, bob1);
    
    CardList alice2, bob2;
    bob2.insert(Card('3', 'h'));
    bob2.insert(Card('a', 'c'));
    
    std::cout << "\nTest 2: one empty hand\n";
    playGame(alice2, bob2);
    
    CardList alice3, bob3;
    alice3.insert(Card('3', 'h'));
    alice3.insert(Card('a', 'c'));
    bob3.insert(Card('5', 's'));
    bob3.insert(Card('j', 'd'));
    
    std::cout << "\nTest 3: no common cards\n";
    playGame(alice3, bob3);
    
    std::cout << "playGame tests done.\n";
}

int main() {
    testCardComparison();
    testBSTInsert();
    testBSTRemove();
    testBSTContains();
    testBSTIterators();
    testPlayGame();
    
    std::cout << "All tests passed!\n";
    return 0;
}
