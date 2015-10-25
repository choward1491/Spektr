//
//  RandomDistributor.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __Data_Structs__RandomDistributor__
#define __Data_Structs__RandomDistributor__

#include <stdio.h>
#include "PseudoRandomGenerator.h"
#include "ParticleDistributor.h"

template<int Dim>
class RandomDistributor : public ParticleDistributor<Dim> {
public:
    typedef SwarmParticle<Dim> Particle;
    typedef Vec<Particle> Particles;
    typedef Coordinate<2> Point2D;
    
    
    virtual void distribute( Particles & particles, Vec<Point2D> & bounds ){
        int numParticles = particles.size();
        double del = 0;
        
        for (int i = 0; i < numParticles; i++) {
            for (int j = 0; j < Dim; j++) {
                del = generator.rand();
                particles[i].pose[j] = bounds[j][0]*(1-del) + bounds[j][1]*del;
            }
        }
    }
    
private:
    PseudoRandomGenerator generator;
    
    
    
};


#endif /* defined(__Data_Structs__RandomDistributor__) */
