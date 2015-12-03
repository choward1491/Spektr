//
//  Simulator.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Simulator.hpp"

    


Simulator::Simulator():preciseTime(0,1){
    currentTime = 0;
    newTime = 0;
    numMC = 1;
    numStates = 0;
    printFrequency = 1;
    writeSimHistory = true;
    itype = ExplicitEuler;
}

void Simulator::initialize(){
    
    
    if ( writeSimHistory ){     // add printer model if writing history
        addVariableToPrint(&newTime, "Time");
        addDiscrete(&dataPrinter, printFrequency);
    }
    
    linkModelsToSim();          // add other models to sim
    buildTotalDynamicState();   // build dynamic state array
    setupSimHistory();          // add variables that will be printed
    setupIntegrator();          // setup integrator module
    
    connectModelsTogether();    // connect models together if needed
}


void Simulator::MonteCarloSetup( int monteCarloCount ){
    
    initializeModels();     // Initialize models for ith MC run
    
    if( monteCarloCount > 0 ){     // If new monte carlo run, reset everything
        scheduler.reset();
        dataPrinter.newMonteCarlo();
        newTime = 0;
        currentTime = 0;
    }
    
    if( writeSimHistory ){      // if writing a sim history
        dataPrinter.update();   // update output sim history file
    }
}


void Simulator::runIndividualSim(){
    
    DiscreteModel* model = 0;   // init temporary discrete model
    double dt = 0.0;            // init time step
    double nextTime = 0;        // init variable to hold next time
    

    while ( not finishedSimulation() ){                                 // loop through sim
        preciseTime   = scheduler.getNextTime();                        // update precise time
        newTime   = preciseTime.convert<double>();                      // obtain t_{i+1}
        model       = scheduler.pop();                                  // get model to run
        scheduler.push( preciseTime + model->getFracDt(), model );      // put model back on
                                                                        // heap at next time
        nextTime    = scheduler.getNextTime().convert<double>();        // obtain time of future event
        dt          = newTime - currentTime;                            // obtain dt step
        
        
        
        if( newTime != nextTime ){    // if the current time is different than the next
            integrator->integrate(currentTime, dt, state, diffeqList);    // integrate state
        }
        
        
        if( model != 0 ){ model->update(); }    // update discrete model
        
        
        if( newTime != nextTime ){    // if the current time is different than the next
            currentTime   = newTime;    // update currentTime; currentTime represents t_{i}
        }                               // for a given time step
        
        
    }// end of simulation run
}


void Simulator::runMonteCarloSim(){
    
    // loop through monte carlo draws
    for (int iMC = 0; iMC < numMC; iMC++) {
        MonteCarloSetup(iMC);
        runIndividualSim();
        finalizeMonteCarloRun();
    }
}


 void Simulator::simLoop()
{
    
    if (integrator == 0) { // check that integrator exists; if not, exit
        printf("No integrator specified for Simulation. Ending.\n");
        return;
    }
    
    runMonteCarloSim(); // run all the monte carlo sim
    finalize();         // finalize overall simulation
    
}


Simulator::~Simulator() {
    if( integrator != 0 ){
        delete integrator;
        integrator = 0;
    }
    
    if( state != 0 ){
        delete [] state;
        state = 0;
    }
}




void Simulator::addDynamics( DynamicModel * model ){
    model->assignParentSimulator(this);
    diffeqList.push(model);
    numStates += model->numDims();
}


void Simulator::addDiscrete( DiscreteModel * model , int computationFrequency ){
    model->assignParentSimulator(this);
    discreteList.push(model);
    model->assignUpdateRate(computationFrequency);
    scheduler.addNewModel( Time(1,computationFrequency), model);
}




void Simulator::initializeModels(){
    for (int i = 0; i < diffeqList.size(); i++) {
        diffeqList[i]->initialize();
    }
    for (int i = 0; i < discreteList.size(); i++) {
        discreteList[i]->initialize();
    }
}


void Simulator::setupIntegrator(){
    
    switch (itype) {
        case ExplicitEuler:
            integrator = new class ExplicitEuler();
            break;
        case ExplicitTrapezoidal:
            integrator = new class ExplicitTrapezoidal();
            break;
        case RungeKutta4:
        default:
            integrator = new class RungeKutta4();
            break;
    }
    integrator->setNumDimensions(numStates);
    
}

void Simulator::setupSimHistory(){
    for (int i = 0; i < diffeqList.size(); i++) {
        diffeqList[i]->setupPrintData();
    }
    for (int i = 0; i < discreteList.size(); i++) {
        discreteList[i]->setupPrintData();
    }
}





void Simulator::buildTotalDynamicState(){
    
    // clear state if it exists
    if( state == 0 ){
    
        // create new state vector
        state = new double[numStates];
        
        // create new pointer to reference along the state array
        double* ptr = &state[0];
        
        // assign the starting address for the state of each dynamic model
        for (int i = 0; i < diffeqList.size(); i++) {
            diffeqList[i]->assignStateAddress(ptr);
            ptr = ptr + diffeqList[i]->numDims();
        }
        
    }
}



//
// Get Integration/Sim Time
//
double Simulator::getCurrentTime() const { return currentTime; }
double Simulator::getNextTime() const { return newTime; }



/*!
 *
 * Get uniform random variable from central random number generator
 *
 */
double Simulator::uniformRand() { return generator.rand(); }
double Simulator::gaussRand(){ return generator.gaussRand(); }
double Simulator::gaussRand( double mean, double sigma ){ return generator.gaussRand(mean, sigma); }
Rand * Simulator::getReferenceToGenerator(){ return &generator; }



void Simulator::addVariableToPrint( const double * varAddress, const std::string & varName ){
    dataPrinter.addData(varAddress, varName);
}

void Simulator::setSimHistoryFilename( std::string & filename ){
    dataPrinter.setFileName(filename);
}

void Simulator::setNumericalIntegratorTo( IntegratorType type ){ itype = type; }

void Simulator::addConfigFile( const char * filename ){ parser.parse( filename ); }
void Simulator::addConfigFile( const std::string & filename ){ parser.parse( filename.c_str() ); }

