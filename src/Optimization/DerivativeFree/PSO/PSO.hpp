//
//  PSO.hpp
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

#ifndef PSO_h
#define PSO_h

#include "Optimizer.hpp"
#include "Swarm.hpp"


namespace opt {
    
    
    template< class Function, class Initializer>
    class pso : public optimizer<pso<Function,Initializer> > {
    public:
        pso():swarm(20),numIter(0),maxIter(200),displayStatus(true){}
        ~pso(){}
        
        void showStatus(){ displayStatus = true; }
        void dontShowStatus(){ displayStatus = false; }
        void setdims( const Mat & lb, const Mat & ub ){
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
        
        
        const Mat & soln() const{
            return swarm.getBestSoln();
        }
        Mat & soln() {
            return swarm.getBestSoln();
        }
        
        Function func;
        
        
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
            if( displayStatus ){
                printf("Iteration Count: %i, Best Cost: %0.8lf\n",numIter,swarm.bestCost());
            }
        }
        
        virtual void finalize_(){}
        
        
        
    private:
        template<class T> friend class optimizer;
        
        
        int numIter;
        int maxIter;
        bool displayStatus;
        
        swarm<Function,Initializer> swarm;
        
    };
    
    
}


#endif /* DerivativeFree_h */
