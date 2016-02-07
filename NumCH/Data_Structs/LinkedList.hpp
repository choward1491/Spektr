//
//  LinkedList.hpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 10/18/15.
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

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>


template<class T>
class Graph;


template<typename T>
class LinkedList {
public:
    
    struct Node{
        T data;
        Node* next;
    };
    
    struct Iter {
        Node* n;
        void operator++(){
            if( n != 0 ){
                n = n->next;
            }
        }
        void operator++(int){
            if( n != 0 ){
                n = n->next;
            }
        }
        
        bool atEnd(){
            return n == 0;
        }
    };
    
    Iter begin(){
        Iter it;
        it.n = head;
        return it;
    }
    
    
    LinkedList():head(0),size_(0){}
    ~LinkedList(){ clear(); }
    
    void push( const T & data );
    T pop();
    int size() const { return size_; }
    
    
    LinkedList<T> & operator=(LinkedList<T> & list );
    
protected:
    
    friend class LinkedList<T>;
    template<class U> friend class Graph;
    
    Node* head;
    int size_;
    
private:
    
    void clear();
    
    
};



template<typename T>
void LinkedList<T>::push(const T & data){
    Node* n = new Node;
    n->data = data;
    n->next = head;
    head = n;
    size_++;
}

template<typename T>
T LinkedList<T>::pop(){
    if( head != 0 ){
        Node* remove = head;
        Node* next = remove->next;
        T output = remove->data;
        delete remove; remove = 0;
        head = next;
        size_--;
        return output;
    }
    
    return T();
}



template<typename T>
void LinkedList<T>::clear(){
    Node* n = 0;
    Node* next = head;
    
    while (next != 0) {
        n = next;
        next = n->next;
        delete n; n = 0;
    }
    
    head = 0;
    size_ = 0;
}



#endif /* LinkedList_hpp */
