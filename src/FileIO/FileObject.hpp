//
//  FileObject.hpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 12/12/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
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
