//
//  ModelState.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/15/16.
//
//  The MIT License (MIT)
//    Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef ModelState_hpp
#define ModelState_hpp

#include <stdio.h>


class ModelState {
public:
    // Constructors
    ModelState();
    ModelState(double ** address, size_t numDims, size_t offset );
    
    // Methods to access data
    double & operator[](size_t i);
    const double & operator[](size_t i) const;
    
    // methods to update state
    void setAddress( double ** address );
    void setNumDims( size_t numDims );
    void setOffset ( size_t offset_ );
    
    // Method to get reference to state pointer
    double * reference(){ return *ref; }
private:
    double ** ref;
    size_t ndim;
    size_t offset;
    
};


#endif /* ModelState_hpp */
