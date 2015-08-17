//
//  TestSim.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "TestSim.hpp"



    TestSim::TestSim():Simulator(){
        integrator = 0;
        models = 0;
        
        object.assignUpdateRate(1000);
        
    }
    
    void TestSim::initialize(){
        object.initialize();
        
        initModelArray(1);
        models[0] = &object;
        object[0] = 200;
        object[1] = 0;
        scheduler.push(0, models[0]);
        
        
        integrator = new ExplicitEuler(models, numModels);
        
    }


    bool TestSim::finishedSimulation() const{
        if( curr_time >= maxSimTime ){
            return true;
        }else{
            return false;
        }
    }


    void TestSim::finalize(){
        printf("Position: %3.3lf, Velocity: %3.3lf\n",object[0], object[1]);
    }