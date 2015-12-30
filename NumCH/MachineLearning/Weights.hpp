//
//  Weights.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Weights_hpp
#define Weights_hpp

#include <stdio.h>
#include <unordered_map>
#include "RandomNumberGenerator.hpp"

namespace ANN{

struct Pair {
    unsigned int iFrom;
    unsigned int iTo;
    
    bool operator==( const Pair & p ) const{
        return p.iFrom == iFrom && p.iTo == iTo;
    }
};

}

template <>
struct std::hash<ANN::Pair>
{
    std::size_t operator()(const ANN::Pair& k) const
    {
        return (k.iFrom << 3) ^ k.iTo;
    }
};



namespace ANN {


class Weights {
public:
    
    Weights(){
        index = 0;
        size_ = 0;
        w = 0;
        ht.reserve(20);
    }
    
    Weights( int count ){
        
        index = 0;
        size_ = count;
        w = new double[count]();
        ht.reserve(count+5);
    }
    
    ~Weights(){
        clear();
    }
    
    void randomWeights(){
        static RandomNumberGenerator gen;
        
        for (int i = 0; i < size_; i++) {
            w[i] = gen.rand()*2.0 - 1.0;
        }
    }
    
    void addPair( const Pair & p ){
        ht[p] = index; index++;
    }
    
    double operator()( const Pair & p ) const {
        return w[ht.at(p)];
    }
    
    double & operator()( const Pair & p ){
        return w[ht[p]];
    }
    
    double operator[]( int ind ) const{
        return w[ind];
    }
    
    double & operator[]( int ind ){
        return w[ind];
    }
    
    Weights & operator=( const Weights & weights ){
        if( this != &weights ){
            clear();
            copy(weights);
        }
        return *this;
    }
    
    
    int size() const {
        return size_;
    }
    
    void print() const{
        printf("w = [ ");
        for (int i = 0; i < size_; i++) {
            printf(" %lf ",w[i]);
        }
        printf("]\n");
    }
    
private:
    
    friend class Weights;
    
    void copy( const Weights & weights ){
        size_ = weights.size_;
        w = new double[size_];
        
        for (int i = 0; i < size_; i++) {
            w[i] = weights.w[i];
        }
        
        ht = weights.ht;
        index = weights.index;
    }
    
    void clear(){
        if ( w != 0 ){ delete [] w; }
    }
    
    
    
    size_t index;
    int size_;
    double * w;
    std::unordered_map<Pair, size_t> ht;
    
    
};
    
}

#endif /* Weights_hpp */
