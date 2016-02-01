//
//  MatScalarMultExpr.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatScalarMultExpr_h
#define MatScalarMultExpr_h

#include "MatrixExpression.hpp"

template <typename T, typename E1>
class MatScalarMult : public MatExpression<T, MatScalarMult<T, E1> > {
    E1 const& _u;
    T const& _v;
    
public:
    MatScalarMult(MatExpression<T,E1> const& u, T const& v) : _u(u), _v(v) {}
    
    const T & operator()(int r, int c)  const { return _u(r,c)*_v; }
    Dims size()                         const { return _u.size(); }
};


template <typename T, typename E1>
MatScalarMult<T,E1> const
operator*(MatExpression<T, E1> const& u, T const& v) {
    return MatScalarMult<T, E1>(u, v);
}

template <typename T, typename E1>
MatScalarMult<T,E1> const
operator*(T const& v, MatExpression<T, E1> const& u) {
    return MatScalarMult<T, E1>(u, v);
}


#endif /* MatScalarMultExpr_h */