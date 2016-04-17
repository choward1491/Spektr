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
    
    if( !file.isOpen() ){ file.openFile(outFile, FileObject::Write); }
    
    if( !hasHeader ){
        
        if( file.isOpen() ){
            writeNameHeader( file.ref() );
            writeDataToFile( file.ref() );
            hasHeader = true;
        }
        
    }else{
        
        if( file.isOpen() ){
            writeDataToFile( file.ref() );
        }
    }
    
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



void DataPrinter::setSimHistoryFileName( const std::string & filename ){
    outFile = filename;
    file.openFile(outFile, FileObject::Write);
}

void DataPrinter::reset(){
    hasHeader = false;
}

void DataPrinter::newMonteCarlo() const {
    
    if( file.isOpen() ){
        
        // print variable values
        fprintf(file.ref(), "\n");
    }
}
    

