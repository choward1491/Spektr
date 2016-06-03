//
//  LocalRegression.hpp
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

#ifndef LocalRegression_h
#define LocalRegression_h

#include "KDTree.hpp"
#include "Matrix.hpp"


template<   class Coordinate,
            class Cost, class Basis,
            class WeightFunc,
            template <int,typename,typename> class DistMeas = L2_Norm
            >
class LocalRegression {
public:
    typedef double Data;
    typedef KDTree<Coordinate,Data,DistMeas> Tree;
    typedef Tree::NNSet Neighbors;
    
    LocalRegression();
    LocalRegression( Tree & tree );
    void setDataSet( Tree & tree );
    void setNumNeighborsForFit( int nn_fit );
    Data operator()( const Coordinate & c ) const;
    
    Basis basis;
    WeightFunc wfunc;
    
private:
    
    Data solveNormalEqn( const Coordinate & c, Neighbors & nset );
    void scale( const Coordinate & lb, const Coordinate rb, const Coordinate & in, Coordinate & out);
    
    la::SMat<double> A;
    la::Mat<double>  y;
    la::Mat<double> coef;
    
    int numNeighbors;
    Tree * tree;
    
    
};


#include "LocalRegression_Impl.hpp"


#endif /* LocalRegression_h */
