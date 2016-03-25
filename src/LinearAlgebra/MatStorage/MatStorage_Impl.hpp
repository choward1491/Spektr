//
//  MatStorage_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/24/16.
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

#ifndef MatStorage_Impl_h
#define MatStorage_Impl_h

#include "MatStorage_Impl.hpp"

#define TEMPLATE_HEADER template< typename T, MatType Type, class Hash >
#define STORAGE MatStorage<T,Type,Hash>


TEMPLATE_HEADER
STORAGE::MatStorage():table(0),nt(0),dims(0,0),dummy(T()),isT(false){}

TEMPLATE_HEADER
STORAGE::MatStorage(int r, int c, T dval):nt(Hash::netSize(r,c)),
table(nt,dval),dims(r,c),dummy(T()),isT(false){}

TEMPLATE_HEADER
STORAGE::MatStorage(Dims d, T dval):nt(Hash::netSize(d.rows,d.cols)),
table(nt,dval),dims(d),dummy(T()),isT(false){}

TEMPLATE_HEADER
void STORAGE::resize(int r, int c){
    nt = r*c;
    dims = Dims(r,c);
    table.resize(nt);
    isT = false;
}

TEMPLATE_HEADER
void STORAGE::transpose(){ isT = !isT; }

TEMPLATE_HEADER
bool STORAGE::isTransposed() const { return isT; }

TEMPLATE_HEADER
T & STORAGE::operator()(int r, int c){
    size_t k = 0;
    if( isT ){
        k = Hash::hash(c,r,dims.cols,nt);
    }else{
        k = Hash::hash(r,c,dims.cols,nt);
    }
    if( k < nt ){ return table[k]; }
    else{ dummy = cdummy; return dummy; }
}

TEMPLATE_HEADER
const T & STORAGE::operator()(int r, int c) const{
    size_t k = 0;
    if( isT ){
        k = Hash::hash(c,r,dims.cols,nt);
    }else{
        k = Hash::hash(r,c,dims.cols,nt);
    }
    if( k < nt ){ return table[k]; }
    else{ return cdummy; }
}

TEMPLATE_HEADER
T & STORAGE::operator()(int k){
    if( k < nt ){ return table[k]; }
    else{ dummy = cdummy; return dummy; }
}

TEMPLATE_HEADER
const T & STORAGE::operator()(int k) const{
    if( k < nt ){ return table[k]; }
    else{ return cdummy; }
}

TEMPLATE_HEADER
Dims STORAGE::size() const { if( isT ){ return Dims(dims.cols,dims.rows); } else{ return dims; } }

TEMPLATE_HEADER
int STORAGE::total() const { return nt; }


#undef TEMPLATE_HEADER
#undef STORAGE


#endif /* MatStorage_Impl_h */
