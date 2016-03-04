//
//  DataPrinter.cpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "DataPrinter.hpp"


void DataPrinter::addVariableToPrint( const double * address, const std::string & name ){
    printList.push_back(address);
    printNames.push_back(name);
}


void DataPrinter::update(){
    
    FILE * file = 0;
    
    if( not hasHeader ){
        file = fopen(outFile.c_str(), "w");
        if( file != 0 ){
            writeNameHeader(file);
            writeDataToFile( file );
            hasHeader = true;
        }
        
    }else{
        file = fopen(outFile.c_str(), "a");
        if( file != 0 ){
            writeDataToFile( file );
        }
    }

    if( file != 0 ){ fclose(file); }
    
}


void DataPrinter::writeDataToFile( FILE* file ) const{
    for (int i = 0; i < printList.size(); i++ ) {
        fprintf(file, "%-15.8lf ",*printList[i]);
    } fprintf(file, "\n");
}
void DataPrinter::writeNameHeader( FILE* file) const{
    for (int i = 0; i < printNames.size(); i++) {
        fprintf(file,"%-15s ",printNames[i].c_str());
    } fprintf(file,"\n");
}



void DataPrinter::setSimHistoryFileName( std::string & filename ){
    outFile = filename;
}

void DataPrinter::reset(){
    hasHeader = false;
}

void DataPrinter::newMonteCarlo() const {
    FILE * file = fopen(outFile.c_str(), "a");
    if( file != 0 ){
        
        // print variable values
        fprintf(file, "\n");
        
        fclose(file);
    }
}
