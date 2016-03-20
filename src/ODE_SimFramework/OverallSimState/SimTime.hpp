//
//  SimTime.hpp
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
