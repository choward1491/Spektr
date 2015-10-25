//
//  Vect.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Vect.hpp"

//
// Data elements
//
//T* elements;

//
// Number of Elements
//
//int numElements;

#ifndef Vect_cpp2
#define Vect_cpp2



        
    
        
    /*!
    * This is the null constructor for the Vect class
    *
    * \returns Vect Object
    */
    template <typename T>
    Vect<T>::Vect(){
        numElements = 0;
        elements    = 0;
    }




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
    template <typename T>
    Vect<T>::Vect( int _numElements, T defaultValue ){
        numElements = _numElements;
        elements = new T[numElements];
        for (int i = 0; i < numElements; i++) {
            elements[i] = defaultValue;
        }
    }






    /*!
    * Constructor that creates a new vector
    * as a copy of an input one
    *
    * \params  Vect Input vector
    * \returns Vect Object
    */
    template <typename T>
    Vect<T>::Vect( const Vect<T> & vect ){
        copy( vect );
    }






    /*!
    * Destructor for Vect class
    *
    * \params  None
    * \returns None
    */
    template <typename T>
    Vect<T>::~Vect(){
        clear();
    }






    //
    // Operators
    //
    template <typename T>
    T & Vect<T>::operator[](int i) const{
        return elements[i];
    }

    template <typename T>
    T & Vect<T>::operator[](int i){
        return elements[i];
    }

    template <typename T>
    Vect<T> Vect<T>::operator*(const T & constant) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]*constant;
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator/( const T & constant) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]/constant;
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator+( const T & constant) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]+constant;
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator-( const T & constant) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]-constant;
        }
        
        return output;
    }
    
    
    template <typename T>
    Vect<T> Vect<T>::operator*(const Vect<T> & vect) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]*vect[i];
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator/(const Vect<T> & vect) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]/vect[i];
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator+(const Vect<T> & vect) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]+vect[i];
        }
        
        return output;
    }
    
    template <typename T>
    Vect<T> Vect<T>::operator-(const Vect<T> & vect) const{
        Vect<T> output(*this);
        for (int i = 0; i < output.size(); i++) {
            output[i] = output[i]-vect[i];
        }
        
        return output;
    }
    
    
    
    
    
    template <typename T>
    Vect<T> & Vect<T>::operator=( const Vect<T> & vect ){
        if( this != &vect ){
            clear();
            copy( vect );
        }
        
        return *this;
    }


    
    
    
    
    
    
    
    
    //
    // Math Stuff
    //

    /*!
    * This is a method to normalize this vector
    *
    * \params  None
    * \returns None
    */
    template <typename T>
    void Vect<T>::normalize(){
        T mag = getMagnitude();
        for (int i = 0; i < numElements; i++) {
            elements[i] = elements[i] / mag;
        }
    }






    /*!
    * This is a method to obtain the magnitude
    * of this vector
    *
    * \params  None
    * \returns Magnitude of Vector
    */
    template <typename T>
    T Vect<T>::getMagnitude(){
        return sqrt( getL2Norm() );
    }








    /*!
    * Method to obtain the L2 Norm of the vector
    *
    * \params  None
    * \returns L2 Norm Value
    */
    template <typename T>
    T Vect<T>::getL2Norm(){
        T output = T();
        for (int i = 0; i < numElements; i++) {
            output = output + elements[i]*elements[i];
        }
    }









    /*!
    * Method to obtain the L1 Norm of the vector
    *
    * \params  None
    * \returns L1 Norm of Vector
    */
    template <typename T>
    T Vect<T>::getL1Norm(){
        T output = T();
        for (int i = 0; i < numElements; i++) {
            output = output + abs(elements[i]);
        }
    }






    /*!
    * Method to create a Normal vector
    * based on the values of this vector
    *
    * \params  None
    * \returns Normalized Vector with same dimensions as
    *          the one that called this method
    */
    template <typename T>
    Vect<T> Vect<T>::getNormal() const{
        return ( *this / getMagnitude() );
    }
    
    
    
    
    template <typename T>
    void Vect<T>::print() const {
        for ( int i = 0; i < numElements; i++ ) {
            if (i == 0 ) {
                printf("< %0.6lf", elements[i]);
            }else{
                printf(", %0.6lf", elements[i]);
            }
        }
        
        printf(" >\n");
    }
    
    
    
    
    
    template <typename T>
    void Vect<T>::clear(){
        if ( elements != 0 ) {
            delete [] elements;
            elements = 0;
        }
    }
    
    template <typename T>
    void Vect<T>::copy( const Vect<T> & vect ){
        numElements = vect.size();
        elements = new T[numElements];
        for (int i = 0; i < numElements; i++) {
            elements[i] = vect[i];
        }
    }
    
    
    
    




#endif