//
//  ConfigParser.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ConfigParser.hpp"





void ConfigParser::parse( const char* filename ){
    
    //
    // Try to open the file
    //
    FILE* fptr = fopen(filename, "r");
    
    
    
    //
    // If the file exists
    //
    if( fptr  != 0 ){
        
        //
        // Define temp variables
        //
        char    str[512];
        char    name[32];
        char    number[64];
        double  value = 0;
        
        
        //
        // Loop through the file and read in the file values
        //
        while ( fscanf(fptr, " %[^\n]\n", str) != EOF ){
            
            if ( str[0] != '#' && str[0] != '/' && str[0] != '\0' ) {
                sscanf(str, "%[^:]: %[-eE1234567890.]", name, number);
                sscanf(number, "%lf", &value);
                printf("name = %s, num = %lf\n",name, value);
                if (name[0] != '\0') {
                    parameters[std::string(name)] = value;
                }
            }
        }
        
        
        //
        // Close the file
        //
        fclose(fptr);
    }

    
}

ConfigParser::ConfigParser( const char* filename ){
    parse(filename);
}





template<typename T>
T ConfigParser::getValueFrom( const char* parameterName ) {
    return (T)parameters[std::string(parameterName)];
}

template<>
double ConfigParser::getValueFrom( const char* parameterName ) {
    return (double)parameters[std::string(parameterName)];
}

template<>
bool ConfigParser::getValueFrom( const char* parameterName ) {
    return (1==(int)parameters[std::string(parameterName)]);
}

template<typename T>
T ConfigParser::getValueFrom( const std::string & parameterName ) {
    return (T)parameters[parameterName];
}

template<>
bool ConfigParser::getValueFrom( const std::string & parameterName ) {
    return (1==(int)parameters[parameterName]);
}

template<>
double ConfigParser::getValueFrom( const std::string & parameterName ) {
    return (double)parameters[parameterName];
}


