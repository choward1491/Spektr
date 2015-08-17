//
//  camera.h
//  GraphicsLearning
//
//  Created by Christian J Howard on 4/17/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef __GraphicsLearning__camera__
#define __GraphicsLearning__camera__

#include <stdio.h>
#include "Vec3.h"
#include "sphere.h"
#include "plane.h"
#include "PointLight.h"
#include "Image.h"


class Camera {
    
public:
    
    Vec3<double> pos;
    Vec3<double> dir1;
    Vec3<double> dir2;
    Vec3<double> dir3;
    double fx;
    double fy;
    double flen;
    Image<double> img;
    double theta;
    
    
    Camera(){
        spheres = 0;
        ns = 0;
        lights = 0;
        npl = 0;
        planes = 0;
        np = 0;
        theta = 0;
    }
    
    
    Camera( int num_spheres, int num_plights, int num_planes , int width, int height ):img(height, width, Vec4<double>(0, 1, 1) ){
        ns  = num_spheres;
        spheres = new Sphere[ns]();
        
        
        npl = num_plights;
        lights = new PLight[npl]();
        
        np  = num_planes;
        planes = new Plane[np]();
        
        theta = 0;
    }
    
    
    Sphere* spheres;
    int ns;
    
    PLight* lights;
    int npl;
    
    Plane * planes;
    int np;
    
    
    
    ~Camera(){
        if ( spheres != 0 ) {
            delete [] spheres;
        }
        
        if ( lights != 0 ) {
            delete [] lights;
        }
        
        if ( planes != 0 ) {
            delete [] planes;
        }
        
    }
    
    //void getOtherDirs();
    void generateScene();
    
    void recursiveFind(Ray<double> & ray, Vec4<double> & color, double & weight );
    
    
private:
    
    
};








#endif /* defined(__GraphicsLearning__camera__) */
