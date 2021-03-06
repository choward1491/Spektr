//
//  LinearKF.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/10/16.
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

#ifndef LinearKF_h
#define LinearKF_h

#include "Matrix.hpp"
#include <vector>

namespace spektr {
    
    namespace filter {
        
        template<class Dynamics, class Measure>
        class LinearKF {
        public:
            
            // define various typedefs for usage in code
            typedef la::SMat<double>    Sym;
            typedef la::Mat<double>     Mat;
            typedef la::LMat<double>    Lower;
            typedef la::DMat<double>    Diag;
            
            // define constructors
            LinearKF();
            LinearKF( const Mat & x0 ); // construct ukf based on initial estimate
            ~LinearKF();
            
            // function that computes cholesky factorization
            // of the Pxx (state coveriance) matrix. This assumes
            // Pxx has been defined. This gets done automatically
            // as start of UKF if user doesn't do it
            void init();
            
            // set the initial state estimate
            void setInitState( const Mat & x0 );
            
            // function that allows user to manipulate
            // state covariance values (Pxx matrix)
            double & stateCov(int i, int j);
            
            // function that allows user to manipulate
            // dynamics noise matrix (Q matrix)
            double & dynNoise(int i, int j);
            
            // function that allows user to manipulate
            // measurement noise matrix (R matrix)
            double & measNoise(int i, int j);
            
            // function to get reference to latest state estimate
            const Mat & state() const;
            
            // function to get reference to latest
            // state covariance estimate
            const Sym & stateCov() const;
            
            // function that takes estimate and current time and
            // updates estimate for state and state covariance.
            // this is the main function that get called at every
            // time step to help propogate the state
            void operator()( double t_, const Mat & meas );
            
            
            
            
            // function to get dimension of state vector
            size_t numState() const { return nx; }
            
            // function to get dimension of measurement vector
            size_t numMeas()  const { return nz; }
            
            // dynamics functor
            Dynamics f;
            
            // measurement functor
            Measure h;
            
        private:
            
            double t;// last time
            Sym Q;   // dynamics noise matrix
            Sym R;   // measurement noise matrix
            Mat x;   // current state estimate
            Sym Pxx; // state covariance matrix
            Sym Pzz; // estimated measurement covariance
            Mat Pxz; // measurement-state cross correlation matrix
            bool setCholesky;   // flag to know if we have
                                // compute cholesky factor
                                // of the Pxx matrix
            
            
            // dimensions of state (nx) and measurement (nz) vectors
            static const size_t nx = Dynamics::Nx;
            static const size_t nz = Measure::Nz;
            
            // helper functions
            void computeStatePrediction( double dt, Mat & xt );
            void computeMeasPrediction( Mat & zt );
            
        };
        
        
        
    }
}


#endif /* LinearKF_h */
