//
//  ClassificationCost.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef Data_Structs_ClassificationCost_h
#define Data_Structs_ClassificationCost_h

#include "CostFunc.h"

template<int Dim>
class ClassificationCost : public CostFunc<Dim> {
public:
    typedef Coordinate<Dim> State;
    virtual double operator()( State & x ){
        double z = 0, p;
        double Np = points->size();
        double invN = -1.0 / Np;
        double cost = 0;
        
        Coordinate<(Dim-1)/2> center;
        Coordinate<(Dim-1)/2> sigma;
        double coef = x[Dim-1];
        int N = functions->size()-1;
        int numVals = (Dim-1)/2;
        
        for (int i = 0; i < numVals; i++) {
            center[i] = x[i];
            sigma[i] = x[numVals+i];
        }
        
        
        (*functions)[N].assignSigma ( sigma );
        (*functions)[N].assignCenter ( center );
        (*functions)[N].assignCoefficient ( coef );
        
        if( points != 0 && values != 0 ){
            for (int i = 0; i < points->size(); i++ ) {
                z = -3.0;
                for (int j = 0; j <= N; j++) {
                    z += (*functions)[j]( (*points)[i] );
                }
                
                p = 1.0 / (1 + exp( -z ));
                
                if ((*values)[i] == 0.0) {
                    cost += weight*log( 1.0 - p );
                }else{
                    cost += log( p );
                }
            }
            
            cost *= invN;
            
            return cost;
        }else{
            return 1e8;
        }
    }
    
    void assignPoints( Vec<Coordinate<(Dim-1)/2>> * _points ){ points = _points; }
    void assignValues( Vec<double> * _values ){ values = _values; }
    void assignFailureWeighting( double _w ){ weight = _w; }
    void assignBasisFunctions( AdaptiveArray<RadialBasisFunc<(Dim-1)/2>>* _functions ){ functions = _functions; }
    
private:
    
    AdaptiveArray<RadialBasisFunc<(Dim-1)/2>> * functions;
    double weight;
    Vec<Coordinate<2>> *bounds;
    Vec<Coordinate<(Dim-1)/2>>* points;
    Vec<double> * values;
    
};



#endif
