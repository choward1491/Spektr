//
//  Optimizer.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/27/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Optimizer_h
#define Optimizer_h

#include <vector>
#include <stdio.h>


namespace opt {
    typedef std::vector<double> vec;

    #define ops static_cast<Specific*>(this)

    template<class Specific>
    class optimizer {
    public:
        
        void init(){
            ops->init_();
        }
        void solve(){
            while( !ops->isComplete_() ){
                ops->update_();
                ops->giveStatus_();
            }
            ops->finalize_();
        }
        
        
        
    protected:
        
        
    private:
        
        
    };

    #undef ops

}

#endif /* Optimizer_h */
