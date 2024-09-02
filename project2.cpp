#include <iostream>
#include <vector>
#include <random>
#include "Character.cpp"
#include "Warrior.h"
#include "Warrior.cpp"
#include "Magician.h"
#include "Magician.cpp"
#include "Assassin.h"
#include "Assassin.cpp"
#include "Goblin.h"
#include "Bat.h"
#include "Wolf.h"

using namespace std;

class Invalid{};
class back{};
class noMP{};

//user attacking NPC character, NPC character attacking user
void character_attack_character(Character* myChar, Character* enemy, int ability, int damage, int mp_Cost, int slow, int heal, int Emp){
    //check the type of ability casted
    if(myChar->getBuff(ability) == "Healed"){
        myChar->Healing(heal);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to heal 20 HP. \n";
    }
    else if(myChar->getBuff(ability) == "Empowered"){
        myChar->Empowered(Emp);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to gain 10 strengths. \n";
    }
    else if(myChar->getBuff(ability) == "Slow" or myChar->getBuff(ability) == "Wither"){
        enemy->Slowed(slow);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to slow " << enemy->getName() << " for " << slow << " speed. \n";
    }
    else if(myChar->getBuff(ability) == "Stealth"){
        myChar->setStealth(true);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to stealth the upcoming attack. \n";
    }
    //the attack be block if the character recieving the attack used stealth
    if(enemy->getStealth() == true){
        cout << enemy->getName() << " used stealth to dodge the attack but not debuff. \n";
        enemy->setStealth(false); 
    }
    else if(myChar->getDamage(ability) > 0){
        enemy->take_damage(damage);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " deals " << damage << " HP to " << enemy->getName() << ". \n";
    }
    //spend MP after using an ability
    myChar->use_MP(mp_Cost);
}

//user attacking a monster
void user_attack_monster(Character* myChar, Monster* mon, int ability, int damage, int mp_Cost, int slow, int heal, int Emp){
    //check the ability user casts
    if(myChar->getBuff(ability) == "Healed"){
        cout << heal << endl;
        myChar->Healing(heal);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to heal 20 HP. \n";
    }
    else if(myChar->getBuff(ability) == "Empowered"){
        myChar->Empowered(Emp);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to gain 10 strengths. \n";
    }
    else if(myChar->getBuff(ability) == "Slow" or myChar->getBuff(ability) == "Wither"){
        mon->slowed(slow);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to slow " << mon->getName() << " for " << slow << " speed. \n";
    }
    else if(myChar->getBuff(ability) == "Stealth"){
        myChar->setStealth(true);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " to stealth the next attack. \n";
    }
    //monster take damage from user's attack
    if(myChar->getDamage(ability) > 0){
        mon->take_damage(damage);
        cout << myChar->getName() << " uses " << myChar->getAbilities(ability) << " deals " << damage << " HP to " << mon->getName() << ". \n";
    }
    //spend MP after using an ability
    myChar->use_MP(mp_Cost);
}

//monster attacking the user
void monster_attack_user(Character* myChar, Monster* mon, int ability, int Damage, int mpCost){
    //check if the monster has enough HP to use an ability
    if(mon->getMP() >= mpCost){
        //stealth the monster's ability if the user cast stealth
        if(myChar->getStealth() == true){
            cout << myChar->getName() << " used Stealth to dodge the attack. \n";
            myChar->setStealth(false); 
        }
        else{
            myChar->take_damage(Damage);
            cout << mon->getName() << " uses " << mon->getAbilities(ability) << " deals " << Damage << " HP to " << myChar->getName() << ". \n";
        }
        //spend MP from the monster
        mon->use_MP(mpCost);
    }
    else{
        cout << mon->getName() << " does not have enought MP to cast an ability." << endl;
    }
}

