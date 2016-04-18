//
//  HeatEquationSim.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/17/16.
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

#ifndef HeatEquationSim_hpp
#define HeatEquationSim_hpp

#include "Simulator.hpp"
#include "HeatEquation.hpp"
#include "ExplicitEuler.hpp"
#include "RungeKutta4.hpp"
#include "ExplicitTrapezoidal.hpp"
#include "Timer.hpp"


class HeatEquationSim : public Simulator<HeatEquationSim,ExplicitTrapezoidal> {
public:
    
    HeatEquationSim(){
        timer.start();
        std::string historyFile("history.txt");
        setSimHistoryPath(historyFile);
        state.printFrequency = 1000;
        numMC = 1;
        writeSimHistory = true;
    }
    
    
    void _linkModelsToSim( SimState & state ){
        addDiscrete(&tstep, 50000);
        addDynamics(&heatEqn);
    }
    void _connectModelsTogether(){
        
    }
    bool _finishedSimulation( SimState & state ) const{
        return getTime() > 1;
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
    HeatEquation heatEqn;
    
};

#endif /* HeatEquationSim_hpp */
