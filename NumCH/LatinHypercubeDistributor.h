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

// typedef a pop array
typedef PopArray<double> Popper;


/*!
 * This class represents a latin hypercube particle
 * distributor for a particle swarm
 *
 */
template<int Dim>
class LatinHypercubeDistributor: public ParticleDistributor<Dim> {
public:
    // set useful typedefs
    typedef SwarmParticle<Dim>  Particle;
    typedef Vec<Particle>       Particles;
    typedef Coordinate<2>       Point2D;
    
    // overwrite particle distributor method
    virtual void distribute( Particles & particles, Vec<Point2D> & bounds ){
        
        
        
        // obtain number of particles
        int numParticles = particles.size();
        
        
        
        // specify amount of cumulative distribution function range each
        // particle will have per dimension
        double df = 1.0/((double)numParticles);
        
        
        
        // specify velocity bound temp variable
        double velBound = 0;
        
        
        
        // Intialize vec array that stores a popper for each
        // dimension
        Vec<Popper> draws(Dim);
        for (int i = 0; i < Dim; i++) {
            draws[i] = Popper(numParticles);
            for( int j = 0; j < numParticles; j++ ){
                draws[i][j] = j;
            }
        }
        
        
        
        
        // Obtain minimum velocity bound
        double del;
        for (int i = 0; i < Dim; i++) {
            del = fabs(bounds[i][1] - bounds[i][0]);
            if( del < velBound ){
                velBound = del;
            }
        }
        
        
        
        
        
        
        // specify temp variables
        int randIndex = 0;
        double lb, rb, s;
        
        // loop through particles
        for (int i = 0; i < numParticles; i++) {
            
            // loop through dimension
            for (int j = 0; j < Dim; j++) {
                
                // pop a random index from the jth popper
                randIndex = draws[j].pop(generator.randInt()%draws[j].size());
                
                
                // compute the lower and upper bound
                // of this dimension based on the random index
                del = bounds[j][1] - bounds[j][0];
                lb = df*randIndex;
                lb = bounds[j][0]*(1-lb) + bounds[j][1]*lb;
                rb = df*(randIndex+1);
                rb = bounds[j][0]*(1-rb) + bounds[j][1]*rb;
                
                
                // compute a random parametrization value betweeon 0 and 1
                s = generator.rand();
                
                
                // compute the jth dimension position for the particle
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
