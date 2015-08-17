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
#include "Model.hpp"

namespace NumCH {

class Scheduler : public MinHeap<double, Model*> {
public:
    double getNextTime(){ return getRootKey(); }

};
    
}

#endif /* Scheduler_cpp */
