//
//  TestPSO1.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/6/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef TestPSO1_h
#define TestPSO1_h

#include "Rosenbrock.hpp"
#include "RandomInit.hpp"
#include "PSO.hpp"
typedef opt::pso<opt::Rosenbrock, opt::RandomInit> rrpso;


void testPSO_Rosenbrock_RandInit(){
     rrpso test;
     opt::vec lb(2,1,-10), rb(2,1,10);
     test.setGlobalStep(0.1);
     test.setLocalStep(0.3);
     test.setMaxIter(100);
     test.setNumParticles(20);
     test.setdims(lb, rb);
     test.init();
     test.solve();
}


#endif /* TestPSO1_h */
