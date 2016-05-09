//
//  RecursiveLS.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/8/16.
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

#ifndef RecursiveLS_hpp
#define RecursiveLS_hpp

#include <stdio.h>
#include "Network.hpp"
#include "Matrix.hpp"
#include <queue>
#include "CircularQueue.hpp"

namespace spektr {
    
    namespace filter {
        
        class RecursiveLS {
        public:
            typedef la::Mat<double> Mat;
            
            RecursiveLS();
            RecursiveLS(int num_data);
            void setNumData(int num_data);
            void setInitState( const double & x0 );
            void operator()( double t_, const double & meas );
            const double & state() const;
            
        private:
            
            double estimate;
            Mat wn, Pn, gn, an, xn;
            double delta, lambda;
            CircularQueue<double> list
        };
        
    }
}

#endif /* RecursiveLS_hpp */
