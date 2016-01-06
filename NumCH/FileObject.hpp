//
//  FileObject.hpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 12/12/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef FileObject_hpp
#define FileObject_hpp

#include <stdio.h>
#include <string>


class FileObject {
public:
    
    enum AccessMode { Read=0, Write, Append, ReadUpdate, WriteUpdate, AppendUpdate };
    
    FileObject();
    FileObject( const char* filename , AccessMode mode );
    FileObject( const std::string & filename, AccessMode mode );
    ~FileObject();
    
    bool isOpen() const;
    void openFile( const char* filename, AccessMode mode );
    void openFile( const std::string & filename, AccessMode mode );
    void resetFile();
    FILE* ref() const;
    
private:
    void clear();
    FILE* file;
    
};


#endif /* FileObject_hpp */
