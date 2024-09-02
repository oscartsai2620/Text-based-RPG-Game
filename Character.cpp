#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include "Character.h"
#include "Warrior.h"
#include "Magician.h"
#include "Assassin.h"

using namespace std;

vector<Character*> read_File(){
    string ability, buffName;
    int mpCostAmount, damageAmount, slowAmount, healAmount, empAmount;
    string username, class_name, blankspace, itemN;
    int strength, maxhp, maxmp, speed, power, level, EXP, maxXP, AP, itemC, num = 1 , skillAmount;
    int itemAmount;
    Character* temp;

    vector<Character*> allChar;
    //open the save file if exits
    ifstream fin("Saved_File.txt");

    //check if the file is opened
    if(fin.is_open()){
        while(!fin.eof()){
            //store values for a temporary character
            vector<string> items;
            vector<int> counts;

            vector<string> abilityName;
            vector<int> mpCost;
            vector<int> damage;
            vector<int> slow;
            vector<int> heal;
            vector<int> emp;
            vector<string> buff;
            

            getline(fin, username);
            
            
            getline(fin, class_name);
            //cout << "Class: " << class_name << endl;

            fin >> strength;
            //fin.ignore();


            fin >> maxhp;
            //fin.ignore();
            

            fin >> maxmp;
            //fin.ignore();
            

            fin >> speed;
            //fin.ignore();
        
            
            fin >> level;
            //fin.ignore();
            

            fin >> EXP;
            //fin.ignore();

            fin >> maxXP;
            //fin.ignore();
            

            fin >> AP;
            //fin.ignore();

            fin >> skillAmount;

            for(int i = 0; i < skillAmount; i++){
                fin >> ability;
                abilityName.push_back(ability);
                fin >> mpCostAmount;
                mpCost.push_back(mpCostAmount);
                fin >> damageAmount;
                damage.push_back(damageAmount);
                fin >> slowAmount;
                slow.push_back(slowAmount);
                fin >> healAmount;
                heal.push_back(healAmount);
                fin >> empAmount;
                emp.push_back(empAmount);
                fin >> buffName;
                buff.push_back(buffName);
            }
            

            fin >> itemAmount;
            //fin.ignore();

            if(itemAmount == 0){
                fin.ignore();
                getline(fin, blankspace);
                getline(fin, blankspace);
            }
            else{
                for(int i = 0; i < itemAmount; i++){
                    fin >> itemN;
                    
                    items.push_back(itemN);
                }

                for(int i = 0; i < itemAmount; i++){
                    fin >> itemC;
                    
                    counts.push_back(itemC);
                }
                fin.ignore();
            }

            /*for(int i = 0; i < itemAmount; i++){
                cout << "Items:" << endl;
                
            }*/
 
            getline(fin, blankspace);
            //create a temporary character
            
            if(class_name == "Warrior"){
                temp = new Warrior(username, class_name, strength, maxhp, maxmp, speed, level, EXP, maxXP, AP, itemAmount, items, counts, abilityName, mpCost, damage, slow, heal, emp, buff);
            }
            else if(class_name == "Magician"){
                temp = new Magician(username, class_name, strength, maxhp, maxmp, speed, level, EXP, maxXP, AP, itemAmount, items, counts, abilityName, mpCost, damage, slow, heal, emp, buff);
            }
            else if(class_name == "Assassin"){
                temp = new Assassin(username, class_name, strength, maxhp, maxmp, speed, level, EXP, maxXP, AP, itemAmount, items, counts, abilityName, mpCost, damage, slow, heal, emp, buff);
            }
            //store it into a vector that has all saved characters
        
            allChar.push_back(temp);
            

        }
    }
    //return empty vector if file is not open
    else{
        return allChar;
    }
    fin.close();

    allChar.pop_back();

    return allChar;
}


