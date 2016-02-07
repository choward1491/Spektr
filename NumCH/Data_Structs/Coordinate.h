//
//  Coordinate.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
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

#ifndef __Data_Structs__Coordinate__
#define __Data_Structs__Coordinate__

#include <stdio.h>

template<int D>
class Coordinate {
public:
    
    double & operator[](int index){ return point[index]; }
    const double & operator[](int index) const { return point[index]; }
    Coordinate<D> & operator=( const Coordinate<D> & coord );
    void fprint( FILE * file) const;
    void fprintln( FILE * file) const;
    void print() const;
    void println() const;
    double point[D];
    int size() const { return D; }
    
    
};

#ifndef _coordinate_cpp_
#include "Coordinate.cpp"
#endif


#endif /* defined(__Data_Structs__Coordinate__) */
