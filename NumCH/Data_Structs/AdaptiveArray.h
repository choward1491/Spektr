//
//  AdaptiveArray.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/6/15.
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

#ifndef __Data_Structs__AdaptiveArray__
#define __Data_Structs__AdaptiveArray__

#include <stdio.h>


template<typename T>
class AdaptiveArray {
public:
    AdaptiveArray();
    AdaptiveArray(int _numElements);
    AdaptiveArray( const AdaptiveArray<T> & arr );
    ~AdaptiveArray();
    AdaptiveArray<T> & operator=( const AdaptiveArray<T> & arr );
    T & operator[](int index){ return data[index]; }
    T & operator[](int index) const { return data[index]; }
    void push( const T & input );
    int size() const { return usedCount; }
    
private:
    template< typename U>
    friend class AdaptiveArray;
    
    void resize();
    void clear();
    void copy( const AdaptiveArray<T> & arr );
    
    T* data;
    int usedCount;
    int totalCount;
    
};


#ifndef _adaptivearray_cpp_
#include "AdaptiveArray.cpp"
#endif

#endif /* defined(__Data_Structs__AdaptiveArray__) */
