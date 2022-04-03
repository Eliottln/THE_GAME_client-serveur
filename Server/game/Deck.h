#include <vector>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include "pile.h"

class Deck
{
private:
    int idJoueur;
    std::vector<int> deck;
    std::vector<int>* pioche;

public:
    Deck(int idJoueur, int nbCard, std::vector<int>* newPioche);
    ~Deck(){}

    void draw();
    void addCard(int numCard, Pile pile);
};
