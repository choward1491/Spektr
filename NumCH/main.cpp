//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <vector>
#include "ANN.hpp"
#include "Builder.hpp"



int main(int argc, const char * argv[]) {
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    
    ANN::Network net(vec);
    ANN::Builder builder;
    builder(net, ANN::Builder::Type::FeedForward);
    net.print();
    std::vector<double> x(1);
    x[0] = 1.0;
    
    net.randomizeWeights();
    std::vector<double> y = net(x);
    printf("y = %lf\n",y[0]);
    
    
    
    return 0;
}