//print the fight menu
void Fight_Menu(Character* myChar, Character* enemy, Monster* mon){
    cout << endl;
    if(enemy != nullptr){
        cout << "| " << enemy->getName() << " Level: " << enemy->getLevel() << " | \n";
        cout << "| " << enemy->getHP() <<  " / " << enemy->getmaxHP() << " | \n";
        cout << "| " << enemy->getMP() <<  " / " << enemy->getmaxMP() << " | \n";
    }
    else if(mon != nullptr){
        cout << "| " << mon->getName() << " Level: " << mon->getLevel() << " | \n";
        cout << "| HP: " << mon->getHP() <<  " / " << mon->getmaxHP() << " | \n";
        cout << "| MP: " << mon->getMP() <<  " / " << mon->getmaxMP() << " | \n";
    }
    cout << endl;
    cout << "| " << myChar->getName() << " Level: " << myChar->getLevel() << " | \n";
    cout << "| HP: " << myChar->getHP() <<  " / " <<  myChar->getmaxHP() << " | \n";
    cout << "| MP: " << myChar->getMP() <<  " / " << myChar->getmaxMP() << " | \n";

    cout << endl;
    cout << "------------------------------------" << endl;
    cout << "| 1. Fight 2. Use Item 3. Run Away |" << endl;
    cout << "------------------------------------" << endl;
    cout << endl;
}

//user to choose an ability to cast
int Choose_Ability(Character* myChar){
    int input, size;
    size = myChar->getAbilitiesList().size();

    //ask user for options
    cout << "What ability does " << myChar->getName() << " want to use?" << endl;
    for(int i = 1; i <= size; i++){
        cout << "| " << i << ". " << myChar->getAbilities(i) << " |";
        if(i == 2){
            cout << endl;
        }
    }
    cout << endl << "| 5. Go Back |" << endl;
    cin >> input;

    if(input > 0 and input < size + 1){
        //checks if the user character has enough MP to cast the ability
        if(myChar->getMP_Cost(input) > myChar->getMP()){
            throw noMP();
        }
        return input;
    }
    else if (input == 5){
        //user choose to go back to the last menu
        throw back();
    }
    else{
        //invalid input
        throw Invalid();
    }
    
}

//user to fight in arena
void Fight_in_Arena(Character* myChar, Character* enemy){
    int choice, ability, enemyAbility, input;
    int damage, mpCost, slow, heal, empowered = 0;
    int enemyDamage, enemympCost, enemySlow, enemyHeal;
    string winner;
    string usedItem;
    //Fight in the wild
    cout << myChar->getName() << " encounter " << enemy->getName() << "." << endl;
    while(myChar->getHP() > 0 and enemy->getHP() > 0){
        //display two user character and enemy status bars with the choices menu
        Fight_Menu(myChar, enemy, nullptr);
        cin >> choice;
        if(choice == 1){
            //both player choose ability
            try{
                ability = Choose_Ability(myChar);
                enemyAbility = rand() % enemy->getAbilitiesList().size() + 1;
            }
            catch(back Back){
                continue;
            }
            catch(noMP MP){
                cout << myChar->getName() << " does not have enought MP to cast an ability." << endl;
                continue; 
            }
            catch(Invalid invalid){
                cout << "Invalid Input! Try Again." << endl;
                continue;
            }


            damage = myChar->getDamage(ability) + (myChar->getEmpower() * 0.2);
            mpCost = myChar->getMP_Cost(ability);
            slow = myChar->getSlow(ability);
            heal = myChar->getHeal(ability);
            empowered = myChar->getEmp(ability);

            enemyDamage = enemy->getDamage(enemyAbility) + (enemy->getEmpower() * 0.2);
            enemympCost = enemy->getMP_Cost(enemyAbility);

            //my character is faster, attack first
            if(myChar->getSpeed() >= enemy->getSpeed()){

                //user attack
                character_attack_character(myChar, enemy, ability, damage, mpCost, slow, heal, empowered);

                //check if the enemy dies after the hit, if so break the loop beforehand
                if(enemy->getHP() <= 0){
                    break;
                }

                //enemy attack
                if(enemy->getMP() >= enemympCost){
                    character_attack_character(enemy, myChar, enemyAbility, damage, mpCost, slow, heal, empowered);
                }
                else{
                    cout << enemy->getName() << " does not have enough MP to cast an ability. \n";
                }
            }
            else{
                //enemy attack first
                if(enemy->getMP() >= enemympCost){
                    character_attack_character(enemy, myChar, enemyAbility, damage, mpCost, slow, heal, empowered);
                }
                else{
                    cout << enemy->getName() << " does not have enough MP to cast an ability. \n";
                }

                //check if user died from the attack, if so break loop
                if(myChar->getHP() <= 0){
                    break;
                }

                //user attack
                character_attack_character(myChar, enemy, ability, damage, mpCost, slow, heal, empowered);
            }

        }
        else if(choice == 2){
            //check if theres items or no
            if(myChar->getItemAmount() == 0){
                cout << "No items in your inventory!" << endl;
                continue;
            }
            //display all items
            cout << "Your Inventory:" << endl;
            for(int i = 0; i < myChar->getItemAmount(); i++){
                cout << "| " << i+1 << ". " << myChar->getItemName().at(i) << " x" << myChar->getItemCount().at(i) << " |" << endl;
            }
            cout << endl;
            //ask which item to use or back
            cout << "Which item does " << myChar->getName() << " want to use?" << endl;
            cin >> input;
            if(input == 5){
                continue;
            }
            input--;
            //use item
            myChar->use_Item(input);

            //enemy get to attack
            enemyAbility = rand() % enemy->getAbilitiesList().size() + 1;

            enemyDamage = enemy->getDamage(enemyAbility);
            enemympCost = enemy->getMP_Cost(enemyAbility);
            //enemy attack
            character_attack_character(enemy, myChar, ability, damage, mpCost, slow, heal, empowered);

            if(myChar->getHP() <= 0){
                throw winner = enemy->getName();
                break;
            }

        }
        //user choose to escpae from the fight
        else if(choice == 3){
            cout << myChar->getName() << " runs away." << endl;
            break;
        }
        else if(choice == 4){
            throw winner = enemy->getName();//demonstrate when the user loses
        }
        //invalid input
        else{
            cout << "Invalid Input! Try Again." << endl;
            continue;
        }

    }
    if(enemy->getHP() <= 0){
        throw winner = myChar->getName();
    }
    else{
        throw winner = enemy->getName();
    }

}

