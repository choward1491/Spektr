//
//  Graph.hpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 10/20/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include "LinkedList.hpp"
#include <stack>
#include <queue>


template<class T>
class Graph {
public:
    
    struct Node{
        T data;
        LinkedList<int> neighbors;
    };
    
    
    Graph();
    Graph( int numNodes );
    ~Graph();
    
    void addNeighbor( int nodeID, int neighborID );
    void removeNeighbor( int nodeID, int neighborID );
    bool pathBetweenNodes( int nodeID1, int nodeID2 ) const;
    int size() const { return numNodes; }
    
    
    LinkedList<T> operator()(int nodeID ) const { return nodes[nodeID]; }
    Graph & operator=( const Graph & graph );
    
    void print() const;
    
private:
    void clear();
    void copy( const Graph & graph );
    void removeNeighbor( LinkedList<T> & list, int neighborID );
    Node* nodes;
    int numNodes;
    
};



#ifndef graph_cpp
#include "Graph.cpp"
#endif


#endif /* Graph_hpp */
