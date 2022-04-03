#include "Deck.h"

Deck::Deck(int idJoueur, int nbCard, std::vector<int>* newPioche)
{
    pioche = newPioche;
    for (int i = 0; i < nbCard; i++)
    {
        draw();
    }

}

void Deck::draw(){
    int card = rand() % pioche->size();
    deck.push_back(pioche->at(card));
    pioche->erase(pioche->begin()+(card-1));
}

void Deck::addCard(int numCard, Pile pile){

    
    for (std::vector<int>::iterator i = deck.begin(); i != deck.end(); i++)
    {
        //Verification que la carte existe dans le deck
        if (numCard==*i)
        {
            //Verification si la carte est posable sur le tas
            //Puis mettre dans le tas ou non
            if (pile.getIsAscendant()==true && (numCard>pile.getLastCard() || numCard==(pile.getLastCard()-10)))
            {
                pile.addCard(numCard);
            }
            else if (pile.getIsAscendant()==false && (numCard<pile.getLastCard() || numCard==(pile.getLastCard()+10)))
            {
                pile.addCard(numCard);
            }
            else
            {
                perror("can't add card to this pile");
            }
            
            //supprime la carte du deck
            deck.erase(i);

        }

    }
    
    //Piocher une nouvelle carte
    draw();
    
}