#include "Deck.h"

Deck::Deck(int idJoueur, int nbCard, std::vector<int>* newPioche, bool turn)
{
    pioche = newPioche;
    isYourTurn = turn;
    cardPlayed = 0;
    for (int i = 0; i < nbCard; i++)
    {
        draw();
    }

}

void Deck::draw(){
    if (!pioche->empty()){
        int card = rand() % pioche->size();
        deck.push_back(pioche->at(card));
        pioche->erase(pioche->begin()+(card-1));
    }
}

std::string Deck::showDeck() const{
    std::string allCards="";
    for (std::vector<int>::const_iterator i = deck.begin(); i != deck.end(); i++)
    {
        allCards += std::to_string(*i) + "\t";
    }
    return allCards+"\n";
}

void Deck::addCard(int numCard, Pile* pile) {

    for (std::vector<int>::iterator i = deck.begin(); i != deck.end(); i++)
    {
        //Verification que la carte existe dans le deck
        if (numCard==*i)
        {
            //Verification si la carte est posable sur le tas
            //Puis mettre dans le tas ou non
            if ((pile->getIsAscendant()==true && (numCard>pile->getLastCard() || numCard==(pile->getLastCard()-10))) ||
                (pile->getIsAscendant()==false && (numCard<pile->getLastCard() || numCard==(pile->getLastCard()+10))) )
            {
                pile->addCard(numCard);
                //supprime la carte du deck
                if(i==deck.end()){
                    deck.erase(deck.begin());
                }
                else{
                    deck.erase(i);
                }
                cardPlayed++;
                break;
            }
            else
            {
                perror("can't add card to this pile");
            }
            
        }
        
    }
}

void Deck::setIsYourTurn(bool turn){
    isYourTurn = turn;
}

bool Deck::getIsYourTurn(){
    return isYourTurn;
}

void Deck::fillDeck(){
    for (int i = 0; i < cardPlayed; i++)
    {
        draw();
    }
    cardPlayed = 0;
}