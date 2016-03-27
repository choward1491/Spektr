//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "Complex.hpp"
#include "Matrix.hpp"

typedef Complex<float> complex;
typedef la::FastMat<complex,3,3> cm33;
typedef la::FastMat<complex,3,1> cm3;
typedef la::Mat<complex> cmat;

int main(int argc, const char * argv[]) {
    
    cm33 mat(complex(1,2));
    mat(0,0) = 1;
    mat.print();
    mat.t();
    mat.print();
    
    cmat mat2(3,3,complex(1,2));
    mat2(0,0) = 1;
    mat2.print();
    
    
    cm3 x(0);
    x(0) = complex(0,3);
    x(1) = complex(1,0.5);
    x(2) = complex(0,-1);
    x.print();
    
    cm3 b = mat*x;
    b.print();
    b.t();
    b.print();
    
    cm3 b2 = mat2*x;
    b2.print();
    b2.t();
    b2.print();
    
    
    
    // exit
    return 0;
}

