//
//  LocalFitter.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef Data_Structs_LocalFitter_h
#define Data_Structs_LocalFitter_h

#include "kd_tree.h"
#include "Coordinate.h"

template<int DI, int DO>
class LocalFitter {
public:
    LocalFitter():tree(){}
    
protected:
    KDTree<DI, double, Coordinate<DI>, Coordinate<DO>> tree;
    
};



#endif
