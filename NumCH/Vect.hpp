//
//  Vect.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Vect_cpp
#define Vect_cpp

#include <stdio.h>




namespace NumCH {
    
    
    /*!
     * This class represents an ND vector templated class
     * for use in mathematical situations, such as representing
     * a 3D coordinate from one point to another in space
     */
    template <typename T>
    class Vect {
    public:
        
        
        
        /*!
         * This is the null constructor for the Vect class
         *
         * \returns Vect Object
         */
        Vect();
        
        
        
        
        /*!
         * Constructor for Vector that uses
         * the number of dimensions for the vector
         * and a default value for the vector 
         * components as an input
         *
         * \params  _numElements    Number of Dimensions for the vector
         * \params  defaultValue    Default value for vector components.
         *                          Defaults to a value of 0
         * \returns Vect Object
         */
        Vect( int _numElements, T defaultValue = T() );
        
        
        
        
        
        
        /*!
         * Constructor that creates a new vector
         * as a copy of an input one
         *
         * \params  Vect Input vector
         * \returns Vect Object
         */
        Vect( const Vect<T> & vect );
        
        
        
        
        
        
        /*!
         * Destructor for Vect class
         *
         * \params  None
         * \returns None
         */
        ~Vect();
        
        
        
        
        
        
        //
        // Operators
        //
        T & operator[](int i) const;
        T & operator[](int i);
        Vect<T> & operator=( const Vect<T> & vect );
        
        Vect<T> operator*( const T & constant) const;
        Vect<T> operator/( const T & constant) const;
        Vect<T> operator+( const T & constant) const;
        Vect<T> operator-( const T & constant) const;
        
        Vect<T> operator*(const Vect<T> & vect) const;
        Vect<T> operator/(const Vect<T> & vect) const;
        Vect<T> operator+(const Vect<T> & vect) const;
        Vect<T> operator-(const Vect<T> & vect) const;
        
        
        
        //
        // Math Stuff
        //
        
        /*!
         * This is a method to normalize this vector
         *
         * \params  None
         * \returns None
         */
        void normalize();
        
        
        
        
        
        
        /*!
         * This is a method to obtain the magnitude
         * of this vector
         *
         * \params  None
         * \returns Magnitude of Vector
         */
        T getMagnitude();
        
        
        
        
        
        
        
        
        /*!
         * Method to obtain the L2 Norm of the vector
         *
         * \params  None
         * \returns L2 Norm Value
         */
        T getL2Norm();
        
        
        
        
        
        
        
        
        
        /*!
         * Method to obtain the L1 Norm of the vector
         *
         * \params  None
         * \returns L1 Norm of Vector
         */
        T getL1Norm();
        
        
        
        
        
        
        /*!
         * Method to create a Normal vector
         * based on the values of this vector
         *
         * \params  None
         * \returns Normalized Vector with same dimensions as
         *          the one that called this method
         */
        Vect<T> getNormal() const;
        
        
        
        /*!
         * Method to return number of dimensions of this vector
         *
         * \params None
         * \returns Number of Dimensions of Vect
         */
        int size() const { return numElements; }
        
        
        
        
        
        
        void print() const;
        
        
    private:
        
        template<int I, int O, class Q>
        friend class Function;
        
        //
        // Data elements
        //
        T* elements;
        
        //
        // Number of Elements
        //
        int numElements;
        
        
        
        void clear();
        void copy( const Vect<T> & vect );
        
        
    };

}


#include "Vect.cpp"



#endif /* Vect_cpp */



