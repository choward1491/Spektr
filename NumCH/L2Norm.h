//
//  L2Norm.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef Data_Structs_L2Norm_h
#define Data_Structs_L2Norm_h

#include "kdfunction.h"

template< int K, class S, class T>
class L2_Norm : public KDFunction< K, S, T > {
    
public:
    
    virtual ~L2_Norm(){}
    
    virtual T operator()( S & point1, S & point2 ){
        T output;
        T tmp;
        
        for( int i = 0; i < K; i++ ){
            tmp = point1[i] - point2[i];
            if( i == 0 ){
                output = tmp*tmp;
            }else{
                output += tmp*tmp;
            }
        }
        
        return output;
    }
    
    virtual T operator()( S & point1, S & point2 , int dim){
        T tmp;
        
        tmp = point1[dim] - point2[dim];
        
        return tmp*tmp;
    }
    
};


#endif
