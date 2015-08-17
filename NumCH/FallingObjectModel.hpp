//
//  FallingObjectModel.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef FallingObjectModel_cpp
#define FallingObjectModel_cpp

#include "Model.hpp"


#define velocity dxdt[0]
#define acceleration dxdt[1]



class FallingObjectModel : public NumCH::Model {
    
    
public:
    FallingObjectModel(){
        mass = 1.0;
        state = Vec(2);
    }
    
    virtual void initialize(){}
    
    virtual void update(){}
    
    virtual int numDims(){
        return 2;
    }
    
    virtual void equationsOfMotion( Vec & dxdt ){
        velocity     = state[1];
        acceleration = -gravity;
    }
    
    virtual double & operator[](int index) const {
        return state[index];
    }
    
    virtual double & operator[](int index) {
        return state[index];
    }
    
    
private:
    double mass;
    const double gravity = 9.81;
    Vec state;
    
    
};

    


#undef velocity
#undef acceleration

#endif /* FallingObjectModel_cpp */
