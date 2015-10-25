//
//  ClassificationLearning.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__ClassificationLearning__
#define __Data_Structs__ClassificationLearning__

#include <stdio.h>
#include "Vec.h"
#include "Coordinate.h"
#include "RadialBasisFunc.h"
#include "Swarm.h"
#include "AdaptiveArray.h"
#include "LatinHypercubeDistributor.h"
#include "ClassificationCost.h"


template<int Dim>
class ClassificationLearning {
public:
    ClassificationLearning();
    ~ClassificationLearning();
    
    void computeClassification();
    
    
    void assignPoints( Vec<Coordinate<Dim>> * _points ){ costFunction.assignPoints(_points); }
    void assignValues( Vec<double> * _values ){ costFunction.assignValues(_values); }
    void assignFailureWeighting( double _w = 1.0 ){ costFunction.assignFailureWeighting(_w); }
    void assignNumberOfBasisFunctions( int _num = 10 ){ maxNumOfBasisFuncs = _num; }
    void assignBounds( Vec<Coordinate<2>> * _bounds ){ bounds = _bounds; }
    double getCost() const { return cost_new; }
    
    AdaptiveArray<RadialBasisFunc<Dim>> functions;
    
    void saveResults( char* filename ) const;
    
protected:
    
    ClassificationCost<2*Dim+1> costFunction;
    
    double cost_old;
    double cost_new;
    
    Vec<Coordinate<2>>* bounds;
    
    int maxNumOfBasisFuncs;
    
    
private:
    
    
};



#ifndef _classification_cpp_
#include "ClassificationLearning.cpp"
#endif


#endif /* defined(__Data_Structs__ClassificationLearning__) */
