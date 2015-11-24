//
//  Fraction.h
//  NumCH
//
//  Created by Christian J Howard on 10/31/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Fraction_h
#define Fraction_h

#include <stdio.h>


class Fraction {
public:
    Fraction();
    Fraction(int num, int denom );
    
    Fraction operator*( const Fraction& ) const;
    Fraction operator+( const Fraction& ) const;
    Fraction operator/( const Fraction& ) const;
    Fraction operator-( const Fraction& ) const;
    Fraction operator-() const;
    void operator-(){ positive = !positive; }
    bool operator==( const Fraction & ) const;
    bool operator<( const Fraction & ) const;
    bool operator<=( const Fraction & ) const;
    bool operator>( const Fraction & ) const;
    bool operator>=( const Fraction & ) const;
    bool operator!=( const Fraction & ) const;
    
    
    template< class T>
    T convert() const;
    
    void print() const {
        if( positive ){
            printf("%u (%u/%u)\n",complete,numerator,denominator);
        }else{
            printf("-%u (%u/%u)\n",complete,numerator,denominator);
        }
    }
    
    
private:
    friend Fraction;
    
    int abs(int a){ if( a >= 0 ){ return a; }else{ return -a; } }
    bool sign( int a ){ return a>=0; }
    unsigned int gcd(unsigned int u, unsigned int v) const;
    unsigned int numerator;
    unsigned int denominator;
    unsigned int complete;
    bool positive;
    
};



#endif /* Fraction_h */
