//
//  Scheduler.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Scheduler_cpp
#define Scheduler_cpp

#include "heap.h"
#include "DiscreteModel.hpp"
#include "PreciseTime.h"



class Scheduler : public MinHeap<Time, DiscreteModel*> {
public:
    Time getNextTime();
    void addNewModel( Time firstTime, DiscreteModel* model );
    void reset();
};
    


#endif /* Scheduler_cpp */
