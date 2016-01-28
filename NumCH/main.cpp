//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Rosenbrock.hpp"
#include "RandomInit.hpp"
#include "PSO.hpp"


int main(int argc, const char * argv[]) {
    
    opt::pso<opt::Rosenbrock, opt::RandomInit> pso;
    std::vector<double> lb {-10,-10};
    std::vector<double> ub {10,10};
    
    pso.setNumParticles(50);
    pso.setMaxIter(100);
    pso.setLocalStep(0.3);
    pso.setGlobalStep(0.2);
    pso.setdims(lb, ub);
    pso.init();
    pso.solve();
    
    return 0;
}