//user character fight in the wild
void Fight_in_Wild(Character* myChar, Monster* mon){
    int choice, ability, enemyAbility, input;
    int damage, mpCost, slow, heal, empowered = 0;
    int enemyDamage, enemympCost;
    string winner;
    //Fight in the wild
    cout << myChar->getName() << " encounter " << mon->getName() << "." << endl;
    while(myChar->getHP() > 0 and mon->getHP() > 0){
        //print the fighting menu
        Fight_Menu(myChar, nullptr, mon);
        cin >> choice;
        if(choice == 1){
            //both player choose ability
            try{
                ability = Choose_Ability(myChar);
                enemyAbility = rand() % mon->getAbilitiesList().size() + 1;
            }
            catch(back Back){
                continue;
            }
            catch(noMP MP){
                cout << myChar->getName() << " does not have enought MP to cast an ability." << endl;
                continue; 
            }
            catch(Invalid invalid){
                cout << "Invalid Input! Try Again." << endl;
                continue;
            }

            
            damage = myChar->getDamage(ability) + (myChar->getEmpower() * 0.2);
            mpCost = myChar->getMP_Cost(ability);
            slow = myChar->getSlow(ability);
            heal = myChar->getHeal(ability);
            empowered = myChar->getEmp(ability);

            enemyDamage = mon->getAbilityDamage(enemyAbility) + (mon->getStrength() * 0.2);
            enemympCost = mon->getmpCost(enemyAbility);

            //my character is faster, attack first
            if(myChar->getSpeed() >= mon->getSpeed()){

                //use ability
                user_attack_monster(myChar, mon, ability, damage, mpCost, slow, heal, empowered);

                //check if the enemy dies after the hit, if so break the loop beforehand
                if(mon->getHP() <= 0){
                    break;
                }

                //enemy attack
                monster_attack_user(myChar, mon, enemyAbility, enemyDamage, enemympCost);
            }
            else{
                //enemy attack first
                monster_attack_user(myChar, mon, enemyAbility, enemyDamage, enemympCost);

                //check if user died from the attack, if so break loop
                if(myChar->getHP() <= 0){
                    break;
                }

                //user attack
                user_attack_monster(myChar, mon, ability, damage, mpCost, slow, heal, empowered);
            }

        }
        else if(choice == 2){
            //check if theres items or no
            if(myChar->getItemAmount() == 0){
                cout << "No items in your inventory!" << endl;
                continue;
            }
            //display all items
            cout << "Your Inventory:" << endl;
            for(int i = 0; i < myChar->getItemAmount(); i++){
                cout << "| " << i+1 << ". " << myChar->getItemName().at(i) << " x" << myChar->getItemCount().at(i) << " |" << endl;
            }
            cout << "| 5. Back |" << endl;
            cout << endl;
            //ask which item to use or back
            cout << "Which item does " << myChar->getName() << " want to use?" << endl;
            cin >> input;
            if(input == 5){
                continue;
            }
            input--;
            //use item
            myChar->use_Item(input);

            //enemy get to attack
            enemyAbility = rand() % mon->getAbilitiesList().size() + 1;

            enemyDamage = mon->getAbilityDamage(enemyAbility);
            enemympCost = mon->getmpCost(enemyAbility);
            //enemy attack
            monster_attack_user(myChar, mon, enemyAbility, enemyDamage, enemympCost);

            if(myChar->getHP() <= 0){
                throw winner = mon->getName();
                break;
            }

        }
        else if(choice == 3){
            cout << myChar->getName() << " runs away." << endl;
            break;
        }
        else if(choice == 4){
            throw winner = mon->getName();//demonstrate when the user loses
        }
        else{
            cout << "Invalid Input! Try Again." << endl;
            continue;
        }

    }

    if(mon->getHP() <= 0){
        throw winner = myChar->getName();
    }
    else{
        throw winner = mon->getName();
    }

}

