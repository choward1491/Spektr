//
//  MatMultExpr.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatMultExpr_h
#define MatMultExpr_h


#include "MatrixExpression.hpp"


/*!
 * This is a class representing multiplication
 * of matrix expressions
 */
template <typename T, typename E1, typename E2>
class MatMult : public MatExpression<T, MatMult<T, E1,E2> > {
    E1 const& _u;
    E2 const& _v;
    mutable T sum;
    
public:
    MatMult(MatExpression<T,E1> const& u, MatExpression<T,E2> const& v) : _u(u), _v(v) {
        assert(_u.size().cols == _v.size().rows);
    }
    
    const T & operator()(int r, int c)  const {
        sum = static_cast<T>(0);
        
        for (int ic = 0; ic < _u.size().cols; ic++) {
            sum += _u(r,ic)*_v(ic,c);
        }
        
        return sum;
    }
    Dims size()                         const {
        return Dims(_u.size().rows,_v.size().cols);
    }
};


template <typename T, typename E1, typename E2>
MatMult<T,E1,E2> const
operator*(MatExpression<T, E1> const& u, MatExpression<T, E2> const& v) {
    return MatMult<T, E1, E2>(u, v);
}



#endif /* MatMultExpr_h */
