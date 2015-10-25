//
//  kdtree.cpp
//  Data_Structs
//
//  Created by Christian J Howard on 9/4/15.
//  Copyright (c) 2015 Christian Howard. All rights reserved.
//

#include "kd_tree.h"


#ifndef _kdtree_cpp_
#define _kdtree_cpp_


template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: KDTree(){
    assignDistanceMeasurement( new L2_Norm<K, S, T>() );
    tree = 0;
}

template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: setData( const S* pts, const D* data , int num_pts ){
    tree = new KDNode<S, D>[ num_pts ];
    npts = num_pts;
    
    for( int i = 0; i < num_pts; i++ ){
        tree[i].point = pts[i];
        tree[i].data  = data[i];
    }
}

template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: KDTree( const S *pts, const D *data , int num_pts ){
    setData( pts, data, num_pts );
    assignDistanceMeasurement( new L2_Norm<K, S, T>() );
    setup_kdtree();
}

template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: setVectorData( const vector<S> & pts, const vector<D> & data ){
    tree = new KDNode<S, D>[ pts.size() ];
    npts = pts.size();
    typename vector<S>::const_iterator p = pts.begin();
    typename vector<D>::const_iterator d = data.begin();
    
    for( int i = 0; p != pts.end(); p++, d++, i++ ){
        tree[i].point = *p;
        tree[i].data  = *d;
    }
}

template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: KDTree( const vector<S> & pts, const vector<D> & data){
    setVectorData( pts, data );
    assignDistanceMeasurement( new L2_Norm<K, S, T>() );
    setup_kdtree();
}

template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: ~KDTree(){
    if( tree != 0 ){
        delete [] tree;
        tree = 0;
    }
    
    if( dist_measurement != 0 ){
        delete dist_measurement;
        dist_measurement = 0;
    }
}





template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: findNN( int li, int ri, S & pt, int dim, MaxHeap<T, KDNode<S,D> >  & neighbors ){
    if( li > ri ){
        
    }else if( li == ri ){
        T dist2hp = (*dist_measurement)(tree[li].point, pt);
        if( neighbors.getHeapCount() < neighbors.getArrayLength() || dist2hp < neighbors.getRootKey()){
            if( neighbors.getHeapCount() >= neighbors.getArrayLength() ){
                neighbors.pop();
            }
            neighbors.push( dist2hp, tree[li] );
        }
        
        
    }else{
        

        int ic = (ri + li)/2;
        bool flag = false;
        
        //cout << ic <<" ( "<< li <<", "<< ri <<", "<< (ic - 1) + (N==2) <<")\n";
        if( pt[dim] < tree[ic].point[dim] ){
            findNN( li, (ic - 1) , pt, (dim+1) % K, neighbors );
            flag = false;
        }else{
            findNN( ic+1, ri, pt, (dim+1) % K, neighbors );
            flag = true;
        }
        
        
        
        T dist2c = (*dist_measurement)(pt, tree[ic].point);
        if( dist2c < neighbors.getRootKey() || neighbors.getHeapCount() < neighbors.getArrayLength() ){
            if( neighbors.getHeapCount() >= neighbors.getArrayLength() ){
                neighbors.pop();
            }
            neighbors.push( dist2c, tree[ic] );
        }
        
        
        
        
        T dist2hp = (*dist_measurement)(tree[ic].point, pt, dim);
        if( dist2hp < neighbors.getRootKey() || neighbors.getHeapCount() < neighbors.getArrayLength() ){
            
            if( flag ){
                findNN( li, ic-1 , pt, (dim+1) % K, neighbors );
            }else{
                findNN( ic+1, ri, pt, (dim+1) % K, neighbors );
            }
        }
        
    }
    
}


template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: findNearestNeighbors( S & pt, int numberOfneighbors , MinHeap< T, KDNode<S, D> > & solution ){
    MaxHeap<T, KDNode<S,D> >  neighbors( numberOfneighbors );
    findNN( 0, npts-1, pt, 0, neighbors );
    
    int N = neighbors.getHeapCount();
    for(int i = 0; i < N; i++ ){
        solution.push( neighbors.getRootKey(), neighbors.getRootData());
        neighbors.pop();
    }
}


