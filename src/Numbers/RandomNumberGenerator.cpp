//
//  RandomNumberGenerator.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "RandomNumberGenerator.hpp"



RandomNumberGenerator::RandomNumberGenerator(int seed){
    setSeed(seed);
}

void RandomNumberGenerator::setSeed( int seed ){
    currentNumber = seed % MAX_NUM_INT;
    p = seed % 16;
    s[0] = (13728 ^ seed);
    for(int i = 1; i < 16; i++ ){
        s[i] = ((234 ^ s[i-1]) << 3) +  s[i-1] ^ seed;
    }
}


double RandomNumberGenerator::rand(){
    return INV_MAX_NUM_DBL * (double)randInt();
}

uint64_t RandomNumberGenerator::randInt(){
    const uint64_t s0 = s[p];
    uint64_t s1 = s[p = (p + 1) & 15];
    s1 ^= s1 << 31; // a
    s[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
    currentNumber = s[p] * UINT64_C(1181783497276652981);
    return currentNumber;
}

double RandomNumberGenerator::gaussRand(){
    return gaussGetXFromCDF( this->rand() );
}

double RandomNumberGenerator::gaussRand(double mean, double sigma){
    double z = gaussGetXFromCDF( this->rand() );
    return z*sigma + mean;
}

double RandomNumberGenerator::gaussGetXFromCDF(double cdfValue){
    
    const int size = 23;
    const int half = size/2;
    double x[] = {-20, -10, -5, -2.50, -1.875, -1.5625, -1.25, -0.9375, -0.625, -0.3125, -0.15625, 	0.0, 0.15625, 0.3125, 0.625, 0.9375, 1.25, 1.5625, 1.875, 2.5, 5.0, 10.0, 20.0};
    double cdf[] = {0, 1.04024324511852e-43, 1.94173988478147e-11, 0.00134953017862185, 0.00688264271044202, 0.0170862893674472, 0.0430088029123236, 0.0976106897365409, 0.193022979479607, 0.331404179122153, 0.413669545623372, 0.500000000000000, 0.586330454376628, 0.668595820877847, 0.806977020520393, 0.902389310263459, 0.956991197087676, 0.982913710632553, 0.993117357289558, 0.998650469821378, 0.999999999980583, 0.999999999999583, 1};
    
    int li = 0;
    if( cdfValue < 0.5 ){
        li = binarySearchForIndex(cdfValue, &cdf[0], half);
    }else{
        li = half + binarySearchForIndex(cdfValue, &cdf[half], half);
    }
    
    double* fi = &cdf[li];
    double* xi = &x[li];
    
    return xi[0] + (xi[1]-xi[0])*(cdfValue - fi[0])/(fi[1]-fi[0]);
    
}



int RandomNumberGenerator::binarySearchForIndex( double value, double * cdf, int size ){
    int end = size-1;
    if( value <= cdf[0] ){ return 0; }
    if( value >= cdf[end] ){ return end-1; }
    int li = 0, ri = end, ci;
    
    // Do binary search
    while( ri - li > 1 ){
        ci = (li + ri) / 2;
        if( value <= cdf[ci] ){
            ri = ci;
        }else{
            li = ci;
        }
    }
    
    return li;
}


void RandomNumberGenerator::print() const{
    printf("Random Number: %0.4lf\n", INV_MAX_NUM_DBL * (double)currentNumber);
}