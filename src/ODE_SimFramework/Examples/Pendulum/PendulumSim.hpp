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
#include "ExplicitEuler.hpp"
#include "RungeKutta4.hpp"
#include "ExplicitTrapezoidal.hpp"
#include "Timer.hpp"
#include "RKCashKarp.hpp"


class PendulumSim : public Simulator<PendulumSim,RKCashKarp> {
public:
    
    PendulumSim(){
        timer.start();
        std::string historyFile("history.txt");
        setSimHistoryPath(historyFile);
        state.printFrequency = 1;
        numMC = 1;
        writeSimHistory = true;
        integrator.setTolerance(1e-10);
    }
   
    
    void _linkModelsToSim( SimState & state ){
        addDiscrete(&tstep, 1);
        addDynamics(&pendulum);
    }
    void _connectModelsTogether(){
        
    }
    bool _finishedSimulation( SimState & state ) const{
        return getTime() > 20;
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
    PendulumModel pendulum;
    
};

#endif /* ExampleSim_hpp */
