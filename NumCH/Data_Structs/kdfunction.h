//
//  kdfunction.h
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef Data_Structs_kdfunction_h
#define Data_Structs_kdfunction_h


template<int K, class I, class O>
class KDFunction {
public:
    virtual ~KDFunction(){}
    virtual O operator()(I & input1, I & input2 ) = 0;
    virtual O operator()(I & input1, I & input2, int dim ) = 0;
private:
};


#endif
