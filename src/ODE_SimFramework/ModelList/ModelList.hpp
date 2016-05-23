//
//  ModelList.hpp
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

#ifndef ModelList_hpp
#define ModelList_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include "DiscreteModel.hpp"
#include "Scheduler.hpp"
#include <vector>

class ModelList {
public:
    
    // Null constructor
    ModelList();
    
    //
    // Methods to add dynamic and discrete models
    // to the simulation
    //
    void addDynamics( DynamicModel * model );
    void addDiscrete( DiscreteModel * model , double computationFrequency );
    
    // Method to initialize models
    void initializeModels();
    
    // method to add sim state and centralized random number
    // generator to each model
    void addParentData( SimState & s, Rand & gen);
    
    // update dynamic models
    void updateDynamicModels();
    
    // Methods to retrieve references to a dynamic or discrete model
    DynamicModel* getDynamicsAt(int index);
    DiscreteModel* getDiscreteAt(int index);
    
    // Method to retrieve a dynamic or discrete model list
    std::vector<DynamicModel*> & getDiffeqList();
    std::vector<DiscreteModel*> & getDiscreteList();
    
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
    typedef std::vector<DynamicModel*> DiffeqList;
    typedef std::vector<DiscreteModel*> DiscreteList;
    
    
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
