#ifndef GOBLIN_H
#define GOBLIN_H
#include <iostream>
#include <vector>
#include "Monster.h"

using namespace std;

class Goblin:public Monster{
public:
    //constructor
    Goblin(){
    name = "Goblin";
    Strength = 20;
    maxHP = 20;
    maxMP = 25;
    origSpeed = 20;
    Speed = 20;
    HP = 20;
    MP = 20;
    Level = 1;
    }
    //Goblin instances to get abilities
    void Edit_Abilities(){
        if (this->Level > 0){
            this->Abilities.push_back("Scratch");
            this->abilities_Damage.push_back(5);
            this->mp_Cost.push_back(3);
        }
        if (this->Level >= 10){
            this->Abilities.push_back("Punch");
            this->abilities_Damage.push_back(10);
            this->mp_Cost.push_back(10);
        }
        if (this->Level >= 20){
            this->Abilities.push_back("Hard-Kick");
            this->abilities_Damage.push_back(20);
            this->mp_Cost.push_back(20);
        }
        if (this->Level == 30){
            this->Abilities.push_back("Rampage");
            this->abilities_Damage.push_back(40);
            this->mp_Cost.push_back(45);
        }
    }

};

#endif 