//
//  TestMPSO1.hpp
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

#ifndef TestMPSO1_h
#define TestMPSO1_h

#include "Rosenbrock.hpp"
#include "Parabola2D.hpp"
#include "RandomInit.hpp"
#include "MultiPSO.hpp"
typedef opt::mpso<4, opt::Rosenbrock, opt::RandomInit> mpso;


void testMPSO_Rosenbrock_RandInit(){
    mpso test;
    opt::vec lb(2,1,-10), rb(2,1,10);
    test.setGlobalStep(0.5);
    test.setLocalStep(3);
    test.setMaxIter(100);
    test.setNumParticles(5);
    test.setdims(lb, rb);
    test.init();
    test.solve();
    test.soln().print();
}

#endif /* TestMPSO1_h */
