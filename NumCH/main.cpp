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
    
    double value = parser.getValueFrom<double>("param1");
    std::vector<double> vec = parser.getValueFrom<std::vector<double> >( std::string("vec") );
    std::vector<double>::iterator it = vec.begin();
    int counter = 0;
    
    printf("[ ");
    for (; it != vec.end(); it++) {
        if( counter == 0 ){
            printf("%lf", *it);
            counter++;
        }else{
            printf(", %lf", *it);
        }
    } printf(" ]\n");
    
    return 0;
}

