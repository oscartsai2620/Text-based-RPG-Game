#include<iostream>
#include <random>
#include "Warrior.h"

using namespace std;
//constructor
Warrior::Warrior():Character(){
    name = "Warrior";
    setCharacter_Class("Warrior");
}

//constructor for characters randomly make in arena
Warrior::Warrior(int lv){
    name = "Warrior";
    Strength = 25 + (5 * lv);
    maxHP = rand() % 10 + (45 + 5 * lv);
    maxMP = 20 + (5 * lv);
    origSpeed = 25 + (5 * lv);
    Speed = origSpeed;
    Empower = Strength;
    HP = maxHP;
    MP = maxMP;
    Level = lv;

    this->set_Abilities();
}

//constructor for new character
Warrior::Warrior(string username, string c){
    name = username;
    Strength = 30;
    maxHP = rand() % 10 + 50;
    maxMP = 25;
    origSpeed = 30;
    Speed = 30;
    Empower = Strength;
    HP = maxHP;
    MP = maxMP;
    Level = 1;
    AmountEXP = 0;
    maxEXP = 100;
    attributePoints = 0;
    ItemAmount = 0;
    setCharacter_Class(c);

    this->Edit_Abilities(); //get first ability
    

}

//constructor to load a save warrior character
Warrior::Warrior(string n, string c, int s,int mHP,int mMP,int speed,int l,int EXP,int mEXP, int AP, int ItemA, vector<string> itemN, vector<int> itemC, vector<string> abilityName, vector<int> mpCost, vector<int> damage, vector<int> slow, vector<int> heal, vector<int> emp, vector<string> buffName){
    this->name = n;
    this->Strength = s,
    this->maxHP = mHP;
    this->HP = mHP;
    this->maxMP = mMP;
    this->MP = mMP;
    this->origSpeed = speed;
    this->Speed = speed;
    this->Empower = s;
    this->Level = l;
    this->AmountEXP = EXP;
    this->maxEXP = mEXP;
    this->attributePoints = AP;
    this->ItemAmount = ItemA;
    this->itemName = itemN;
    this->itemCount = itemC;
    this->Abilities = abilityName;
    this->mp_Cost = mpCost;
    this->abilities_Damage = damage;
    this->Slow = slow;
    this->Heal = heal;
    this->Emp = emp;
    this->buff_and_debuff = buffName;
    setCharacter_Class(c);

}

//get abilities for warrior instances
void Warrior::Edit_Abilities(){
    switch(this->Level){
        case 1:
            cout << endl << "Raging-Fist is " << this->name << "'s first ability!" << endl;
            this->Abilities.push_back("Raging-Fist");
            this->abilities_Damage.push_back(5);
            this->mp_Cost.push_back(3);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Raging-Fist:" << endl;
            cout << "Damage: 5, MP cost: 3" << endl << endl;
            break;
        case 5:
            cout << endl << this->name << " just learned Hit-Strike!" << endl;
            this->Abilities.push_back("Hit-Strike");
            this->abilities_Damage.push_back(10);
            this->mp_Cost.push_back(10);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Hit-Strike:" << endl;
            cout << "Damage: 10, MP cost: 10" << endl << endl;
            break;
        case 10:
            cout << endl << this->name << " just learned Berserker!" << endl;
            this->Abilities.push_back("Berserker");
            this->abilities_Damage.push_back(0);
            this->mp_Cost.push_back(25);
            this->buff_and_debuff.push_back("Empowered");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(10);
            cout << "Berserker:" << endl;
            cout << "Increase strength by 10, MP cost: 25" << endl << endl;
            break;
        case 15:
            cout << endl << this->name << " just learned Critical-Hit!" << endl;
            this->Abilities.push_back("Critical-Hit");
            this->abilities_Damage.push_back(15);
            this->mp_Cost.push_back(20);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Critical-Hit:" << endl;
            cout << "Damage: 15, MP cost: 20" << endl << endl;
            break;
        case 20:
            cout << endl << this->name << " just learned Restore!" << endl;
            this->Abilities.push_back("Restore");
            this->abilities_Damage.push_back(0);
            this->mp_Cost.push_back(35);
            this->buff_and_debuff.push_back("Healed");
            this->Slow.push_back(0);
            this->Heal.push_back(20);
            this->Emp.push_back(0);
            cout << "Restore:" << endl;
            cout << "Heal HP by 20, MP cost: 35" << endl << endl;
            break;
        case 25:
            cout << endl << this->name << " just learned Dragon-Slash!" << endl;
            this->Abilities.push_back("Dragon-Slash");
            this->abilities_Damage.push_back(35);
            this->mp_Cost.push_back(45);
            this->buff_and_debuff.push_back("Slow"); //show enemy speed by 3
            this->Slow.push_back(3);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Dragon-Slash:" << endl;
            cout << "Damage: 35, Slows enemy, MP cost: 45" << endl << endl;
            break;
        case 30:
            cout << endl << this->name << " just learned Fire-Cleave!" << endl;
            this->Abilities.push_back("Fire-Cleave");
            this->abilities_Damage.push_back(45);
            this->mp_Cost.push_back(50);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Fire-Cleave:" << endl;
            cout << "Damage: 45, MP cost: 50" << endl << endl;
            break;
    }
    this->maxAbilities();

}

//get abilities for warrior instances in the arena
void Warrior::set_Abilities(){
    int loop = 0;
    if (this->Level > 0){
        this->Abilities.push_back("Raging-Fist");
        this->abilities_Damage.push_back(5);
        this->mp_Cost.push_back(3);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 5){
        this->Abilities.push_back("Hit-Strike");
        this->abilities_Damage.push_back(10);
        this->mp_Cost.push_back(10);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 10){
        this->Abilities.push_back("Berserker");
        this->abilities_Damage.push_back(0);
        this->mp_Cost.push_back(25);
        this->buff_and_debuff.push_back("Empowered");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(10);
    }
    if (this->Level >= 15){
        this->Abilities.push_back("Critical-Hit");
        this->abilities_Damage.push_back(15);
        this->mp_Cost.push_back(20);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 20){
        this->Abilities.push_back("Restore");
        this->abilities_Damage.push_back(0);
        this->mp_Cost.push_back(35);
        this->buff_and_debuff.push_back("Healed");
        this->Slow.push_back(0);
        this->Heal.push_back(20);
        this->Emp.push_back(0);
        loop++;
    }
    if (this->Level >= 25){
        this->Abilities.push_back("Dragon-Slash");
        this->abilities_Damage.push_back(35);
        this->mp_Cost.push_back(45);
        this->buff_and_debuff.push_back("Slow"); //show enemy speed by 3
        this->Slow.push_back(3);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
        loop++;
    }
    if (this->Level >= 30){
        this->Abilities.push_back("Fire-Cleave");
        this->abilities_Damage.push_back(45);
        this->mp_Cost.push_back(50);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
        loop++;
    }
    while(loop > 0){
        this->Abilities.erase(this->Abilities.begin());
        this->abilities_Damage.erase(this->abilities_Damage.begin());
        this->mp_Cost.erase(this->mp_Cost.begin());
        this->buff_and_debuff.erase(this->buff_and_debuff.begin());
        this->Slow.erase(this->Slow.begin());
        this->Heal.erase(this->Heal.begin());
        this->Emp.erase(this->Emp.begin());
        loop--;
    }

}
