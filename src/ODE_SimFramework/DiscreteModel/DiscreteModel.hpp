//
//  DiscreteModel.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/2/15.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef DiscreteModel_hpp
#define DiscreteModel_hpp

#include <stdio.h>
#include "PreciseTime.h"
#include "RandomNumberGenerator.hpp"
#include <string>
#include "SimExceptions.hpp"

typedef RandomNumberGenerator Rand;
class SimState;

/*!
 * This is a class built to represent
 * a model that will be used within
 * the simulation
 *
 */
class DiscreteModel {
    
public:
    
    
    DiscreteModel():model_name("dscrt_model"){}
    
    
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
     * Method to return model name
     *
     * \params None
     * \returns Reference to model name
     */
    virtual const std::string & modelName() const { return model_name; }
    
    
    
    
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
    void assignUpdateRate( int updateRateInHz ){
        try {
            if( updateRateInHz <= 0 ){
                throw sim::exception("Invalid Update Rate: Must be Greater than 0.");
            }
            incrementTime = Time(1, updateRateInHz);
        } catch ( std::exception & e ){
            printf("Error in %s.\nMsg = '%s'\n",model_name.c_str(),e.what());
        }
    }
    
    
    
    
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
    
    
    // method to assign the random number generator
    void assignRandomGenerator( Rand & gen ){ generator = &gen; }
    void assignSimState( SimState & simState_ ){ simState = &simState_; }
    
    
protected:
    
    //
    // Discrete model name
    //
    std::string model_name;
    
    //
    // Time between updates
    //
    Time incrementTime;
    Rand * generator;
    SimState * simState;
    
    
};



#endif /* DiscreteModel_hpp */
