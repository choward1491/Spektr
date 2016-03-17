//
//  Parser.hpp
//  NumCH
//
//  Created by Christian J Howard on 8/9/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//
//  The MIT License (MIT)
//  Copyright © 2016 Christian Howard. All rights reserved.
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

#ifndef Parser_cpp
#define Parser_cpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <queue>




    /*!
     * Class to read inputs from a file and put them into
     * a hash table for look up
     *
     */
    class Parser {
    public:
        
        // Null constructor
        Parser(){}
        
        // Initialize config file parser from filename
        Parser( const char* filename );
        
        // get your value from the table
        template<typename T>
        T getValueFrom( const char* parameterName ) ;
        
        template<typename T>
        T getValueFrom( const std::string & parameterName ) ;
        
        
        
        
        // method to parse a file and dump it's contents into a hash table
        //
        // Note that comments are denoted by either # or // and are only one line
        // An example config file could be the following:
        //
        // # Here's some comment
        // test: 15
        // toDance: 1
        //
        // # Here's another comment
        // variable1: 104.3
        //
        // # Here's some vector
        // vec: [12.5, 1.5, 12:2:24]
        //
        void parse( const char* filename );
        
    private:
        
        enum StringType{ Number, Vector, Word };
        enum StringType getStringType( const std::string & str );
        std::vector<double> getVectorFromString( const std::string & vec ) const;
        std::vector<double> parseSubVector( const std::string & vec ) const;
        std::vector<double> increment( double start, double end, double incr ) const;
        bool isOnlyNumbers( const std::string & str);
        std::map<std::string, std::string> parameters;
        
        
    };
    


#endif /* ConfigParser_cpp */
