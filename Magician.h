#ifndef MAGICIAN_H
#define MAGICIAN_H

#include <iostream>
#include <vector>
#include "Character.h"

using namespace std;

class Magician:public Character{
public:
    Magician();
    Magician(int lv);
    Magician(string, string);
    Magician(string n, string c, int s,int mHP,int mMP,int speed,int l,int EXP,int mEXP, int AP, int ItemAmount, vector<string> itemN, vector<int> itemC, vector<string> abilityName, vector<int> mpCost, vector<int> damage, vector<int> slow, vector<int> heal, vector<int> emp, vector<string> buffName);
    void Edit_Abilities();
    void set_Abilities();
    //~Magician();

};

#endif 