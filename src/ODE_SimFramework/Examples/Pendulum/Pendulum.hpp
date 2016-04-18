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
#include "SimState.hpp"
#include <math.h>
#include "Constants.hpp"





/*!
 * These dynamics represent a simple 1D nonlinear Pendulum model
 */
class PendulumModel : public DynamicModel {
    
public:
    
    
    PendulumModel(){
        model_name = "pendulum";
    }
    
    
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
        state[0]        = Constants::pi/3;
        state[1]        = Constants::pi/12;
        theta           = state[0];
        thetaDot        = state[1];
    }
    
    
    /*!
     *
     * Method that allows a model to have some
     * data saved to a sim history file
     *
     */
    virtual void setupPrintData(){
        simState->dataPrinter.addVariableToPrint(&state[0],    "Theta");
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
    virtual int numDims() const { return 2; }
    
    
    
    
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
    virtual void operator()( double time , ModelState & dqdt ){
        theta    = state[0];
        thetaDot = state[1];
        dqdt[0] = thetaDot;
        dqdt[1] = -( dampening*thetaDot/mass + gravity * sin(theta)/ lengthPendulum);
    }
    
    
private:
    double theta, thetaDot;
    double mass;            // in kg
    double dampening;       //
    double gravity;         // m/s^2
    double lengthPendulum;  // in meters
    
    
};

#endif /* Pendulum_hpp */
