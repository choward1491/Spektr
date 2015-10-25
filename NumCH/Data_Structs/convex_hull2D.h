//
//  convex_hull.h
//  DataStructures
//
//  Created by Christian J Howard on 4/11/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#ifndef DataStructures_convex_hull2d_h
#define DataStructures_convex_hull2d_h

#ifndef _heap_h_
#include "heap.h"
#endif

#include <math.h>
#include <iostream>
using namespace std;

template< typename T>
typedef struct CHNode{
    int index;
    CHNode* left;
    CHNode* right;
    
};



template< typename T >
class Convex_Hull2D{
public:
    Convex_Hull2D();
    Convex_Hull2D( T * x_arr, T * y_arr, int number_pts );
    void generateConvexHull();
    CHNode<T>* getData();
    void printConvexHull() const;
    
private:
    CHNode<T>* head;
    int num_pts;
    T * x_data;
    T * y_data;
    void getConvexHullHelper(CHNode<T> * ln, CHNode<T> * rn, MaxHeap<T,int> & heap );
    void recursivePrint( CHNode<T>* node) const;
};





template< typename T >
Convex_Hull2D<T>::Convex_Hull2D()
{
    head = 0;
    x_data = 0;
    y_data = 0;
    num_pts = 0;
}

template< typename T >
Convex_Hull2D<T>::Convex_Hull2D( T * x_arr, T * y_arr, int number_pts )
{
    head = 0;
    x_data = x_arr;
    y_data = y_arr;
    num_pts = number_pts;
}

template< typename T >
void Convex_Hull2D<T>::generateConvexHull()
{
    int max_ind = 0, min_ind = 0;
    T max_v = x_data[0], min_v = x_data[0];
    
    // find the indices for the min and max x values
    for (int i = 1; i < num_pts; i++) {
        if (x_data[i] > max_v) {
            max_v = x_data[i];
            max_ind = i;
        }
        
        if (x_data[i] < min_v) {
            min_v = x_data[i];
            min_ind = i;
        }
    }
    
    
    CHNode<T> * ln = new CHNode<T>();
    CHNode<T> * rn = new CHNode<T>();
    
    ln->right = rn;
    ln->left  = rn;
    ln->index = min_ind;
    
    rn->left  = ln;
    rn->right = ln;
    rn->index = max_ind;
    
    
    head = ln;
    
    
    T x1[] = {x_data[ln->index], y_data[ln->index]};
    T x2[] = {x_data[rn->index], y_data[rn->index]};
    
    T dx = x2[0] - x1[0];
    T dy = x2[1] - x1[1];
    
    
    T mag = sqrt( dx*dx + dy*dy );
    T n1[] = {-dy/mag, dx/mag};
    T d;
    
    
    MaxHeap<T, int> upper(3*num_pts/4);
    MaxHeap<T, int> lower(3*num_pts/4);
    
    
    for(int i = 0; i < num_pts; i++){
        if (i != min_ind && i != max_ind) {
            d = (x_data[i] - x1[0])*n1[0] + (y_data[i] - x1[1])*n1[1];
            
            if (d > 0) {
                upper.push(d, i);
            }else if(d < 0){
                lower.push(-d, i);
            }
        }
        
    }
    
    getConvexHullHelper(ln, rn , upper );
    getConvexHullHelper(rn, ln , lower );
    
}

template< typename T >
CHNode<T>* Convex_Hull2D<T>::getData()
{
    return head;
}

template< typename T >
void Convex_Hull2D<T>::getConvexHullHelper(CHNode<T> * ln, CHNode<T> * rn, MaxHeap<T,int> & heap )
{
    if ( heap.getHeapCount() > 0 ) {
        
        CHNode<T>* newnode = new CHNode<T>();
        
        // Find the new maximum
        newnode->index = heap.pop();
        
        // Connect the new maximum to neighbor nodes
        ln->right = newnode;
        newnode->left = ln;
        
        rn->left = newnode;
        newnode->right = rn;
        
        // Find max points above each new line
        
        // Find values used to find distances of points from lines
        T x1[] = {x_data[ln->index], y_data[ln->index]};
        T x2[] = {x_data[newnode->index], y_data[newnode->index]};
        T x3[] = {x_data[rn->index], y_data[rn->index]};
        
        T dx = x2[0] - x1[0];
        T dy = x2[1] - x1[1];
        
        T mag = sqrt( dx*dx + dy*dy );
        T n1[] = {-dy/mag, dx/mag};
        
        
        dx = x3[0] - x2[0];
        dy = x3[1] - x2[1];
        mag = sqrt( dx*dx + dy*dy );
        T n2[] = {-dy/mag, dx/mag};
        
        T d, pt[2];
        
        int ind = 0;
        MaxHeap<T, int> leftHeap;
        MaxHeap<T, int> rightHeap;
        
        // Loop through the contents and generate new heaps for
        // recursive processing
        for (int i = 0; i < heap.getHeapCount(); i++ ){
            ind = heap.pop();
            pt[0] = x_data[ind];
            pt[1] = y_data[ind];
            
            d = (pt[0] - x1[0])*n1[0] + (pt[1] - x1[1])*n1[1];
            
            if( d > 0 ){
                leftHeap.push(d, ind);
            }else{
                d = (pt[0] - x2[0])*n2[0] + (pt[1] - x2[1])*n2[1];
                if (d > 0) {
                    rightHeap.push(d, ind);
                }
            }// end if d > 0
        }// end for loop
        
        
        // Do recursive processing
        getConvexHullHelper(ln, newnode , leftHeap );
        getConvexHullHelper( newnode, rn , rightHeap );
    }
}


template< typename T>
void Convex_Hull2D<T>::printConvexHull() const
{
    if (head != 0) {
        cout << "( " << x_data[head->index] << ", " << y_data[head->index] << ") ";
        recursivePrint( head->left );
        cout << "\n";
    }
    
    
}


template< typename T>
void Convex_Hull2D<T>::recursivePrint( CHNode<T>* node ) const
{
    if (node != 0 && node != head){
        cout << "-> ( " << x_data[node->index] << ", " << y_data[node->index] << ") ";
        recursivePrint( node->left );
    }
    
}


#endif
