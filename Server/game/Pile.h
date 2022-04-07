#include <vector>
#include <errno.h>
#include <stdio.h>
#include <iostream>

class Pile
{
private:
    int id;
    std::vector<int> card;
    bool isAscendant;
    
public:
    Pile();
    Pile(int id, bool isAscendant);

    void addCard(int);
    int getLastCard();
    bool getIsAscendant();
};
