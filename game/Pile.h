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

    bool addCard(int);
    int getLastCard();
    bool getIsAscendant();
};

Pile::Pile(){
}

Pile::Pile(int id_, bool is_ascendant)
{
    isAscendant = is_ascendant;
    id=id_;
    if(isAscendant){
        card.push_back(1);
    }else{
        card.push_back(100);
    }
}


bool Pile::addCard(int num){
    card.push_back(num);
}

int Pile::getLastCard(){
    return card.back();
}

bool Pile::getIsAscendant(){
    return isAscendant;
}
