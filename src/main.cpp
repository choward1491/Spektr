//
//  main.cpp
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include <string>
#include "TestADELINE_Filter1.hpp"
#include "Network.hpp"

void updateWeights( std::vector<double> & w, std::vector<double> grad, double alpha ){
    for(int i = 0; i < w.size(); i++ ){
        w[i] -= alpha*grad[i];
    }
    //w[0] = 2;
    //w[1] = 3;
}

void inputMap( std::vector<double> & in ){
    for(int i = 0; i < in.size(); i++ ){
        in[i] = (in[i]-10.0)/10.0;
    }
}
void outputMap( std::vector<double> & out ){
    
}


int main(int argc, const char * argv[]) {
    
    runExample1_ADELINE();
    
    /*
    ANN::Network net({1,1});
    
    std::vector<double> x, y;
    for(int i = 1; i < 15; i++){
        x.push_back( i );
        y.push_back( 2*i + 3 );
    }
    
    double error = 0;
    std::vector<double> input(1),output(1);
    std::vector<double> grad(2), dEdO(1);
    for(int i = 0; i < 1600; i++ ){
        error = 0;
        for( int j = 0; j < 2; j++ ){ grad[j] = 0.0; }
        
        for( int j = 0; j < x.size(); j++ ){
            input[0] = x[j];
            net(input,output);
            double derr = output[0] - y[j];
            error += 0.5*derr*derr;
            
            dEdO[0] = derr;
            net.backprop(dEdO, grad);
        }
        
        printf("Error(%i) = %lf\n",i,error);
        updateWeights(net.w(), grad, 1e-3);
        printf("Weights = [%lf, %lf]\n",net.weightAt(0), net.weightAt(1));
    }
     */
    
    
    // exit
    return 0;
}

