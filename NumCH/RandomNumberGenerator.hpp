//
//  RandomNumberGenerator.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef RandomNumberGenerator_cpp
#define RandomNumberGenerator_cpp


#include <stdio.h>

namespace NumCH {

class RandomNumberGenerator {
    
public:
    RandomNumberGenerator(int seed = 173);
    double simple();
    void print() const;
    
private:
    unsigned int currentNumber;
    unsigned int m_z;
    unsigned int m_w;
    const unsigned int    MAX_NUM_INT = 0xFFFFFFFF;
    const double INV_MAX_NUM_DBL = 1.0 / (double)MAX_NUM_INT;
    
};
    
}



#endif /* RandomNumberGenerator_cpp */