void print_File(vector<Character*> allChar){
    //print the save file
    for(int i = 0; i < allChar.size(); i++){
        cout << i+1 << ". \n";
        cout << "Name: " << allChar.at(i)->getName() << endl;
        cout << "Class: " << allChar.at(i)->getCharacterClass() << endl;
        cout << "Strength: " << allChar.at(i)->getStrength() << endl;
        cout << "maxHP: " << allChar.at(i)->getmaxHP() << endl;
        cout << "maxMP: " << allChar.at(i)->getmaxMP() << endl;
        cout << "Speed: " << allChar.at(i)->getSpeed() << endl;
        cout << "Level: " << allChar.at(i)->getLevel() << endl;
        cout << "Current EXP: " << allChar.at(i)->getEXP() << " / " << allChar.at(i)->getmaxEXP() << endl;
        cout << "Attribute Points Avaliable: " << allChar.at(i)->getAP() << endl;
        cout << "Item Amount: " << allChar.at(i)->getItemAmount() << endl;
        for(int j = 0; j < allChar.at(i)->getItemName().size(); j++){
            cout << allChar.at(i)->getItemName().at(j) << " x" << allChar.at(i)->getItemCount().at(j) << endl;
        }
        cout << "Abilities:" << endl;
        for(int k = 0; k < allChar.at(i)->getAbilitiesList().size(); k++){
            cout << allChar.at(i)->getAbilitiesList().at(k) << " ";
            if(k % 2 != 0){
                cout << endl;
            }
        }
        cout << endl << endl;
    }
}

Character::Character(){
    name = " ";
    Strength = 0;
    maxHP = 0;
    maxMP = 0;
    origSpeed = 0;
    Speed = 0;
    Empower = 0;
    HP = 0;
    MP = 0;
    Level = 0;
    AmountEXP = 0;
    maxEXP = 0;
    attributePoints = 0;
    ItemAmount = 0;
}


Character::Character(string userName, string class_name){
    name = userName;
    Strength = 0;
    maxHP = 0;
    maxMP = 0;
    origSpeed = 0;
    Speed = 0;
    Empower = 0;
    HP = 0;
    MP = 0;
    Level = 1;
    AmountEXP = 0;
    maxEXP = 100;
    attributePoints = 5;
    ItemAmount = 0;
    setCharacter_Class(class_name);
}


void Character::my_Status(){
    //show current attributes
    cout << this->name << "'s current attributes:" << endl;
    cout << "Class: " << this->getCharacterClass() << endl;
    cout << "Strength: " << this->Strength << endl;
    cout << "maxHP: " << this->maxHP << endl;
    cout << "maxMP: " << this->maxMP << endl;
    cout << "Speed: " << this->origSpeed << endl;
    cout << "Level: " << this->Level << endl;
    cout << "EXP: " << this->AmountEXP << " / " << this->maxEXP << endl;
}

//character takes damage
void Character::take_damage(int damage){
    this->HP -= damage;
}

//character heals
void Character::Healing(int heal){
    this->HP += heal;
}

//character get slow by the enemy
void Character::Slowed(int slow){
    this->Speed -= slow;
}

//character spend MP after using an ability
void Character::use_MP(int mpCost){
    this->MP -= mpCost;
}

//treat the empower variable as the strength varaible with the amount of strength empowered
void Character::Empowered(int emp){
    this->Empower += emp;
}

//user uses an item
void Character::use_Item(int num){
    //determine the item used
    if(this->itemName.at(num) == "steak"){
        this->HP += 30;
        cout << this->name << " healed for 30 HP." << endl;
    }
    else if(this->itemName.at(num) == "apple"){
        this->HP += 15;
        cout << this->name << " healed for 15 HP." << endl;
    }
    else if(this->itemName.at(num) == "juice"){
        this->MP += 30;
        cout << this->name << " gain 30 MP." << endl;
    }
    else if(this->itemName.at(num) == "water"){
        this->MP += 15;
        cout << this->name << " gain 15 MP." << endl;
    }

    //take away the item after its used
    if(this->itemCount.at(num) == 1){
        this->itemCount.erase(this->itemCount.begin() + num);
        this->itemName.erase(this->itemName.begin() + num);
        this->ItemAmount--;
    }
    else{
        this->itemCount.at(num)--;
    }

}

//print inventory
void Character::my_Inventory(){
    string noIven = "Inventory is empty!";

    //throw a no inventory string if inventory is empty
    if(this->ItemAmount == 0){
        throw noIven;
    }
    else{
        cout << "Your inventory: " << endl;
        for(int j = 0; j < this->ItemAmount; j++){
            cout << this->getItemName().at(j) << " x" << this->getItemCount().at(j) << " ";
        }
    }
    cout << endl << endl;
}

//user levels up
void Character::Level_Up(){
    
    //add level and 
    this->Level++;
    cout << this->name << " level up to " << this->Level << " level!" << endl;
    this->AmountEXP -= this->maxEXP;
    
    //add status
    this->Strength += 5;
    this->maxHP += 10;
    this->maxMP += 10;
    this->origSpeed += 5;
    this->attributePoints += 5;
    this->Add_Attribute();
    this->maxEXP += (this->maxEXP * 0.1);

    if(this->Level == 5 or this->Level == 10 or this->Level == 15 or this->Level == 20 or this->Level == 25 or this->Level == 30){
        this->Edit_Abilities();
    }
}



