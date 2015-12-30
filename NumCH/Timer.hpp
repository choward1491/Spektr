//
//  Timer.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/27/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <cstdio>
#include <ctime>


class Timer{
    
public:
    void start(){
        start_ = std::clock();
    }
    
    void stop(){
        end_ = std::clock();
    }
    
    double getDuration(){
        return ( end_ - start_) / (double) CLOCKS_PER_SEC;
    }
    
private:
    std::clock_t start_;
    std::clock_t end_;
};

#endif /* Timer_hpp */
