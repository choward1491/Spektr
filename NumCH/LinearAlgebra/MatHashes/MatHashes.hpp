//
//  MatHashes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatHashes_hpp
#define MatHashes_hpp

#include <stdio.h>
#include "MatTypes.hpp"

template< MatType T >
class Hasher {
public:
    static size_t hash(int i, int j, int nc, int nt){
        return nc*i + j;
    }
    
    static size_t netSize(int r, int c){
        return r*c;
    }
};





#endif /* MatHashes_h */
