//
//  ButcherTable.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/15/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef ButcherTable_hpp
#define ButcherTable_hpp

#include <stdio.h>
#include <vector>


class ButcherTable {
public:
    
    ButcherTable();
    ButcherTable( int size, int num_compute = 1 );
    
    void resize( int size, int num_compute = 1 );
    
    double & c(int i);
    double & b(int row, int column);
    double & a(int row, int column);
    const double & c(int i) const;
    const double & b(int row, int column) const;
    const double & a(int row, int column) const;
    
    bool isImplicit() const;
    bool isExplicit() const;
    bool isAdaptive() const;
    
    int numSteps() const;
    int numEstimates() const;
    
private:
    int dim;
    int num_estimates;
    std::vector<double> c_;
    std::vector<double> a_;
    std::vector<double> b_;
};



#endif /* ButcherTable_hpp */
