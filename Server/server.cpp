#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <ctime>
#include <clocale>
#include "../socket.h"
#include "game/Game.h"

using namespace std;
using namespace stdsock;

Game game;

void reader(StreamSocket* client, ConnectionPoint* server){
    while (true) {
        string msg;
        int nb=client->read(msg); // bloque la boucle en attendant un msg d'un client

        if(nb > 0){
            // message recu avec nb caracteres
            cout << "Client: \t"<< msg << endl;
            // creation partie
            if (msg == "MAKE")
            {
                try{
                    string player;
                    // client->send(player);
                    // player.clear();
                    client->read(player);
                    int nbPlayer = stoi(player);
                    cout<<"Le jeu sera composé de "<<nbPlayer<<" joueur(s)"<<endl;

                    string cards;
                    // client->send(cards);
                    // cards.clear();
                    client->read(cards);
                    int nbCards = stoi(cards);
                    cout<<"Les joueurs auront "<<nbCards<<" cartes"<<endl;

                    game.init(nbPlayer,nbCards,client);
                }
                catch(exception& e){
                    cout<<e.what()<<endl;
                }

            }
            else if (msg == "JOIN")
            {
                game.addPlayer(client);
            }
            else if (msg == "PILE")
            {
                try{
                    if(game.testTurn(client)){

                        string card;
                        client->read(card);
                        int idCard;
                        int idPile;
                        
                        string word="";
                        for (auto x : card) 
                        {
                            if (x == '-')
                            {
                                idCard = stoi(word);
                                word = "";
                            }
                            else {
                                word = word + x;
                            }
                        }
                        idPile = stoi(word);

                        cout<<"Carte "<<idCard<<endl;                    
                        cout<<"Pile "<<idPile<<endl;
                        game.playCard(client,idCard,idPile);
                        game.sendState("\n");
                    }
                }
                catch(exception& e){
                    cout<<e.what()<<endl;
                }
            }
            else if (msg == "SKIP" && game.testTurn(client))
            {
                game.nextTurn(client);
                game.draw(client);
                game.sendState("\n");
            }

        }else{
            // client n'existe plus, on sort
            printf("[-]Client disconnected.\n");
            break;
        }
    }
}


/*void writer(vector<StreamSocket*>* clientTab) {
    while (true) {
        string veryLongString;
        getline(cin,veryLongString); // on attend que le serveur ecrive

        // envoie le message a tous les clients
        for (std::vector<StreamSocket*>::iterator i = clientTab->begin(); i != clientTab->end(); i++)
        {
            (*i)->send(veryLongString);
        }
    }
}*/


int main()
{
    srand(time(NULL));
    ConnectionPoint *server=new ConnectionPoint(3490);

    int err= server->init();
    //std::cout << server->getIP() << ":" << server->getPort() << std::endl;
    if (err != 0) {
        std::cout << strerror(err) << std::endl;
        exit(err);
    }
    cout<<"Server start"<<endl;

    vector<StreamSocket*> clientTab; // vecteur de tous les clients
    // std::thread (writer, &clientTab).detach(); // pour écrire à tous les clients

    while (true) {
        StreamSocket* client = server->accept(); // attend un nouveau client
        
        if (!client->valid()) {
            delete client;
            continue;
        }else{
            std::cout << "Got a client!" << std::endl;
            clientTab.push_back(client);
            std::thread (reader, client, server).detach(); // pour lire un texte recu par un seul client
        }

    }


    for (std::vector<StreamSocket*>::iterator i = clientTab.begin(); i != clientTab.end(); i++)
    {
        delete *i;
    }
    delete server;
    return 0;
}
