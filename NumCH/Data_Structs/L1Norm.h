//
//  L1Norm.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
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

#ifndef Data_Structs_L1Norm_h
#define Data_Structs_L1Norm_h

#include "kdfunction.h"


template<class T>
T abs( T val ) {
    if( val < (T)0 ){
        return -val;
    }else{
        return val;
    }
}




template< int K, class S, class T>
class L1_Norm : public KDFunction< K, S, T > {
    
public:
    
    virtual ~L1_Norm(){}
    
    virtual T operator()( S & point1, S & point2 ){
        T output;
        T tmp;
        
        for( int i = 0; i < K; i++ ){
            tmp = abs(point1[i] - point2[i]);
            if( i == 0 ){
                output = tmp;
            }else{
                output += tmp;
            }
        }
        
        return output;
    }
    
    virtual T operator()( S & point1, S & point2 , int dim){
        T tmp;
        
        return abs(point1[dim] - point2[dim]);
    }
    
};


#endif
