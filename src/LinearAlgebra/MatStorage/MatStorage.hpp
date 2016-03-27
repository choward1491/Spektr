//
//  MatHashes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef MatStorage_h
#define MatStorage_h


#include <vector>
#include "MatTypes.hpp"
#include "MatHashes.hpp"
#include "Dims.hpp"

//namespace la {


template< typename T, MatType Type, class Hash = Hasher<Type>  >
class MatStorage {
public:
    
    MatStorage();
    MatStorage(int r, int c, T dval);
    MatStorage(Dims d, T dval);
    
    void resize(int r, int c, T dval = static_cast<T>(0));
    void resize(Dims d, T dval = static_cast<T>(0));
    
    void transpose();
    bool isTransposed() const;
    
    T & operator()(int r, int c);
    const T & operator()(int r, int c) const;
    T & operator()(int k);
    const T & operator()(int k) const;
    
    Dims size() const;
    int total() const;
    
    void print() const;
    
    
private:
    
    Dims dims;
    int nt;
    bool isT;
    std::vector<T> table;
};

#include "MatStorage_Impl.hpp"
#include "MatStorage_Sparse.hpp"
#include "ComplexMatStorage.hpp"
    
//}


#endif /* MatHashes_h */
