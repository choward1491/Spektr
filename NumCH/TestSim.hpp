//
//  TestSim.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef TestSim_cpp
#define TestSim_cpp

#include "Simulator.hpp"
#include "FallingObjectModel.hpp"
#include "ExplicitEuler.hpp"


class TestSim : public NumCH::Simulator {
    
public:
    TestSim();
    virtual void initialize();
    virtual bool finishedSimulation() const;
    virtual void finalize();
    
private:
    
    FallingObjectModel object;
    const double maxSimTime = 5.0;
    
    
};

#endif /* TestSim_cpp */
