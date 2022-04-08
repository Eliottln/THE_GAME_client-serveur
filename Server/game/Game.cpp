#include "Game.h"

Game::Game(int nb_joueurs, int nb_cartes, ConnectionPoint* server_, StreamSocket* client)
{
    init(nb_joueurs, nb_cartes, server_, client);
}

void Game::init(int nb_joueurs, int nb_cartes, ConnectionPoint* server_, StreamSocket* client){
    //Création de la partie
    server = server_;

    //Création de la pioche
    for(int i=2; i < 100; i++ ){
        pioche.push_back(i);
    }

    //Création deck
    nbCartes=nb_cartes;
    nbJoueurs=nb_joueurs;
    addPlayer(client);

    //Création des tas
    tas1 = Pile (1,true);
    tas2 = Pile (2,true);
    tas3 = Pile (3,false);
    tas4 = Pile (4,false);
}

//TODO : Quitter une partie
Game::~Game()
{
    map<StreamSocket*,Deck>::iterator itr;
    for (itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
        delete itr->first;
    }
}

// Rejoindre une partie
void Game::addPlayer(StreamSocket* client){
    if (playersTab.size()<nbJoueurs)
    {
        playersTab.insert(pair<StreamSocket*, Deck>(client, Deck(playersTab.size()+1,nbCartes,&pioche)));
        cout<<playersTab.size()<<"\t"<<nbJoueurs<<endl;
        if (playersTab.size()==nbJoueurs)
        {
            startGame();
        }
        else{
            client->send("Waiting player...\n");
        }
    }
    else{
        client->send("Game full\n");
    }
}

void Game::showPile(){
    for (map<StreamSocket*,Deck>::iterator itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
        string pile = to_string(tas1.getLastCard()) + "\t"
                    + to_string(tas2.getLastCard()) + "\t"
                    + to_string(tas3.getLastCard()) + "\t"
                    + to_string(tas4.getLastCard()) + "\n";
        itr->first->send(pile);
    }
}

void Game::startGame(){
    
    for (map<StreamSocket*,Deck>::iterator itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
        itr->first->send(itr->second.showDeck());
    }
}