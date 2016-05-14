//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "TestNeuralKalmanFilter.hpp"
#include "Network.hpp"
#include "TestExample1.hpp"




int main(int argc, const char * argv[]) {
    
    //runExample1_ADELINE();
    runExample1_NeuralKalman();
    //runExample1_UKF();
    /*
    ANN::Network net({1,1});
    
    std::vector<double> x{1, 5}, y{3, 11};
    
    double error = 0, eps = 1e-2;
    std::vector<double> input(1),output(1);
    std::vector<double> grad(2), dEdO(1);
    for(int i = 0; i < 3000; i++ ){
        error = 0;
        dEdO[0] = 0;
        for( int j = 0; j < 2; j++ ){ grad[j] = 0.0; }
        
        for( int j = 0; j < x.size(); j++ ){
            input[0] = x[j];
            net(input,output);
            double derr = output[0] - y[j];
            error += 0.5*derr*derr;
            dEdO[0] += derr;
            net.backprop(dEdO, grad);
        }
        
        for(int j = 0; j < grad.size(); j++ ){
            net.w()[j] -= eps*grad[j];
        }
        printf("Error = %0.8lf, Grad = [%lf, %lf], Weights = [%lf, %lf]\n",error, grad[0], grad[1], net.weightAt(0), net.weightAt(1));
    }
    */
    
    
    // exit
    return 0;
}

