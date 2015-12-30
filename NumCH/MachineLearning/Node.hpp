//
//  Node.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>

namespace ANN{

class Node {
public:
    
    Node();
    void setNetInput( double z );
    double getNetInput() const;
    void setNetOutput( double o );
    double getNetOutput() const;
    
    void setDerivative( double d );
    double getDerivative() const;
    
    void setLayer( unsigned int l);
    unsigned int getLayer() const;
    
    void makeBias();
    bool isBias() const;
    
private:
    double z;
    double o;
    double deriv;
    unsigned int layer;
    bool isBias_;
    
};

    
}
#endif /* Node_hpp */