void Wild_Arena(Character* myChar, string WildorArena){
    //check if the user wanted to go into wild or arena
    if(WildorArena == "Wild"){
        int monsterChoice = 0;
        //generate a random monster out of the 3 choices: goblin/bat/wolf
        monsterChoice = rand() % 3 + 1;

        Monster* monster;

        //make a monster pointer with the corresponding random number
        if(monsterChoice == 1){
            monster = new Goblin();
            monster->Lv_Up(myChar->getLevel());
        }
        else if(monsterChoice == 2){
            monster = new Bat();
            monster->Lv_Up(myChar->getLevel());
        }
        else{
            monster = new Wolf();
            monster->Lv_Up(myChar->getLevel());
        }
        //get abilities for the monster
        monster->Edit_Abilities();
        
        Fight_in_Wild(myChar, monster);
    }
    else if(WildorArena == "Arena"){
        int characterChoice = 0;
        //generate a random character out of the 3 choices: warrior/assassin/magician
        characterChoice = rand() % 3 + 1;

        Character* enemy;

        //make a pointer corresponds to the random number
        if(characterChoice == 1){
            enemy = new Warrior(myChar->getLevel());
        }
        else if(characterChoice == 2){
            enemy = new Magician(myChar->getLevel());
        }
        else{
            enemy = new Assassin(myChar->getLevel());
        }
        //get ability for the opposing character
        Fight_in_Arena(myChar, enemy);
    }

}


int Choose_Saved_Game(){
    int input;
    vector<Character*> allChar;
    allChar = read_File();
    print_File(allChar);

    if(allChar.size() == 0){
        //warn the user there is no saved file
        cout << "You have no saved files. You need to start a new character first!" << endl;
        return 6;
    }
    else{
        while(true){
        //ask for which game state user want to load
        cout << "Which game state do you want to load? 6. Back" << endl;
        cin >> input;
        if(input < 1 or input > allChar.size()){
            if(input == 6){
                return input;
            }
            cout << "Invalid game state!" << endl;
        }
        else{
            return input;
        }
        }
    }
}

Character* Load_Previous_Game(int choice){
    //bring out the specific character state the user chose
    Character* myChar;
    vector<Character*> allChar;

    allChar = read_File();

    myChar = allChar.at(choice -1);

    return myChar;
    
}

