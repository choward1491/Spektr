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

#define TEMPLATE_HEADER template<   class Coordinate,\
                                    class Data,\
                                    template <typename,typename> LocalFitter,\
                                    template <int,typename,typename> class DistMeas >
#define LR LocalRegression<Coordinate,Data,LocalFitter,DistMeas>



/*
typedef KDTree<Coordinate,Data,DistMeas> Tree;
typedef std::vector<Coordinate> CoordList;
typedef std::vector<Data>       DataList;
 Weight wfunc;
 Tree storage;
 */

TEMPLATE_HEADER
LR::LocalRegression(){}

TEMPLATE_HEADER
LR::LocalRegression( const CoordList & c, const DataList & v ):tree(c,v){}

TEMPLATE_HEADER
void LR::setDataSet( const CoordList & coordinates, const DataList & values ){
    tree.setData(coordinates,values);
}

TEMPLATE_HEADER
Data LR::operator()( const Coordinate & c ) const{
    Tree::NNSet soln;
    tree.findNearestNeighbors( c, LocalFitter<Coordinate,Data>::NumNeighbors, soln );
    return fitter( soln );
}










#undef TEMPLATE_HEADER
#undef LR


#endif /* LocalRegression_Impl_h */
