//
//  TestAutomator.hpp
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
//

#ifndef TestAutomator_h
#define TestAutomator_h


#include <vector>
#include <map>
#include <string>


class UnitTest;

class TestAutomator {
public:
    static TestAutomator automator;
    typedef std::map<std::string,std::vector<UnitTest*> > TestSets;
    typedef std::map<std::string,int> TestSuccesses;
    
    TestAutomator();
    ~TestAutomator();
    void runTests();
    void addTest( std::string group, UnitTest* test );
    
private:
    void outputStatistics();
    TestSets unit_tests;
    TestSuccesses successes;
    int totalSuccesses;
    int totalTests;
    
};



#endif /* TestAutomator_h */
