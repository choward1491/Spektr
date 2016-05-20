//
//  PointBodyModel.hpp
//  Spektr
//
//  Created by Christian J Howard on 5/18/16.
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

#ifndef PointBodyModel_hpp
#define PointBodyModel_hpp

#include <stdio.h>
#include "DynamicModel.hpp"
#include "SimState.hpp"
#include <vector>
#include <math.h>
#include "vec3.hpp"





/*!
 * These dynamics represent a simple time varying 1D Heat Equation
 */
class PointBodyModel : public DynamicModel {
    
public:
    
    
    PointBodyModel(){
        static int id = 1;
        body_id = id;id++;
        model_name = "PoingBodyModel";
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
        double p1[2] = {-0.97000436,0.24308753}, v1[2] = {0.466203685,0.43236573};
        double p2[2] = {-p1[0],-p1[1]},v2[2] = {v1[0],v1[1]};
        double p3[2] = {0.0,0.0},v3[2] = {-2*v1[0],-2*v1[1]};
        double * p_ptr = 0, *v_ptr = 0;
        
        if( body_id == 1 ){
            p_ptr = p1;
            v_ptr = v1;
        }else if( body_id == 2 ){
            p_ptr = p2;
            v_ptr = v2;
        }else{
            p_ptr = p3;
            v_ptr = v3;
        }
        
        m = 1.0;
        G = 1.0;
        
        state[0] = p_ptr[0];
        state[1] = p_ptr[1];
        state[2] = v_ptr[0];
        state[3] = v_ptr[1];
        update();
    }
    
    
    /*!
     *
     * Method that allows a model to have some
     * data saved to a sim history file
     *
     */
    virtual void setupPrintData(){
        char varname[24];
        sprintf(varname,"x_b%i",body_id);
        simState->dataPrinter.addVariableToPrint(&state[0], std::string(varname) );
        
        sprintf(varname,"y_b%i",body_id);
        simState->dataPrinter.addVariableToPrint(&state[1], std::string(varname) );
        
        sprintf(varname,"vx_b%i",body_id);
        simState->dataPrinter.addVariableToPrint(&state[2], std::string(varname) );
        
        sprintf(varname,"vy_b%i",body_id);
        simState->dataPrinter.addVariableToPrint(&state[3], std::string(varname) );
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
    
    
    
    virtual void update(){
        p = vec3_ops::equal(state[0], state[1], 0.0);
        v = vec3_ops::equal(state[2], state[3], 0.0);
    }
    
    
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
        dqdt[0] = state[2];
        dqdt[1] = state[3];
        
        vec3 dvdt = 0;
        for( int i = 0; i < bodies.size(); i++ ){
            vec3 r = bodies[i]->p - p;
            double inv_rmag = 1.0/vec3_ops::magnitude(r);
            dvdt = dvdt + (G*bodies[i]->m)*(inv_rmag*inv_rmag*inv_rmag)*r;
        }
        dqdt[2] = dvdt[0];
        dqdt[3] = dvdt[1];
    }
    
    void addBody( PointBodyModel & body ){
        bodies.push_back(&body);
    }
    
private:
    
    double m;
    double G;
    int body_id;
    std::vector<PointBodyModel*> bodies;
    vec3 p;
    vec3 v;
    
    
};

#endif /* PointBodyModel_hpp */
