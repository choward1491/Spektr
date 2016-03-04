//
//  RBF_Poly.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/10/16.
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

#ifndef RBF_Poly_h
#define RBF_Poly_h

#include "Matrix.hpp"
#include <vector>
#include <math.h>

namespace ml {
    
    typedef la::Mat<double> Mat;
    
    namespace rbf {
        class Poly {
        public:
            
            int numDims() const {
                return centers.size();
            }
            
            
            // evaluation methods
            double evaluate( const Mat & x, const Mat & coefs ){
                double output = 0;
                for (int i = 0; i < numDims(); i++) {
                    output += ( coefs(i)*(*this)(x,i) );
                }
                return output;
            }
            
            double operator()( const Mat & x, int index ){
                Mat dx = x - centers[index];
                double r = magnitude(dx)/maxr;
                if (r > 1) {
                    return 0.0;
                }else{
                    return 1.0 + (2.0*r - 3.0)*r*r;
                }
            }
            
            
            // iterator methods
            int start( const Mat & x ){ cindex = -1 + (numDims() > 0); return cindex; }
            int increment(){
                cindex++;
                if( cindex >= numDims() ){
                    return -1;
                }else{ return cindex; }
            }
            
            
            
            std::vector<Mat> centers;
            double maxr;
            
        private:
            double magnitude( const Mat & m ){
                double mag = 0;
                double tmp = 0;
                for (int i = 0; i < m.total(); i++) {
                    tmp = m(i);
                    mag += tmp*tmp;
                }
                return sqrt(mag);
            }
            
            int cindex;
            
        };
    }
}



#endif /* RBF_Poly_h */