template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: findWithin( int li, int ri, S & pt, int dim, T neighborhoodThresh, MaxHeap<T, KDNode<S,D> >  & neighbors ){
    if( li > ri ){
        
    }else if( li == ri ){
        T dist2hp = (*dist_measurement)(tree[li].point, pt);
        if( dist2hp <= neighborhoodThresh ){
            neighbors.push( dist2hp, tree[li] );
        }
        
        
    }else{
        

        int ic = (ri + li)/2;
        bool flag = false;
        
        if( pt[dim] < tree[ic].point[dim] ){
            findWithin( li, (ic - 1) , pt, (dim+1) % K, neighborhoodThresh, neighbors );
            flag = false;
        }else{
            findWithin( ic+1, ri, pt, (dim+1) % K, neighborhoodThresh, neighbors );
            flag = true;
        }
        
        

        T dist2c = (*dist_measurement)(pt, tree[ic].point);
        if( dist2c <= neighborhoodThresh ){
            neighbors.push( dist2c, tree[ic] );
        }
        
        
        
        
        T dist2hp = (*dist_measurement)(tree[ic].point, pt, dim);
        if( dist2hp <= neighborhoodThresh ){
            
            if( flag ){
                findWithin( li, ic-1 , pt, (dim+1) % K, neighborhoodThresh, neighbors );
            }else{
                findWithin( ic+1, ri, pt, (dim+1) % K, neighborhoodThresh, neighbors );
            }
        }
        
    }
    
    
}


template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: findNeighborsWithinRegion( S & pt,
                                                     T neighborhoodSize,
                                                     MinHeap<T, KDNode<S,D> > & solution )
{
    MaxHeap<T, KDNode<S,D> >  neighbors( 10 );
    findWithin( 0, npts-1, pt, 0, neighborhoodSize, neighbors );
    
    int N = neighbors.getHeapCount();
    for(int i = 0; i < N; i++ ){
        solution.push( neighbors.getRootKey(), neighbors.getRootData());
        neighbors.pop();
    }
}


template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: assignDistanceMeasurement( KDFunction<K, S, T> * dm ){
    dist_measurement = dm;
}



template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: splitDataByMedian( int ns, int ne , int dim ){
    int N = ne-ns + 1;
    
    KDNode<S, D>* tmpNodes = new KDNode<S,D>[N];
    
    if( N > 1 ){
        MinHeap<T, int> topHalf(N/2 + 3);
        MaxHeap<T, int> botHalf(N/2 + 3);
        
        for( int i = ns; i <= ne; i++ ){
            
            if( i == ns ){
                botHalf.push( tree[i].point[dim], i );
            }else{
                
                // see which heep the next thing of data should be in
                if( botHalf.getRootKey() < tree[i].point[dim] ){
                    topHalf.push( tree[i].point[dim], i );
                } else {
                    botHalf.push( tree[i].point[dim], i );
                }
                
                
                // Check if we need to swap data from one heap to the other
                if( botHalf.getHeapCount() > topHalf.getHeapCount() + 1 ){
                    T s = botHalf.getRootKey();
                    int d = botHalf.getRootData();
                    topHalf.push( s, d );
                    botHalf.pop();
                    
                }else if( topHalf.getHeapCount() > botHalf.getHeapCount() ){
                    T s = topHalf.getRootKey();
                    int d = topHalf.getRootData();
                    botHalf.push( s, d );
                    topHalf.pop();
                    
                }
            }
        }// end for loop
        
        
        int index;
        int cnt = 0;
        KDNode<S, D> tmp;
        for( int i = (botHalf.getHeapCount()-1) ; i >= 0; i--, cnt++ ){
            index = botHalf[i];
            tmpNodes[cnt]= tree[index];
        }
        
        
        for( int i = 0 ; i < topHalf.getHeapCount(); i++, cnt++ ){
            index = topHalf[i];
            tmpNodes[cnt] = tree[index];
        }
        
        for( int i = ns, cnt = 0; i <= ne; i++,cnt++ ){
            tree[i] = tmpNodes[cnt];
        }
        
        delete [] tmpNodes;
        
        int median = (ne+ns)/2;
        
        // Look at left half
        splitDataByMedian( ns, median - 1 + (N==2)   , (dim+1) % K );
        
        // look at right half
        splitDataByMedian( median + 1, ne , (dim+1) % K );
    }
    
    
    
}

template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: setup_kdtree(){
    splitDataByMedian( 0, npts-1 , 0 );
}


#endif
