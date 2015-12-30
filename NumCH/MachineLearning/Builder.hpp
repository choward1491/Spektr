//
//  Builder.hpp
//  NumCH
//
//  Created by Christian J Howard on 12/28/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Builder_hpp
#define Builder_hpp

#include <stdio.h>
#include "ANN.hpp"

namespace ANN {
    
    class Builder {
    public:
        
        enum Type { FeedForward = 0 };
        
        Builder();
        void operator()( Network & net, Builder::Type type );
        void buildNetwork( Network & net, Builder::Type type );
        
    private:
        void feedForwardSetup( Network & net );
        void buildConnectionsBetweenLayers( Network & net, int start_index, int nL, int nR );
    };
    
    
}

#endif /* Builder_hpp */
