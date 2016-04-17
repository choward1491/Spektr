//
//  Simulator_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/20/16.
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

#ifndef Simulator_Impl_h
#define Simulator_Impl_h

#include "Simulator.hpp"

/*!
 *
 * Start Code for Sim Framework Definitions. Don't Modify!
 *
 */

template<class Sim, class Integrator>
Simulator<Sim,Integrator>::Simulator() {
    queue.resize(20);
}



template<class Sim, class Integrator>
double Simulator<Sim,Integrator>::getTime() const{
    return state.time.getPreciseTime(); // get precise latest sim time
}


template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::runSim(){
    initialize();
    runMonteCarloSim(); // run all the monte carlo sim
    finalize();         // finalize overall simulation
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::initialize(){
    static bool didSetup = false;
    
    if( !didSetup ){
        
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
        didSetup = true;
    }

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
    if( writeSimHistory ){
        state.mlist.setupSimHistory();  // Setup the sim history files
    }
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
    
    while ( !finishedSimulation() ){     // loop through sim
        
        t->setPreciseTime(scheduler->getNextTime()); // get next time
        tn          = t->getPreciseTime();
        model       = scheduler->pop();     // get model to run at the moment
        
        // put model back on heap at next time it will run
        newt = t->getFractionalTime() + model->getFracDt();
        scheduler->push( newt, model );
        
        
        nextTime    = scheduler->getNextTime().convert<double>();// obtain time of future event
        if( tn < nextTime ){    // if the current time is different than the next
            dt          = tn - to;                              // obtain time step
            integrator.integrate(to, dt,                        // integrate state
                                 state.getStateReference(),
                                 state.mlist.getDiffeqList());
            to = tn;                // update old time to latest time
            
            // update the dynamic models after time integration
            state.mlist.updateDynamicModels();
            
            // execute models in queue
            while( queue.size() != 0 ){
                model = queue.front(); queue.pop_back();
                if( model != 0 ){ model->update(); }            // update discrete model
            }
        }else{
            queue.push_back(model); // add model to queue that will run
                                    // once all models executing at current time have been seen
        }
        
    }// end of simulation run
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::runMonteCarloSim(){
    completedMC = 1;
    for (int iMC = 0; iMC < numMC; iMC++, completedMC++) { // loop through all monte carlo draws
        MonteCarloSetup(iMC);               // setup iMCth monte carlo sim
        runIndividualSim();                 // run an individual sim
        finalizeMonteCarloRun();            // finalize latest individual sim
    }
}

template<class Sim, class Integrator>
size_t Simulator<Sim,Integrator>::getCompletedMC() const{
    return completedMC;
}

template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::setSimHistoryPath( const std::string & filepath ){
    state.dataPrinter.setSimHistoryFileName(filepath);
}

// interface method to add dynamics model
template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::addDynamics( DynamicModel * model ){
    state.mlist.addDynamics(model);
}

// interface method to add discrete model
template<class Sim, class Integrator>
void Simulator<Sim,Integrator>::addDiscrete( DiscreteModel * model , int computationFrequency ){
    state.mlist.addDiscrete(model, computationFrequency);
}

/*!
 *
 * End Code for Sim Framework Definitions.
 *
 */


#endif /* Simulator_Impl_h */
