//
//  SampleCubicModel.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/23/16.
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

#ifndef SampleCubicModel_h
#define SampleCubicModel_h

template<class DataSet, class Sets>
class CubicModel {
public:
    CubicModel(const DataSet & ds_, const Sets & sets_):ds(ds_),sets(sets_){
        coefs[0] = coefs[1] = coefs[2] = coefs[3] = 0.0;
    }
    
    void train( int hold_out_set ){
        double eps = 1e-3;
        grad[0] = grad[1] = grad[2] = grad[3] = 0.0;
        
        for(int iter = 0; iter < 1000; ++iter ){
            N = 0.0;
            for(int set = 0; set < sets.numSets(); ++set ){
                if( set != hold_out_set ){
                    for(int j = 0; j < sets.setSize(set); ++j ){
                        int index = sets(set,j);
                        typename DataSet::Pair p = ds[index];
                        
                        x  = p.x;
                        y  = p.y;
                        N  += 1.0;
                        
                        double e = coefs[0] + (coefs[1] + coefs[2]*x)*x - y;
                        grad[0] += e;
                        grad[1] += e*x;
                        grad[2] += e*x*x;
                        grad[3] += e*x*x*x;
                    }
                }
            }
            
            for(int i = 0; i < 4; ++i){
                grad[i] *= (2.0/N);
                coefs[i] -= eps*grad[i];
            }
        }
        
    }
    
    double testError( int test_set ){
        double error = 0.0;
        double inv_n = 1.0 / static_cast<double>(sets.setSize(test_set));
        for(int j = 0; j < sets.setSize(test_set); ++j ){
            typename DataSet::Pair p = ds[sets(test_set,j)];
            double e = p.y - coefs[0] - ((coefs[2] + coefs[3]*p.x)*p.x + coefs[1])*p.x;
            error += e*e;
        }
        error *= inv_n;
        return error;
    }
    
private:
    const DataSet & ds;
    const Sets & sets;
    double coefs[4];
    double x,x2,xy,y,N;
    double grad[4];
    
};

#endif /* SampleCubicModel_h */
