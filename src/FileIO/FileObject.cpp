//
//  FileObject.cpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 12/12/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "FileObject.hpp"

//FILE* file;
//enum AccessMode { Read=0, Write, Append, ReadUpdate, WriteUpdate, AppendUpdate };

    FileObject::FileObject(){
        file = 0;
    }
FileObject::FileObject( const char* filename , AccessMode mode ):file(0){
        openFile(filename, mode);
    }
FileObject::FileObject( const std::string & filename, AccessMode mode ):file(0){
        openFile(filename, mode);
    }
    void FileObject::clear(){
        if( isOpen() ){ fclose(file); }
    }

    FileObject::~FileObject(){
        clear();
    }

    bool FileObject::isOpen() const{
        return (file != 0);
    }
    void FileObject::openFile( const char* filename, AccessMode mode ){
        clear();
        
        char m[3] = {'r','\0','\0'};
        
        switch (mode) {
            case AccessMode::Read:
                break;
            case AccessMode::Write:
                m[0] = 'w';
                break;
            case AccessMode::Append:
                m[0] = 'a';
                break;
            case AccessMode::ReadUpdate:
                m[1] = '+';
                break;
            case AccessMode::WriteUpdate:
                m[0] = 'w'; m[1] = '+';
                break;
                
            case AccessMode::AppendUpdate:
                m[0] = 'a'; m[1] = '+';
                break;
        }
        
        file = fopen(filename, &m[0]);
    }
    void FileObject::openFile( const std::string & filename, AccessMode mode ){
        openFile(filename.c_str(), mode);
    }
    void FileObject::resetFile(){
        if( isOpen() ){ rewind(file); }
    }

    FILE*  FileObject::ref() const { return file; }


