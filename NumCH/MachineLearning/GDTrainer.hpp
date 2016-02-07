//
//  GDTrainer.hpp
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

#ifndef GDTrainer_hpp
#define GDTrainer_hpp

#include <stdio.h>
#include "Trainer.hpp"

namespace ANN {
    
    template<class Cost, class Step>
    class GDTrainer : public Trainer<GDTrainer<Cost,Step>> {
    private:
        typedef std::vector<double> vec;
        
        int iter, maxiter;
        vec momentum, dw, y, dE;
        double dstep;
        double mcoef;
        
        

    public:
        GDTrainer();
        Cost cfunc;
        Step sfunc;
        void setMomentumCoef( double mcoef_ );
        void setMaxIterations( int maxiter_ );
        void setDefaultStep( double dstep );
        void init( Network & net);
        bool doneTraining();
        void updateNet( Network & net, DataSet & dset );
    };

    
}

#include "GDTrainerImpl.hpp"

#endif /* GDTrainer_hpp */
