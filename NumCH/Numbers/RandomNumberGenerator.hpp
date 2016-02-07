//
//  RandomNumberGenerator.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef RandomNumberGenerator_cpp
#define RandomNumberGenerator_cpp


#include <stdio.h>


class RandomNumberGenerator {
    
public:
    RandomNumberGenerator(int seed = 173);
    void setSeed( int seed );
    double rand();
    unsigned int randInt();
    double gaussRand();
    double gaussRand(double mean, double sigma);
    void print() const;
    
private:
    unsigned int currentNumber;
    unsigned int m_z;
    unsigned int m_w;
    const unsigned int    MAX_NUM_INT = 0xFFFFFFFF;
    const double INV_MAX_NUM_DBL = 1.0 / (double)MAX_NUM_INT;
    
    double gaussGetXFromCDF(double cdfValue);
    int binarySearchForIndex( double value, double * cdf, int size );
};
    




#endif /* RandomNumberGenerator_cpp */
