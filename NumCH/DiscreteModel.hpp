//
//  DiscreteModel.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/2/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef DiscreteModel_hpp
#define DiscreteModel_hpp

#include <stdio.h>
#include "PreciseTime.h"
#include "RandomNumberGenerator.hpp"
typedef RandomNumberGenerator Rand;

class Simulator;

/*!
 * This is a class built to represent
 * a model that will be used within
 * the simulation
 *
 */
class DiscreteModel {
    
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
    
    
    virtual void setupPrintData(){}
    
    
    
    
    // Destructor
    virtual ~DiscreteModel(){}
    
    
    
    
    
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
     * This method is to set the rate at which this model will be updated
     *
     * \params updateRateInHz The update rate in Hz
     * \returns None
     */
    void assignUpdateRate( int updateRateInHz ){ incrementTime = Time(1, updateRateInHz); }
    
    
    
    
    /*!
     * This method returns the time step between each
     * update of this model
     *
     * \params None
     * \returns Returns the time step between each
     update of this model
     */
    double getDt() const { return incrementTime.convert<double>(); }
    Time   getFracDt() const { return incrementTime; }
    
    
    
    
protected:
    
    friend class Simulator;
    
    // method to assign the random number generator
    void assignRandomGenerator( Rand & gen ){ generator = &gen; }
    void assignParentSimulator( Simulator* p ){ parent = p; }
    
    
    
    

    
    //
    // Time between updates
    //
    Time incrementTime;
    
    Simulator* parent;
    
    Rand * generator;
    
    
};



#endif /* DiscreteModel_hpp */
