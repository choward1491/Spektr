//
//  Scheduler.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Scheduler.hpp"


Time Scheduler::getNextTime(){ return getRootKey(); }

void Scheduler::addNewModel( Time firstTime, DiscreteModel* model ){
    this->push(firstTime, model);
}

void Scheduler::reset(){
    for (int i = 0; i < size(); i++) {
        setKeyAt(i, getDataAt(i)->getFracDt());
    }
    generateHeap();
}