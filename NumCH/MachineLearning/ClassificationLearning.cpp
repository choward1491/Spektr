//
//  ClassificationLearning.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "ClassificationLearning.h"

#ifndef _classification_cpp_
#define _classification_cpp_


template<int Dim>
ClassificationLearning<Dim>::ClassificationLearning(){
    cost_old = 0;
    cost_new = 0;
}

template<int Dim>
ClassificationLearning<Dim>::~ClassificationLearning(){
    
}


template<int Dim>
void ClassificationLearning<Dim>::computeClassification(){
    int count = functions.size();
    Swarm<2*Dim+1> swarm( 70 );
    LatinHypercubeDistributor<2*Dim + 1> LHD;
    Coordinate<Dim> center;
    Coordinate<Dim> sigma;
    double coef;
    swarm.assignBounds(bounds);
    swarm.assignCostFunc(&costFunction);
    swarm.assignDistributor(&LHD);
    swarm.setMaxIters(20);
    costFunction.assignBasisFunctions( &functions );

    
    
    while ( count < maxNumOfBasisFuncs ){
        functions.push( RadialBasisFunc<Dim>() );
        swarm.initializePoints();
        swarm.runOptimization();
        MinHeap<double, Coordinate<2*Dim+1>> results = swarm.getResults(1);
        
        cost_new = results.getRootKey();
        
        for (int i = 0; i < Dim; i++) {
            center[i] = results[0][i];
            sigma[i] = results[0][Dim + i];
        }
        coef = results[0][2*Dim];
        functions[count].assignSigma ( sigma );
        functions[count].assignCenter ( center );
        functions[count].assignCoefficient ( coef );
        
        count++;
    }
}


template<int Dim>
void ClassificationLearning<Dim>::saveResults( char* filename ) const{
    FILE* file = fopen(filename, "w+");
    if( file != 0 ){
        
        for (int i = 0; i < functions.size(); i++) {
            
            //
            // Print the coefficient
            //
            fprintf(file, "%lf", functions[i].coef);
            
            
            //
            // Print Center
            //
            for (int j = 0; j < Dim; j++) {
                fprintf(file, ", %lf",functions[i].center[j] );
            }
            
            //
            // Print Standard Deviations
            //
            for (int j = 0; j < Dim; j++) {
                fprintf(file, ", %lf",functions[i].sigma[j] );
            }fprintf(file, "\n");
            
            
            
        }
        
        
        fclose(file);
    }
}

//AdaptiveArray<RadialBasisFunc<Dim>> functions;

/*
double cost_old;
double cost_new;

double weight;
Vec<Coordinate<Dim>>* points;
Vec<double> * values;
int maxNumOfBasisFuncs;
*/


#endif