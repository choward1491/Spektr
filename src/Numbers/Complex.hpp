//
//  Complex.hpp
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

#ifndef Complex_h
#define Complex_h


template<typename T>
class Complex {
public:
    
    struct CPolar {
        T mag;
        T phase;
    };
    
    
    Complex();
    Complex( const T & a, const T & b , bool useRealImaginary = true );
    
    template<typename S>
    Complex( const S & v ){
        re_ = static_cast<T>(v);
        im_ = static_cast<T>(0);
    }
    
    Complex( const Complex & c ){
        re_ = c.re_;
        im_ = c.im_;
    }
    
    Complex operator+( const Complex & c ) const;
    Complex operator-( const Complex & c ) const;
    Complex operator*( const Complex & c ) const;
    Complex operator/( const Complex & c ) const;
    Complex operator-() const;
    void operator+=( const Complex & c ) ;
    void operator-=( const Complex & c ) ;
    void operator*=( const Complex & c ) ;
    void operator/=( const Complex & c ) ;
    
    template<typename S>
    Complex operator+( const S & v ) const {
        return Complex(re_ + static_cast<T>(v), im_ );
    }
    
    template<typename S>
    Complex operator-( const S & v ) const {
        return Complex(re_ - static_cast<T>(v), im_ );
    }
    
    template<typename S>
    Complex operator*( const S & v ) const {
        return Complex(re_ * static_cast<T>(v), im_ * static_cast<T>(v));
    }
    
    template<typename S>
    Complex operator/( const S & v ) const {
        return Complex(re_ / static_cast<T>(v), im_ / static_cast<T>(v));
    }
    
    template<typename S>
    void operator+=( const S & v ) {
        re_ += static_cast<T>(v);
    }
    
    template<typename S>
    void operator-=( const S & v ) {
        re_ -= static_cast<T>(v);
    }
    
    template<typename S>
    void operator*=( const S & v ) {
        re_ *= static_cast<T>(v); im_ *= static_cast<T>(v);
    }
    
    template<typename S>
    void operator/=( const S & v ) {
        re_ /= static_cast<T>(v); im_ /= static_cast<T>(v);
    }
    
    Complex & operator=( const Complex & v ){
        this->im_ = v.im_;
        this->re_ = v.re_;
        return *this;
    }
    
    template<typename S>
    Complex & operator=( const S & v ){
        this->re_ = static_cast<T>(v);
        this->im_ = static_cast<T>(0);
        return *this;
    }
    
    T & re();
    T & im();
    
    const T & re() const;
    const T & im() const;
    T abs() const;
    T phase() const;
    CPolar polar() const;
    
    
    Complex getconj() const;
    void conj();
    
    void print() const;
    void println() const;
    
private:
    T im_;
    T re_;
    void polar2rect( const T & mag, const T & arg );
    void rect2polar( T & mag, T & arg ) const ;
    
};

#include "Complex_Impl.hpp"


#endif /* Complex_h */
