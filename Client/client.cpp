#include <iostream>
#include <thread>
#include <sys/time.h>
#include "../socket.h"

using namespace std;
using namespace stdsock;


void reader(StreamSocket* sock){
    while (true)
    {   
        string msg;
        int nb=sock->read(msg); // attend un message du server
        if(nb <= 0){
            printf("[-]Error in receiving data.\n"); // le serveur ne repond plus
            break;
        }else{
            cout << "Server: \t"<< msg << endl;
        }
    }
}


int main(int argc, char* argv[])
{
    int port;

    if(argc!=3)
    {
        printf("usage: %s server_address port\n", argv[0]);
        return 0;
    }
    if(sscanf(argv[2], "%d", &port)!=1)
    {
        printf("usage: %s server_address port\n", argv[0]);
        return 1;
    }

    // creer la connexion et la test
    StreamSocket *sock=new StreamSocket(argv[1],port);
    int err= sock->connect();
    if (err!=0) {
        delete sock;
        perror("[-]Error in connection: ");
        return(err);
    }
    cout << "[+]Connected to Server " << sock->getIP() <<":" << sock->getPort() << endl;


    // pour lire les msg du serveur
    std::thread (reader, sock).detach();
    // pour ecrire sur le serveur
    while (true) {
        string veryLongString;
        getline(cin,veryLongString);
        sock->send(veryLongString);
    }

    delete sock;
    return 0;
}
