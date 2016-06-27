//
//  TestANN_Autoencoder.hpp
//  Spektr
//
//  Created by Christian J Howard on 6/24/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef TestANN_Autoencoder_hpp
#define TestANN_Autoencoder_hpp

#include "ANN_Network.hpp"
#include "RandomNumberGenerator.hpp"
#include "FileObject.hpp"
#include "MultiPSO.hpp"
#include "PSO.hpp"
#include "RandomInit.hpp"
#include "GradientBase.hpp"
#include "ConstantStep.hpp"
#include "HessianFreeStep.hpp"


class CostFunction {
public:
    
    CostFunction():net(0),x(0),y(0),batchSize(10){}
    
    void init(){
        grad.resize(net->numWeights(),1);
    }
    
    int numDims(){
        return grad.size().rows;
    }
    
    la::Mat<double> & gradient(){ return grad; }
    
    double operator()( la::Mat<double> & input ){
        
        static la::Mat<double> out(1,1,0), de(1,1,0);
        static la::Mat<double> in(2,1,0);
        grad = 0;
        
        for( int i = 0; i < net->numWeights(); i++ ){
            net->weightAt(i) = input(i);
        }
        
        double toterr = 0;
        int N = 0*batchSize + x->size();
        for( int i = 0; i < N; i++ ){
            int ind = i+0*(rng.randInt()%x->size());
            in[0] = (*x)[ind];
            in[1] = (*y)[ind];
            (*net)(in,out);
            de = (out - in)/static_cast<double>(N);
            net->backprop(de, grad);
            toterr += 0.5*(de[0]*de[0]+de[1]*de[1]);
        }
        return toterr;
    }


    RandomNumberGenerator rng;
    ANN::Network *net;
    std::vector<double> *x, *y;
    static la::Mat<double> grad;
    int batchSize;
    
    
};

la::Mat<double> CostFunction::grad(1,1,0);

typedef opt::gradient<CostFunction, opt::HessianFreeStep > grad_descent;


double testPath( double x ){
    return x*x;
    
    if( x < 0.5 ){
        return 3.0 * x;
    }else{
        return 1.5 - 3*(x-0.5);
    }
}

bool TestANN_Autoencoder(){
    
    // File object for writing data
    FileObject file;
    
    // define random number generator instance
    RandomNumberGenerator rng;
    
    // define number of data values
    const int N = 1000;
    
    // set training data
    std::vector<double> x(N), y(N);
    for(int i = 0; i < N; i++){
        x[i] = i/static_cast<double>(N);
        y[i] = testPath(x[i]);
    }
    
    // set the layers
    std::vector<int> layers { 2, 8, 1, 8, 2 };
    
    // create autoencoder
    ANN::Network autoencoder( layers );
    for( int i = 1; i < layers.size()-1; i++ ){
        autoencoder.setActivationFunc(i, ANN::linear);
    }
    
    // Try to find lower dimensional path representation
    la::Mat<double> guess(autoencoder.numWeights(),1,0);
    la::Mat<double> lb(autoencoder.numWeights(),1), rb(autoencoder.numWeights(),1);
    
    
    for( int i = 0; i < autoencoder.numWeights(); i++ ){
        guess(i) = (1*rng.rand()-0*1.5);
        lb[i] = -3; rb[i] = 3;
    }
    
    
    grad_descent gd;
    gd.setGuess(guess);
    gd.setMaxIter(1000);
    gd.setTolerance(1e-2);
    gd.setMomentumCoef(0.6);
    //gd.step.setStepSize(1e-3);
    gd.func.net = &autoencoder;
    gd.func.x   = &x;
    gd.func.y   = &y;
    gd.func.batchSize = 100;
    gd.func.init();
    gd.init();
    gd.solve();
    
    
    la::Mat<double> in(2,1,0), out(2,1,0);
    
    for( int i = 0; i < autoencoder.numWeights(); i++ ){
        autoencoder.weightAt(i) = gd.soln()[i];
    }
    
    
    // save truth data
    file.openFile("truth.csv", FileObject::Write);
    if( file.isOpen() ){
        for( int i = 0; i < x.size(); i++ ){
            fprintf(file.ref(), "%0.6lf, %0.6lf\n",x[i],y[i]);
        }
    }
    
    // save results
    file.openFile("approx.csv", FileObject::Write);
    if( file.isOpen() ){
        for( int i = 0; i < x.size(); i++ ){
            in[0] = x[i];
            in[1] = y[i];
            autoencoder(in,out);
            fprintf(file.ref(), "%0.6lf, %0.6lf\n",out[0],out[1]);
        }
    }
    
    return true;
}

#endif /* TestANN_Autoencoder_hpp */