void Character::Add_Attribute(){
    int input, attribute;

    //show current attributes
    if(this->attributePoints > 0){
        cout << this->name << "'s current attributes:" << endl;
        cout << "Strength: " << this->Strength << endl;
        cout << "maxHP: " << this->maxHP << endl;
        cout << "maxMP: " << this->maxMP << endl;
        cout << "Speed: " << this->origSpeed << endl;
    }

    //add attribute
    do{
        if(this->attributePoints > 0){
            cout << "Avaliable points to add: " << this->attributePoints << endl;

            //ask which attribute to add or add later
            cout << "Add " << this->name << "'s attributes 1.Now or 2.Later" << endl;
            cin >> input;
            if(input == 1){
                cout << "Which attribute do you want to add?" << endl;
                cout << "1.Strength 2.maxHP 3.maxMP 4.Speed" << endl;
                cin >> attribute;
                if(attribute == 1){
                    this->Strength++;
                    this->Empower++;
                    this->attributePoints--;
                    cout << this->name << " have increased in strength!" << endl;
                }
                else if(attribute == 2){
                    this->maxHP++;
                    this->HP++;
                    this->attributePoints--;
                    cout << this->name << " have increased in maxHP!" << endl;
                }
                else if(attribute == 3){
                    this->maxMP++;
                    this->MP++;
                    this->attributePoints--;
                    cout << this->name << " have increased in maxMP!" << endl;
                }
                else if(attribute == 4){
                    this->origSpeed++;
                    this->Speed++;
                    this->attributePoints--;
                    cout << this->name << " have increased in speed!" << endl;
                }
                else{
                    cout << "Invalid Number! Try Again." << endl;
                }
            }
            else if(input == 2){
                break;
            }
            else{
                cout << "Invalid Number! Try Again." << endl;
            }
        }
        else{
            cout << this->name << " do not have enough points avaliable to increase attributes!" << endl;
            break;        
        }

    }while(true);

}


void Character::getRandomItem(){
    int dropRate, itemNum;
    vector<string>::iterator itr;
    //item has a 25% rate to drop, get a random integer between 4
    dropRate = rand() % 4;

    if(dropRate == 0){
        //item is drop randomly between the 4 items
        itemNum = rand() % 4;
        switch(itemNum){
            case 0:
                itr = find(this->itemName.begin(), this->itemName.end(), "steak");
                if(itr != this->itemName.end()){
                    this->itemCount.at(itr - this->itemName.begin())++;
                }
                else{
                    this->itemName.push_back("steak");
                    this->itemCount.push_back(1);
                    this->ItemAmount++;
                }
                cout << this->name << " picked up a steak!" << endl;
                break;
            case 1:
                itr = find(this->itemName.begin(), this->itemName.end(), "apple");
                if(itr != this->itemName.end()){
                    this->itemCount.at(itr - this->itemName.begin())++;
                }
                else{
                    this->itemName.push_back("apple");
                    this->itemCount.push_back(1);
                    this->ItemAmount++;
                }
                cout << this->name << " picked up an apple!" << endl;
                break;
            case 2:
                itr = find(this->itemName.begin(), this->itemName.end(), "juice");
                if(itr != this->itemName.end()){
                    this->itemCount.at(itr - this->itemName.begin())++;
                }
                else{
                    this->itemName.push_back("juice");
                    this->itemCount.push_back(1);
                    this->ItemAmount++;
                }
                cout << this->name << " picked up a juicebox!" << endl;
                break;
            case 3:
                itr = find(this->itemName.begin(), this->itemName.end(), "water");
                if(itr != this->itemName.end()){
                    this->itemCount.at(itr - this->itemName.begin())++;
                }
                else{
                    this->itemName.push_back("water");
                    this->itemCount.push_back(1);
                    this->ItemAmount++;
                }
                cout << this->name << " picked up a water bottle!" << endl;
                break;
        }
    }


}

void Character::recievedEXP(){
    int EXPdrop = 30 + (this->getLevel() * 5);
    
    this->AmountEXP += EXPdrop;
    cout << this->name << " recieved " << EXPdrop << " EXP." << endl;

}

void Character::Win(){
    this->getRandomItem();

    if(this->Level == 30){
        cout << this->name << " has reached the highest level - 30!" << endl;
    }
    else{
        this->recievedEXP(); 

        //check if the character is eligible to level up
        if(this->AmountEXP >= this->maxEXP){
            this->Level_Up();
        }
        else{
            cout << this->name << " is " << this->AmountEXP << " / " << this->maxEXP << " away from leveling up!" << endl;
        }
    }
}

