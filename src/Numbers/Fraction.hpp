//
//  Fraction.h
//  NumCH
//
//  Created by Christian J Howard on 10/31/15.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef Fraction_h
#define Fraction_h

#include <stdio.h>


class Fraction {
public:
    
    typedef unsigned long num_type;
    static Fraction decimal2fraction( double val );
    
    
    Fraction();
    Fraction( double decimal );
    Fraction(int num, int denom );
    Fraction(int complete, int rem_num, int rem_denom );
    template<typename T>
    Fraction( const T & val ){
        *this = val;
    }
    
    Fraction operator*( const Fraction& ) const;
    Fraction operator+( const Fraction& ) const;
    Fraction operator/( const Fraction& ) const;
    Fraction operator-( const Fraction& ) const;
    Fraction operator-() const;
    void operator+=( const Fraction & ) ;
    void operator-=( const Fraction & ) ;
    void operator-(){ positive = !positive; }
    bool operator==( const Fraction & ) const;
    bool operator<( const Fraction & ) const;
    bool operator<=( const Fraction & ) const;
    bool operator>( const Fraction & ) const;
    bool operator>=( const Fraction & ) const;
    bool operator!=( const Fraction & ) const;
    
    template<typename T>
    void operator=( const T & val ){
        *this = Fraction(static_cast<int>(val),1);
    }
    
    template<typename T>
    operator T() const {
        return convert<T>();
    }
    
    
    template< class T>
    T convert() const{
        T output = static_cast<T>(complete) + (static_cast<T>(numerator) / static_cast<T>(denominator));
        if( positive ){ return output; }
        return -output;
    }
    
    void print() const {
        if( positive ){
            printf("%u (%u/%u)\n",complete,numerator,denominator);
        }else{
            printf("-%u (%u/%u)\n",complete,numerator,denominator);
        }
    }
    
    
private:
    friend Fraction;
    
    static void methodOfContinuousFractions( double val, Fraction & frac, double thresh  );
    static void MCF_helper( double val, Fraction & frac, double thresh, int count );
    
    int abs(int a){ if( a >= 0 ){ return a; }else{ return -a; } }
    bool sign( int a ){ return a>=0; }
    num_type gcd(num_type u, num_type v) const;
    num_type numerator;
    num_type denominator;
    num_type complete;
    bool positive;
    
};



#endif /* Fraction_h */
