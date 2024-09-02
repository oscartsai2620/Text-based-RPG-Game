#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>

using namespace std;

class Character{
public:
    Character();
    Character(string, string);
    void my_Status();
    void take_damage(int damage);
    void Healing(int heal);
    void Slowed(int slow);
    void use_MP(int mpCost);
    void Empowered(int emp);
    void use_Item(int num);
    void my_Inventory();
    void Level_Up();
    void getRandomItem();
    void recievedEXP(); 
    virtual void Edit_Abilities() = 0;
    virtual void set_Abilities() = 0;
    void Add_Attribute();
    void Win();
    void Finish_Combat();
    void Save();
    void LV_5(); //secret function that levels 5 levels for the character
    void maxAbilities();
    
    void setStealth(bool s){this->stealth = s;}
    void setCharacter_Class(string c){Character_Class = c;}

    //getters for status
    string getName(){return name;}
    int getStrength(){return Strength;}
    int getmaxHP(){return maxHP;}
    int getHP(){return HP;}
    int getmaxMP(){return maxMP;}
    int getMP(){return MP;}
    int getSpeed(){return origSpeed;}
    int getLevel(){return Level;}
    int getEXP(){return AmountEXP;}
    int getmaxEXP(){return maxEXP;}
    int getAP(){return attributePoints;}
    int getEmpower(){return Empower;}
    bool getStealth(){return stealth;}
    string getCharacterClass(){return Character_Class;}

    //getters for items
    int getItemAmount(){return ItemAmount;}
    vector<string> getItemName(){return itemName;}
    vector<int> getItemCount(){return itemCount;}

    //getters for abilities 
    string getAbilities(int choice){return Abilities.at(choice-1);}
    int getDamage(int choice){return abilities_Damage.at(choice-1);}
    int getMP_Cost(int choice){return mp_Cost.at(choice-1);}
    string getBuff(int choice){return buff_and_debuff.at(choice-1);}
    int getSlow(int choice){return Slow.at(choice-1);}
    int getHeal(int choice){return Heal.at(choice-1);}
    int getEmp(int choice){return Emp.at(choice-1);}
    vector<string> getAbilitiesList(){return Abilities;}

private:
    string Character_Class;


protected:
    string name;
    vector<string> itemName;
    vector<int> itemCount;
    int Strength;
    int maxHP;
    int maxMP;
    int origSpeed;
    int Speed;
    int Empower;
    int HP;
    int MP;
    int Level;
    int AmountEXP;
    int maxEXP;
    int attributePoints;
    int ItemAmount;
    bool stealth = false;
    vector<string> Abilities;
    vector<int> mp_Cost;
    vector<int> abilities_Damage;
    vector<int> Slow;
    vector<int> Heal;
    vector<int> Emp;
    vector<string> buff_and_debuff;
};

#endif 