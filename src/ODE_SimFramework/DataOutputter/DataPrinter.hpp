//
//  DataPrinter.hpp
//  NumCH
//
//  Created by Christian J Howard on 11/21/15.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//

#ifndef DataPrinter_hpp
#define DataPrinter_hpp

#include <stdio.h>
#include "DiscreteModel.hpp"
#include <vector>
#include <string>
#include "FileObject.hpp"

typedef std::vector<const double*> PrintValueList;
typedef std::vector<std::string> PrintNames;




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
    void setSimHistoryFileName( const std::string & filename );
    void newMonteCarlo() const;
    void reset();
    
    
private:
    
    
    // write data values
    void writeDataToFile( FILE* file ) const;
    void writeNameHeader( FILE* file ) const;
    
    
    
    //
    // List of variables users want
    // to be printed at some defined frequency
    //
    PrintValueList  printList;
    PrintNames      printNames;
    FileObject      file;
    std::string     outFile;
    bool hasHeader;
    
    
};





#endif /* DataPrinter_hpp */
