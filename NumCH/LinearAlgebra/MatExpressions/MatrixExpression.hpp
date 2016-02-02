//
//  MatrixExpression.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatrixExpression_h
#define MatrixExpression_h

#include "Dims.hpp"
#include "MatTypes.hpp"
#include <math.h>
#include <cassert>


// A CRTP base class for Vecs with a size and indexing.
// The template parameter is named 'E' for 'Expression'.
template <typename T, typename E>
class MatExpression {
public:
    const T & operator()(int r, int c) const { return static_cast<E const&>(*this)(r,c);     }
    Dims size()               const { return static_cast<E const&>(*this).size(); }
    
    
    operator E&()             { return static_cast<      E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }
};


#endif /* MatrixExpression_h */