Character *new_Game(){ //TODO prob change to return a regular character type then pass in the character into the actual in game, declare a character ptr in there.
    string userName;
    int class_choice;

    //name the character
    cout << "What do you want to be named?" << endl;
    //input name
    cin.ignore();
    getline(cin,userName);
    cout << "Hello " << userName << " !" << endl;
    Character* mychar;

    //choose the class of the character
    while(true){
        cout << "What class does " << userName << " want to be? " << endl;
        cout << "1.Warrior: Warriors use swords abilities to attack enemy. They are born with higher HP. \n";
        cout << "2.Magician: Magicians use lighting, fire, and ice magic to attack enemy. They are born with higher Strength. \n";
        cout << "3.Assassin: Assassins use two daggers to attack enemy. They are born with higher speed. \n" << endl;
        cin >> class_choice;

        //Character* mychar = new Character(userName);
        if(class_choice == 1){
            mychar = new Warrior(userName, "Warrior");
            break;
        }
        else if(class_choice == 2){
            mychar = new Magician(userName, "Magician");
            break;
        }
        else if(class_choice == 3){
            mychar = new Assassin(userName, "Assassin");
            break;
        }
        else{
            cout << "Invalid Input! Try Again." << endl;
        }
    }

    return mychar;
}

void In_game(Character* myChar){
    int input, choice, win;
    Character* loadedChar;

    while(true){
        //ask user for option
        cout << endl;
        cout << "What does " << myChar->getName() << " want to do?" << endl;

        cout << "|1. Show " << myChar->getName() << "'s status, 2. Add " << myChar->getName() << "'s attributes, 3. " << myChar->getName() << "'s inventory, 4. Go into wild|" << endl;
        cout << "|5. Fight in arena, 6. Load a game, 7. Save the game, 8. Exit |" << endl;
        cin >> input;
        
        //show status
        if(input == 1){
            myChar->my_Status();
        }
        //add attribute for the character
        else if(input == 2){
            myChar->Add_Attribute();
        }
        //show inventory
        else if(input == 3){
            try{
                myChar->my_Inventory();
            }
            //catch exception if there is no inventory
            catch(string noIven){
                cout << noIven << endl << endl;
            }
        }
        //go into wild
        else if(input == 4){
            try{
                Wild_Arena(myChar, "Wild");
            }
            catch(string winner){
                //print the winner
                cout << winner << " won!" << endl;
                //if the user's character won, the user character recieves exp and has an oppportunity to get a random item
                if(winner == myChar->getName()){
                    myChar->Win();
                }
            }
            //finish the combat so reset the status of the user character
            myChar->Finish_Combat();
            
        }
        //go into arena
        else if(input == 5){
            try{
                Wild_Arena(myChar, "Arena");
            }
            catch(string winner){
                //print the winner
                cout << winner << " won!" << endl;
                //user character recieves exp and item if it wins the battle
                if(winner == myChar->getName()){
                    myChar->Win();
                }
            }
            //finish battle so reset status
            myChar->Finish_Combat();
        }
        else if(input == 6){
            //ask user to choose a saved game
            choice = Choose_Saved_Game();
            //back
            if(choice == 6){
                continue;
            }
            loadedChar = Load_Previous_Game(choice);
            myChar = loadedChar;
        }
        else if(input == 7){
            //save the current character into the file
            myChar->Save();
            continue;
        }
        else if(input == 8){
            //exit
            break;
        }
        else if(input == 9){
            //speical function to level 5 levels up for the character
            myChar->LV_5();
        }
        else{
            //invalid input
            cout << "Invalid Input! Try Again." << endl;
        }

    }
    
}

string start(){
    int input = 0, choice;
    
    while(true){
        cout << "Input the number of your choice:" << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << "| 1. Load A Previous Game | 2. Start A New Game | 3. Exit |" << endl;
        cout << "-----------------------------------------------------------" << endl;

        cin >> input;


        if(input == 1){
            //Load A Previous Game
            Character* savedChar;
            choice = Choose_Saved_Game();
            if(choice == 6){
                continue;
            }
            savedChar = Load_Previous_Game(choice);
            //get into game
            In_game(savedChar);

            delete savedChar;
            savedChar = NULL;
        }
        else if (input == 2){
            //Start a new game
            Character* newChar;
            //Create new character
            newChar = new_Game();
            //get into game
            In_game(newChar);

            delete newChar;
            newChar = NULL;
        }
        else if (input == 3){
            //exit
            return "exit";
        }
        else{
            //Invalid input
            cout << "Invalid Input! Try Again" << endl;
        }
    }


}


int main(){

    if (start() == "exit"){
        return 0;
    }




    return 0;
}