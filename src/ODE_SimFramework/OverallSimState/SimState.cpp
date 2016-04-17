//
//  SimState.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "SimState.hpp"


SimState::SimState(){
    state = 0;
    numStates = 0;
    printFrequency = 1;
}
SimState::~SimState(){
    clear();
}

void SimState::buildState(){
        
    // create new state vector
    numStates = mlist.getNumStates();
    state = new double[numStates];
    
    // create new pointer to reference along the state array
    size_t offset = 0;
    
    // assign the starting address for the state of each dynamic model
    for (int i = 0; i < mlist.diffeqList.size(); i++) {
        mlist.diffeqList[i]->assignStateAddress( &state, offset );
        offset += mlist.diffeqList[i]->numDims();
    }
}
double *& SimState::getStateReference(){
    return state;
}
int SimState::size() const{
    return numStates;
}
bool SimState::isEmpty(){ return state == 0; }


void SimState::clear(){
    if( state != 0 ){
        delete [] state; state = 0;
    }
}