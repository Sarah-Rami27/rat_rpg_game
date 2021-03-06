#ifndef __DAMAGE_INCREASE_H__
#define __DAMAGE_INCREASE_H__

#include "WeaponDecorator.hpp" 
#include "Rng.h"

class DamageIncrease: public WeaponDecorator {
    private: 
        double extraDamage; 
    public:
        DamageIncrease(Weapon*, int); 
        ~DamageIncrease(); 
        double calculateDamage(double, double);  
        void printStats(std::ostream&);
};

#endif 
