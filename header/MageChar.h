#ifndef __MAGE_CHAR_H__
#define __MAGE_CHAR_H__

#include "Character.hpp"

class MageChar: public Character {
    public:
        MageChar();
        MageChar(string, double, double, double);
        ~MageChar(); 
        void attack(); 
        void defend(); 
        void reduceHealth(); 

};

#endif