//
//  Graph.cpp
//  TechInterviewPractice
//
//  Created by Christian J Howard on 10/20/15.
//  Copyright © 2015 Christian Howard. All rights reserved.
//

#include "Graph.hpp"


#ifndef graph_cpp
#define graph_cpp

template<class T>
Graph<T>::Graph(){
    nodes = 0;
    numNodes = 0;
}

template<class T>
Graph<T>::Graph( int numNodes_ ){
    nodes = new Node[numNodes_];
    numNodes = numNodes_;
}

template<class T>
Graph<T>::~Graph(){
    clear();
}

template<class T>
void Graph<T>::addNeighbor( int nodeID, int neighborID ){
    nodes[nodeID].neighbors.push(neighborID);
}

template<class T>
void Graph<T>::removeNeighbor( int nodeID, int neighborID ){
    removeNeighbor( nodes[nodeID].neighbors, neighborID );
}

template<class T>
bool Graph<T>::pathBetweenNodes( int nodeID1, int nodeID2 ) const{
    typedef struct LinkedList<int>::Node LNode;
    
    bool pathExistBetweenNodes = false;
    
    // array to keep track of if a node has been visited
    bool* seenNode = new bool[numNodes];
    for (int i = 0; i < numNodes; i++) {
        seenNode[i] = false;
    }
    
    // stack to do DFS; initialize to hold nodeID1
    std::stack<int> nodeSet;
    nodeSet.push(nodeID1);
    
    
    // loop through graph until either nodeID2
    // or all paths coming from nodeID1 have been visited
    while ( !nodeSet.empty() ){
        int node = nodeSet.top();
        nodeSet.pop();
        
        if( node == nodeID2 ){
            pathExistBetweenNodes = true;
            break;
        }
        
        if( !seenNode[node] ){
            seenNode[node] = true;
            for (LNode* n = nodes[node].neighbors.head; n != 0; n = n->next ) {
                nodeSet.push(n->data);
            }
        }
    }
    
    
    
    // in the event no path between the nodes
    // has been found
    if( !pathExistBetweenNodes ){
        
        // initialize the stack to empty
        while (!nodeSet.empty()) {
            nodeSet.pop();
        }
        // set all graph nodes to not being seen
        for (int i = 0; i < numNodes; i++) {
            seenNode[i] = false;
        }
        // initialize stack with nodeID2
        nodeSet.push(nodeID2);
        
        // loop through graph until
        // path to nodeID1 is found or
        // all paths have been walked through
        while ( !nodeSet.empty() ){
            int node = nodeSet.top();
            nodeSet.pop();
            
            if( node == nodeID1 ){
                pathExistBetweenNodes = true;
                break;
            }
            
            if( !seenNode[node] ){
                seenNode[node] = true;
                for (LNode* n = nodes[node].neighbors.head; n != 0; n = n->next ) {
                    nodeSet.push(n->data);
                }
            }
        }
    }
    
    // delete bool array
    delete [] seenNode;
    
    
    // return result from algorithm
    return pathExistBetweenNodes;
}



template<class T>
void Graph<T>::clear(){
    if( nodes != 0 ){
        delete [] nodes;
        nodes = 0;
    }
    numNodes = 0;
}

template<class T>
void Graph<T>::copy( const Graph & graph ){
    numNodes = graph.size();
    nodes = new Node[numNodes];
    
    for (int i = 0; i < numNodes; i++) {
        nodes[i] = graph(i);
    }
}



template<class T>
Graph<T> & Graph<T>::operator=( const Graph<T> & graph ){
    if( this != &graph ){
        clear();
        copy(graph);
    }
    
    return *this;
}


template<class T>
void Graph<T>::removeNeighbor( LinkedList<T> & list, int neighborID ){
    struct LinkedList<T>::Node * n = list.head;
    struct LinkedList<T>::Node * next = 0;
    struct LinkedList<T>::Node ** prev = &list.head;
    
    while ( n != 0 ){
        if( n->data == neighborID ){
            next = n->next;
            delete n; n = 0;
            (*prev) = next;
            break;
        }else{
            prev = &n->next;
            n = n->next;
        }
    }
    
}


template<class T>
void Graph<T>::print() const{
    if( nodes != 0 ){
        struct LinkedList<T>::Node * n = 0;
        for (int i = 0; i < numNodes; i++) {
            
            printf("%i: ", i);
            n = nodes[i].neighbors.head;
            int cnt = 0;
            while ( n != 0 ) {
                if( cnt == 0 ){
                    printf("%i", n->data ); cnt++;
                }else{
                    printf(", %i", n->data);
                }
                n = n->next;
            }
            printf("\n");
        }// end for i
    }// end nodes != 0
}




#endif