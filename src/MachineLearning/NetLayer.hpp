//
//  NetLayer.hpp
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

#ifndef NetLayer_hpp
#define NetLayer_hpp

#include <stdio.h>
#include <vector>
#include "Matrix.hpp"

class NetFunc;

class NetLayer {
public:
    typedef la::Mat<double> Mat;
    NetLayer( int num_nodes = 1 );
    ~NetLayer();
    
    int numNodes() const;
    int numNodesWithoutBias() const;
    
    Mat & getLayerInput();
    Mat & getLayerOutput();
    Mat & getLayerBackPropError();
    Mat & getLayerDerivatives();
    void computeActivation();
    
    void setFuncAt( int index, NetFunc * node );
    void setLayerFunc( NetFunc * func);
    
private:
    int num_nodes;
    Mat outputs, inputs, err, derivs;
    std::vector<NetFunc*> node_funcs;
};

#endif /* NetLayer_hpp */