void Character::Finish_Combat(){
    //reset all status for the character
    this->stealth = false;
    this->HP = this->maxHP;
    this->MP = this->maxMP;
    this->Speed = this->origSpeed;
    this->Empower = this->Strength;
}


void Character::Save(){
    string username, class_name, blankspace, itemN;
    int strength, maxhp, maxmp, speed, power, level, EXP, maxXP, AP, itemC;
    int input, itemAmount;
    Character* add;

    vector<Character*> allChar;
    ifstream fin;
    fin.open("Saved_File.txt");


    //check if file is open
    if(fin.is_open()){

        allChar = read_File();

        //if there are 5 characters saved, replace a character
        if(allChar.size() == 5){
            ofstream fout("Saved_File.txt");

            //find a saved character to replace if there is 5 characters saved
            cout << "Which saved file do you want to replace?" << endl;
            cin >> input;
            input--;

            /// remove the characer 
            allChar.erase(allChar.begin() + input);

            // add the new character to the end of the vector
            add = this;
            
            allChar.push_back(add);


            for(int i = 0; i < allChar.size(); i++){

                fout << allChar.at(i)->name << endl;
                fout << allChar.at(i)->Character_Class << endl;
                fout << allChar.at(i)->Strength << endl;
                fout << allChar.at(i)->maxHP << endl;
                fout << allChar.at(i)->maxMP << endl;
                fout << allChar.at(i)->origSpeed << endl;
                fout << allChar.at(i)->Level << endl;
                fout << allChar.at(i)->AmountEXP << endl;
                fout << allChar.at(i)->maxEXP << endl;
                fout << allChar.at(i)->attributePoints << endl;
                fout << allChar.at(i)->Abilities.size() << endl;
                for(int i = 0; i < allChar.at(i)->Abilities.size(); i++){
                    fout << allChar.at(i)->Abilities.at(i) << " ";
                    fout << allChar.at(i)->mp_Cost.at(i) << " ";
                    fout << allChar.at(i)->abilities_Damage.at(i) << " ";
                    fout << allChar.at(i)->Slow.at(i) << " ";
                    fout << allChar.at(i)->Heal.at(i) << " ";
                    fout << allChar.at(i)->Emp.at(i) << " ";
                    fout << allChar.at(i)->buff_and_debuff.at(i) << " ";
                    fout << endl;
                }
                fout << allChar.at(i)->ItemAmount << endl;
                for(int i = 0; i < allChar.at(i)->itemName.size(); i++){
                    fout << allChar.at(i)->itemName.at(i);
                    if(i != allChar.at(i)->itemName.size() - 1){
                        fout << " ";
                    }
                } 
                fout << endl;
                for(int i = 0; i < allChar.at(i)->itemCount.size(); i++){
                    fout << allChar.at(i)->itemCount.at(i);
                    if(i != allChar.at(i)->itemCount.size() - 1){
                        fout << " ";
                    }
                } 
                fout << endl << endl;

            }
            fout.close();
        }
        //or else add/append a new character
        else{

            ofstream fout("Saved_File.txt", ios::app);

            fout << this->name << endl;
            fout << this->Character_Class << endl;
            fout << this->Strength << endl;
            fout << this->maxHP << endl;
            fout << this->maxMP << endl;
            fout << this->origSpeed << endl;
            fout << this->Level << endl;
            fout << this->AmountEXP << endl;
            fout << this->maxEXP << endl;
            fout << this->attributePoints << endl;
            fout << this->Abilities.size() << endl;
            for(int i = 0; i < this->Abilities.size(); i++){
               fout << this->Abilities.at(i) << " ";
               fout << this->mp_Cost.at(i) << " ";
               fout << this->abilities_Damage.at(i) << " ";
               fout << this->Slow.at(i) << " ";
               fout << this->Heal.at(i) << " ";
               fout << this->Emp.at(i) << " ";
               fout << this->buff_and_debuff.at(i) << " ";
               fout << endl;
            }
            fout << this->ItemAmount << endl;
            for(int i = 0; i < this->ItemAmount; i++){
                fout << this->itemName.at(i);
                if(i != this->itemName.size() - 1){
                    fout << " ";
                }
            } 
            fout << endl;
            for(int i = 0; i < this->ItemAmount; i++){
                fout << this->itemCount.at(i);
                if(i != this->itemCount.size() - 1){
                    fout << " ";
                }
            } 
            fout << endl << endl;

            fout.close();

        }

    }
    else{

        //open a file and start write the character as the first saved character
        ofstream fout;
        fout.open("Saved_File.txt");

        fout << this->name << endl;
        fout << this->Character_Class << endl;
        fout << this->Strength << endl;
        fout << this->maxHP << endl;
        fout << this->maxMP << endl;
        fout << this->origSpeed << endl;
        fout << this->Level << endl;
        fout << this->AmountEXP << endl;
        fout << this->maxEXP << endl;
        fout << this->attributePoints << endl;
        fout << this->Abilities.size() << endl;
        for(int i = 0; i < this->Abilities.size(); i++){
            fout << this->Abilities.at(i) << " ";
            fout << this->mp_Cost.at(i) << " ";
            fout << this->abilities_Damage.at(i) << " ";
            fout << this->Slow.at(i) << " ";
            fout << this->Heal.at(i) << " ";
            fout << this->Emp.at(i) << " ";
            fout << this->buff_and_debuff.at(i) << " ";
            fout << endl;
        }
        fout << this->ItemAmount << endl;
        for(int i = 0; i < this-> ItemAmount; i++){
            fout << this->itemName.at(i);
            if(i != this->itemName.size() - 1){
                fout << " ";
            }
        } 
        fout << endl;
        for(int i = 0; i < this->ItemAmount; i++){
            fout << this->itemCount.at(i);
            if(i != this->itemCount.size() - 1){
                fout << " ";
            }
        } 
        fout << endl << endl;

        fout.close();
    }





}

