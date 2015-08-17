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
        char    str[64];
        char    name[16];
        char    number[64];
        double  value = 0;
        
        
        //
        // Loop through the file and read in the file values
        //
        while ( fscanf(fptr, " %[^\n]\n", str) != EOF ){
            
            if ( str[0] != '#' && str[0] != '/' && str[0] != '\0' ) {
                sscanf(str, "%[^:]: %[-eE1234567890.]", name, number);
                sscanf(number, "%lf", &value);
                //printf("Name: %s, Number: %lf \n",name, value);
                if (name[0] != '\0') {
                    parameters[string(name)] = value;
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
    return (T)parameters[string(parameterName)];
}


