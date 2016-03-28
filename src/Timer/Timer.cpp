//
//  Timer.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/27/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Timer.hpp"

void Timer::start(){
    start_ = std::clock();
}

void Timer::stop(){
    end_ = std::clock();
}

double Timer::getDuration() const {
    return ( end_ - start_) / (double) CLOCKS_PER_SEC;
}