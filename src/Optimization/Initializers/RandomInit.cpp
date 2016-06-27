//
//  RandomInit.cpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "RandomInit.hpp"

namespace opt {
    
void RandomInit::operator()( std::vector<RandomInit::vec> & set,
                            const vec & lb, const vec & rb, int size )
{
    RandomNumberGenerator rng;
    if( set.size() != size ){ set.resize(size); }
    double s = 0;
    for (int i = 0; i < size; i++) {
        if( set[i].size() != lb.size() ){ set[i].resize( lb.size() ); }
        for (int j = 0; j < set[i].size().rows; j++) {
            s = rng.rand();
            set[i][j] = lb[j]*s + rb[j]*(1-s);
        }
    }
}
    
}