//check and replace abilities
void Character::maxAbilities(){
    int input, choice;

    if(this->Abilities.size() == 5){
        cout << this->name << "'s current abilities:" << endl;
        for(int i = 0; i < 4; i++){
            cout << i+1 << ". " << this->Abilities.at(i) << ":" << endl;
            cout << "Damage: " << this->abilities_Damage.at(i) << ", MP cost: " << this->mp_Cost.at(i) << ", Buff/Debuff: " << this->buff_and_debuff.at(i) << endl;
            cout << endl;
        }

        //ask user which ability to delete or keep ability that just learned
        while(true){
            cout << "Does " << this->name << " want to keep the new skill or forget the new skill? 1.Keep 2.Forget" << endl;
            cin >> input;
            if(input == 1){
                //keep, ask which ability to take away
                cout << "Which skill does " << this->name << " want the new skill to replace? Input 1 to 4" << endl;
                cin >> choice;
                choice--;
                this->Abilities.erase(this->Abilities.begin() + choice);
                this->abilities_Damage.erase(this->abilities_Damage.begin() + choice);
                this->mp_Cost.erase(this->mp_Cost.begin() + choice);
                this->buff_and_debuff.erase(this->buff_and_debuff.begin() + choice);
                this->Slow.erase(this->Slow.begin() + choice);
                this->Heal.erase(this->Heal.begin() + choice);
                this->Emp.erase(this->Emp.begin() + choice);
                break;
            }
            //forget, pop back the ability that the character just learned
            else if(input == 2){
                this->Abilities.pop_back();
                this->abilities_Damage.pop_back();
                this->mp_Cost.pop_back();
                this->buff_and_debuff.pop_back();
                this->Slow.pop_back();
                this->Heal.pop_back();
                this->Emp.pop_back();
                break;
            }
            else{
                cout << "Invalid Input! Try Again." << endl;
            }
        }
    }
}

//secret function to level 5 levels up
void Character::LV_5(){
    if(this->Level < 5){
        this->Level = 5;
        this->Strength += 5 *(5-this->Level);
        this->maxHP += 10 * (5-this->Level);
        this->maxMP += 10 * (5-this->Level);
        this->origSpeed += 5 * (5-this->Level);
        this->maxEXP += (this->maxEXP * 0.1) * (5-this->Level);
        this->Speed = origSpeed;
        this->Empower = this->Strength;
        this->MP = maxMP;
        this->HP = maxHP;
        this->Edit_Abilities();
    }
    else if(this->Level < 30){
        this->Level += 5;
        this->Strength += 5 * 5;
        this->Empower = this->Strength;
        this->maxHP += 10 * 5;
        this->HP = maxHP;
        this->maxMP += 10 * 5;
        this->MP = maxMP;
        this->origSpeed += 5 * 5;
        this->Speed = origSpeed;
        this->attributePoints += 5 * 5;
        this->maxEXP += (this->maxEXP * 0.1) * 5;
        this->Edit_Abilities();
    }
    if(this->Level == 30){
        cout << this->name << " has reached the highest level - 30!" << endl;
    }
    

}