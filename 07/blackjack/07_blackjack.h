// *** Blackjack.h
#ifndef _BLACKJACK_H_
#define _BLACKJACK_H_ 

// *** Урок 07. Поддержка модульности. Написание игры Blackjack / Modularity support. Writing a Blackjack Game

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

class Card
{
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};           
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};
    
    Card(rank r, suit s, bool ifu = true):  m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {};

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
}; // class Card

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
}; // class Hand

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
}; // class GenericPlayer

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
}; // class Player

class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) {};
    virtual ~House() {};

    // indicates whether house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;

    // flips over first card
    void FlipFirstCard();
}; // class House

/*
 * 3. Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт. 
 *    Класс Deck имеет 4 метода:
 *    • vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора;
 *    • void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle;
 *    • vold Deal (Hand& aHand) - метод, который раздает в руку одну карту;
 *    • void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать.
 *    Обратите внимание на применение полиморфизма.
 */

class Deck : public Hand
{
public:
    Deck();
    virtual ~Deck() {};

    //create a standard deck of 52 cards
    void Populate();

    //shuffle cards
    void Shuffle();

    //deal one card to a hand
    void Deal(Hand& aHand);

    //give additional cards to a generic player 
    void AdditionalCards(GenericPlayer& aGenericPlayer);
}; // class Deck

/*
 * 4. Реализовать класс Game, который представляет собой основной процесс игры. 
 *    У этого класса будет 3 поля:
 *    • колода карт;
 *    • рука дилера;
 *    • вектор игроков.
 *    Конструктор класса принимает в качестве параметра вектор имен игроков и создает объекты самих игроков.
 *    В конструкторе создается колода карт и затем перемешивается.
 *    Также класс имеет один метод play(). В этом методе раздаются каждому игроку по две стартовые карты,
 *    а первая карта дилера прячется. Далее выводится на экран информация о картах каждого игра, в т.ч. и для дилера. 
 *    Затем раздаются игрокам дополнительные карты. Потом показывается первая карта дилера и дилер набирает карты,
 *    если ему надо. После этого выводится сообщение, кто победил, а кто проиграл. 
 *    В конце руки всех игроков очищаются.
 */

class Game
{
public:
    Game(const vector<string>& names);
    ~Game() {};
 
    // plays the game of blackjack    
    void Play();
private:
    Deck m_Deck;
    House m_House;
    vector<Player> m_Players;  
}; // class Game

// operator prototypes
ostream& operator << (ostream& os, const Card& aCard);
ostream& operator << (ostream& os, const GenericPlayer& aGenericPlayer);

#endif // _BLACKJACK_H_