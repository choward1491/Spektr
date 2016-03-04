//
//  L2Cost.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef L2Cost_h
#define L2Cost_h

#include <vector>

namespace ANN {
    
template<class Regularization>
class L2Cost {
public:
    
    double operator()( std::vector<double> & truth,
                     std::vector<double> & approx,
                     std::vector<double> & ErrorDeriv) const
    {
        double error = 0.0, dy=0.0;
        double invN = 1.0/(double)truth.size();
        for (int i = 0; i < truth.size(); i++) {
            dy = (approx[i]-truth[i]);
            ErrorDeriv[i] = (approx[i]-truth[i])*invN;
            error += 0.5*dy*ErrorDeriv[i];
        }
        return error;
    }
    
    void regularization( std::vector<double> & weights, std::vector<double> & gradient )
    {
        static_cast<Regularization*>(this)->reg_(weights,gradient);
    }
    
};




class NoReg : public L2Cost<NoReg> {
public:
    void reg_( std::vector<double> & weights, std::vector<double> & gradient ){}
};


    
}






#endif /* L2Cost_h */
