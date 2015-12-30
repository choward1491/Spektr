//
//  SimTime.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef SimTime_hpp
#define SimTime_hpp

#include <stdio.h>
#include "PreciseTime.h"


struct SimTime {
public:
    SimTime();          // null constructor
    void nullTime();    // method to initialize times to zero
    void setPreciseTime( const Time & time_ );  // method to set precision time
    void setLastTime( const double time_ );     // method to set last time, to
    double getPreciseTime() const;              // method to get precise time
    Time getFractionalTime() const;             // method to get precise time in integer form
    
    double * refNewTime();                      // method to get reference to tn var
                                                // (this is used in dataPrinter to print time)
    
private:
    Time time;  // precise integer based time
    double tn;  // new/current time/t_{i+1}
    double to;  // old time/t_{i}
    
};

#endif /* SimTime_hpp */
