//
//  MatHashes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
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

#ifndef MatHashes_hpp
#define MatHashes_hpp

#include <stdio.h>
#include "MatTypes.hpp"




template< MatType T >
class Hasher {
public:
    static size_t hash(int i, int j, int nc, int nt){
        return nc*i + j;
    }
    
    static size_t netSize(int r, int c){
        return r*c;
    }
};


#define DEFINITION public:\
                    static size_t hash(int i, int j, int nc, int nt);\
                    static size_t netSize(int r, int c);

template<> class Hasher<Diagonal>{DEFINITION};
template<> class Hasher<Symmetric>{DEFINITION};
template<> class Hasher<Lower>{DEFINITION};
template<> class Hasher<Upper>{DEFINITION};
template<> class Hasher<Tridiagonal>{DEFINITION};
template<> class Hasher<Sparse>{DEFINITION};

#undef DEFINITION





#endif /* MatHashes_h */
