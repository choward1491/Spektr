//
//  SimTime.cpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "SimTime.hpp"

SimTime::SimTime(){
    nullTime();
}
void SimTime::nullTime(){
    time = Time(0,1);
    tn = 0; to = 0;
}
void SimTime::setPreciseTime( const Time & time_ ){
    time = time_;
    tn = time.convert<double>();
}
void SimTime::setLastTime( const double time_ ){
    to = time_;
}
double SimTime::getPreciseTime() const{
    return time.convert<double>();
}
Time SimTime::getFractionalTime() const{
    return time;
}
double * SimTime::refNewTime(){
    return &tn;
}



/*
Time time;
double tn;
double to;
*/