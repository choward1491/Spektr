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
typedef la::Mat<complex> CMat;

int main(int argc, const char * argv[]) {
    
    CMat mat(3,3,complex(1,2));
    mat(0,0) = 1;
    mat.print();
    
    CMat x(3,1,0);
    x(0) = complex(0,3);
    x(1) = complex(1,0.5);
    x(2) = complex(0,-1);
    x.print();
    
    CMat b = mat*x;
    b.print();
    
    complex a = -b(0);
    a.println();
    
    // exit
    return 0;
}

