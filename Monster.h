#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <vector>

using namespace std;

class Monster{
public:
    //constructor
    Monster(){
        name = "Unknown";
        Strength = 25;
        maxHP = 20;
        maxMP = 25;
        origSpeed = 20;
        Speed = 20;
        HP = 20;
        MP = 20;
        Level = 1;
    }
    //pure virtual function for monsters to get abilities
    virtual void Edit_Abilities() = 0;
    //monster gain status with its level
    void Lv_Up(int lv){
        this->Strength += (lv *5);
        this->maxHP += (lv *8);
        this->HP = this->maxHP;
        this->maxMP += (lv *8);
        this->MP = this->maxMP;
        this->origSpeed += (lv *5);
        this->Speed = this->origSpeed;
        this->Level = lv;
    }
    //monster takes damage
    void take_damage(int damage){
        this->HP -= damage;
    }
    //monster uses MP after casting an ability
    void use_MP(int mpCost){
        this->MP -= mpCost;
    }
    //monster get slow
    void slowed(int slowAmount){
        this->Speed -= slowAmount;
    }

    //getters for variables
    string getName(){return name;}
    int getStrength(){return Strength;}
    int getmaxHP(){return maxHP;}
    int getHP(){return HP;}
    int getmaxMP(){return maxMP;}
    int getMP(){return MP;}
    int getSpeed(){return Speed;}
    int getLevel(){return Level;}
    string getAbilities(int choice){return Abilities.at(choice-1);}
    vector<string> getAbilitiesList(){return Abilities;}
    int getAbilityDamage(int choice){return abilities_Damage.at(choice-1);}
    int getmpCost(int choice){return mp_Cost.at(choice-1);}

protected:
    string name;
    int Strength;
    int maxHP;
    int maxMP;
    int origSpeed;
    int Speed;
    int HP;
    int MP;
    int Level;
    vector<string> Abilities;
    vector<int> abilities_Damage;
    vector<int> mp_Cost;

};

#endif 