//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "Quaternion.hpp"

int main(int argc, const char * argv[]) {
    
    vec3 x = vec3_ops::equal(0.0, -1.0, 0.0);
    x.print();
    //Quaternion q( 0, 0, Constants::pi*0.5);
    Quaternion q(Constants::pi*0.5, vec3_ops::equal(0, 0, 1));
    Quaternion qinv = q.getInverse();
    vec3 xn = q.rotate(x);
    xn.print();
    
    
    // exit
    return 0;
}

