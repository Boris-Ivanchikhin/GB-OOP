// *** Урок 03. Виртуальные функции и полиморфизм / Virtual functions and polymorphism

/*
 * 4. Создать класс Card, описывающий карту в игре БлэкДжек. 
 *    У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой). 
 *    Сделать поля масть и значение карты типом перечисления (enum). Положение карты - тип bool. 
 *    Также в этом классе должно быть два метода:
 *    a. метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот;
 *    б. метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.
 */

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

    //flips a card; if face up, becomes face down and vice versa
    void Flip();
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

    //adds a card to the hand
    void Add(Card* pCard);

    //clears hand of all cards
    void Clear();

    //gets hand total value, intelligently treats aces as 1 or 11
    int GetTotal() const;
protected:
    vector<Card*> m_Cards;
};

class GenericPlayer : public Hand
{
public:
    GenericPlayer(const string& name = "");
    virtual ~GenericPlayer();

    //indicates whether or not generic player wants to keep hitting
    virtual bool IsHitting() const = 0;

    //returns whether generic player has busted - has a total greater than 21
    bool IsBusted() const;

    //announces that the generic player busts
    void Bust() const;
protected:
    string m_Name;
};

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");
    virtual ~Player();

    //returns whether or not the player wants another hit       
    virtual bool IsHitting() const;

    //announces that the player wins
    void Win() const;

    //announces that the player loses
    void Lose() const;

    //announces that the player pushes
    void Push() const;
};

class House : public GenericPlayer
{
public:
    House(const string& name = "House");
    virtual ~House();

    //indicates whether house is hitting - will always hit on 16 or less
    virtual bool IsHitting() const;

    //flips over first card
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