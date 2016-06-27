//
//  MultiPSO.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/7/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef MultiPSO_hpp
#define MultiPSO_hpp

#include <stdio.h>

#include "Optimizer.hpp"
#include "Swarm.hpp"


namespace opt {
    
    
    template<int NumSwarms, class Function, class Initializer>
    class mpso : public optimizer< mpso<NumSwarms,Function,Initializer> > {
    public:
        mpso():numIter(0),maxIter(200),displayStatus(true){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i] = Swarm(5);
            }
        }
        ~mpso(){}
        
        void showStatus(){ displayStatus = true; }
        void dontShowStatus(){ displayStatus = false; }
        void setdims( const Mat & lb, const Mat & ub ){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].setdims(lb,ub);
            }
        }
        void setNumParticles( int np ){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].setNumParticles(np);
            }
        }
        void setLocalStep( double ls_ ){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].setLocalStep(ls_);
            }
        }
        void setGlobalStep( double gs_ ){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].setGlobalStep(gs_);
            }
        }
        void setMaxIter( int mi ){
            maxIter = mi;
        }
        
        
        const Mat & soln() const{
            double bcost = swarms[0].bestCost();
            int bind = 0;
            
            for (int i = 1; i < NumSwarms; i++) {
                if( swarms[i].bestCost() < bcost ){
                    bind = i; bcost = swarms[i].bestCost();
                }
            }
            return swarms[bind].getBestSoln();
        }
        Mat & soln() {
            double bcost = swarms[0].bestCost();
            int bind = 0;
            
            for (int i = 1; i < NumSwarms; i++) {
                if( swarms[i].bestCost() < bcost ){
                    bind = i; bcost = swarms[i].bestCost();
                }
            }
            return swarms[bind].getBestSoln();
        }
        
        Function func;
        
        
    protected:
        
        void init_(){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].setFunc( &func );
                swarms[i].initialize();
            }
        }
        virtual bool isComplete_(){
            return (numIter >= maxIter);
        }
        void update_(){
            for (int i = 0; i < NumSwarms; i++) {
                swarms[i].update();
            }
            numIter++;
        }
        void giveStatus_(){
            if( displayStatus ){
                double bcost = swarms[0].bestCost();
                
                for (int i = 1; i < NumSwarms; i++) {
                    if( swarms[i].bestCost() < bcost ){
                        bcost = swarms[i].bestCost();
                    }
                }
                printf("Iteration Count: %i, Best Cost: %0.8lf\n",numIter,bcost);
            }
        }
        
        virtual void finalize_(){}
        
        
        
    private:
        template<class T> friend class optimizer;
        typedef swarm<Function, Initializer> Swarm;
        
        
        int numIter;
        int maxIter;
        bool displayStatus;
        
        Swarm swarms[NumSwarms];
        
    };
    
    
}


#endif /* MultiPSO_hpp */
