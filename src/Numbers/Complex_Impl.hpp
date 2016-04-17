//
//  Complex_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/26/16.
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

#ifndef Complex_Impl_h
#define Complex_Impl_h

#define HEADER template<typename T>
#define COMPLEX Complex<T>
#include <math.h>
#include <stdio.h>

HEADER
void COMPLEX::polar2rect( const T & mag, const T & arg ){
    double m = static_cast<double>(mag);
    double a = static_cast<double>(arg);
    re_ = static_cast<T>(m*cos(a));
    im_ = static_cast<T>(m*sin(a));
}

HEADER
void COMPLEX::rect2polar( T & mag, T & arg ) const {
    mag = static_cast<T>(sqrt( static_cast<double>(re_*re_ + im_*im_) ));
    arg = static_cast<T>(atan2( static_cast<double>(im_), static_cast<double>(re_) ));
}

HEADER
COMPLEX::Complex(){
    re_ = static_cast<T>(0);
    im_ = static_cast<T>(0);
}

HEADER
COMPLEX::Complex( const T & a, const T & b , bool useRealImaginary ){
    if( useRealImaginary ){
        re_ = a; im_ = b;
    }else{
        polar2rect(a,b);
    }
}

HEADER
COMPLEX COMPLEX::operator+( const Complex & c ) const{
    return Complex( re_ + c.re_, im_ + c.im_ );
}

HEADER
COMPLEX COMPLEX::operator-( const Complex & c ) const{
    return Complex( re_ - c.re_, im_ - c.im_ );
}

HEADER
COMPLEX COMPLEX::operator*( const Complex & c ) const{
    return Complex(re_*c.re_ - im_*c.im_,re_*c.im_ + c.re_ * im_);
}

HEADER
COMPLEX COMPLEX::operator/( const Complex & c ) const{
    T mag, phase;
    CPolar cp2 = c.polar();
    rect2polar(mag,phase);
    return Complex(mag/cp2.mag,phase-cp2.phase, false);
}

HEADER
COMPLEX COMPLEX::operator-() const{
    return Complex(-re_,-im_);
}

HEADER
void COMPLEX::operator+=( const Complex & c ) {
    re_ += c.re_;
    im_ += c.im_;
}

HEADER
void COMPLEX::operator-=( const Complex & c ) {
    re_ -= c.re_;
    im_ -= c.im_;
}

HEADER
void COMPLEX::operator*=( const Complex & c ) {
    *this = this->operator*(c);
}

HEADER
void COMPLEX::operator/=( const Complex & c ) {
    *this = this->operator/(c);
}



HEADER
typename COMPLEX::CPolar COMPLEX::polar() const{
    CPolar out;
    rect2polar(out.mag,out.phase);
    return out;
}


HEADER
T & COMPLEX::re(){
    return re_;
}

HEADER
T & COMPLEX::im(){
    return im_;
}

HEADER
const T & COMPLEX::re() const{
    return re_;
}

HEADER
const T & COMPLEX::im() const{
    return im_;
}

HEADER
T COMPLEX::abs() const{
    return static_cast<T>(sqrt( static_cast<double>(re_*re_ + im_*im_) ));
}

HEADER
T COMPLEX::phase() const{
    return static_cast<T>(atan2( static_cast<double>(im_), static_cast<double>(re_) ));
}

HEADER
COMPLEX COMPLEX::getconj() const{
    return Complex(re_,-im_);
}

HEADER
void COMPLEX::conj(){
    im_ = -im_;
}

HEADER
void COMPLEX::print() const{
    if( im_ >= 0 ){
        printf("%lf + %lfi",static_cast<double>(re_),fabs(static_cast<double>(im_)));
    }else{
        printf("%lf - %lfi",static_cast<double>(re_),fabs(static_cast<double>(im_)));
    }
}

HEADER
void COMPLEX::println() const{
    if( im_ >= 0 ){
        printf("%lf + %lfi\n",static_cast<double>(re_),fabs(static_cast<double>(im_)));
    }else{
        printf("%lf - %lfi\n",static_cast<double>(re_),fabs(static_cast<double>(im_)));
    }
}
    
#undef HEADER
#undef COMPLEX




#endif /* Complex_Impl_h */
