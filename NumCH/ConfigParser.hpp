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

/*!
 * Class to read inputs from a file and put them into
 * a hash table for look up
 *
 */
class ConfigParser {
public:
    
    // Initialize config file parser from filename
    ConfigParser( const char* filename );
    
    // get your value from the table
    template<typename T>
    T getValueFrom( const char* parameterName ) ;
    
    // method to parse a file and dump it's contents into a hash table
    void parse( const char* filename );
    
private:
    
    map<string, double> parameters;
    
    
};

#endif /* ConfigParser_cpp */
