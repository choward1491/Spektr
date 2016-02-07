//
//  MatTypes.hpp
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

#ifndef MatTypes_h
#define MatTypes_h


enum MatType { General=0, Symmetric, Upper, Lower, Tridiagonal, Diagonal, Sparse };


namespace la {
    
template<class T> class LMat;
template<class T> class UMat;
template<class T> class Mat;
template<class T> class SMat;
template<class T> class TDMat;
template<class T> class DMat;
template<class T> class SpMat;
    
}

    
template<class T, class CRTP>
class MType {
public:
    const static MatType Type = General;
};
    
template<class T>
class MType<T,la::LMat<T> > {
public:
    const static MatType Type = Lower;
};
    
template<class T>
class MType<T,la::UMat<T> > {
public:
    const static MatType Type = Upper;
};

template<class T>
class MType<T,la::Mat<T> > {
public:
    const static MatType Type = General;
};

template<class T>
class MType<T,la::SMat<T> >{
public:
    const static MatType Type = Symmetric;
};

template<class T>
class MType<T,la::TDMat<T> > {
public:
    const static MatType Type = Tridiagonal;
};

template<class T>
class MType<T,la::DMat<T> > {
public:
    const static MatType Type = Diagonal;
};

template<class T>
class MType<T,la::SpMat<T> > {
public:
    const static MatType Type = Sparse;
};
    
    
//}

#endif /* MatTypes_h */
