//
//  ExampleSim.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef PendulumSim_hpp
#define PendulumSim_hpp

#include "Simulator.hpp"
#include "Pendulum.hpp"


class PendulumSim : public Simulator<PendulumSim,RungeKutta4> {
public:
    
    PendulumSim(){
        std::string historyFile("history.txt");
        state.dataPrinter.setSimHistoryFileName(historyFile);
        state.printFrequency = 30;
        numMC = 10;
        writeSimHistory = true;
        initialize();
    }
   
    
    void _linkModelsToSim( SimState & state ){
        state.mlist.addDiscrete(&tstep, 100);
        state.mlist.addDynamics(&pendulum);
    }
    void _connectModelsTogether(){
        
    }
    bool _finishedSimulation( SimState & state ) const{
        return getTime() > 5;
    }
    void _finalizeMonteCarloRun(){
        printf("Finished the %ith Monte Carlo run!\n",static_cast<int>(getCompletedMC()));
    }
    void _finalize(){
        printf("Finished!\n");
    }
    
private:
    
    TimeStep tstep;
    PendulumModel pendulum;
    
};

#endif /* ExampleSim_hpp */
