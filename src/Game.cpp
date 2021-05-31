#ifndef __GAME_CPP__
#define __GAME_CPP__

#include "../header/Game.h"
#include <iostream>

using namespace std;

Game::Game() {
    factory = nullptr;
    player = nullptr;
    levelNum = 1; 
    enemy = nullptr;
    telegraph = false;
    smashed = false;
}

Game::~Game() {
    delete factory; 
    delete player; 
    delete enemy;
}

bool Game::isAlive(){
    if((player->getCurHp() <= 0) || smashed){
        return false;
    }
    return true;
}

void Game::setFactory(int charType) {
    if (charType == 1) {
        this->factory = new WarriorFactory(); 
    }
    else if (charType == 2) {
        this->factory = new MageFactory();
    }
}

void Game::displayOptions() {
    cout << endl;
    cout << "Rat Hero!, Pick your next move! (input a number)" << endl;
    cout << "1) Attack the enemy!" << endl;
    cout << "2) Defend!" << endl;
    cout << "Input: ";
}


void Game::createPlayer() {
    this->player = this->factory->createCharacter(); 
}

void Game::spawnEnemy() {
    cout << "You have encountered an enemy!\n";
    this->enemy = new Enemy(this->levelNum);
    cout << enemy->getName() << " approaches!" << endl;
}

void Game::spawnLoot() {
    Loot loot; 
    int playerInput;

    Weapon* newWeapon = loot.spawnWeapon(levelNum, factory); 
    cout << "You found a new weapon!" << endl;
    std::string weaponPrompt = "Do you want to replace your current weapon?\n1) Yes\n2) No\n3) Compare stats\nInput: ";
    cout << weaponPrompt; 
    
    while (true) {
        cin >> playerInput; 
        if (playerInput == 1) {
            delete player->getCurrWeapon();
            player->setCurrWeapon(newWeapon);
	    cout << endl;
            cout << "You take the new weapon." << endl;
        }
        else if (playerInput == 2) {
            delete newWeapon; 
	    cout << endl;
            cout << "You leave the new weapon." << endl;
        }
        else if (playerInput == 3) {
	    cout << endl;
            cout << "NEW WEAPON STATS" << endl; 
            cout << "================" << endl;
            newWeapon->printStats(cout);
            cout << endl; 
            cout << "CURRENT WEAPON STATS" << endl; 
            cout << "====================" << endl;
            player->getCurrWeapon()->printStats(cout);
            cout << endl;
            cout << weaponPrompt; 
            continue; 
        }
        else {
            cout << "Enter a valid input: ";
	    if(cin.fail()) {
	        cin.clear();
	        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    }
            continue;
        }
        break;
    }
    cout << endl;    
 
    Armor* newArmor = loot.spawnArmor(levelNum, factory);
    cout << "You found new armor!" << endl;
    std::string armorPrompt = "Do you want to replace your current armor?\n1) Yes\n2) No\n3) Compare stats\nInput: ";
    cout << armorPrompt; 
    
    while (true) {
        cin >> playerInput; 
        if (playerInput == 1) {
            delete player->getCurrArmor();
            player->setCurrArmor(newArmor);
	    cout << endl;
            cout << "You take the new armor." << endl;
        }
        else if (playerInput == 2) {
            delete newArmor; 
	    cout << endl;
            cout << "You leave the new armor." << endl;
        }
        else if (playerInput == 3) {
	    cout << endl;
            cout << "NEW ARMOR STATS" << endl;
            cout << "===============" << endl; 
            newArmor->printStats(cout); 
            cout << endl;
            cout << "CURRENT ARMOR STATS" << endl; 
            cout << "===================" << endl;
            player->getCurrArmor()->printStats(cout);
            cout << endl;
            cout << armorPrompt; 
            continue; 
        }
        else {
            cout << "Enter a valid input: ";
	    if(cin.fail()) {
	        cin.clear();
	        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    }
            continue;
        }
        break;
    }
    cout << endl;

    player->increaseHealth(player->getMaxHp() * loot.spawnFood());
    cout << endl;
}

void Game::startCombat() {
    spawnEnemy();
    while(player->getCurHp() > 0 && enemy->getHp() > 0 && !smashed){
        int userInput;
	
	if(rng.roll(1,5)) { //head on attack!
    		cout << endl;
		cout << "\e[1;31mSkinner is preparing a head on smash!!!...\e[0m";
		telegraph = true;
		cout << endl;;
	}
	
        displayOptions();                                   //1) attack 2)defend
        cin >> userInput;
	if(cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

        while(userInput != 1 && userInput != 2){
            cout << "Please enter a valid choice: ";
            cin >> userInput;
	    if(cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    }
        }
	
        if(userInput == 1){
            player->attack(enemy);                              //player attacks first

            if(enemy->getHp() <= 0){                            //player wins
		cout << "You have slain the enemy! Your rat legend continues." << endl << endl;
                if (levelNum % 5 == 0) {
                    spawnLoot();   
                }
                delete this->enemy;
		telegraph = false;
                ++levelNum;
                return;
            }
        }

        if(userInput == 2){
            player->defend();
        }

        if(enemy->getHp() > 0){                             
            if(telegraph && userInput != 2) {
		cout << "\e[1;31mSkinner ended you instantly! Perhaps you'll defend in another life...\e[0m" << endl;	
		cout << endl;
		cout << " ,-=-. " << endl;
		cout << "/  +  \\" << endl;
		cout << "| ~~~ |" << endl;
		cout << "|R.I.P|" << endl;
		cout << "|_____|" << endl;
		cout << endl;
		smashed = true;
		return;	
	    }
	    else if(telegraph && userInput == 2) {
		cout << "Your preperation payed off, you defended the attack! 0 damage taken." << endl;
	    }
	    else {
            	enemy->attack(player);                          //enemy attacks player
	    }
            if (player->getCurHp() <= 0) {
		cout << endl;
		cout<<R"(
        ,-=-.       
       /  +  \     
       | ~~~ |    
       |R.I.P|      
,v,VvV,|_____|V,vV,v
        )";
		cout << endl;
                return;                                     //enemy wins
            }
	    telegraph = false;
        }

        if(userInput == 2) {
            player->reduceDefense();
        }
    }
}


#endif 
