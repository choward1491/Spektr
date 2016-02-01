//
//  RandomInit.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef RandomInit_h
#define RandomInit_h

#include <vector>
#include "RandomNumberGenerator.hpp"
#include "Matrix.hpp"

namespace opt {
    
    class RandomInit {
    private:
        typedef la::Matrix<double, General> vec;
    public:
        void operator()( std::vector<vec> & set, const vec & lb, const vec & rb, int size );
    };
    
}


#endif /* RandomInit_h */
