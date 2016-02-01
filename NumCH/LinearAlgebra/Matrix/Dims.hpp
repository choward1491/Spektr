//
//  Dim.hpp
//  NumCH
//
//  Created by Christian J Howard on 1/30/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef Dim_h
#define Dim_h

struct Dims {
    size_t rows;
    size_t cols;
    
    Dims( size_t r, size_t c ):rows(r),cols(c){}
    
    bool operator==( const Dims & d ){
        return (d.rows == rows) && (d.cols == cols);
    }
    bool operator!=( const Dims & d ){
        return !operator==(d);
    }
};

#endif /* Dim_h */
