//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <iostream>
//#include "NumCH.h"
//#include "ODESim.h"
#include "cpng.h"
#include "PreciseTime.h"



int main(int argc, const char * argv[]) {
    
    Time test(50,29);
    double val = test.convert<double>();
    printf("Value = %lf\n",val);
    
    return 0;
}

