// *** Blackjack.cpp

#include "06_blackjack.h"

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

// * class Hand

Hand::Hand() {
    m_Cards.reserve(7);
}

Hand::~Hand() {
    Clear ();
}

void Hand::Add(Card* pCard) {
    m_Cards.push_back (pCard);
}

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
    // if a first card has value of 0, then card is face down; return 0
    if (!m_Cards[0]->GetValue())
        return 0;
    
    // add up card values, treat each Ace as 1
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        total += (*iter)->GetValue();

    // determine if hand contains an Ace
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
        if ((*iter)->GetValue() == Card::ACE)
            containsAce = true;

    // if hand contains Ace and total is low enough, treat Ace as 11
    if (containsAce && total <= 11)
        // add only 10 since we've already added 1 for the Ace
        total += 10;   

    // return        
    return total;
}

// * class GenericPlayer

bool GenericPlayer::IsBusted() const { 
    return (GetValue() > 21);
}

void GenericPlayer::Bust() const {
    cout << m_Name << " busts.\n";
}

// * class Player

bool Player::IsHitting() const {
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const {
    cout << m_Name <<  " wins.\n";
}

void Player::Lose() const {
    cout << m_Name <<  " loses.\n";
}

void Player::Push() const {
    cout << m_Name <<  " pushes.\n";
}

// * class House

bool House::IsHitting() const {
    return (GetValue() <= 16);
}   

void House::FlipFirstCard() {
    if (!(m_Cards.empty()))
        m_Cards[0]->Flip();
    else 
        cout << "No card to flip!\n";
}




// * overloads << operator so Card object can be sent to cout
ostream& operator << (ostream& os, const Card& aCard) {
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const string SUITS[] = {"c", "d", "h", "s"};

    if (aCard.m_IsFaceUp)
        os << RANKS[aCard.m_Rank] << SUITS[aCard.m_Suit];
    else
        os << "XX";
    // return
    return os;
}

// * overloads << operator so a GenericPlayer object can be sent to cout
ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer) {
    os << aGenericPlayer.m_Name << ":\t";
    
    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty()) {
        for (pCard = aGenericPlayer.m_Cards.begin(); pCard != aGenericPlayer.m_Cards.end(); ++pCard)
            os << *(*pCard) << "\t";
        if (aGenericPlayer.GetValue() != 0)
            cout << "(" << aGenericPlayer.GetValue() << ")";
    } else
        os << "<empty>";
    // return
    return os;
}




// * MAIN

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe Game is Over!");
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