//
//  ADELINE.cpp
//  Spektr
//
//  Created by Christian J Howard on 5/3/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "ADELINE.hpp"

namespace spektr {
    
    namespace filter {
        
        void updateWeights( std::vector<double> & w, std::vector<double> grad, double alpha ){
            for(int i = 0; i < w.size(); i++ ){
                w[i] -= alpha*grad[i];
            }
        }
        
        
        ADELINE::ADELINE():out(1),max_iters(10){
            
        }
        ADELINE::ADELINE(int num_data):input(num_data),list(num_data),out(1),max_iters(10){
            
            
        }
        
        void ADELINE::setMaxLearningIterations( int max_iter ){
            max_iters = max_iter;
        }
        
        void ADELINE::setLearningStepSize( double step ){
            stepsize = step;
        }
        
        void ADELINE::setInitState( const Mat & x0 ){
            
            int num_data = static_cast<int>(input.size());
            int num_meas = static_cast<int>(x0.size().rows);
            estimate.resize(x0.size());
            
            std::vector<int> layout(3);
            layout[0] = num_data;
            layout[1] = 3;
            layout[2] = 1;
            
            num_meas = static_cast<int>(x0.size().rows);
            nets.resize(num_meas);
            
            for(int i = 0; i < num_meas; i++ ){
                nets[i].setLayers(layout);
            }
            
            for(int i = 0; i < num_data; i++ ){
                list.push(x0);
            }
            grad.resize(nets[0].numWeights());
            dEdO.resize(nets[0].numOutputs());
        }
        
        void ADELINE::setNumData(int num_data){
            input.resize(num_data);
            list.setMaxSize(num_data);
        }
        
        void ADELINE::operator()( double t_, const Mat & meas ){
            static int num_meas = static_cast<int>(meas.size().rows);;
            int num_data = static_cast<int>(input.size());
            double derr = 0;
            
            
            // Refine the filter based on measurement
            for(int i = 0; i < num_meas; i++ ){
                for(int j = 0; j < num_data; j++ ){
                    input[j] = list[j][i];
                }
                
                for(int j = 0; j < max_iters; j++ ){
                    nets[i](input,out);
                    if( j == max_iters-1 ){
                        estimate[i] = out[0];
                    }
                    derr = out[0]-meas[i];
                    dEdO[0] = derr;
                    nets[i].backprop(dEdO, grad);
                    updateWeights(nets[i].w(), grad, stepsize);
                    //printf("Error = %0.8lf, Grad = [%lf, %lf], Weights = [%lf, %lf]\n",0.5*derr*derr, grad[0], grad[1],
                    //       nets[i].weightAt(0), nets[i].weightAt(1));
                    for(int k = 0; k < grad.size(); k++ ){ grad[k] = 0.0; }
                }//printf("\n");
            }
            
            
            // add current measurement to list
            list.push(meas);
            
        }
        
        const ADELINE::Mat & ADELINE::state() const{
            return estimate;
        }
        
    }
}