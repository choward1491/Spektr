//
//  ExampleSim.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/25/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ExampleSim_hpp
#define ExampleSim_hpp

#include "TemplateSimulator.h"
#include "Pendulum.hpp"


class ExampleSim : public Simulator<ExampleSim,RungeKutta4> {
public:
    
    ExampleSim(){
        std::string historyFile("/Users/christianjhoward/history.txt");
        state.dataPrinter.setSimHistoryFileName(historyFile);
        state.printFrequency = 30;
        numMC = 100;
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
    void _finalizeMonteCarloRun(){}
    void _finalize(){
        printf("Finished!\n");
    }
    
    
private:
    TimeStep tstep;
    PendulumModel pendulum;
};

#endif /* ExampleSim_hpp */
