//
//  Fraction.cpp
//  NumCH
//
//  Created by Christian J Howard on 10/31/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//


#include "Fraction.hpp"

template<>
void Fraction::operator=( const double & val ){
    *this = Fraction::decimal2fraction(val);
}

template<>
void Fraction::operator=( const float & val ){
    *this = Fraction::decimal2fraction(val);
}

template<>
void Fraction::operator=( const int & val ){
    *this = Fraction(val,1);
}

template<>
double Fraction::convert() const {
    double output = (double)complete + ((double)numerator / (double)denominator);
    if( positive ){ return output; }
    return -output;
}

template<>
float Fraction::convert() const {
    float output = (float)complete + ((float)numerator / (float)denominator);
    if( positive ){ return output; }
    return -output;
}

template<>
int Fraction::convert() const {
    int output = (int)complete;
    if( positive ){ return output; }
    return -output;
}


Fraction::Fraction(){
    numerator = 0;
    denominator = 1;
    complete = 0;
    positive = true;
}

Fraction::Fraction( double decimal ){
    *this = Fraction::decimal2fraction(decimal);
}

Fraction::Fraction(int num, int denom ){
    
    num_type n = abs(num);
    num_type d = abs(denom);
    num_type gc = gcd(n, d);
    n /= gc;
    d /= gc;
    
    if( n >= d ){
        complete = n/d;
        n = n%d;
    }else{ complete = 0; }
    
    positive = sign(num) == sign(denom);
    numerator = n;
    denominator = d;
    
}

Fraction::Fraction(int complete_, int rem_num, int rem_denom ){
    int odd = (complete_ < 0) + ( rem_num < 0 ) + (rem_denom < 0);
    if (odd%2==1) {
        positive = false;
    }else{ positive = true; }
    num_type gc = gcd(rem_num, rem_denom);
    complete = complete_;
    numerator = rem_num / gc;
    denominator = rem_denom / gc;
}

Fraction Fraction::decimal2fraction( double val ){
    Fraction f;
    methodOfContinuousFractions(val, f, 1e-8);
    return f;
}

void Fraction::methodOfContinuousFractions( double val, Fraction & frac, double thresh ){
    double mag = val;
    if( mag < 0 ){ mag = -mag; }
    int w = (int)mag;
    double rem = mag-w;
    Fraction r;
    MCF_helper(rem, r, thresh, 0);
    frac = r + Fraction(w,1);
    frac.positive = (val >= 0);
}

void Fraction::MCF_helper( double val, Fraction & frac, double thresh, int count ){
    if( val > thresh && count <= 20 ){
        double inv = 1.0/val;
        int w = (int)inv;
        double rem = inv-w;
        Fraction r;
        MCF_helper(rem, r, thresh, count + 1);
        frac = Fraction(1,1)/(Fraction(w,1) + r);
    }else{ frac = Fraction(); }
}

Fraction Fraction::operator*( const Fraction& frac ) const{
    Fraction output;
    
    num_type num = this->complete * frac.complete * frac.denominator * this->denominator;
    num += this->numerator * frac.complete * frac.denominator;
    num += this->complete * this->denominator * frac.numerator;
    num += this->numerator * frac.numerator;
    
    num_type denom = this->denominator * frac.denominator;
    num_type gc = gcd(num, denom);
    num /= gc;
    denom /= gc;
    num_type comp = 0;
    
    bool pos = this->positive == frac.positive;
    
    if( num >= denom ){
        comp = num / denom;
        num = num % denom;
    }
    
    output.complete = comp;
    output.numerator = num;
    output.denominator = denom;
    output.positive = pos;
    
    return output;
}

void Fraction::operator+=( const Fraction & f ) {
    *this = *this + f;
}
void Fraction::operator-=( const Fraction & f ) {
    *this = *this - f;
}


/*
 (a + c/b)*(e + g/h) = a*e + e*c/b + a*g/h + c*g/(b*h)
 (a + c/b) + (e + g/h) = (a+e) + (c/b + g/h) = (a+e) + (c*h + g*b)/(b*h)
 (a + c/b) - (e + g/h) = (a-e) + (c/b - g/h) = (a-e) + (c*h - g*b)/(b*h)
 (a + c/b) / (e + g/h) = (a*b + c )*h / (e*h + g)*b = simplify
 */
Fraction Fraction::operator+( const Fraction& frac ) const{
    Fraction output;
    num_type num, denom, gc, comp = 0;
    bool pos;
    
    
    if( frac.positive == this->positive ){
        num = (this->complete + frac.complete)*frac.denominator*this->denominator;
        num += this->numerator*frac.denominator + this->denominator*frac.numerator;
        denom = this->denominator * frac.denominator;
        pos = frac.positive;
    }else{
        
    }
    
    gc = gcd(num, denom);
    num /= gc;
    denom /= gc;
    
    if( num >= denom ){
        comp = num / denom;
        num = num % denom;
    }
    
    output.numerator = num;
    output.denominator = denom;
    output.complete = comp;
    output.positive = pos;
    
    return output;
    
}

/*
 (a + c/b)*(e + g/h) = a*e + e*c/b + a*g/h + c*g/(b*h)
 (a + c/b) + (e + g/h) = (a+e) + (c/b + g/h) = (a+e) + (c*h + g*b)/(b*h)
 (a + c/b) - (e + g/h) = (a-e) + (c/b - g/h) = (a-e) + (c*h - g*b)/(b*h)
 (a + c/b) / (e + g/h) = (a*b + c )*h / (e*h + g)*b = simplify
 */


