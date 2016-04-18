//
//  AdvectionEqn.hpp
//  Spektr
//
//  Created by Christian J Howard on 4/17/16.
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

#ifndef AdvectionEqn_hpp
#define AdvectionEqn_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include "SimState.hpp"
#include <vector>
#include <math.h>





/*!
 * These dynamics represent a simple time varying 1D Heat Equation
 */
class AdvectionEqn : public DynamicModel {
    
public:
    
    
    AdvectionEqn(){
        num_points = 1000;
        x_pos.resize(num_points);
        xmin = 0;
        xmax = 1;
        b[0] = 0.5; b[1] = -2; b[2] = 1.5;
        dx = (xmax - xmin)/static_cast<double>(num_points-1);
        for(float i = 0.0; i < num_points; i+=1.0 ){
            x_pos[i] = xmin + i*dx;
        }
        model_name = "advection_equation";
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
        speed            = generator->rand() * 4 + -2;
        initialCondition();
    }
    
    
    /*!
     *
     * Method that allows a model to have some
     * data saved to a sim history file
     *
     */
    virtual void setupPrintData(){
        char varname[24];
        for(int i = 0; i < num_points; i++ ){
            sprintf(varname,"u_%i",i);
            simState->dataPrinter.addVariableToPrint(&state[i], std::string(varname) );
        }
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
    virtual int numDims() const { return num_points; }
    
    
    
    
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
        interiorComputation(time, dqdt);
        leftBC(time, dqdt);
        rightBC(time, dqdt);
    }
    
    
private:
    int num_points;
    double b[3];
    double speed; // thermal diffusivity
    double xmin, xmax, dx;
    std::vector<float> x_pos;
    
    
    
    void interiorComputation( double time, ModelState & dqdt ){
        double c = speed / dx;
        if( c >= 0.0 ){
            for(int i = 2; i < num_points; i++ ){
                dqdt[i] = -c * (b[0]*state[i-2] + b[1]*state[i-1] + b[2]*state[i]);
            }
        }else{
            for(int i = 0; i < (num_points-2); i++ ){
                dqdt[i] = -c * -(b[0]*state[i+2] + b[1]*state[i+1] + b[2]*state[i]);
            }
        }
    }
    void leftBC( double time, ModelState & dqdt ){
        // periodic BC
        if( speed > 0 ){
            double c = speed / dx;
            int end = num_points-1;
            dqdt[0] = -c * (b[0]*state[end-1] + b[1]*state[end] + b[2]*state[0]);
            dqdt[1] = -c * (b[0]*state[end]   + b[1]*state[0]   + b[2]*state[1]);
        }
    }
    void rightBC( double time, ModelState & dqdt ){
        // periodic BC
        if( speed < 0 ){
            double c = speed / dx;
            int end = num_points-1;
            dqdt[end]   = -c * -(b[0]*state[1] + b[1]*state[0]    + b[2]*state[end]);
            dqdt[end-1] = -c * -(b[0]*state[0] + b[1]*state[end]  + b[2]*state[end-1]);
        }
    }
    void initialCondition(){
        double m = 0.5*(xmin+xmax);
        double s = (xmax-m)/3.0, del = 0.0;
        
        // Centered Gaussian
        for(int i = 0; i < num_points; i++){
            del = (x_pos[i]-m)/s;
            state[i] = 5*exp( -del*del );
        }
    }
    
    
};


#endif /* AdvectionEqn_hpp */
