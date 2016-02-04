//
//  MatScalarMinusExpr.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatScalarMinusExpr_h
#define MatScalarMinusExpr_h


#include "ScalarTypes.hpp"
#include "MatrixExpression.hpp"

template <typename T, typename E1, typename S>
class MatScalarSubtract : public MatExpression<T, MatScalarSubtract<T, E1, S> > {
    E1 const& _u;
    S const& _v;
    
public:
    MatScalarSubtract(MatExpression<T,E1> const& u, S const& v) : _u(u), _v(v) {}
    
    const T & operator()(int r, int c)  const { return _u(r,c)-static_cast<T>(_v); }
    Dims size()                         const { return _u.size(); }
};


template <typename T, typename E1>
MatScalarSubtract<T,E1,double> const
operator-(MatExpression<T, E1> const& u, double const& v) {
    return MatScalarSubtract<T, E1,double>(u, v);
}

template <typename T, typename E1>
MatScalarSubtract<T,E1,int> const
operator-(MatExpression<T, E1> const& u, int const& v) {
    return MatScalarSubtract<T, E1,int>(u, v);
}

template <typename T, typename E1>
MatScalarSubtract<T,E1,float> const
operator-(MatExpression<T, E1> const& u, float const& v) {
    return MatScalarSubtract<T, E1,float>(u, v);
}




template <typename T, typename E1, typename S>
class MatScalarSubtract2 : public MatExpression<T, MatScalarSubtract2<T, E1, S> > {
    E1 const& _u;
    S const& _v;
    
public:
    MatScalarSubtract2(S const& v, MatExpression<T,E1> const& u ) : _u(u), _v(v) {}
    
    const T & operator()(int r, int c)  const { return static_cast<T>(_v) - _u(r,c); }
    Dims size()                         const { return _u.size(); }
};





template <typename T, typename E1>
MatScalarSubtract2<T,E1,double> const
operator-( double const& v, MatExpression<T, E1> const& u ) {
    return MatScalarSubtract2<T, E1,double>(v, u);
}

template <typename T, typename E1>
MatScalarSubtract2<T,E1,float> const
operator-( float const& v, MatExpression<T, E1> const& u ) {
    return MatScalarSubtract2<T, E1,float>(v, u);
}

template <typename T, typename E1>
MatScalarSubtract2<T,E1,int> const
operator-( int const& v, MatExpression<T, E1> const& u ) {
    return MatScalarSubtract2<T, E1,int>(v, u);
}





#endif /* MatScalarMinusExpr_h */
