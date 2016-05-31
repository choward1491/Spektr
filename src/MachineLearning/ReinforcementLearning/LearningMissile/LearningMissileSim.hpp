//
//  LearningMissileSim.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/24/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef LearningMissileSim_hpp
#define LearningMissileSim_hpp

#include <stdio.h>
#include "ExplicitEuler.hpp"
#include "Timer.hpp"
#include "Simulator.hpp"

class LearningMissileSim : public Simulator<LearningMissileSim ,ExplicitEuler> {
public:
    
    LearningMissileSim (){
        timer.start();
        numMC = 20;
        writeSimHistory = false;
    }
    
    
    void _linkModelsToSim( SimState & state ){
        addDiscrete(&tstep, 100);
    }
    void _connectModelsTogether(){
        
    }
    bool _finishedSimulation( SimState & state ) const{
        return getTime() > 10.0;
    }
    void _finalizeMonteCarloRun(){
        printf("Finished #%i Monte Carlo run!\n",static_cast<int>(getCompletedMC()));
    }
    void _finalize(){
        printf("Finished!\n");
        timer.stop();
        
        printf("Simulation complete after %lf seconds\n",timer.getDuration());
    }
    
private:
    
    Timer timer;
    TimeStep tstep;
    
};

#endif /* LearningMissileSim_hpp */
