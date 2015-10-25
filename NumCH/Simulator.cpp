//
//  Simulator.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Simulator.hpp"

    


Simulator::Simulator(){
    last_time = 0;
    curr_time = 0;
}


 void Simulator::simLoop() {
    
    Model * model   = 0;
    double dt       = 0;
    
    //
    // Initialize the Simulator
    //
    initialize();
    
    
    
    
    //
    // Loop through the simulation
    //
    while ( not finishedSimulation() ){
        curr_time   = scheduler.getNextTime();
        model       = scheduler.pop();
        dt          = curr_time - last_time;
        last_time   = curr_time;
        
        
        //
        // Update State Variables
        //
        integrator->integrate(dt);
        
        
        
        //
        // Update current model
        //
        if( model != 0 ){
            model->update();
        }
        
        
        
        //
        // Push this model back onto
        // the heap
        //
        scheduler.push( curr_time + model->getDt(), model );
    }
    
    
    
    //
    // Finalize the simulation
    //
    finalize();
    
}


Simulator::~Simulator() {
    if( integrator != 0 ){
        delete integrator;
        integrator = 0;
    }
    
    if( models != 0 ){
        delete [] models;
        models = 0;
    }
}



void Simulator::initModelArray( int _numModels ) {
    numModels = _numModels;
    models = new Model*[numModels];
    for (int i = 0; i < numModels; i++) {
        models[i] = 0;
    }
}
    

