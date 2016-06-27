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
            avg_error.resize(num_meas);
            meas_error.resize(num_meas);
            ratio.resize(num_meas);
            ratio_avg.resize(num_meas);
            num_times = 0;
            
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
        
        double coef( double ratio , double ratio_avg ){
            /*if( ratio > 3 ){
                return ratio*ratio;
            }else if( ratio > 2 ){
                return 6e-1/(ratio*ratio);
            }else if( ratio > 1 ){
                return 1e-1;
            }else if( ratio > 0.5 ){
                return ratio*ratio*ratio;
            }else if( ratio > 0.3 ){
                return ratio*ratio;
            }else{
                return ratio;
            }*/
            
            return 7*(1.01 - exp( -1*(ratio-ratio_avg)*(ratio-ratio_avg) ));
        }
        
        void NeuralFilter::operator()( double t_, const Mat & meas ){
            static int num_meas = static_cast<int>(meas.size().rows);;
            static int counter = 0;
            int num_data = static_cast<int>(input.size().rows);
            double derr = 0;
            int num_iters = max_iters;
            double alpha = 0.05;
            
            
            // Refine the filter based on measurement
            for(int i = 0; i < num_meas; i++ ){
                for(int j = 0; j < num_data; j++ ){
                    input[j] = list[j][i];
                }
                
                for(int j = 0; j < num_iters; j++ ){
                    nets[i](input,out);
                    derr = out[0]-meas[i];
                    
                    if( j == 0 ){
                        estimate[i] = out[0];
                        meas_error[i] = (1-alpha)*fabs(derr) + alpha*meas_error[i];
                        if( num_times == 0 ){
                            avg_error[i] = fabs(derr);
                            num_times++;
                        }else{
                            double K = static_cast<double>(num_times);
                            double N = K+1.0;
                            avg_error[i] = (fabs(derr) + K*avg_error[i])/N;
                            num_times++;
                        }
                        ratio[i] = meas_error[i]/avg_error[i];
                        ratio_avg[i] = 0.5*ratio[i] + 0.5*ratio_avg[i];
                        //stepsize = 20e-4/coef(ratio[i],ratio_avg[i]);
                        double del = fabs(ratio[i]-ratio_avg[i]);
                        //stepsize = (1e-1*fabs(1.0-ratio[i]) + 1e-2*del)/(1 + 7*ratio_avg[i]*ratio_avg[i]);
                        //stepsize = (1e-3 + 4e-2*del)/(ratio[i]*(1+del));
                    }
                    
                    
                    dEdO[0] = derr;
                    nets[i].backprop(dEdO, grad);
                    updateWeights(nets[i], grad, stepsize);
                    /*printf("Error = %0.8lf, Grad = [%lf, %lf], Weights = [%lf, %lf]\n",0.5*derr*derr, grad[0], grad[1],nets[i].weightAt(0), nets[i].weightAt(1));*/
                }//printf("\n");
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