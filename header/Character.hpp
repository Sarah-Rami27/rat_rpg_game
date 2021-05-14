#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <string>  

using namespace std; 

class Character {
    protected:
        string name;
        double atk;
        double def;
        double hp; 

    public:
        virtual void attack() = 0; 
        virtual void defend() = 0; 
        virtual void reduceHealth() = 0; 
};

#endif 