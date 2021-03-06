//
//  MatScalarAddExpr.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatScalarAddExpr_h
#define MatScalarAddExpr_h

#include "ScalarTypes.hpp"
#include "MatrixExpression.hpp"



/*!
 * This is a class representing the addition
 * of scalars with matrices. This is built to handle
 * using different types of numbers, ints, floats, doubles,
 * and having their use still work even if the matrix
 * uses doubles
 */
template <typename T, typename E1,typename S>
class MatScalarAdd : public MatExpression<T, MatScalarAdd<T, E1, S> > {
    E1 const& _u;
    S const& _v;
    mutable T tmp;
    
public:
    MatScalarAdd(MatExpression<T,E1> const& u, S const& v) : _u(u), _v(v) {}
    
    const T & operator()(int r, int c)  const { tmp = _u(r,c)+static_cast<T>(_v); return tmp; }
    Dims size()                         const { return _u.size(); }
};


template <typename T, typename E1>
MatScalarAdd<T,E1,double> const
operator+(MatExpression<T, E1> const& u, double const& v) {
    return MatScalarAdd<T, E1, double>(u, v);
}

template <typename T, typename E1>
MatScalarAdd<T,E1,double> const
operator+(double const& v, MatExpression<T, E1> const& u) {
    return MatScalarAdd<T, E1, double>(u, v);
}

template <typename T, typename E1>
MatScalarAdd<T,E1,int> const
operator+(MatExpression<T, E1> const& u, int const& v) {
    return MatScalarAdd<T, E1, int>(u, v);
}

template <typename T, typename E1>
MatScalarAdd<T,E1,int> const
operator+(int const& v, MatExpression<T, E1> const& u) {
    return MatScalarAdd<T, E1, int>(u, v);
}


template <typename T, typename E1>
MatScalarAdd<T,E1,float> const
operator+(MatExpression<T, E1> const& u, float const& v) {
    return MatScalarAdd<T, E1, float>(u, v);
}

template <typename T, typename E1>
MatScalarAdd<T,E1,float> const
operator+(float const& v, MatExpression<T, E1> const& u) {
    return MatScalarAdd<T, E1, float>(u, v);
}

#endif /* MatScalarAddExpr_h */
