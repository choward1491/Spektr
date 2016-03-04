//
//  SimState.hpp
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
