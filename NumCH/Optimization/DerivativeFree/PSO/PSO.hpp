//
//  DerivativeFree.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef DerivativeFree_h
#define DerivativeFree_h

#include "Optimizer.hpp"
#include "Swarm.hpp"


namespace opt {
    
    typedef la::Matrix<double, General> vec;
    
    template< class Function, class Initializer>
    class pso : public optimizer<pso<Function,Initializer> > {
    public:
        pso():swarm(20),numIter(0),maxIter(200){}
        ~pso(){}
        
        void setdims( const vec & lb, const vec & ub ){
            swarm.setdims(lb,ub);
        }
        void setNumParticles( int np ){
            swarm.setNumParticles(np);
        }
        void setLocalStep( double ls_ ){
            swarm.setLocalStep(ls_);
        }
        void setGlobalStep( double gs_ ){
            swarm.setGlobalStep(gs_);
        }
        void setMaxIter( int mi ){
            maxIter = mi;
        }
        
        
        const vec & soln() const{
            return swarm.getBestSoln();
        }
        vec & soln() {
            return swarm.getBestSoln();
        }
        
        
    protected:
        
        void init_(){
            swarm.setFunc( &func );
            swarm.initialize();
        }
        virtual bool isComplete_(){
            return (numIter >= maxIter);
        }
        void update_(){
            swarm.update();
            numIter++;
        }
        void giveStatus_(){
            printf("Iteration Count: %i, Best Cost: %0.8lf\n",numIter,swarm.bestCost());
        }
        
        virtual void finalize_(){}
        
        
        
    private:
        template<class T> friend class optimizer;
        Function func;
        
        int numIter;
        int maxIter;
        
        swarm<Function,Initializer> swarm;
        
    };
    
    
}


#endif /* DerivativeFree_h */
