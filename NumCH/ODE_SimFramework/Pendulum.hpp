//
//  Pendulum.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Pendulum_hpp
#define Pendulum_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include <math.h>
#include "SimState.hpp"
#include "ConstantsSet.hpp"





/*!
 * These dynamics represent the
 * following model diffeq equation:
 *
 * dxdt = lambda*x
 *
 * The exact solution to this is:
 * x(t) = x(t0) * exp( lambda * t )
 *
 * Note| This equation will blow up if lambda
 * is greater than 0. It is numerically unstable
 * no matter what integration method is used
 */
class PendulumModel : public DynamicModel {
    
public:
    
    /*!
     * This method is used to do initialization
     * that needs to be done every time a sim is run
     * but could benefit from occuring after all the
     * proper model constructions and linking has occurred.
     * A good example could be initializing this model
     * based on data in other models in the simulation.
     * Another use of this function is to ensure each
     * monte carlo sim run is initialized properly
     *
     * \params None
     * \returns None
     */
    virtual void initialize(){
        mass            = generator->rand() * 50 + 50;
        dampening       = generator->rand() * 15;
        lengthPendulum  = generator->rand() * 10;
        gravity         = 9.81;
        state[0]        = generator->rand() * 180 - 180;
        state[1]        = generator->rand() * 5 - 10.0;
    }
    
    
    /*!
     *
     * Method that allows a model to have some
     * data saved to a sim history file
     *
     */
    virtual void setupPrintData(){
        simState->dataPrinter.addVariableToPrint(&state[0], "Theta");
        simState->dataPrinter.addVariableToPrint(&state[1], "ThetaDot");
    }
    
    
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
    virtual int numDims(){ return 2; }
    
    
    
    
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
    virtual void operator()( double time , double* dqdt ){
        double theta    = state[0];
        if( theta > 180 ){ theta -= 180; }
        if( theta < -180 ){ theta += 180; }
        state[0] = theta;
        theta *= Constants::deg2rad;
        double thetaDot = state[1];
        dqdt[0] = thetaDot;
        dqdt[1] = -( dampening*thetaDot/mass + gravity * sin(theta)/ lengthPendulum);
    }
    
    
private:
    double mass;            // in kg
    double dampening;       //
    double gravity;         // m/s^2
    double lengthPendulum;  // in meters
    
    
};

#endif /* Pendulum_hpp */
