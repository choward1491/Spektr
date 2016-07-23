//
//  SampleDataSet.h
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

#ifndef SampleDataSet_h
#define SampleDataSet_h

#include <vector>

class QuadraticDataSet {
public:
    typedef double Input;
    typedef double Output;
    struct Pair {
        const Input & x;
        const Output & y;
        Pair( const Input & x_, const Output & y_):x(x_),y(y_){}
    };
    
    QuadraticDataSet(){
        double xbds[] = {-2, 2};
        double N = 10000.0;
        double dx = (xbds[1] - xbds[0])/(N-1.0);
        x.resize((int)N,0);
        y.resize((int)N,0);
        for(int i = 0; i < (int)N; i++){
            x[i] = xbds[0] + dx*i;
            y[i] = x[i]*x[i];
        }
    }
    Pair operator[](int index) const {
        return Pair(x[index],y[index]);
    }
    int size() const{
        return x.size();
    }
    
    
private:
    std::vector<Input> x;
    std::vector<Output> y;
};


#endif /* SampleDataSet_h */
