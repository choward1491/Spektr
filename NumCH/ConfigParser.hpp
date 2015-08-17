//
//  ConfigParser.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef ConfigParser_cpp
#define ConfigParser_cpp

#include <stdio.h>
#include <map>
#include <string>
using namespace std;


class ConfigParser {
public:
    
    
    ConfigParser( const char* filename );
    
    template<typename T>
    T getValueFrom( const char* parameterName ) ;
    
    void parse( const char* filename );
    
private:
    
    map<string, double> parameters;
    
    
};

#endif /* ConfigParser_cpp */
