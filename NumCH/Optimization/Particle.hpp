//
//  Particle.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Particle_h
#define Particle_h

#include "Optimizer.hpp"


namespace opt {
    
    
    struct particle {
        vec pose;       // position
        vec vel;   //momentum
        vec pbest;      //personal best
        double cbest;   // best cost
        
        double* lstep;
        double* gstep;
        vec* gbest;
        
        
        particle():lstep(0),gstep(0),gbest(0),cbest(1e10){}
        
        void setNumDimensions( int ndim ){
            if( pose.size()  != ndim ){ pose.resize(ndim); }
            if( vel .size()  != ndim ){ vel.resize(ndim); }
            if( pbest.size() != ndim ){ pbest.resize(ndim); }
        }
        
        void update(){
            for(int i = 0; i < pose.size(); i++ ){
                vel[i]  += ( (*lstep)*( pbest[i] - pose[i] ) + (*gstep)*( (*gbest)[i] - pose[i] ) );
                pose[i] += vel[i];
            }
        }
        
    };
    
    
    
}




#endif /* Particle_h */
