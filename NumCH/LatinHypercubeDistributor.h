//
//  LatinHypercubeDistributor.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/5/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__LatinHypercubeDistributor__
#define __Data_Structs__LatinHypercubeDistributor__

#include <stdio.h>
#include "ParticleDistributor.h"
#include "PseudoRandomGenerator.h"
#include "PopArray.h"

typedef PopArray<double> Popper;

template<int Dim>
class LatinHypercubeDistributor: public ParticleDistributor<Dim> {
public:
    typedef SwarmParticle<Dim> Particle;
    typedef Vec<Particle> Particles;
    typedef Coordinate<2> Point2D;
    
    
    virtual void distribute( Particles & particles, Vec<Point2D> & bounds ){
        int numParticles = particles.size();
        double df = 1.0/((double)numParticles);
        double velBound = 0;
        
        Vec<Popper> draws(Dim);
        for (int i = 0; i < Dim; i++) {
            draws[i] = Popper(numParticles);
            for( int j = 0; j < numParticles; j++ ){
                draws[i][j] = j;
            }
        }
        
        double del;
        for (int i = 0; i < Dim; i++) {
            del = fabs(bounds[i][1] - bounds[i][0]);
            if( del > velBound ){
                velBound = del;
            }
        }
        
        
        
        int randIndex = 0;
        double lb, rb, s;
        for (int i = 0; i < numParticles; i++) {
            for (int j = 0; j < Dim; j++) {
                randIndex = draws[j].pop(generator.randInt()%draws[j].size());
                del = bounds[j][1] - bounds[j][0];
                lb = df*randIndex;
                lb = bounds[j][0]*(1-lb) + bounds[j][1]*lb;
                rb = df*(randIndex+1);
                rb = bounds[j][0]*(1-rb) + bounds[j][1]*rb;
                s = generator.rand();
                
                particles[i].velocity[j] = s*del;
                particles[i].pose[j] = lb*(1-s) + rb*s;
                particles[i].velBound = velBound;
            }
        }
    }
    
private:
    PseudoRandomGenerator generator;
};


#endif /* defined(__Data_Structs__LatinHypercubeDistributor__) */
