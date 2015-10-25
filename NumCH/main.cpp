//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <iostream>
#include "NumCH.h"
typedef NeuralNetwork<1, 1, 1, 1> ANN;



int main(int argc, const char * argv[]) {
    int num = ANN::numWeights;
    
    ANN net;
    
    net(0,0,0) = 1;
    net(0,1,0) = 0;
    net(1,0,0) = 1;
    net(1,1,0) = 0;
    
    double x = 5.0;
    ANN::Input in = { x };
    
    printf("f(%lf) = %lf\n", x, net(in));
    
    
    return 0;
}
