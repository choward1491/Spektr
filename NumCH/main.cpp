//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <vector>
#include "Network.hpp"
#include "RandomNumberGenerator.hpp"
#include "GDTrainer.hpp"
#include "L2Cost.hpp"
#include "ConstantStep.hpp"

void linearDataSet( ANN::DataSet & dset ){
    const int N = 20;
    dset.in.resize(N);
    dset.out.resize(N);
    
    for (int i = 0; i < N; i++) {
        dset.in[i].resize(1);
        dset.out[i].resize(1);
        dset.in[i][0] = i;
        dset.out[i][0] = 5*dset.in[i][0] + 1;
    }
}


int main(int argc, const char * argv[]) {
    
    RandomNumberGenerator rng(3829);
    std::vector<int> layers;
    layers.push_back(1);
    layers.push_back(1);
    
    ANN::Network net(layers);
    net.weightAt(0) = 0;
    net.weightAt(1) = 1;
    
    ANN::DataSet dset;
    linearDataSet(dset);
    
    ANN::GDTrainer<ANN::NoReg, ANN::ConstantStep> trainer;
    trainer.setDefaultStep(1e-3);
    trainer.setMaxIterations(150);
    trainer.setMomentumCoef(0.3);
    trainer.train(net, dset);
    
    
    std::vector<double> x(1),y(1);
    x[0] = 6;
    
    net(x,y);
    
    printf("y = %lf\n",y[0]);
    
    
    return 0;
}

