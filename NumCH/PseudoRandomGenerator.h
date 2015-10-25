//
//  PseudoRandomGenerator.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__PseudoRandomGenerator__
#define __Data_Structs__PseudoRandomGenerator__

#include <stdio.h>

class PseudoRandomGenerator {
public:
    PseudoRandomGenerator():x(1),y(1923),z(12304),seed(123492349){}
    double rand(){
        updateSeed();
        return seed * invCoef;
    }
    unsigned int randInt(){
        updateSeed();
        return seed;
    }
    
    
protected:
    void updateSeed(){
        unsigned int t = x ^ (x << 11);
        x = y; y = z; z = seed;
        seed = seed ^ (seed >> 19) ^ t ^ (t >> 8);
    }
    unsigned int seed;
    unsigned int x, y, z;
    const double invCoef = 1.0/4294967295.0;
    
    
};

#endif /* defined(__Data_Structs__PseudoRandomGenerator__) */
