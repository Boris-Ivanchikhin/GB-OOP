// *** Blackjack.cpp

#include "04_blackjack.h"

using namespace std;

// * class Card

// returns the value of a card, 1 - 11
int Card::GetValue() const {
    // if a cards is face down, its value is 0
    int value = 0;
    if (m_IsFaceUp) {
        // value is number showing on card
        value = m_Rank;
        // value is 10 for face cards
        if (value > 10)
            value = 10;
    }
    return value;
}

void Card::Flip() {
    m_IsFaceUp = !(m_IsFaceUp);
}

Hand::Hand() {
    m_Cards.reserve(7);
}

Hand::~Hand() {
    Clear ();
}

void Hand::Add(Card* pCard) {
    m_Cards.push_back (pCard);
}

// * class Hand

void Hand::Clear() {
    // iterate through vector, freeing all memory on the heap
    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        delete *iter;
        *iter = 0;
    }
    // clear vector of pointers
    m_Cards.clear();
}

int Hand::GetValue() const {
    if (m_Cards.empty()) return 0;
    //if a first card has value of 0, then card is face down; return 0
    if (!m_Cards[0]->GetValue())
        return 0;
    
    //add up card values, treat each Ace as 1
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        total += (*iter)->GetValue();

    //determine if hand contains an Ace
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        if ((*iter)->GetValue() == Card::ACE)
            containsAce = true;

    //if hand contains Ace and total is low enough, treat Ace as 11
    if (containsAce && total <= 11)
        //add only 10 since we've already added 1 for the Ace
        total += 10;   
            
    return total;
}



// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

     // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // * TODO


    // return o.k.
    return EXIT_SUCCESS;
} // main