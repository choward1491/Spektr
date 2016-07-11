//
//  NeuralFilter.cpp
//  Spektr
//
//  Created by Christian J Howard on 5/3/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "NeuralFilter.hpp"

namespace spektr {
    
    namespace filter {
        
        void updateWeights( ANN::Network & net, la::Mat<double> & grad, double alpha ){
            for(int i = 0; i < net.numWeights(); i++ ){
                net.weightAt(i) -= alpha*grad[i];
                grad[i] = 0.0;
            }
        }
        
        
        NeuralFilter::NeuralFilter():out(1,1,0),max_iters(10){
            
        }
        NeuralFilter::NeuralFilter(int num_data):input(num_data,1,0),list(num_data),out(1,1,0),max_iters(10){
            
        }
        
        void NeuralFilter::setMaxLearningIterations( int max_iter ){
            max_iters = max_iter;
        }
        
        void NeuralFilter::setLearningStepSize( double step ){
            stepsize = step;
        }
        
        void NeuralFilter::setInitState( const Mat & x0 ){
            
            int num_data = static_cast<int>(input.size().rows);
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
            

            grad.resize(nets[0].numWeights(),1);
            dEdO.resize(nets[0].numOutputs(),1);
        }
        
        void NeuralFilter::setNumData(int num_data){
            input.resize(num_data,1);
            list.setMaxSize(num_data);
        }
        
        void NeuralFilter::operator()( double t_, const Mat & meas ){
            static int num_meas = static_cast<int>(meas.size().rows);;
            static int counter = 0;
            int num_data = static_cast<int>(input.size().rows);
            double derr = 0;
            int num_iters = max_iters;
            
            
            // Refine the filter based on measurement
            for(int i = 0; i < num_meas; i++ ){
                for(int j = 0; j < num_data; j++ ){
                    input[j] = list[j][i];
                }
                
                for(int j = 0; j < num_iters; j++ ){
                    nets[i](input,out);
                    derr = out[0]-meas[i];
                    dEdO[0] = derr;
                    nets[i].backprop(dEdO, grad);
                    updateWeights(nets[i], grad, stepsize);
                }
            }
            
            
            // add current measurement to list
            list.push(meas);
            counter++;
            
        }
        
        const NeuralFilter::Mat & NeuralFilter::state() const{
            return estimate;
        }
        
    }
}