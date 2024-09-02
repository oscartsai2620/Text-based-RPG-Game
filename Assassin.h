#ifndef ASSASSIN_H
#define ASSASSIN_H

#include <iostream>
#include <vector>
#include "Character.h"

using namespace std;

class Assassin:public Character{
public:
    Assassin();
    Assassin(int lv);
    Assassin(string, string);
    Assassin(string n, string c, int s,int mHP,int mMP,int speed,int l,int EXP,int mEXP, int AP, int ItemAmount, vector<string> itemN, vector<int> itemC, vector<string> abilityName, vector<int> mpCost, vector<int> damage, vector<int> slow, vector<int> heal, vector<int> emp, vector<string> buffName);
    void Edit_Abilities();
    void set_Abilities();
    //~Assassin();

};

#endif 