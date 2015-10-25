//
//  LinkedList.hpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 10/18/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
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
