#include <vector>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include "pile.h"
#include <string>

class Deck
{
private:
    int idJoueur;
    std::vector<int> deck;
    std::vector<int>* pioche;
    bool isYourTurn;
    int cardPlayed;

public:
    Deck(int idJoueur, int nbCard, std::vector<int>* newPioche, bool turn);
    ~Deck(){}

    void draw();
    std::string showDeck() const;
    void addCard(int numCard, Pile* pile) ;
    void setIsYourTurn(bool turn);
    bool getIsYourTurn();
    void fillDeck();
};
