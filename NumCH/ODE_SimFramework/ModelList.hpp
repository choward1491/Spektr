//
//  ModelList.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ModelList_hpp
#define ModelList_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include "DiscreteModel.hpp"
#include "AdaptiveArray.h"
#include "Scheduler.hpp"

class ModelList {
public:
    
    // Null constructor
    ModelList();
    
    //
    // Methods to add dynamic and discrete models
    // to the simulation
    //
    void addDynamics( DynamicModel * model );
    void addDiscrete( DiscreteModel * model , int computationFrequency );
    
    // Method to initialize models
    void initializeModels();
    
    // method to add sim state and centralized random number
    // generator to each model
    void addParentData( SimState & s, Rand & gen);
    
    // Methods to retrieve references to a dynamic or discrete model
    DynamicModel* getDynamicsAt(int index);
    DiscreteModel* getDiscreteAt(int index);
    
    // Method to retrieve a dynamic or discrete model list
    AdaptiveArray<DynamicModel*> & getDiffeqList();
    AdaptiveArray<DiscreteModel*> & getDiscreteList();
    
    // Method to return the total number of states
    int getNumStates() const;
    
    // Method to setup the sim history file
    void setupSimHistory();
    
    // Sim Scheduler to handle discrete time events
    // in the correct order in time
    Scheduler scheduler;
    
    
private:
    friend class SimState;
    
    // typedefs for Lists with dynamic and discrete models
    typedef AdaptiveArray<DynamicModel*> DiffeqList;
    typedef AdaptiveArray<DiscreteModel*> DiscreteList;
    
    
    int numStates; // total number of states
    
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
    
};


#endif /* ModelList_hpp */
