//
//  MatMinusExpr.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatMinusExpr_h
#define MatMinusExpr_h

#include "MatrixExpression.hpp"

/*!
 * This is a class representing subtraction
 * of matrix expressions
 */
template <typename T, typename E1, typename E2>
class MatMinus : public MatExpression<T, MatMinus<T, E1, E2> > {
    E1 const& _u;
    E2 const& _v;
    
public:
    MatMinus(MatExpression<T,E1> const& u, MatExpression<T,E2> const& v) : _u(u), _v(v) {
        assert(u.size() == v.size());
    }
    
    const T & operator()(int r, int c) const { return _u(r,c) - _v(r,c); }
    Dims size()               const { return _v.size(); }
};


template <typename T, typename E1, typename E2>
MatMinus<T,E1,E2> const
operator-(MatExpression<T, E1> const& u, MatExpression<T, E2> const& v) {
    return MatMinus<T, E1, E2>(u, v);
}



#endif /* MatMinusExpr_h */
