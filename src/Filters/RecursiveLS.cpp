//
//  RecursiveLS.cpp
//  Spektr
//
//  Created by Christian J Howard on 5/8/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "RecursiveLS.hpp"

namespace spektr {
    
    namespace filter {
        
        
        RecursiveLS::RecursiveLS(){
            
        }
        RecursiveLS::RecursiveLS(int num_data):list(num_data){
            
            
        }
        
        void RecursiveLS::setInitState( const double & x0 ){
            
            int num_data = static_cast<int>(list.maxsize());
            
            for(int i = 0; i < num_data; i++ ){
                list.push(x0);
            }
        }
        
        void RecursiveLS::setNumData(int num_data){
            list.setMaxSize(num_data);
        }
        
        void RecursiveLS::operator()( double t_, const double & meas ){
            static int num_meas = 1;
            static int num_data = static_cast<int>(list.maxsize());
            
            
            
            // add current measurement to list
            list.push(meas);
            
        }
        
        const double & RecursiveLS::state() const{
            return estimate;
        }
        
    }
}