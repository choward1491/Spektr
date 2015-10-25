//
//  L1Norm.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
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
