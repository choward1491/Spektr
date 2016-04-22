//
//  HodgkinHuxleyNeuronModel.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/18/16.
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

#ifndef HodgkinHuxleyNeuronModel_hpp
#define HodgkinHuxleyNeuronModel_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include "SimState.hpp"
#include <vector>
#include <math.h>





/*!
 * These dynamics represent a simple time varying 1D Heat Equation
 */
class HodgkinHuxleyNeuronModel : public DynamicModel {
    
public:
    
    
    HodgkinHuxleyNeuronModel(){
        
        model_name = "HodgkinHuxleyNeuronModel";
    }
    
    
    /*!
     * This method is used to do initialization
     * that needs to be done every time a sim is run
     * but could benefit from occuring after all the
     * proper model constructions and linking has occurred.
     * A good example could be initializing this model
     * based on data in other models in the simulation.
     * Another use of this function is to ensure each
     * monte carlo sim run is initialized properly
     *
     * \params None
     * \returns None
     */
    virtual void initialize(){
        Cm = 1.0;
        gk = 36.0;
        gNa= 120.0;
        gl = 0.3;
        Vm = -65;
        n  = 0.317;
        m  = 0.05;
        h  = 0.6;
        state[0] = Vm;
        state[1] = n;
        state[2] = m;
        state[3] = h;
        VK = -77;
        VNa= 50;
        Vl = -54.4;
        initialCondition();
    }
    
    
    /*!
     *
     * Method that allows a model to have some
     * data saved to a sim history file
     *
     */
    virtual void setupPrintData(){
        simState->dataPrinter.addVariableToPrint(&state[0], "Vm" );
        simState->dataPrinter.addVariableToPrint(&state[1], "n" );
        simState->dataPrinter.addVariableToPrint(&state[2], "m" );
        simState->dataPrinter.addVariableToPrint(&state[3], "h" );
    }
    
    
    /*!
     * In the event this model
     * is based on differential
     * equations, this method returns
     * the number of dimensions
     * in the ODE equations
     *
     * \params None
     * \returns Number of Dimensions in System of ODEs
     */
    virtual int numDims() const { return 4; }
    
    
    
    
    /*!
     * This is a method that represents
     * the system of differential equations
     * and outputs the rate of change of the
     * variables in the equations
     *
     * \params dxdt A vector that will hold the rate of hange
     of the diffeq variables. This vector
     will be modified in this method and in
     turn make this input also the output
     * \returns None
     */
    virtual void operator()( double time , ModelState & dqdt ){
        Vm = state[0];
        n  = state[1];
        m  = state[2];
        h  = state[3];
        double n4 = pow(n,4.0), m3 = pow(m,3.0);
        dqdt[0] = (I(time) - gk*n4*(Vm-VK) - gNa*m3*h*(Vm-VNa) - gl*(Vm-Vl) )/Cm;
        dqdt[1] = alpha_n(Vm)*(1.0-n) - beta_n(Vm)*n;
        dqdt[2] = alpha_m(Vm)*(1.0-m) - beta_m(Vm)*m;
        dqdt[3] = alpha_h(Vm)*(1.0-h) - beta_h(Vm)*h;
    }
    
    
private:
    
    double Cm, gk, gNa, gl, Vm, n, m, h;
    double VK, VNa, Vl;
    
    double alpha_n( double Vm ){
        return 0.01*(Vm-10.0)/( exp( (Vm-10.0)*0.1) - 1.0 );
    }
    
    double alpha_m( double Vm ){
        return 0.1*(Vm-25.0)/( exp( (Vm-25.0)*0.1) - 1.0 );
    }
    
    double alpha_h( double Vm ){
        return 0.07*exp(Vm/20.0);
    }
    
    double beta_n( double Vm ){
        return 0.125*exp(Vm/80.0);
    }
    
    double beta_m( double Vm ){
        return 4.0*exp(Vm/18.0);
    }
    
    double beta_h( double Vm ){
        return 1.0/( exp( (Vm - 30.0)* 0.1 ) + 1.0);
    }
    
    double I( double time ){
        if( time > 0.3 && time < 0.6 ){
            return 15;
        }
        return 0;
    }
    
    void initialCondition(){
        
    }
    
};


#endif /* HodgkinHuxleyNeuronModel_hpp */
