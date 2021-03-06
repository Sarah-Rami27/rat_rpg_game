#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

class Enemy;        // forward declaration to resolve circular dependency  
#include "Enemy.h"
#include "Armor.hpp"
#include "Weapon.hpp"

#include <string>  
#include <iostream>

using namespace std; 

class Character {
    protected:
        string name;
        double atk;
        double def;
        double curHp; 
        double maxHp; 
        Weapon* currWeapon;
        Armor* currArmor;

    public:
		virtual ~Character() {}
        virtual void attack(Enemy*) = 0; 
        virtual void defend() = 0; 
        virtual void reduceDefense() = 0; 
        virtual void reduceHealth(double damage) = 0;
        virtual void increaseHealth(double heal) = 0;

        virtual void printStats(std::ostream& out) {
            out << "Name: " + name + "\nAtk: " << atk << + "\nDef: " 
            << def << "\nHp: "  << curHp <<  "/" << maxHp << endl;
        } 
        void setCurrWeapon(Weapon* weapon){
            this->currWeapon = weapon;
        }
        void setCurrArmor(Armor* armor){
            this->currArmor = armor;
        }
        Weapon* getCurrWeapon(){
            return this->currWeapon;
        }
        Armor* getCurrArmor(){
            return this->currArmor;
        }

        string getName() const {
            return this->name;
        }
        double getAtk() const {
            return this->atk;
        }
        double getDef() const {
            return this->def;
        }
        double getCurHp() const {
            return this->curHp;
        }
        double getMaxHp() const {
            return this->maxHp;
        }
};

#endif 
