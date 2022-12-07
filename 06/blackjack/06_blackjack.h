// *** Blackjack.h
#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_ 

// *** Урок 06. Потоки ввода-вывода / I/O Streams

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Card
{
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};           
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
    
    Card(rank r, suit s, bool ifu):  m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {};

    // returns the value of a card, 1 - 11
    int GetValue() const;

    // flips a card; if face up, becomes face down and vice versa
    void Flip();

    // overloading << operator so can send Card object to standard output 
    friend ostream& operator<<(ostream& os, const Card& aCard);

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

class Hand
{
public:
    Hand();
    virtual ~Hand();

    // adds a card to the hand
    void Add(Card* pCard);

    // clears hand of all cards
    void Clear();

    // gets hand total value, intelligently treats aces as 1 or 11
    int GetValue() const;

protected:
    vector<Card*> m_Cards;
};

class GenericPlayer : public Hand
{
public:
    GenericPlayer(const string& name = "") : m_Name(name) {};
    virtual ~GenericPlayer() {};

    // indicates whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;

    // returns whether generic player has busted - has a total greater than 21
    bool IsBusted() const;

    // announces that the generic player busts
    void Bust() const;

    // overloads << operator so a GenericPlayer object can be sent to cout
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

protected:
    string m_Name;
};

/*
 * 3. Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
 *    • virtual bool IsHitting() const -> реализация чисто виртуальной функции базового класса. 
 *      Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false;
 *    • void Win() const  -> выводит на экран имя игрока и сообщение, что он выиграл;
 *    • void Lose() const -> выводит на экран имя игрока и сообщение, что он проиграл;
 *    • void Push() const -> выводит на экран имя игрока и сообщение, что он сыграл вничью.
 */

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) {};
    virtual ~Player() {};

    // returns whether or not the player wants another hit       
    virtual bool IsHitting() const;

    // announces that the player wins
    void Win() const;

    // announces that the player loses
    void Lose() const;

    // announces that the player pushes
    void Push() const;
};

/*
 * 4. Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
 *    • virtual bool IsHitting() const -> метод указывает, нужна ли дилеру еще одна карта. 
 *      Если у дилера не больше 16 очков, то он берет еще одну карту;
 *    • void FlipFirstCard()           -> метод переворачивает первую карту дилера.
 */

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {};
    virtual ~House() {};

    // indicates whether house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;

    // flips over first card
    void FlipFirstCard();
};

class Deck : public Hand
{
public:
    Deck();
    virtual ~Deck();

    //create a standard deck of 52 cards
    void Populate();

    //shuffle cards
    void Shuffle();

    //deal one card to a hand
    void Deal(Hand& aHand);

    //give additional cards to a generic player 
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

class Game
{
public:
    Game(const vector<string>& names);
    ~Game();
    
    //plays the game of blackjack    
    void Play();
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;  
};

/*
 * 5. Написать перегрузку оператора вывода для класса Card. 
 *    Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты. 
 *    Также для класса GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты, 
 *    а также общую сумму очков его карт.
 */

// operator prototypes
ostream& operator << (ostream& os, const Card& aCard);
ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);

#endif // _BLACKJACK_H_