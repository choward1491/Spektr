//
//  Parser.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Parser.hpp"





    void Parser::parse( const char* filename ){
        
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
                if ( str[0] != '#' && str[0] != '\0' ) {
                    sscanf(str, "%[^:]: %[^#]", name, value);
                    
                    int ind = 0;
                    for (int i = 0; name[i] != '\0'; i++) {
                        if( name[i] != ' '){
                            name[ind] = name[i]; ind++;
                        }
                    }name[ind] = '\0';
                    
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

    Parser::Parser( const char* filename ){
        parse(filename);
    }




    template<typename T>
    T Parser::getValueFrom( const std::string & parameterName ) {
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
    bool Parser::getValueFrom( const std::string & parameterName ) {
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
    double Parser::getValueFrom( const std::string & parameterName ) {
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
    std::string Parser::getValueFrom( const std::string & parameterName ){
        return parameters[parameterName];
    }


    template<>
    std::vector<double> Parser::getValueFrom( const std::string & parameterName ){
        return getVectorFromString(parameters[parameterName]);
    }


    std::vector<double> Parser::increment( double start, double end, double incr ) const{
        std::vector<double> out;
        double val = start;
        if( start < end && incr > 0 ){
            while ( val <= end ){
                out.push_back(val);
                val+=incr;
            }
        }else if( start > end && incr < 0 ){
            while ( val >= end ){
                out.push_back(val);
                val+=incr;
            }
        }
        return out;
    }


    std::vector<double> Parser::parseSubVector( const std::string & vec ) const{
        std::string copy = vec;
        std::vector<double> out;
        int colonCount = 0;
        double values[3];
        for (int i = 0; i < copy.size(); i++) {
            if( copy[i] == ':' ){ colonCount++; }
        }
        
        if( colonCount == 0 ){
            sscanf(copy.c_str(), "%lf", &values[0]);
            out.push_back(values[0]);
        }else if( colonCount == 1 ){
            sscanf(copy.c_str(), "%lf:%lf", &values[0], &values[1]);
            if( values[0] < values[1] ){
                out = increment(values[0], values[1], 1.0);
            }else{
                out = increment(values[0], values[1], -1.0);
            }
        }else{
            sscanf(copy.c_str(), "%lf:%lf:%lf", &values[0], &values[1], &values[2]);
            out = increment(values[0], values[2], values[1]);
        }
        
        return out;
    }

    std::vector<double> Parser::getVectorFromString( const std::string & vec ) const{
        std::queue<std::string> substrings;
        std::vector<double> output;
        char c;
        char temp[64];
        int tracker = 0;
        
        for (int i = 0; i < vec.size(); i++) {
            c = vec[i];
            if ( (c <= '9' && c >= '0') || c == '-' || c == 'e' || c == 'E' || c == ':' || c == '.') {
                temp[tracker] = c; tracker++;
            }else if( c == ',' ){
                temp[tracker] = '\0';
                tracker = 0;
                substrings.push(std::string(&temp[0]));
            }
        }
        if( tracker > 0 ){
            temp[tracker] = '\0';
            substrings.push(std::string(&temp[0]));
        }
        
        
        while (substrings.size() > 0) {
            std::string sub = substrings.front(); substrings.pop();
            std::vector<double> subvec = parseSubVector( sub );
            std::vector<double>::iterator it = subvec.begin();
            for (; it != subvec.end(); it++) {
                output.push_back(*it);
            }
        }
        
        
        
        return output;
    }


    template<typename T>
    T Parser::getValueFrom( const char* parameterName ) {
        return getValueFrom<T>(std::string(parameterName));
    }

    template<>
    double Parser::getValueFrom( const char* parameterName ) {
        return getValueFrom<double>(std::string(parameterName));
    }

    template<>
    std::string Parser::getValueFrom( const char* parameterName ){
        return parameters[std::string(parameterName)];
    }

    template<>
    bool Parser::getValueFrom( const char* parameterName ) {
        return getValueFrom<bool>(std::string(parameterName));
    }

    template<>
    std::vector<double> Parser::getValueFrom( const char* parameterName ){
        return getValueFrom<std::vector<double> >( std::string( parameterName ) );
    }







    bool Parser::isOnlyNumbers( const std::string & str){
        return getStringType(str) == StringType::Number;
    }


    //enum StringType{ Number, Vector, Word };
    enum Parser::StringType Parser::getStringType( const std::string & str ){
        enum StringType type = StringType::Word;
        
        bool hasLetter = false;
        bool hasNumber = false;
        bool hasVectorStuff = false;
        bool isE = false;
        int eCounter = 0;
        char c;
        
        for (int i = 0; i < str.size(); i++) {
            c = str[i];
            
            isE = (c == 'e' || c == 'E');
            if( isE ){
                eCounter++;
            }
            
            if ( ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ) {
                if( isE && eCounter > 1 ){
                    hasLetter = true;
                }else if( !isE ){
                    hasLetter = true;
                }
            }else if( (c <= '9' && c >= '0') || c == '-' ){
                hasNumber = true;
            }else if( c == ',' || c == ']' || c == '[' || c == ':' ){
                hasVectorStuff = true;
            }
        }
        
        
        if( hasLetter ){
            type = StringType::Word;
        }else if( hasNumber && hasVectorStuff ){
            type = StringType::Vector;
        }else if( hasNumber ){
            type = StringType::Number;
        }
        
        
        return type;
    }
    

