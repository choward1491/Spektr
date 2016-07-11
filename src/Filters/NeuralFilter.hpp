//
//  NeuralFilter.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/3/16.
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

#ifndef ADELINE_hpp
#define ADELINE_hpp

#include <stdio.h>
#include "ANN_Network.hpp"
#include "Matrix.hpp"
#include <queue>
#include "CircularQueue.hpp"

namespace spektr {
    namespace filter {

        class NeuralFilter {
        public:
            // <define various typedefs for usage in code>
            typedef la::Mat<double> Mat;
            
            // <neural filter constructors>
            NeuralFilter();
            NeuralFilter(int num_data);
            
            // number of data points in sequence to use
            // to try and estimate future points
            void setNumData(int num_data);
            
            // set the initial state estimate
            void setInitState( const Mat & x0 );
            
            // set the max number of optimization iterations, per
            // time step, to use to make the neural network learn
            void setMaxLearningIterations( int max_iter );
            
            // set the learning step size for optimization
            // small step sizes push for slow but sure convergence,
            // while large step sizes lead to tracking the measurements
            void setLearningStepSize( double step );
            
            // operator to update filter estimate based on time
            // and a new measurements
            void operator()( double t_, const Mat & meas );
            
            // function to get latest state estimate
            const Mat & state() const;
            
            // vector storing neural networks.
            // each neural network estimates
            // one component of the state vector
            std::vector<ANN::Network> nets;
            
        private:
            
            // estimate vector
            Mat estimate;
            
            // input vector for neural network
            Mat input;
            
            // output vector for neural network
            Mat out;
            
            // gradient vector
            Mat grad;
            
            // derivative of cost
            // with respect to
            // network output
            Mat dEdO;
            
            // queue storing last N
            // time sequence vectors
            // from the measurement data.
            // these are used as an input to
            // the neural networks to do
            // time series estimation
            CircularQueue<Mat> list;
            
            // maximum iteration count
            // for optimization of networks
            // at each time step
            int max_iters;
            
            // stepsize neural networks
            // train with when using
            // gradient descent
            double stepsize;
            
        };
        
    }
}

#endif /* ADELINE_hpp */
