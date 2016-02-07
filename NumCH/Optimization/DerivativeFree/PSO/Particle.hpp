//
//  Particle.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef Particle_h
#define Particle_h

#include "Optimizer.hpp"


namespace opt {
    
    typedef la::Mat<double> vec;
    
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
