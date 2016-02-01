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
    
    typedef la::Matrix<double, General> vec;
    
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
            if( pose.size().rows  != ndim ){ pose.resize(ndim,1); }
            if( vel .size().rows  != ndim ){ vel.resize(ndim,1); }
            if( pbest.size().rows != ndim ){ pbest.resize(ndim,1); }
        }
        
        void update(){
            for(int i = 0; i < pose.size().rows; i++ ){
                vel(i)  += ( (*lstep)*( pbest - pose ) + (*gstep)*( (*gbest) - pose ) )(i,0);
                pose(i) += vel(i);
            }
        }
        
    };
    
    
    
}




#endif /* Particle_h */
