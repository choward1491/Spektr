//
//  ConstantStep.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef ConstantStep_h
#define ConstantStep_h

#include <vector>

namespace ANN {
    
    class Network;
    class DataSet;
    
class ConstantStep {
public:
    void setNetwork( Network * net ){}
    void setGradient(std::vector<double> * grad){}
    void setOutputVec(std::vector<double> * ov){}
    double operator()( double s, DataSet & ds ){ return s; }
};
    
}


#endif /* ConstantStep_h */
