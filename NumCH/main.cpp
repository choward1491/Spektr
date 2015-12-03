//
//  main.cpp
//  NumCH
//
//  Created by Christian J Howard on 8/8/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Quaternion.hpp"
#include "ConstantsSet.hpp"
#include "ConfigParser.hpp"



int main(int argc, const char * argv[]) {
    
    ConfigParser parser("/Users/christianjhoward/test.cfg");
    
    double value = parser.getValueFrom<double>("param5");
    std::string name = parser.getValueFrom<std::string>("name");
    printf("Value = %lf\n",value);
    printf("My name is %s\n",name.c_str());
    
    return 0;
}

