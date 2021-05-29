#ifndef __RNG_CPP__
#define __RNG_CPP__

#include "../header/Rng.h"

bool RNG::roll(int good, int all) { //good = success, all = total rolls
    double succRate = static_cast<double>(good) / all; //succRate = success percentage
    
    if(succRate == 0.00) { return false; }
    else if(succRate == 1.00) { return true; }
    else { return (double)rand()/RAND_MAX <= succRate; }
}

double RNG::pickDouble(double min, double max) {
    double ratio = (double)rand()/RAND_MAX;
    double result = min + ((max - min) * ratio);
    result = std::ceil(result * 100.0) / 100.0;
    return result;
}

#endif //__RNG_CPP__