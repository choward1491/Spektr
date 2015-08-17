//
//  Model.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Model_cpp
#define Model_cpp

#include "Vect.hpp"

//
// Simplified alias for a double Vect
//
using Vec = NumCH::Vect<double>;

namespace NumCH {


/*!
 * This is a class built to represent
 * a model that will be used within
 * the simulation
 *
 */
class Model {
    
public:
    

    /*!
     * This method is used to do any
     * other initialization for a model
     * that won't be done in the constructor,
     * such as if this model depends on any
     * other external models
     *
     * \params None
     * \returns None
     */
    virtual void initialize(){}
    
    
    
    
    
    /*!
     * This method will be used to update
     * any discrete models that aren't
     * based on differential equations
     *
     * \params None
     * \returns None
     */
    virtual void update(){}
    
    
    
    
    
    /*!
     * In the event this model
     * is based on differential
     * equations, this method returns
     * the number of dimensions
     * in the ODE equations
     *
     * \params None
     * \returns Number of Dimensions in System of ODEs
     */
    virtual int numDims(){ return 0; }
    
    
    
    
    
    
    /*!
     * This is a method that represents
     * the system of differential equations
     * and outputs the rate of change of the
     * variables in the equations
     *
     * \params dxdt A vector that will hold the rate of hange
                    of the diffeq variables. This vector
                    will be modified in this method and in
                    turn make this input also the output
     * \returns None
     */
    virtual void equationsOfMotion( Vec & dxdt ){}
    
    
    
    
    
    
    
    /*!
     * This method is for returning state
     * variable values based on a dimension index
     *
     * \params index Dimension index
     * \returns Reference Double value for the state variable
                associated with the input index
     */
    virtual double & operator[](int index) const    = 0;
    
    
    
    
    
    
    /*!
     * This method is for returning state
     * variable values based on a dimension index
     *
     * \params index Dimension index
     * \returns Reference Double value for the state variable
                associated with the input index
     */
    virtual double & operator[](int index)          = 0;
    
    
    
    
    
    /*!
     * This method is to set the rate at which this model will be updated
     *
     * \params updateRateInHz The update rate in Hz
     * \returns None
     */
    void assignUpdateRate( double updateRateInHz ){ timeBetweenUpdates = 1.0/updateRateInHz; }
    
    
    
    
    /*!
     * This method returns the time step between each
     * update of this model
     *
     * \params None
     * \returns Returns the time step between each 
                update of this model
     */
    double getDt() const { return timeBetweenUpdates; }
    
    
private:
    
    //
    // Time between updates
    //
    double timeBetweenUpdates;
    
    
};
    
}


#endif /* Model_cpp */
