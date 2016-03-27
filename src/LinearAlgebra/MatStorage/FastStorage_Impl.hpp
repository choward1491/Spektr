//
//  FastStorage_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 3/25/16.
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

#ifndef FastStorage_Impl_h
#define FastStorage_Impl_h

#define TEMPLATE_HEADER template< typename T, int Rows, int Cols  >
#define STORAGE FastStorage<T,Rows,Cols>

TEMPLATE_HEADER
STORAGE::FastStorage(T dval):dims(Rows,Cols){
    nt = Rows*Cols+1;
    isT = false;
    for (int i = 0; i < nt; i++) {
        data[i] = dval;
    }
}

TEMPLATE_HEADER
STORAGE::FastStorage(int dummyRows, int dummyCols, T dval ):dims(Rows,Cols){
    nt = Rows*Cols+1;
    isT = false;
    for (int i = 0; i < nt; i++) {
        data[i] = dval;
    }
}

TEMPLATE_HEADER
void STORAGE::transpose(){
    isT = !isT;
}

TEMPLATE_HEADER
bool STORAGE::isTransposed() const{
    return isT;
}

TEMPLATE_HEADER
T & STORAGE::operator()(int r, int c){
    int k = 0;
    if( isT ){
        k = Hash::hash(c,r,Cols,nt);
    }else{
        k = Hash::hash(r,c,Cols,nt);
    }
    return data[k%nt];
}
TEMPLATE_HEADER
const T & STORAGE::operator()(int r, int c) const{
    int k = 0;
    if( isT ){
        k = Hash::hash(c,r,Cols,nt);
    }else{
        k = Hash::hash(r,c,Cols,nt);
    }
    return data[k%nt];
}
TEMPLATE_HEADER
T & STORAGE::operator()(int k){
    return data[k%nt];
}
TEMPLATE_HEADER
const T & STORAGE::operator()(int k) const{
    return data[k%nt];
}

TEMPLATE_HEADER
Dims STORAGE::size() const{
    if( isT ){ return Dims(Cols,Rows); }
    return dims;
}

TEMPLATE_HEADER
int STORAGE::total() const{
    return nt;
}
    


#undef TEMPLATE_HEADER
#undef STORAGE


#endif /* FastStorage_Impl_h */
