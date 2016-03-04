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
#include "DynamicModel.hpp"
#include "DiscreteModel.hpp"
#include "heap.h"
#include "ExplicitEuler.hpp"
#include "Scheduler.hpp"
#include "RandomNumberGenerator.hpp"
#include "PreciseTime.h"
#include "ConfigParser.hpp"
#include "DataPrinter.hpp"
#include "ConstantsSet.hpp"

typedef RandomNumberGenerator Rand;
typedef std::vector<DynamicModel*> DiffeqList;
typedef std::vector<DiscreteModel*> DiscreteList;
class RungeKutta4;
class ExplicitTrapezoidal;




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
     * This method is the destructor for the simulator
     *
     * \params None
     * \returns None
     */
    virtual ~Simulator();
    
    
    
    
    
    /*!
     * This method is the main simulation
     * loop. This runs a loop in time and
     * does the necessary time updates and
     * time integration for models based
     * on differential equations.
     *
     * \params None
     * \returns None
     */
    void simLoop();
    
    
    
    
    
    
    /*!
     * This method initializes the simulation variables
     *
     * \params None
     * \returns None
     */
    void initialize();
    
    
    /*!
     * This method initializes the models
     * based on their implementation of their
     * own `initialize()` methods
     *
     * \params None
     * \returns None
     */
    void initializeModels();
    
    
    
    /*!
     * This method connects models to the sim.
     * It is expected you do this via the addDynamics
     * and addDiscrete methods
     * `Lol()`
     *
     * \params None
     * \returns None
     */
    virtual void linkModelsToSim(){}
    
    
    
    /*!
     * This method connects models dependent 
     * on other models together. This may often
     * not be needed since each model has a
     * reference to the parent sim and in turn
     * all the models (assuming you put the
     * models as protected)
     *
     * \params None
     * \returns None
     */
    virtual void connectModelsTogether(){}
    
    
    
    /*!
     * This method sets up a numerical integrator.
     * A typical implementation of this just assigns
     * the GenIntegrator pointer to a dynamically
     * allocated GenIntegrator Subclass and then
     * calls `integrator->setNumDimensions(numStates);`
     *
     * \params None
     * \returns None
     */
    void setupIntegrator();
    
    
    
    /*!
     * This method calls the `setupPrintData()`
     * methods of all the models to make sure
     * the output sim history file writes all
     * the appropriate data it needs to
     *
     * \params None
     * \returns None
     */
    void setupSimHistory();
    
    
    
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
    virtual bool finishedSimulation() const { return getCurrentTime() > 1.0; }
    
    
    
    
    
    
    /*!
     * This method finalizes a Monte Carlo
     * Simulation run in whatever way, such
     * as writing data to a file or writing
     * something to the terminal
     *
     * \params None
     * \returns None
     */
    virtual void finalizeMonteCarloRun(){}
    
    
    
    
    
    /*!
     * This method finalizes the simulation in any
     * ways that appear necessary, such as writing
     * a final file with concluding information,
     * or printing a message to the screen
     *
     * \params None
     * \returns None
     */
    virtual void finalize(){}
    
    
    
    
    //
    // Get Integration/Sim Time
    //
    double getCurrentTime() const;
    double getNextTime() const;
    
    
    
    /*!
     *
     * Get uniform random variable from central random number generator
     *
     */
    double uniformRand();
    double gaussRand();
    double gaussRand(double mean, double sigma);
    Rand * getReferenceToGenerator();
    
    
    
    /*!
     * Methods to get a numeric value based on data
     * obtained from config files
     *
     * \params variableName A C/C++ string input of the variable name
     *                      that you wish to obtain the value for
     * \returns Output value of variable
     */
    template<class T>
    T get( const std::string & variableName ){ return parser.getValueFrom<T>( variableName ); }
    
    template<class T>
    T get( const char* variableName ){ return parser.getValueFrom<T>( variableName ); }
    
    
    
    
    
    /*!
     * Helper method for models to use to get a variable
     * added to the list of sim history output variables
     *
     * \params varAddress Address to the variable being added to the list
     * \params varName    The name you wish to associate with this variable
     *                    in the output file
     * \returns None
     */
    void addVariableToPrint( const double * varAddress, const std::string & varName );
    
    
    /*!
     * Method to set the path and name of the output sim history file
     *
     * \params filename The path and file name for the output sim history file
     * \returns None
     */
    void setSimHistoryFilename( std::string & filename );
    
    
    /*!
     * Methods to add a new config file's data to the total look up table
     * of variable values
     *
     * \params filename C/C++ path and file name
     * \returns None
     */
    void addConfigFile( const char * filename );
    void addConfigFile( const std::string & filename );
    
    
    
    /*!
     * This method adds the data of the file
     * with file path 'filename' to the simulation
     * parser object
     * 
     * \params None
     * \returns Returns current simulation time
     */
    void addFileData( const char* filename );
    
    
    void setNumericalIntegratorTo( IntegratorType type );
    
    
    
protected:
    
    //
    // Specify any friends
    //
    friend class RungeKutta4;
    friend class ExplicitTrapezoidal;
    
    
    //
    // Methods to add dynamic and discrete models
    // to the simulation
    //
    void addDynamics( DynamicModel * model );
    void addDiscrete( DiscreteModel * model , int computationFrequency );
    
    
    
    //
    // Array that will point to the models
    // that are based on differential equations
    // and in turn must be integrated.
    //
    DiffeqList diffeqList;
    
    //
    // Array that will point to the models
    // that are based on discrete time equations.
    //
    DiscreteList discreteList;
    
    
    
    
    //
    // Dynamic array of state, used
    // to integrate all the simulation
    // states at once
    //
    double* state;
    int numStates;
    
    
    
    //
    // The next simulation time
    //
    double newTime;
    Time preciseTime;
    
    
    //
    // The current sim time
    //
    double currentTime;
    
    
    
    //
    // This is the scheduler for the simulation
    //
    Scheduler scheduler;
    
    
    
    
    //
    // Random Number Generator for Models to use
    //
    Rand generator;
    
    
    
    
    //
    // Config File Parser
    //
    ConfigParser parser;
    
    
    
    
    //
    // Sim history data printer
    //
    DataPrinter dataPrinter;
    int printFrequency;
    bool writeSimHistory;
    
    
    
    
    //
    // Number of Monte Carl Sims
    //
    int numMC;
    
    
    
    
    //
    // Specify the Time Integrator
    // that will be used for any
    // differential equations
    //
    GenIntegrator* integrator;
    IntegratorType itype;
    
    
private:
    
    
    /*!
     * This method builds the total state vector
     * that represents ALL variables being numerically
     * integrated
     *
     * \params None
     * \returns None
     */
    void buildTotalDynamicState();
    
    
    
    /*!
     * This method setups the ith monte carlo run
     *
     * \params monteCarloCount Variable specifying the number of the current Monte Carlo sim
     * \returns None
     */
    void MonteCarloSetup( int monteCarloCount );
    
    
    
    /*!
     * This method runs an individual sim, or one Monte Carlo sim
     *
     * \params None
     * \returns None
     */
    void runIndividualSim();
    
    
    
    
    /*!
     * This method runs ALL the Monte Carlo Sims, assuming
     * there is more than one.
     *
     * \params None
     * \returns None
     */
    void runMonteCarloSim();
    
    
};



#ifndef RungeKutta4_hpp
#include "RungeKutta4.hpp"
#endif

#ifndef ExplicitTrapezoidal_hpp
#include "ExplicitTrapezoidal.hpp"
#endif



#endif /* Simulator_cpp */
