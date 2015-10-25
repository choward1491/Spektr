//
//  ArtilleryCost.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 10/16/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ArtilleryCost.hpp"


double ArtilleryCost::operator()( State & x ){
    
    
    for (int i = 0; i < net.size(); i++ ){
        net[i] = x[i];
    }
    
    
    
    
    int N = 10;
    
    double cost = 0, time = 0.0, dt = 1e-3;
    double r[2], v[2], g = -9.81;
    double rnums[4];
    double xb[4], tgt[4];
    
    for (int i = 0 ; i < 4*N; i++ ){
        rnums[i] = rnd.rand();
    }
    
    for( int i = 0; i < N; i++ ){
        
        
        
        rnums[0] = rnd.rand();
        rnums[1] = rnd.rand();
        rnums[2] = rnd.rand();
        rnums[3] = rnd.rand();
        r[0] = 5000 * rnums[0];
        r[1] = -500 * rnums[1];
        v[0] = 80 * rnums[2] - 40;;
        v[1] = 0;
        
        ANN::Input inv = { rnums[0], rnums[1], rnums[2], rnums[4] };
        
        ANN::Output out = net( inv );
        double vl = 500;
        double theta = (out[0] - 0.5)*M_1_PI;
        double c = 0.1;
        
        xb[0] = 0;
        xb[1] = 0;
        xb[2] = vl*cos(theta);
        xb[3] = vl*sin(theta);
        
        
        tgt[0] = r[0];
        tgt[1] = r[1];
        tgt[2] = v[0];
        tgt[3] = v[1];
        
        while( 1 ){
            xb[0] = xb[0] + dt * xb[2];
            xb[1] = xb[1] + dt * xb[3];
            xb[3] = xb[3] + dt * g;
            
            tgt[0] = tgt[0] + dt * tgt[2];
            tgt[1] = tgt[1] + dt * tgt[3];
            
            if( xb[1] < tgt[1] ){
                cost = cost + fabs(xb[0] - tgt[0])/((double)N);
                break;
            }
        }
    }
    
    
    
    
    return cost;
}




double ArtilleryCost::gradient( ArtilleryCost::State & x, ArtilleryCost::State & gradient, Hessian * hessian ){
    
    for (int i = 0; i < net.size(); i++ ){
        net[i] = x[i];
    }
    
    
    
    
    int N = 100;
    
    double cost = 0, time = 0.0, dt = 1e-3;
    double r[2], v[2], g = -9.81;
    double rnums[4*N];
    double xb[4], tgt[4];
    double h = 1e-4;
    double center = 0;
    
    for (int i = 0 ; i < 4*N; i++ ){
        rnums[i] = rnd.rand();
    }
    
    for ( int k = 0; k <= net.size(); k++ ){
        
        if( k == 1 ){
            net[k-1] = net[k-1] + h;
        }else{
            net[k-2] = net[k-2] - h;
            net[k-1] = net[k-1] + h;
        }
        
        cost = 0;
        
        for( int i = 0; i < N; i++ ){
            
            
            r[0] = 5000 * rnums[4*i];
            r[1] = -500 * rnums[4*i+1];
            v[0] = 80 * rnums[4*i + 2] - 40;
            v[1] = 0;
            
            /*r[0] = 5000 * rnums[4*i];
            r[1] = -500 * rnums[4*i+1];
            v[0] = 80 * rnums[4*i + 2] - 40;
            v[1] = 0;*/
            
            ANN::Input inv = { rnums[4*i], rnums[4*i+1], rnums[4*i+2], rnums[4*i+3] };
            
            ANN::Output out = net( inv );
            double vl = 500;
            double theta = (out[0] - 0.5)*M_1_PI;
            double c = 0.1;
            
            xb[0] = 0;
            xb[1] = 0;
            xb[2] = vl*cos(theta);
            xb[3] = vl*sin(theta);
            
            
            tgt[0] = r[0];
            tgt[1] = r[1];
            tgt[2] = v[0];
            tgt[3] = v[1];
            
            while( 1 ){
                xb[0] = xb[0] + dt * xb[2];
                xb[1] = xb[1] + dt * xb[3];
                xb[3] = xb[3] + dt * g;
                
                tgt[0] = tgt[0] + dt * tgt[2];
                tgt[1] = tgt[1] + dt * tgt[3];
                
                if( xb[1] < tgt[1] ){
                    cost = cost + fabs(xb[0] - tgt[0])/((double)N);
                    break;
                }
            }
        }
        
        if( k == 0 ){
            center = cost;
        }else{
            
            gradient[k-1] = (cost - center)/h;
            if( k == net.size() ){
                net[k-1] = net[k-1] - h;
            }
        }
        
    }
    
    
    return center;
}

