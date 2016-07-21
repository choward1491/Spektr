//
//  CrossValidation.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/17/16.
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

#ifndef CrossValidation_h
#define CrossValidation_h

#include <vector>

template< int K_, class DataSet_, template<class,class> class Model_>
class CrossValidation {
protected:
    class Sets;
    
public:
    
    // number of folds to break data into
    static const int K = K_;
    
    // typedefs
    typedef DataSet_ DataSet;
    typedef Model_<DataSet,Sets>   Model;
    
    
    // null constructor
    CrossValidation();
    
    // get/set number of shuffles to do
    // in cross validation evaluation
    void setNumShuffles(int ns);
    int getNumShuffles(int ns) const;
    
    // compute cross validation
    double evaluate();
    
    // Cross Validation Data Set and Models
    DataSet data_set;
    Model model;
    
protected:
    friend class Model_<DataSet,Sets>;
    
    class Sets {
    public:
        int operator()(int set, int set_index) const;
        void init( DataSet &data);
        int setSize(int set) const;
        int numSets() const;
        
    private:
        static const int K = K_;
        int size;
        std::vector<int> indices;
        std::vector<int> start;
        std::vector<int> sub_size;
    };
    
private:
    void init();
    int numShuffles;
    Sets subsets;
    
};

#include "CrossValidation_Impl.hpp"

#endif /* CrossValidation_h */
