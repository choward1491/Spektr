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
#include "Network.hpp"
#include "Matrix.hpp"
#include <queue>
#include "CircularQueue.hpp"

namespace spektr {
    
    namespace filter {

        class NeuralFilter {
        public:
            typedef la::Mat<double> Mat;
            
            NeuralFilter();
            NeuralFilter(int num_data);
            void setNumData(int num_data);
            void setInitState( const Mat & x0 );
            void setMaxLearningIterations( int max_iter );
            void setLearningStepSize( double step );
            void operator()( double t_, const Mat & meas );
            const Mat & state() const;
            Mat truth;
            std::vector<ANN::Network> nets;
            
            
        private:
            
            Mat estimate;
            std::vector<double> input;
            std::vector<double> grad;
            std::vector<double> dEdO;
            std::vector<double> out;
            CircularQueue<Mat> list;
            
            int max_iters;
            double stepsize;
        };
        
    }
}

#endif /* ADELINE_hpp */
