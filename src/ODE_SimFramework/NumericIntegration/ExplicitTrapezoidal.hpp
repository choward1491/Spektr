//
//  ExplicitTrapezoidal.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/22/15.
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

#ifndef ExplicitTrapezoidal_hpp
#define ExplicitTrapezoidal_hpp

#include "DynamicModel.hpp"
#include <vector>

class ExplicitTrapezoidal {
    
public:
    typedef std::vector<DynamicModel*> DiffeqList;
    
    ExplicitTrapezoidal():numDims(-1),k1(0),k2(0){}
    ~ExplicitTrapezoidal();
    void setNumDimensions( int numDimensions );
    void integrate( double time, double dt , double* inOutState, DiffeqList & list );
    
private:
    void clear();
    void create( int totalNumber );
    void computeNewStep( double * y0, double* dydt, double dt, double * out);
    void computeDerivatives( double time, double * & dqdt, DiffeqList & list );
    double* k1;
    double* k2;
    double* tmp;
    
    int numDims;
    
};

#endif /* ExplicitTrapezoidal_hpp */
