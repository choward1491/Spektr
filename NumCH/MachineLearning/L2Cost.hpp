//
//  L2Cost.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef L2Cost_h
#define L2Cost_h

#include <vector>

namespace ANN {
    
template<class Regularization>
class L2Cost {
public:
    
    double operator()( std::vector<double> & truth,
                     std::vector<double> & approx,
                     std::vector<double> & ErrorDeriv) const
    {
        double error = 0.0, dy=0.0;
        double invN = 1.0/(double)truth.size();
        for (int i = 0; i < truth.size(); i++) {
            dy = (approx[i]-truth[i]);
            ErrorDeriv[i] = (approx[i]-truth[i])*invN;
            error += 0.5*dy*ErrorDeriv[i];
        }
        return error;
    }
    
    void regularization( std::vector<double> & weights, std::vector<double> & gradient )
    {
        static_cast<Regularization*>(this)->reg_(weights,gradient);
    }
    
};




class NoReg : public L2Cost<NoReg> {
public:
    void reg_( std::vector<double> & weights, std::vector<double> & gradient ){}
};


    
}






#endif /* L2Cost_h */
