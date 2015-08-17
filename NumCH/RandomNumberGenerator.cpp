//
//  RandomNumberGenerator.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "RandomNumberGenerator.hpp"





NumCH::RandomNumberGenerator::RandomNumberGenerator(int seed){
    currentNumber = seed % MAX_NUM_INT;
}
double NumCH::RandomNumberGenerator::simple(){
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    currentNumber = (m_z << 16) + m_w;
    return INV_MAX_NUM_DBL * (double)currentNumber;
}

void NumCH::RandomNumberGenerator::print() const{
    printf("Random Number: %0.4lf\n", INV_MAX_NUM_DBL * (double)currentNumber);
}