//
//  Swarm.hpp
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

#ifndef Swarm_h
#define Swarm_h

#include "Particle.hpp"
#include "RandomNumberGenerator.hpp"

namespace opt {
    
    template<class Function, class Initializer>
    class swarm {
    public:
        swarm(int numParticles = 10):ls(0.3),gs(0.1){
            setNumParticles(numParticles);
        }
        void setNumParticles( int np ){
            if( particles.size() != np ){ particles.resize(np); }
        }
        
        void initialize();
        void setdims( const vec & lb_, const vec & ub_ ){
            lb = lb_;
            ub = ub_;
        }
        void setFunc( Function * f ){ func = f; }
        void setLocalStep( double ls_ ){ ls = ls_; }
        void setGlobalStep( double gs_ ){ gs = gs_; }
        void update();
        
        
        vec & getBestSoln(){ return *gbest; }
        const vec & getBestSoln() const{ return *gbest; }
        double bestCost() const { return gbestCost; }
        
    private:
        Function* func;
        Initializer init;
        vec lb, ub;
        vec* gbest;
        double gbestCost;
        std::vector<particle> particles;
        double ls, gs;
        static RandomNumberGenerator rng;
        
    };
    
    template<class F, class I>
    RandomNumberGenerator swarm<F,I>::rng(12374);
    
    
    template<class F, class I>
    void swarm<F,I>::initialize(){
        std::vector<vec> set;
        init(set,lb,ub,(int)particles.size());
        for (int i = 0; i < particles.size(); i++) {
            particles[i].setNumDimensions(lb.size().cols);
            for (int j = 0; j < set[i].size().rows; j++) {
                particles[i].pose[j] = set[i][j];
                particles[i].pbest[j] = set[i][j];
            }
            particles[i].lstep = &ls;
            particles[i].gstep = &gs;
            particles[i].cbest = 1e30;
        }
        gbest = &particles[0].pose;
        gbestCost = 1e100;
        
    }
    
    
    
    template<class F, class I>
    void swarm<F,I>::update(){
        double cost = 0;
        int ibest = -1;
        
        // compute cost for each particle
        // and the global best
        for (int i = 0; i < particles.size(); i++) {
            cost = (*func)(particles[i].pose);
            
            
            if( cost < particles[i].cbest ){
                particles[i].cbest = cost;
                for (int j = 0; j < particles[i].pose.size().cols; j++) {
                    particles[i].pbest[j] = particles[i].pose[j];
                }
            }
            
            if( cost < gbestCost ){
                gbestCost = cost;
                gbest = &particles[i].pbest;
            }
            
            
        }
        
        
        // update particle locations
        double s = 0;
        for (int i = 0; i < particles.size(); i++) {
            particles[i].gbest = gbest;
            if( gbest != &particles[i].pbest ){
                particles[i].update();
            }else{
                for (int j = 0; j < particles[i].pose.size().cols; j++) {
                    s = rng.rand();
                    particles[i].pose[j] += 1e-4*(lb[j]*s + ub[j]*(1-s));
                }
            }
        }
        
    }
    
    
    
    
}

#endif /* Swarm_h */
