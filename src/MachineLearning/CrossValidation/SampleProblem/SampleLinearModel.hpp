//
//  SampleLinearModel.hpp
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

#ifndef SampleLinearModel_h
#define SampleLinearModel_h

template<class DataSet, class Sets>
class LinearModel {
public:
    LinearModel(const DataSet & ds_, const Sets & sets_):ds(ds_),sets(sets_){
        coefs[0] = coefs[1] = 0.0;
    }
    
    void train( int hold_out_set ){
        x = x2 = xy = y = N = 0.0;
        for(int set = 0; set < sets.numSets(); ++set ){
            if( set != hold_out_set ){
                for(int j = 0; j < sets.setSize(set); ++j ){
                    int index = sets(set,j);
                    typename DataSet::Pair p = ds[index];
                    x  += p.x;
                    x2 += p.x*p.x;
                    xy += p.x *p.y;
                    y  += p.y;
                    N  += 1.0;
                }
            }
        }
        
        coefs[0] = (y*x2 - x*xy)/(N*x2-x*x);
        coefs[1] = (N*xy - x*y) / (N*x2-x*x);
        
    }
    
    double testError( int test_set ){
        double error = 0.0;
        double inv_n = 1.0 / static_cast<double>(sets.setSize(test_set));
        for(int j = 0; j < sets.setSize(test_set); ++j ){
            typename DataSet::Pair p = ds[sets(test_set,j)];
            double e = p.y - coefs[0] - coefs[1]*p.x;
            error += e*e;
        }
        error *= inv_n;
        //printf("Soln = [%lf, %lf]\n",coefs[0],coefs[1]);
        return error;
    }
    
private:
    const DataSet & ds;
    const Sets & sets;
    double coefs[2];
    double x,x2,xy,y,N;
    
};



#endif /* SampleLinearModel_h */
