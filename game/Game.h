#include "pile.h"
#include "deck.h"

class Game
{
private:
    int idGame;

    Pile tas1, tas2, tas3, tas4;
    std::vector<int> pioche;
    std::vector<Deck> tabJoueurs;
    int nbCartes, nbJoueurs;
    int socket;
public:
    Game(){}
    Game(int, int);
    ~Game();

    int getNbJoueurs();
    void setSocket(int);
};


Game::Game(int nb_cartes,int nb_joueurs)
{
    //Création de la partie

    //Création de la pioche
    for(int i=2; i < 100; i++ ){
        pioche.push_back(i);
    }

    //Création des tas
    tas1 = Pile (1,true);
    tas2 = Pile (2,true);
    tas3 = Pile (3,false);
    tas4 = Pile (4,false);

    //Création deck
    nbCartes=nb_cartes;
    nbJoueurs=nb_joueurs;
    //Attribution des cartes de la pioche dans les deck des joueurs
    for (int i = 1; i <= nbJoueurs; i++)
    {
        tabJoueurs.push_back(Deck(i,nbCartes,&pioche));
    }
    
}


//TODO : Rejoindre une partie 

//TODO : Quitter une partie 


Game::~Game()
{
}

int Game::getNbJoueurs(){
    return nbJoueurs;
}

void Game::setSocket(int sock){
    socket=sock;
}