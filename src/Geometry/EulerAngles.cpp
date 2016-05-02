//
//  EulerAngles.cpp
//  Spektr
//
//  Created by Christian J Howard on 4/29/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#include "EulerAngles.hpp"

//double angles[3];

EulerAngles::EulerAngles(){
    angles[0] = 0.0;
    angles[1] = 0.0;
    angles[2] = 0.0;
}

EulerAngles::EulerAngles(double a1, double a2, double a3){
    angles[0] = a1;
    angles[1] = a2;
    angles[2] = a3;
}
double & EulerAngles::operator[](int i){
    return angles[i%3];
}
const double & EulerAngles::operator[](int i) const{
    return angles[i%3];
}