#ifndef BAT_H
#define BAT_H
#include <iostream>
#include <vector>
#include "Monster.h"

using namespace std;

class Bat:public Monster{
public:
    //constructor
    Bat(){
    name = "Bat";
    Strength = 20;
    maxHP = 20;
    maxMP = 25;
    origSpeed = 20;
    Speed = 20;
    HP = 20;
    MP = 20;
    Level = 1;
    }
    //bat instances to get abilities
    void Edit_Abilities(){
        if (this->Level > 0){
            this->Abilities.push_back("Bites");
            this->abilities_Damage.push_back(5);
            this->mp_Cost.push_back(3);
        }
        if (this->Level >= 10){
            this->Abilities.push_back("Wind-Attack");
            this->abilities_Damage.push_back(10);
            this->mp_Cost.push_back(10);
        }
        if (this->Level >= 20){
            this->Abilities.push_back("Air-Slash");
            this->abilities_Damage.push_back(20);
            this->mp_Cost.push_back(20);
        }
        if (this->Level == 30){
            this->Abilities.push_back("Supersonic");
            this->abilities_Damage.push_back(40);
            this->mp_Cost.push_back(45);
        }
    }

};

#endif 