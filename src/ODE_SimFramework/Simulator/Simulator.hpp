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


/*!
 *
 * Templated class to represent a specific simulation
 * that has a default Explicit Euler integration approach
 * and uses a CRTP Sim template parameter.
 *
 * The resulting Sim input needs to implement some extra methods,
 * which are defined in the private section of the class.
 *
 */
template<class Sim, class Integrator = ExplicitEuler >
class Simulator {
public:
    
    // Method to run the actual simulation
    void runSim();
    
    // Methods to pass in a config file path
    void addConfigFile( const char * filename );
    void addConfigFile( const std::string & filename );
    
    // Method to get the current sim time (used by models)
    double getTime() const;
    
    // get number of completed Monte Carlo runs
    size_t getCompletedMC() const;
    
    // method to grab values from config files
    template<typename T>
    T get(const std::string & param){
        return state.parser.getValueFrom<T>(param);
    }
    
    // set the sim history file
    void setSimHistoryPath( const std::string & filepath );
    
    // interface method to add dynamics model
    void addDynamics( DynamicModel * model );
    
    // interface method to add discrete model
    void addDiscrete( DiscreteModel * model , int computationFrequency );
    
    
protected:
    
    SimState state;        // data structure holding main sim states
    Rand generator;        // centralized random number generator
    size_t numMC;          // the total number of monte carlo runs
    size_t completedMC;    // the completed number of monte carlo runs
    bool writeSimHistory;  // flag used to decide whether to write results
    Integrator integrator; // Integrator class
    
private:
    
    
    void initialize();              // Method to initialize everything before running a simulation
    void initializeModels();        // method to initialize models
    void setupSimHistory();         // method to setup sim history
    void linkModelsToSim();         // method to link models to sim
    void connectModelsTogether();   // method to connect models together, if necessary
    bool finishedSimulation();      // method to return whether the sim has finished
    void finalizeMonteCarloRun();   // method to finalize a monte carlo run
    void finalize();                // method to finalize the whole completed simulation
    void buildTotalDynamicState();  // method to construct the total data associated with dynamic models
    void MonteCarloSetup( int monteCarloCount ); // method to setup ith monte carlo draws
    void runIndividualSim();        // method to run an individual simulation
    void runMonteCarloSim();        // method to run a whole Monte Carlo sim (calls runIndividualSim)
    
    /*
     * CRTP Methods that Sim must implement:
     */
    
    /* - void _linkModelsToSim( SimState & state );
     *   This method should connect models to the simulation.
     *   Example:
     *
     *      void _linkModelsToSim( SimState & state ){
     *          state.mlist.addDiscrete(&tstep, 100);
     *          state.mlist.addDynamics(&someDynamics);
     *      }
     */
    
    /* - void _connectModelsTogether();
     *   This method should connect models to each other,
     *   through whatever interfaces models have.
     *   Example:
     *
     *      void _connectModelsTogether(){
     *          someMissile.addGNC(&gncModel);
     *          someMissile.addMotor(&rocketMotor);
     *          rocketMotor.addAtmosphericModel(&atmoModel);
     *      }
     */
    
    /* - bool _finishedSimulation( SimState & state ) const;
     *   This method should figure out when simulation has finished
     *   Example:
     *
     *      bool _finishedSimulation( SimState & state ) const{
     *          return getTime() > 5;
     *      }
     */
    
    /* - void _finalizeMonteCarloRun();
     *   This method gives an individual to do something after a Monte Carlo run finishes
     *   TODO: Add input so one can pass in index for monte carlo run
     *   Example:
     *
     *      void _finalizeMonteCarloRun(){
     *          printf("Finished the %ith Monte Carlo run!\n",static_cast<int>(getCompletedMC()));
     *      }
     *   TODO: Add input so one can pass in index for monte carlo run
     */
    
    /* - void _finalize();
     *   This method can print info to the screen after the completed
     *   overall simulation.
     *   Example:
     *
     *      void _finalize(){
     *          printf("Simulation completed after %0.3lf seconds\n",runTime);
     *          printSimStatistics();
     *      }
     */
    
};



#include "Simulator_Impl.hpp"


#endif /* TemplateSimulator_h */
