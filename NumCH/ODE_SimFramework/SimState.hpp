//
//  SimState.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef SimState_hpp
#define SimState_hpp

#include <stdio.h>

#include "SimTime.hpp"
#include "ConfigParser.hpp"
#include "DataPrinter.hpp"
#include "ModelList.hpp"

class SimState {
public:
    
    SimState();                     // null constructor
    ~SimState();                    // destructor
    
    void buildState();              // method to build the complete state
                                    // after all models have been added
    
    double* & getStateReference();  // get reference to start of state array
    
    int size() const;               // method to get size of state
    
    bool isEmpty();                 // method to see if the state vector
                                    // is empty or not
    
    //
    // Sim history data printer
    //
    DataPrinter dataPrinter;
    int printFrequency; // frequency the data printer will print to file
    
    // list of all the models
    // and interface to access them
    ModelList mlist;
    
    // Simulation time
    SimTime time;
    
    // Config file parser
    ConfigParser parser;
    
    
private:
    
    // method to free data associated with the states
    void clear();
    double *state;  // array storing all values for the states
    int numStates;  // total number of states
    
};



#endif /* SimState_hpp */
