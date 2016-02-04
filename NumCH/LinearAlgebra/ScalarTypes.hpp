//
//  ScalarTypes.hpp
//  NumCH
//
//  Created by Christian J Howard on 2/2/16.
//  Copyright © 2016 Christian Howard. All rights reserved.
//

#ifndef ScalarTypes_h
#define ScalarTypes_h

template<typename S>
class ScalarType {
    using Type = double;
};

template<>
class ScalarType<double> {
    using Type = double;
};

template<>
class ScalarType<float> {
    using Type = float;
};

template<>
class ScalarType<int> {
    using Type = int;
};

template<>
class ScalarType<unsigned int> {
    using Type = unsigned int;
};

#endif /* ScalarTypes_h */
