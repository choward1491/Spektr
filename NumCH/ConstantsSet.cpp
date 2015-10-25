//
//  ConstantsSet.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "ConstantsSet.hpp"


    
void Constants::readFile( const char* filename ){
    if( parser == 0 ){
        parser = new ConfigParser(filename);
    }else{
        parser->parse(filename);
    }
}
    
Constants::~Constants(){
    deleteParser();
}

void Constants::setConstants(){
    // Do nothing for this object
}

void Constants::deleteParser(){
    if( parser != 0 ){
        delete parser;
        parser = 0;
    }
}