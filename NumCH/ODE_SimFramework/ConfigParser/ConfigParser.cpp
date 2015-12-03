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
        char    value[512];
        
        
        //
        // Loop through the file and read in the file values
        //
        while ( fscanf(fptr, " %[^\n]\n", str) != EOF ){
            if ( str[0] != '#' && str[0] != '/' && str[0] != '\0' ) {
                sscanf(str, "%[^:]: %[^/#]", name, value);
                if (name[0] != '\0') {
                    parameters[std::string(name)] = std::string(value);
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
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[std::string(parameterName)];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf", &value);
        }
    }
    
    return (T)value;
}

template<>
double ConfigParser::getValueFrom( const char* parameterName ) {
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[std::string(parameterName)];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf", &value);
        }
    }
    
    return value;
}

template<>
std::string ConfigParser::getValueFrom( const char* parameterName ){
    return parameters[std::string(parameterName)];
}

template<>
bool ConfigParser::getValueFrom( const char* parameterName ) {
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[std::string(parameterName)];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf", &value);
        }
    }
    
    return (value == 1);
}

template<typename T>
T ConfigParser::getValueFrom( const std::string & parameterName ) {
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[parameterName];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf", &value);
        }
    }
    return (T)value;
}

template<>
bool ConfigParser::getValueFrom( const std::string & parameterName ) {
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[parameterName];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf%*[ ]", &value);
        }
    }
    
    return (value == 1);
}

template<>
double ConfigParser::getValueFrom( const std::string & parameterName ) {
    double value = 0.0;
    if( parameters.count(parameterName) > 0 ){
        std::string out = parameters[parameterName];
        if ( isOnlyNumbers(out) ) {
            sscanf(out.c_str(), "%lf", &value);
        }
    }
    
    return value;
}

template<>
std::string ConfigParser::getValueFrom( const std::string & parameterName ){
    return parameters[parameterName];
}


bool ConfigParser::isOnlyNumbers( const std::string & str){
    bool out = true;
    
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if( (c <= '9' && c >= '0') || c == '.' || c == 'e' || c == 'E' || c == '-' || c == ' '){
        }else{
            out = false;
            break;
        }
    }
    
    return out;
}