Fraction Fraction::operator/( const Fraction& frac ) const{
    Fraction output;
    num_type num, denom, gc, comp = 0;
    bool pos = this->positive == frac.positive;
    
    num = (this->complete*this->denominator + this->numerator)*frac.denominator;
    denom = (frac.complete*frac.denominator + frac.numerator)*this->denominator;
    
    gc = gcd(num, denom);
    num /= gc;
    denom /= gc;
    
    if( num >= denom ){
        comp = num / denom;
        num = num % denom;
    }
    
    output.numerator = num;
    output.denominator = denom;
    output.complete = comp;
    output.positive = pos;
    
    
    return output;
}


Fraction Fraction::operator-( const Fraction& frac ) const{
    
    Fraction output;
    num_type num, denom, gc, comp = 0;
    num_type tmp1, tmp2;
    bool pos1, pos2;
    bool pos = true;
    
    if( this->positive != frac.positive ){
        num = (this->complete + frac.complete)*frac.denominator*this->denominator;
        num += this->numerator*frac.denominator + this->denominator*frac.numerator;
        denom = this->denominator * frac.denominator;
        if( !this->positive ){
            pos = false;
        }else{ pos = true; }
        
    }else{
        // compute first term of numerator
        if( this->complete > frac.complete ){
            pos1 = true;
            tmp1 = (this->complete - frac.complete)*frac.denominator*this->denominator;
        }else{
            pos1 = false;
            tmp1 = (frac.complete - this->complete)*frac.denominator*this->denominator;
        }
        
        // compute second term of numerator
        if( this->numerator*frac.denominator > frac.numerator*this->denominator ){
            pos2 = true;
            tmp2 = this->numerator*frac.denominator - frac.numerator*this->denominator;
        }else{
            pos2 = false;
            tmp2 = frac.numerator*this->denominator - this->numerator*frac.denominator;
        }
        
        // try to compute the net numerator
        if( pos1 && pos2 ){
            num = tmp1 + tmp2;
        }else if( !pos1 && !pos2 ){
            num = tmp1 + tmp2;
            pos = false;
        }else if( pos1 ){
            if( tmp1 > tmp2 ){
                num = tmp1 - tmp2;
                pos = true;
            }else{
                num = tmp2 - tmp1;
                pos = false;
            }
        }else{
            if( tmp2 > tmp1 ){
                num = tmp2 - tmp1;
                pos = true;
            }else{
                num = tmp1 - tmp2;
                pos = false;
            }
        }
        
        
        denom = this->denominator * frac.denominator;
        if ( !frac.positive ){
            pos = !pos;
        }
        
    }
    
    gc = gcd(num, denom);
    num /= gc;
    denom /= gc;
    
    if( num >= denom ){
        comp = num / denom;
        num = num % denom;
    }
    
    output.numerator = num;
    output.denominator = denom;
    output.complete = comp;
    output.positive = pos;
    
    return output;
}

Fraction Fraction::operator-() const{
    Fraction output = (*this);
    output.positive = !output.positive;
    return output;
}


bool Fraction::operator==( const Fraction & frac ) const{
    if ( this->positive != frac.positive ){ return false; }
    if ( this->complete != frac.complete ){ return false; }
    if ( this->numerator!= frac.numerator){ return false; }
    if ( this->denominator != frac.denominator ){ return false; }
    return true;
}


bool Fraction::operator<( const Fraction & frac ) const {
    return this->convert<float>() < frac.convert<float>();
}
bool Fraction::operator<=( const Fraction & frac ) const{
    return this->convert<float>() <= frac.convert<float>();
}
bool Fraction::operator>( const Fraction & frac ) const{
    return this->convert<float>() > frac.convert<float>();
}
bool Fraction::operator>=( const Fraction & frac ) const{
    return this->convert<float>() >= frac.convert<float>();
}
bool Fraction::operator!=( const Fraction & frac) const{
    return (positive == frac.positive) && (complete == frac.complete) && (numerator == frac.numerator) && (denominator == frac.denominator);
}


Fraction::num_type Fraction::gcd(num_type u, num_type v) const
{
    int shift;
    
    /* GCD(0,v) == v; GCD(u,0) == u, GCD(0,0) == 0 */
    if (u == 0) return v;
    if (v == 0) return u;
    
    /* Let shift := lg K, where K is the greatest power of 2
     dividing both u and v. */
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }
    
    while ((u & 1) == 0)
        u >>= 1;
    
    /* From here on, u is always odd. */
    do {
        /* remove all factors of 2 in v -- they are not common */
        /*   note: v is not zero, so while will terminate */
        while ((v & 1) == 0)  /* Loop X */
            v >>= 1;
        
        /* Now u and v are both odd. Swap if necessary so u <= v,
         then set v = v - u (which is even). For bignums, the
         swapping is just pointer movement, and the subtraction
         can be done in-place. */
        if (u > v) {
            num_type t = v; v = u; u = t;}  // Swap u and v.
        v = v - u;                       // Here v >= u.
    } while (v != 0);
    
    /* restore common factors of 2 */
    return u << shift;
}









