//
//  UnitTest.h
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

#ifndef UnitTest_h
#define UnitTest_h

#include <string>
#include "TestAutomator.hpp"

class UnitTest {
public:
    virtual std::string getName() const = 0;
    virtual bool runTest() = 0;
    virtual ~UnitTest(){}
};


#ifdef UNIT_TEST
    #define FRIEND_TEST(TestName) friend class TestName;
    #define TEST(Group,TestName) class TestName : public UnitTest { \
                            public:\
                            TestName(){ TestAutomator::automator.addTest(#Group,this); }\
                            std::string getName() const { return #TestName; }\
                            bool runTest();\
                            ~TestName(){}\
                            };\
                            TestName TestName ## _;\
                            bool TestName::runTest()
#else
    #define FRIEND_TEST(TestName)
    #define TEST(Group,TestName)
    #define TEST_F(TestName)
#endif






#endif /* UnitTest_h */
