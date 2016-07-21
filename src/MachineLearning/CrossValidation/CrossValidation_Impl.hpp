//
//  CrossValidation_Impl.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/18/16.
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

#ifndef CrossValidation_Impl_h
#define CrossValidation_Impl_h

#include "CrossValidation.hpp"
#include "PopArray.hpp"
#include "RandomNumberGenerator.hpp"

#define HEADER template< int K, class DS, template<class,class> class M>
#define CV CrossValidation<K,DS,M>
    
// number of folds to break data into
//static const int K = K_;

// typedefs
//typedef DataSet DataSet;
//typedef Model   Model;

// Cross Validation Data Set and Models
//DataSet data_set;
//Model<DataSet> model;

// null constructor
HEADER
CV::CrossValidation():data_set(),model(data_set,subsets){
    
}

HEADER
void CV::setNumShuffles(int ns){
    numShuffles = ns;
}

HEADER
int CV::getNumShuffles(int ns) const{
    return numShuffles;
}

// compute cross validation
HEADER
double CV::evaluate(){
    double inv_count = 1.0 / static_cast<double>(K*numShuffles) ;
    double error = 0.0;
    
    for(int shuffle = 0; shuffle < numShuffles; ++shuffle){
        subsets.init(); // reshuffle
        for(int set = 0; set < K; ++set ){
            model.train(set, subsets);
            error += (model.testError(set, subsets) * inv_count);
        }
    }
    return error;
}


HEADER
int CV::Sets::operator()(int set, int set_index) const{
    return indices[ (start[set] + sub_size[set_index]) % size ];
}

HEADER
int CV::Sets::setSize(int set) const {
    return sub_size[set];
}

HEADER
int CV::Sets::numSets() const {
    return K;
}

HEADER
void CV::Sets::init( DataSet & data_set ) {
    static RandomNumberGenerator rng;
    static bool hasNotInit = true;
    static PopArray<int> pa(data_set.size());
    
    // init variables for use in
    // subset creation
    size = data_set.size();
    int indiv_size = size/K;
    int rem = size % K;
    
    // init indices to random
    // locations
    if( hasNotInit ){
        indices.resize(size);
        start.resize(K);
        sub_size.resize(K);
        hasNotInit = false;
    }else{
        pa.reset();
    }
    
    // initialize indices
    for(int i = 0; i < size; i++ ){
        indices[i] = pa.pop( rng.randInt() % pa.size() );
    }
    
    // reset starting location and each subset size
    start[0] = rng.randInt() % size;
    sub_size[0] = indiv_size + (rem > 0);
    --rem;
    for(int i = 1; i < K; i++ ){
        start[i] = ( start[i-1] + sub_size[i-1] ) % size;
        sub_size[i] = indiv_size + (rem > 0);
        --rem;
    }
}

#undef HEADER
#undef CV

#endif /* CrossValidation_Impl_h */
