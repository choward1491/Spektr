//
//  FiniteDifference.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/2/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef FiniteDifference_hpp
#define FiniteDifference_hpp

#include <stdio.h>
#include <vector>


class FiniteDifference{
public:
    FiniteDifference();
    FiniteDifference( int center, int stencilSize, int derivOrder );
    void buildApproximation( int center, int stencilSize, int derivOrder );
    double operator()( const std::vector<double> & fvals, double dx ) const;
    
protected:
    std::vector<double> coefs;
    
private:
    
};

#endif /* FiniteDifference_hpp */
