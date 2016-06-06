//
//  LocalRegression_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/23/16.
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

#ifndef LocalRegression_Impl_h
#define LocalRegression_Impl_h

#include "LocalRegression.hpp"
#include <math.h>

#define TEMPLATE_HEADER template<   class Coordinate,\
                                    class Basis, \
                                    class WeightFunc, \
                                    template <int,typename,typename> class DistMeas \
                                    >
#define LR LocalRegression<Coordinate,Basis,WeightFunc,DistMeas>





TEMPLATE_HEADER
LR::LocalRegression():tree(0){
}

TEMPLATE_HEADER
LR::LocalRegression( Tree & tree_ ):tree(&tree_){
}

TEMPLATE_HEADER
void LR::setDataSet( Tree & tree_ ){
    tree = &tree_;
}

TEMPLATE_HEADER
void LR::setNumNeighborsForFit( int nn_fit ){
    numNeighbors = nn_fit;
}


TEMPLATE_HEADER
void LR::scale( const Coordinate & lb, const Coordinate rb, const Coordinate & in, Coordinate & out){
    for( int i = 0; i < Coordinate::Dims; i++){
        out[i] = (in[i] - lb[i])/(rb[i]-lb[i]);
    }
}


TEMPLATE_HEADER
typename LR::Data LR::solveNormalEqn( Coordinate & c, Neighbors & nset ){
    
    if( y.size().rows != Basis::size ){
        A.resize( Basis::size, Basis::size );
        y.resize( Basis::size, 1);
    }
    
    // find bounds for points
    Coordinate lb = nset[0].point, rb = nset[0].point, tmp;
    
    for( int j = 0; j < Coordinate::Dims ; j++ ){
        for( int i = 1; i < nset.size(); i++ ){
            lb[j] = fmin(nset[i].point[j],lb[j]);
            rb[j] = fmax(nset[i].point[j],rb[j]);
        }
    }
    
    
    
    // compute weights
    std::vector<double> weights(nset.size());
    wfunc(weights,nset);
    
    
    // store values for A
    A = 0;
    for(int j = 0; j < Basis::size; j++ ){
        for( int k = j; k < Basis::size; k++ ){
            for( int i = 0; i < nset.size(); i++ ){
                scale(lb,rb,nset[i].point,tmp);
                A(j,k) += basis(k, tmp)*basis(j, tmp)*weights[i];
            }
        }
    }
    
    
    // store values for y
    y = 0;
    for(int j = 0; j < Basis::size; j++ ){
        for( int i = 0; i < nset.size(); i++ ){
            scale(lb,rb,nset[i].point,tmp);
            y[j] += basis(j, tmp)*weights[i]*nset[i].data;
        }
    }
    
    // solve system of equations
    la::solve(A,y,coef);
    
    // compute point
    Data output = 0;
    
    for( int i = 0; i < Basis::size; i++ ){
        scale(lb,rb,c,tmp);
        output += coef[i]*basis(i,tmp);
    }
    
    return output;
}

TEMPLATE_HEADER
typename LR::Data LR::operator()( Coordinate & c ) {
    Neighbors soln;
    tree->findNearestNeighbors( c, numNeighbors, soln );
    return solveNormalEqn( c, soln );
    
}










#undef TEMPLATE_HEADER
#undef LR


#endif /* LocalRegression_Impl_h */
