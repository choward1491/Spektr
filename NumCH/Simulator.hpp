//
//  Simulator.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Simulator_cpp
#define Simulator_cpp

#include <stdio.h>
#include "Model.hpp"
#include "heap.h"
#include "GenIntegrator.hpp"
#include "Scheduler.hpp"
#include "RandomNumberGenerator.hpp"

using Rand = NumCH::RandomNumberGenerator;



namespace NumCH {

/*!
 * This object is built to represent
 * a system of ODE equations and
 * discrete time based models that
 * will be solved over time
 *
 *
 */
class Simulator {
    
public:
    
    /*!
     * Simulator null constructor
     *
     * \params None
     * \returns New Simulator Object
     */
    Simulator();
    
    
    
    /*!
     * This method is the main simulation
     * loop. This runs a loop in time and
     * does the necessary time updats and
     * time integration for models based
     * on differential equations.
     *
     * \params None
     * \returns None
     */
    virtual void simLoop();
    
    
    
    /*!
     * This method is the destructor for the simulator
     *
     * \params None
     * \returns None
     */
    virtual ~Simulator();
    
    
    
    
    
    /*!
     * This method initializes the simulation
     *
     * \params None
     * \returns None
     */
    virtual void initialize()               = 0;
    
    
    
    /*!
     * This method checks to see if the simulation
     * has completed. It returns a boolean based
     * on the result of such checks
     *
     * \params None
     * \returns Returns true if the simulation
     *          has finished, returns false
     *          if it hasn't finished
     */
    virtual bool finishedSimulation() const = 0;
    
    
    
    
    /*!
     * This method finalizes the simulation in any
     * ways that appear necessary, such as writing
     * a final file with concluding information,
     * or printing a message to the screen
     *
     * \params None
     * \returns None
     */
    virtual void finalize()                 = 0;
    
    
    
    
    
    
    /*!
     * This method obtains the current simulation time
     *
     * \params None
     * \returns Returns current simulation time
     */
    double getSimTime()const { return curr_time; }
    
    
    
    
    
protected:
    
    friend Model;
    
    
    
    /*!
     * Method to initialize the model array.
     *
     * \params _numModels   This is the number
                            of models being used
                            in this simulation
     * \returns None
     */
    void initModelArray( int _numModels );
    
    
    
    
    
    //
    // Array that will point to the models
    // that are based on differential equations
    // and in turn must be integrated
    //
    // Must have same length as the number
    // of models in this simulation that
    // need to be updated via
    // numerical integration
    //
    
    Model ** models;
    
    //
    // Number of models in the array
    //
    int numModels;
    
    
    
    
    
    
    
    //
    // The current simulation time
    //
    double curr_time;
    
    
    //
    // The last simulation time work
    // was done at
    //
    double last_time;
    
    
    
    
    
    
    //
    // This is the scheduler for the simulation
    //
    Scheduler scheduler;
    
    
    
    
    
    //
    // Random Number Generator for Models to use
    //
    Rand generator;
    
    
    
    
    
    //
    // Place All discrete and continuous Models Here
    //
    
    
    
    
    
    
    //
    // Specify the Time Integrator
    // that will be used for any
    // differential equations
    //
    GenIntegrator* integrator;
    
};

    
}

#endif /* Simulator_cpp */
