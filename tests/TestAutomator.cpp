//
//  TestAutomator.cpp
//  TestAutomation
//
//  Created by Christian J Howard on 7/13/16.
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

#include <stdio.h>

#include "TestAutomator.hpp"
#include "UnitTest.hpp"

// define singleton test automator
TestAutomator TestAutomator::automator;

// define constructor
TestAutomator::TestAutomator(){
    totalTests = 0;
    totalSuccesses =0 ;
}

// define destructor
TestAutomator::~TestAutomator(){
    
}

// define method to run the tests
void TestAutomator::runTests(){
    
    // init iterators
    TestSets::iterator it = unit_tests.begin();
    TestSuccesses::iterator success_counter = successes.begin();
    
    // init overall-test statistic variables
    totalSuccesses = 0;
    totalTests = 0;
    
    printf("\n");
    
    // loop through each test group
    for(; it != unit_tests.end(); ++it, ++success_counter ){
        std::string group = it->first;
        success_counter->second = 0;
        
        printf("Test Group %s\n",group.c_str());
        printf("-----------------------------------------\n");
        
        // loop through each test in the current test group
        for(int i = 0; i < it->second.size(); i++ ){
            UnitTest * test = it->second[i];
            bool success = test->runTest();
            
            if( success ){
                printf("\033[1;32m[\xE2\x9C\x93]\033[0m - %s\n",test->getName().c_str());
                success_counter->second++;
                ++totalSuccesses;
            }else{
                printf("\033[1;31m[ ]\033[0m - %s\n",test->getName().c_str());
            }
            ++totalTests;
        }
        printf("\n");
    }
    
    // output statistics
    outputStatistics();
    
}

// define method to output statistics
void TestAutomator::outputStatistics(){
    
    // compute and show group success
    TestSuccesses::iterator it = successes.begin();
    
    // loop through each test group
    for(; it != successes.end(); ++it ){
        std::string group = it->first;
        int success_count = it->second;
        int fail_count = static_cast<int>(unit_tests[group].size()) - success_count;
        
        printf("Test Group %s| \033[1;32m%i\033[0m Successes, \033[1;31m%i\033[0m Failures\n",group.c_str(), success_count, fail_count);
        
    }
    
    
    // compute and share overall success
    printf("\n");
    double overallSuccess = 100.0*static_cast<double>(totalSuccesses)/static_cast<double>(totalTests);
    printf("%0.1lf%% of All Unit Tests Passed.\n",overallSuccess);
    printf("There was %i successes and %i failures, overall.\n\n",totalSuccesses, totalTests - totalSuccesses);
}

void TestAutomator::addTest( std::string group, UnitTest* test ){
    unit_tests[group].push_back(test);
    successes[group] = 0;
}


//std::vector<UnitTest*> unit_tests;

