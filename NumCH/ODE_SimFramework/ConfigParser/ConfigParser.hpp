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

/*!
 * Class to read inputs from a file and put them into
 * a hash table for look up
 *
 */
class ConfigParser {
public:
    
    // Null constructor
    ConfigParser(){}
    
    // Initialize config file parser from filename
    ConfigParser( const char* filename );
    
    // get your value from the table
    template<typename T>
    T getValueFrom( const char* parameterName ) ;
    
    template<typename T>
    T getValueFrom( const std::string & parameterName ) ;
    
    
    
    
    // method to parse a file and dump it's contents into a hash table
    //
    // Note that comments are denoted by either # or // and are only one line
    // An example config file could be the following:
    //
    // # Here's some comment
    // test: 15
    // toDance: 1
    //
    // # Here's another comment
    // variable1: 104.3
    //
    void parse( const char* filename );
    
private:
    
    std::map<std::string, double> parameters;
    
    
};

#endif /* ConfigParser_cpp */
