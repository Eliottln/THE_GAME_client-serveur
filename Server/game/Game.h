#include <vector>
#include <unordered_map>
#include <thread>
#include "../../socket.h"
#include "Deck.h"

using namespace std;
using namespace stdsock;

class Game
{
private:
    int idGame;
    unordered_map<StreamSocket*,Deck> playersTab;
    Pile tas1, tas2, tas3, tas4; //tas du jeu
    vector<int> pioche;
    int nbCartes, nbJoueurs;

public:
    Game(){}
    Game(int nb_joueurs, int nb_cartes, StreamSocket* client);
    void init(int nb_joueurs, int nb_cartes, StreamSocket* client);
    ~Game();

    void addPlayer(StreamSocket* client);
    string showPile();
    void sendState(string msg);
    void playCard(StreamSocket* client, int idCard, int idPile);
    void nextTurn(StreamSocket* client);
    bool testTurn(StreamSocket* client);
    void draw(StreamSocket* client);
};
