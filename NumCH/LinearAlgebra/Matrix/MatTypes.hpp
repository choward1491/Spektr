//
//  MatTypes.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef MatTypes_h
#define MatTypes_h

//namespace la {

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
