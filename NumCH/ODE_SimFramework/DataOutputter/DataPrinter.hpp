//
//  DataPrinter.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef DataPrinter_hpp
#define DataPrinter_hpp

#include <stdio.h>
#include "DiscreteModel.hpp"
#include "AdaptiveArray.h"
#include <string>

typedef AdaptiveArray<const double*> PrintValueList;
typedef AdaptiveArray<std::string> PrintNames;




class DataPrinter : public DiscreteModel {
public:
    
    
    DataPrinter():hasHeader(false),outFile("history.txt"),printList(),printNames(){}
    
    
    
    /*!
     * This method is used to do any
     * other initialization for a model
     * that won't be done in the constructor,
     * such as if this model depends on any
     * other external models
     *
     * \params None
     * \returns None
     */
    virtual void initialize(){}
    
    
    
    
    // Destructor
    virtual ~DataPrinter(){}
    
    
    
    
    
    /*!
     * This method will be used to update
     * any discrete models that aren't
     * based on differential equations
     *
     * \params None
     * \returns None
     */
    virtual void update();
    
    
    void addVariableToPrint( const double * address, const std::string & name );
    void setSimHistoryFileName( std::string & filename );
    void newMonteCarlo() const;
    void reset();
    
    
private:
    
    
    // write data values
    void writeDataToFile( FILE* file ) const;
    void writeNameHeader( FILE* file) const;
    
    
    
    //
    // List of variables users want
    // to be printed at some defined frequency
    //
    PrintValueList  printList;
    PrintNames      printNames;
    std::string     outFile;
    bool hasHeader;
    
    
};





#endif /* DataPrinter_hpp */
