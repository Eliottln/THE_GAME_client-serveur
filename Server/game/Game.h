#include <vector>
#include <map>
#include <thread>
#include "../../socket.h"
#include "Deck.h"

using namespace std;
using namespace stdsock;

class Game
{
private:
    int idGame;
    ConnectionPoint* server;
    // vector<StreamSocket*> clientTab;
    map<StreamSocket*,Deck> playersTab;

    Pile tas1, tas2, tas3, tas4;
    vector<int> pioche;

    // vector<Deck> tabJoueurs;
    int nbCartes, nbJoueurs;

public:
    Game(){}
    Game(int nb_joueurs, int nb_cartes, ConnectionPoint* server_, StreamSocket* client);
    void init(int nb_joueurs, int nb_cartes, ConnectionPoint* server_, StreamSocket* client);
    ~Game();

    void addPlayer(StreamSocket* client);
    void showPile();
    void startGame();
};
