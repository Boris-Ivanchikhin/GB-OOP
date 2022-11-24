// * Blackjack.cpp

#include "03_blackjack.h"

using namespace std;

// * class Card


// returns the value of a card, 1 - 11
int Card::GetValue() const
{
    //if a cards is face down, its value is 0
    int value = 0;
    if (m_IsFaceUp)
    {
        //value is number showing on card
        value = m_Rank;
        //value is 10 for face cards
        if (value > 10)
            value = 10;
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}

