//
//  TestANN_GradientCheck.hpp
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

#ifndef TestANN_GradientCheck_h
#define TestANN_GradientCheck_h

#include "ANN_Network.hpp"

bool TestANN_GradientCheck(){
    
    std::vector<int> l {1, 1, 1};
    ANN::Network net( l );
    net.setActivationFunc(1, ANN::leakyReLU);
    net.setActivationFunc(2, ANN::leakyReLU);
    net.weightAt(0) = 5;
    net.weightAt(1) = 7;
    net.weightAt(2) = 1;
    net.weightAt(3) = 3;
    
    la::Mat<double> x(1,1,5), z(1,1,0),grad(4,1,0),dEdO(1,1,1);
    la::Mat<double> true_grad(4,1,0);
    
    true_grad[0] = 5;
    true_grad[1] = 1;
    true_grad[2] = 32;
    true_grad[3] = 1;
    
    net(x,z);
    net.backprop(dEdO, grad);
    
    la::Mat<double> delta = true_grad - grad;
    double norm = sqrt( delta.innerProduct() );
    
    
    return (norm < 1e-10);
}


#endif /* TestANN_GradientCheck_h */
