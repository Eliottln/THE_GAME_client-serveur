#include "Game.h"

Game::Game(int nb_joueurs, int nb_cartes, StreamSocket* client)
{
    init(nb_joueurs, nb_cartes, client);
}

void Game::init(int nb_joueurs, int nb_cartes, StreamSocket* client){
    //Création de la partie
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
    unordered_map<StreamSocket*,Deck>::iterator itr;
    for (itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
        delete itr->first;
    }
}

// Rejoindre une partie
void Game::addPlayer(StreamSocket* client){
    if (playersTab.size()<nbJoueurs)
    {
        if (playersTab.empty())
            playersTab.insert(pair<StreamSocket*, Deck>(client, Deck(playersTab.size()+1,nbCartes,&pioche,true)));
        else
            playersTab.insert(pair<StreamSocket*, Deck>(client, Deck(playersTab.size()+1,nbCartes,&pioche,false)));
        cout<<playersTab.size()<<"\t"<<nbJoueurs<<endl;
        if (playersTab.size()==nbJoueurs)
        {
            sendState();
            // unordered_map<StreamSocket*,Deck>::iterator itr = playersTab.end();
            // auto pv = std::prev(itr, 1);
            // pv->second.setIsYourTurn(true);
        }
        else{
            client->send("Waiting player...\n");
            // unordered_map<StreamSocket*,Deck>::iterator itr = playersTab.end();
            // auto pv = std::prev(itr, 1);
            // pv->second.setIsYourTurn(false);
        }
        // string message = playersTab.cend()->second.showDeck();
        // client->send(message);
    }
    else{
        client->send("Game full\n");
    }
}

string Game::showPile(){
    string pile = to_string(tas1.getLastCard()) + "\t"
                + to_string(tas2.getLastCard()) + "\t"
                + to_string(tas3.getLastCard()) + "\t"
                + to_string(tas4.getLastCard()) + "\n";
        
    return pile;    
}

void Game::sendState(){
    string pile = showPile();
    for (unordered_map<StreamSocket*,Deck>::iterator itr = playersTab.begin(); itr != playersTab.end(); ++itr) {
        itr->first->send(pile);
        itr->first->send(itr->second.showDeck());
    }
}

void Game::playCard(StreamSocket* client, int idCard, int idPile){
    std::unordered_map<StreamSocket*,Deck>::iterator got = playersTab.find(client);

    if ( got == playersTab.end() )
        std::cout << "Player not found";
    else{
        switch (idPile)
        {
        case 1:
            got->second.addCard(idCard,&tas1);
            break;
        case 2:
            got->second.addCard(idCard,&tas2);
            break;
        case 3:
            got->second.addCard(idCard,&tas3);
            break;
        case 4:
            got->second.addCard(idCard,&tas4);
            break;
        default:
            break;
        }
    }
}

bool Game::testTurn(StreamSocket* client){

    unordered_map<StreamSocket*,Deck>::iterator itr = playersTab.begin();

    while (itr != playersTab.end()) {
        
        if (itr->first == client && itr->second.getIsYourTurn() == true)
        {
            return true;
        }
        
        ++itr;
    }
    client->send("Pas votre tour\n");
    return false;
}

void Game::nextTurn(StreamSocket* client){

    unordered_map<StreamSocket*,Deck>::iterator itr = playersTab.begin();

    while (itr != playersTab.end()) {
        
        if (itr->second.getIsYourTurn() == true)
        {
            itr->second.setIsYourTurn(false);
            itr->first->send("Fin de tour\n");
            ++itr;

            if (itr == playersTab.end())
            {
                itr = playersTab.begin();
                itr->second.setIsYourTurn(true);
            }
            itr->second.setIsYourTurn(true);
            break;
        }
        
        ++itr;
    }
    if (itr == playersTab.end())
    {
        itr = playersTab.begin();
        itr->second.setIsYourTurn(true);

    }
    
    itr->first->send("Votre tour\n");
}