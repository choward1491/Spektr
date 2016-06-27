//
//  TestANN_SingleClassificationPSO.hpp
//  Spektr
//
//  Created by Christian J Howard on 6/26/16.
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

#ifndef TestANN_SingleClassificationPSO_h
#define TestANN_SingleClassificationPSO_h

#include "ANN_Network.hpp"
#include "RandomNumberGenerator.hpp"
#include "FileObject.hpp"
#include "PSO.hpp"
#include "RandomInit.hpp"


class CostFunction {
public:
    
    CostFunction():net(0),x(0),y(0),batchSize(10){}
    
    void init(){
        //grad.resize(net->numWeights(),1);
    }
    
    int numDims(){
        return grad.size().rows;
    }
    
    double logisticCost( double y, double out, bool isGrad ){
        
        if( isGrad ){
            if( y == 1.0 ){
                return -1.0/out;
            }else{
                return 1.0/(1-out);
            }
        }else{
            if( y == 1.0 ){
                return -log(out);
            }else{
                return -log(1-out);
            }
        }
    }
    
    la::Mat<double> & gradient(){ return grad; }
    
    double operator()( la::Mat<double> & input ){
        
        static la::Mat<double> out(2,1,0), de(2,1,0);
        static la::Mat<double> in(2,1,0);
        grad = 0;
        
        for( int i = 0; i < net->numWeights(); i++ ){
            net->weightAt(i) = input(i);
        }
        
        double toterr = 0;
        int N = x->size();
        for( int i = 0; i < N; i++ ){
            int ind = i+0*(rng.randInt()%x->size());
            in[0] = (*x)[ind];
            in[1] = (*y)[ind];
            (*net)(in,out);
            de = logisticCost((*z)[ind], out[0], true)/static_cast<double>(N);
            toterr += logisticCost((*z)[ind], out[0], false)/static_cast<double>(N);
        }
        return toterr;
    }
    
    
    RandomNumberGenerator rng;
    ANN::Network *net;
    std::vector<double> *x, *y, *z;
    static la::Mat<double> grad;
    int batchSize;
    
    
};

la::Mat<double> CostFunction::grad(1,1,0);

typedef opt::pso<CostFunction,opt::RandomInit> PSO;

static double binaryField( double x, double y ){
    bool check = ((x*x + y*y) <= (0.25*0.25));
    return static_cast<double>(check);
}

bool TestANN_SingleClassificationPSO(){
    
    // File Object to save data
    FileObject file;
    
    // define random number generator instance
    RandomNumberGenerator rng;
    
    // define number of data values
    const int N = 100;
    
    // set training data
    std::vector<double> x(N*N), y(N*N), z(N*N);
    for(int i = 0; i < N; i++){
        for( int j = 0; j < N; j++ ){
            int k = i+N*j;
            x[k] = i/static_cast<double>(N);
            y[k] = j/static_cast<double>(N);
            z[k] = binaryField(x[k],y[k]);
        }
    }
    
    // set the layers
    std::vector<int> layers { 2, 15, 1 };
    
    // create classifier
    ANN::Network classifier( layers );
    classifier.setActivationFunc(2, ANN::sigmoid);
    
    la::Mat<double> guess(classifier.numWeights(),1,0);
    la::Mat<double> lb(classifier.numWeights(),1,0), ub(classifier.numWeights(),1,0);
    
    // Try to classify given inputs
    for( int i = 0; i < classifier.numWeights(); i++ ){
        lb[i] = -1; ub[i] = 1;
    }
    
    
    PSO gd;
    gd.setMaxIter(500);
    gd.setdims(lb, ub);
    gd.setLocalStep(0.5);
    gd.setGlobalStep(0.5);
    gd.setNumParticles(20);
    gd.func.net = &classifier;
    gd.func.x   = &x;
    gd.func.y   = &y;
    gd.func.z   = &z;
    gd.func.init();
    gd.init();
    gd.solve();
    
    
    la::Mat<double> in(2,1,0), out(2,1,0);
    
    for( int i = 0; i < classifier.numWeights(); i++ ){
        classifier.weightAt(i) = gd.soln()[i];
    }
    
    // save truth data
    file.openFile("/Users/christianjhoward/truth.csv", FileObject::Write);
    if( file.isOpen() ){
        for( int i = 0; i < x.size(); i++ ){
            fprintf(file.ref(), "%0.6lf, %0.6lf, %0.6lf\n",x[i],y[i],z[i]);
        }
    }
    
    // save results
    file.openFile("/Users/christianjhoward/approx.csv", FileObject::Write);
    if( file.isOpen() ){
        for( int i = 0; i < x.size(); i++ ){
            in[0] = x[i];
            in[1] = y[i];
            classifier(in,out);
            fprintf(file.ref(), "%0.6lf, %0.6lf, %0.6lf\n",x[i],y[i],out[0]);
        }
    }
    
    
    return true;
}


#endif /* TestANN_SingleClassificationPSO_h */
