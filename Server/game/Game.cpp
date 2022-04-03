#include "Game.h"

void reader(StreamSocket* client){
    while (true) {
        string msg;
        int nb=client->read(msg); // bloque la boucle en attendant un msg d'un client

        if(nb > 0){
            // message recu avec nb caracteres
            cout << "Client: \t"<< msg << endl;
        }else{
            // client n'existe plus, on sort
            printf("[-]Client deconnection.\n");
            break;
        }
    }
}

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
    // playersTab.insert(pair<StreamSocket*, Deck>(client, Deck(1,nbCartes,&pioche)));

    //Création des tas
    tas1 = Pile (1,true);
    tas2 = Pile (2,true);
    tas3 = Pile (3,false);
    tas4 = Pile (4,false);


    //Attribution des cartes de la pioche dans les deck des joueurs
    // for (int i = 1; i <= nbJoueurs; i++)
    // {
    //     tabJoueurs.push_back(Deck(i,nbCartes,&pioche));
    // }
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
            map<StreamSocket*,Deck>::iterator itr;
            for (itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
                itr->first->send("1\t1\t100\t100");
            }
        }
        else{
            client->send("Waiting player...");
        }
    }
    else{
        client->send("Game full");
    }
}


int Game::getNbJoueurs(){
    return nbJoueurs;
}