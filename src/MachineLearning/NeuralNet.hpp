//
//  NeuralNet.hpp
//  Spektr
//
//  Created by Christian J Howard on 7/24/16.
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

#ifndef NeuralNet_hpp
#define NeuralNet_hpp

#include <vector>
#include "Matrix.hpp"

class NetLayer;
class NetFunc;

class NeuralNet {
public:
    typedef la::Mat<double> Mat;
    
    // constructor/destructor stuff
    NeuralNet();
    NeuralNet( const std::vector<int> & layers );
    NeuralNet( const NeuralNet & net );
    ~NeuralNet();
    
    // set layer dimensions
    void setLayers( const std::vector<int> & layers );
    
    // operator
    Mat operator()(Mat & input );
    void operator()(Mat & input , Mat & output );
    void operator()(std::vector<double> & input , std::vector<double> & output );
    NeuralNet & operator=( const NeuralNet & net );
    
    // back propogation
    void backprop( const Mat & dEdO,Mat & gradient );
    Mat backprop( const Mat & dEdO );
    
    // get gradient with respect to input
    void grad( Mat & gradient );
    
    
    
    
    // weight stuff
    size_t numWeights() const;
    const double & weightAt(int index) const;
    double & weightAt(int index);
    const double & weightAt(int layer, int li, int ri) const;
    double & weightAt(int layer, int li, int ri);
    void printWeights() const;
    
    
    
    // node stuff
    size_t numNodes( int layer );
    size_t numNodes() const;
    void setActivationFunc( int layer, NetFunc * func);
    
    size_t numInputs() const;
    size_t numOutputs() const;
    size_t numLayers() const;
    
    
private:
    std::vector<NetLayer> layers;
    std::vector<Mat> weights;
    int total_nodes;
    int total_weights;
    std::vector<int> weight_count;
    
    int binarySearchWeightIdx( int index, int & mat_idx ) const ;
    
};

#endif /* NeuralNet_hpp */
