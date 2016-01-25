//
//  DataSet.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/24/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef DataSet_hpp
#define DataSet_hpp

#include <stdio.h>
#include <vector>

namespace ANN {
    
    
    class DataSet {
    public:
        typedef std::vector<std::vector<double>> Data;
        
        DataSet(){}
        void setDataRetreiver( void (*f)( Data & in, Data & out ) ){}
        
        Data in;
        Data out;
        
    private:
        void (*getData)( Data & in, Data & out );
        
    };
    
    
    
    
}

#endif /* DataSet_hpp */
