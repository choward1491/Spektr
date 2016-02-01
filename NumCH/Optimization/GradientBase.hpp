//
//  GradientBase.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/28/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef GradientBase_h
#define GradientBase_h

#include "Optimizer.hpp"

namespace opt {
    
    template< class Function, class Step >
    class gradient  : public optimizer< gradient > {
    public:
        
        
        void setMaxIter( int mi ){ maxIter = mi; }
        void setTolerance( double eps ){ tol = eps; }
        void setMomentumCoef( double mc ){ mom_coef = mc; }
        
        double getBestResult( std::vector<double> & best );
        
        
    protected:
        void init_(){
            if( )
        }
        virtual bool isComplete_(){
            return (numIter >= maxIter || err < tol );
        }
        void update_(){
            gradientUpdate();
            numIter++;
        }
        void giveStatus_(){
            printf("Iteration Count: %i, Best Cost: %0.8lf\n",numIter,);
        }
        
        virtual void finalize_(){}
    private:
        
        
        void gradientUpdate(){
            
        }
        
        void initStateSize(){
            if( func.numDims())
        }
        
        
        Function func;
        Step step;
        
        int numIter;
        int maxIter;
        
        double cost;
        double bcost;
        double tol;
        double err;
        double mom_coef;
        
        std::vector<double> x;
        std::vector<double> xbest;
        std::vector<double> momentum;
        
        
    }
    
    
    
}





#endif /* GradientBase_h */
