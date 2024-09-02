#include<iostream>
#include <random>
#include "Assassin.h"

using namespace std;

//constructor
Assassin::Assassin():Character(){
    name = "Assassin";
    setCharacter_Class("Assassin");
}

//constructor for assassin characters made in arena
Assassin::Assassin(int lv){
    name = "Assassin";
    Strength = 25 + (5 * lv);
    maxHP = 25 + (5 * lv);
    maxMP = 20 + (5 * lv);
    origSpeed = rand() % 10 + (45 + 5 * lv);
    Speed = origSpeed;
    Empower = Strength;
    HP = maxHP;
    MP = maxMP;
    Level = lv;

    this->set_Abilities();
}

//constructor for new assassin character
Assassin::Assassin(string username, string c){
    name = username;
    Strength = 30;
    maxHP = 30;
    maxMP = 25;
    origSpeed = rand() % 10 + 50;
    Speed = origSpeed;
    Empower = Strength;
    HP = maxHP;
    MP = maxMP;
    Level = 1; // TODO: need to fix to 1
    AmountEXP = 0;
    maxEXP = 100;
    attributePoints = 0;
    ItemAmount = 0;
    setCharacter_Class(c);

    this->Edit_Abilities(); //get first ability
    

}

//constructor for saved assassin character
Assassin::Assassin(string n, string c, int s,int mHP,int mMP,int speed,int l,int EXP,int mEXP, int AP, int ItemA, vector<string> itemN, vector<int> itemC, vector<string> abilityName, vector<int> mpCost, vector<int> damage, vector<int> slow, vector<int> heal, vector<int> emp, vector<string> buffName){
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

//get abilities for assassin instances 
void Assassin::Edit_Abilities(){
    int input, choice;

    switch(this->Level){
        case 1:
            cout << endl << "Quick-Stab is " << this->name << "'s first ability!" << endl;
            this->Abilities.push_back("Quick-Stab");
            this->abilities_Damage.push_back(5);
            this->mp_Cost.push_back(3);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Quick-Stab:" << endl;
            cout << "Damage: 5, MP cost: 3" << endl << endl;
            break;
        case 5:
            cout << endl << this->name << " just learned Knife-Throw!" << endl;
            this->Abilities.push_back("Knife-Throw");
            this->abilities_Damage.push_back(10);
            this->mp_Cost.push_back(10);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Knife-Throw:" << endl;
            cout << "Damage: 10, MP cost: 10" << endl << endl;
            break;
        case 10:
            cout << endl << this->name << " just learned Master-Focus!" << endl;
            this->Abilities.push_back("Master-Focus");
            this->abilities_Damage.push_back(0);
            this->mp_Cost.push_back(25);
            this->buff_and_debuff.push_back("Empowered");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(10);
            cout << "Master-Focus:" << endl;
            cout << "Increase strength by 10, MP cost: 25" << endl << endl;
            break;
        case 15:
            cout << endl << this->name << " just learned Cross-Slash!" << endl;
            this->Abilities.push_back("Cross-Slash");
            this->abilities_Damage.push_back(15);
            this->mp_Cost.push_back(20);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Cross-Slash:" << endl;
            cout << "Damage: 15, MP cost: 20" << endl << endl;
            break;
        case 20:
            cout << endl << this->name << " just learned Stealth!" << endl;
            this->Abilities.push_back("Stealth");
            this->abilities_Damage.push_back(0);
            this->mp_Cost.push_back(25);
            this->buff_and_debuff.push_back("Stealth");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Stealth:" << endl;
            cout << "Dodge a hit, MP cost: 25" << endl << endl;
            break;
        case 25:
            cout << endl << this->name << " just learned Headhunt!" << endl;
            this->Abilities.push_back("Headhunt");
            this->abilities_Damage.push_back(35);
            this->mp_Cost.push_back(45);
            this->buff_and_debuff.push_back("Healed");
            this->Slow.push_back(0);
            this->Heal.push_back(20);
            this->Emp.push_back(0);
            cout << "Headhunt:" << endl;
            cout << "Damage: 35, Heal HP by 20, MP cost: 45" << endl << endl;
            break;
        case 30:
            cout << endl << this->name << " just learned Death-Chain!" << endl;
            this->Abilities.push_back("Death-Chain");
            this->abilities_Damage.push_back(45);
            this->mp_Cost.push_back(50);
            this->buff_and_debuff.push_back("None");
            this->Slow.push_back(0);
            this->Heal.push_back(0);
            this->Emp.push_back(0);
            cout << "Death-Chain:" << endl;
            cout << "Damage: 45, MP cost: 50" << endl << endl;
            break;
    }
    this->maxAbilities();

}

//get abilities for assassin instances in the arena
void Assassin::set_Abilities(){
    int loop = 0;
    if (this->Level > 0){
        this->Abilities.push_back("Quick-Stab");
        this->abilities_Damage.push_back(5);
        this->mp_Cost.push_back(3);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 5){
        this->Abilities.push_back("Knife-Throw");
        this->abilities_Damage.push_back(10);
        this->mp_Cost.push_back(10);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 10){
        this->Abilities.push_back("Master-Focus");
        this->abilities_Damage.push_back(0);
        this->mp_Cost.push_back(25);
        this->buff_and_debuff.push_back("Empowered");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(10);
    }
    if (this->Level >= 15){
        this->Abilities.push_back("Cross-Slash");
        this->abilities_Damage.push_back(15);
        this->mp_Cost.push_back(20);
        this->buff_and_debuff.push_back("None");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
    }
    if (this->Level >= 20){
        this->Abilities.push_back("Stealth");
        this->abilities_Damage.push_back(0);
        this->mp_Cost.push_back(25);
        this->buff_and_debuff.push_back("Stealth");
        this->Slow.push_back(0);
        this->Heal.push_back(0);
        this->Emp.push_back(0);
        loop++;
    }
    if (this->Level >= 25){
        this->Abilities.push_back("Headhunt");
        this->abilities_Damage.push_back(35);
        this->mp_Cost.push_back(45);
        this->buff_and_debuff.push_back("Healed"); 
        this->Slow.push_back(0);
        this->Heal.push_back(20);
        this->Emp.push_back(0);
        loop++;
    }
    if (this->Level >= 30){
        this->Abilities.push_back("Death-Chain");
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
