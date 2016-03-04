//
//  TemplateSimulator.h
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
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

#ifndef TemplateSimulator_h
#define TemplateSimulator_h

#include "ModelList.hpp"
#include "SimState.hpp"
#include "SimTime.hpp"
#include "NumericIntegration.h"

class TimeStep : public DiscreteModel {};

template<class Sim, class Integrator = ExplicitEuler >
class Simulator {
public:
    
    void initialize();
    void runSim();
    void addConfigFile( const char * filename );
    void addConfigFile( const std::string & filename );
    double getTime() const;
    
protected:
    
    SimState state;
    Rand generator;
    int numMC;
    bool writeSimHistory;
    Integrator integrator;
    
private:
    
    void initializeModels();
    void setupSimHistory();
    void linkModelsToSim();
    void connectModelsTogether();
    bool finishedSimulation();
    void finalizeMonteCarloRun();
    void finalize();
    void buildTotalDynamicState();
    void MonteCarloSetup( int monteCarloCount );
    void runIndividualSim();
    void runMonteCarloSim();
};




/*!
 *
 * Start Code for Sim Framework Definitions. Don't Modify!
 *
 */

template<class Sim, class Integrator>
double Simulator<Sim,Integrator>::getTime() const{
    return state.time.getPreciseTime(); // get precise latest sim time
}

    
template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::runSim(){
    runMonteCarloSim(); // run all the monte carlo sim
    finalize();         // finalize overall simulation
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::initialize(){
    
    if ( writeSimHistory ){     // add printer model if writing history
        state.mlist.addDiscrete( &state.dataPrinter, state.printFrequency);
        state.dataPrinter.addVariableToPrint( state.time.refNewTime(), "Time");
    }
    
    
    linkModelsToSim();          // add other models to sim
    buildTotalDynamicState();   // build dynamic state array
    integrator.setNumDimensions(state.size()); // initialize integrator
    state.mlist.addParentData(state, generator); // add state and RNG to models
    setupSimHistory();          // add variables that will be printed
    connectModelsTogether();    // connect models together if needed
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::initializeModels(){
    state.mlist.initializeModels(); // initialize the models
}




/*!
 *
 * Start to write CRTP methods.
 * Check internals to see what the Sim template parameter
 * should have for some of its public methods
 *
 */

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::linkModelsToSim(){
    static_cast<Sim*>(this)->_linkModelsToSim( state );
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::connectModelsTogether(){
    static_cast<Sim*>(this)->_connectModelsTogether();
}


template<class Sim, class Integrator>
bool Simulator<Sim,Integrator>::finishedSimulation()  {
    return static_cast<Sim*>(this)->_finishedSimulation( state );
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::finalizeMonteCarloRun() {
    static_cast<Sim*>(this)->_finalizeMonteCarloRun();
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::finalize() {
    static_cast<Sim*>(this)->_finalize();
}

/*!
 *
 * End to CRTP methods.
 *
 */




template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::setupSimHistory(){
    state.mlist.setupSimHistory();  // Setup the sim history files
}


template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::addConfigFile( const char * filename ){
    state.parser.parse( filename );  // parse 'filename'
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::addConfigFile( const std::string & filename ){
    state.parser.parse( filename.c_str() ); // parse 'filename'
}


template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::buildTotalDynamicState(){
    if( state.isEmpty() ){      // if dynamic state is empty
        state.buildState();     // then build the state
    }
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::MonteCarloSetup( int monteCarloCount ){
    initializeModels();     // Initialize models for ith MC run
    
    
    if( monteCarloCount >= 0 ){     // If new monte carlo run, reset everything
        state.mlist.scheduler.reset();
        state.time.nullTime();
        
        if( monteCarloCount != 0 ){
            state.dataPrinter.newMonteCarlo();
        }else{
            state.dataPrinter.reset();
        }
    }
    
    if( writeSimHistory ){              // if writing a sim history,
        state.dataPrinter.update();     // update output sim history
    }                                   // file with initial condition
    
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::runIndividualSim(){
    DiscreteModel* model = 0;   // init temporary discrete model
    
    double dt = 0.0;            // init step size
    double tn = 0;              // init new time var
    double to = 0;              // init old time var
    double nextTime = 0.0;      // init temp var for holding next scheduled time
    Time newt(0,1);             // init model's next time to appear var
    SimTime* t = &state.time;   // get SimTime reference
    
    Scheduler* scheduler = &state.mlist.scheduler;  // reference scheduler
    t->setPreciseTime(scheduler->getNextTime());    // set latest time to first nonzero start time
    
    while ( not finishedSimulation() ){     // loop through sim
        tn          = t->getPreciseTime();  // obtain t_{i+1}
        model       = scheduler->pop();     // get model to run
        
        
        // put model back on heap at next time
        newt = t->getFractionalTime() + model->getFracDt();
        scheduler->push( newt, model );
        nextTime    = scheduler->getNextTime().convert<double>();        // obtain time of future event
        dt          = tn - to;                                          // obtain time step
        
        
        if( tn != nextTime ){    // if the current time is different than the next
            integrator.integrate(to, dt,                        // integrate state
                                 state.getStateReference(),
                                 state.mlist.getDiffeqList());
            to = tn;                // update old time to latest time
            t->setLastTime( tn );   // update old time to latest time
        }
        
        if( model != 0 ){ model->update(); }            // update discrete model
        t->setPreciseTime(scheduler->getNextTime());    // update precise time
        
    }// end of simulation run
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::runMonteCarloSim(){
    for (int iMC = 0; iMC < numMC; iMC++) { // loop through all monte carlo draws
        MonteCarloSetup(iMC);               // setup iMCth monte carlo sim
        runIndividualSim();                 // run an individual sim
        finalizeMonteCarloRun();            // finalize latest individual sim
    }
}

/*!
 *
 * End Code for Sim Framework Definitions.
 *
 */



#endif /* TemplateSimulator_h */
