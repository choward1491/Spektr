//
//  ConstantsSet.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ConstantsSet_cpp
#define ConstantsSet_cpp


#include "ConfigParser.hpp"



class Constants {
public:
    
    Constants():parser(0){}
    
    const double pi      = 3.1415926535897932384626433832795028841971693993751;
    const double pi_2    = pi * 2.0;
    const double deg2rad = pi/180.0;
    const double rad2deg = 180.0/pi;
    
    void readFile( const char* filename );
    virtual void setConstants();
    virtual ~Constants();
    
protected:
    ConfigParser* parser;
    void deleteParser();
    
private:
    
    
};
    


#endif /* ConstantsSet_cpp */
