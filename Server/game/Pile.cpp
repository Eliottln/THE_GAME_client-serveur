#include "Pile.h"

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


void Pile::addCard(int num){
    card.push_back(num);
}

int Pile::getLastCard(){
    return card.back();
}

bool Pile::getIsAscendant(){
    return isAscendant;
}
