


#ifndef _kdtree_h_
#define _kdtree_h_

#ifndef _heap_h_
#include "heap.h"
#endif

#include "function.h"



template< class S, class D>
typedef struct KDNode{
		S point;
		D data;
};


template<int K, class I, class O>
class KDFunction {
public:
	virtual O operator()(I & input1, I & input2 ) = 0;
	virtual O operator()(I & input1, I & input2, int dim ) = 0;
private:
};


template< int K, class S, class T>
class L2_Norm : public KDFunction< K, S, T > {

public:
	virtual T operator()( S & point1, S & point2 ){
		T output;
		T tmp;

		for( int i = 0; i < K; i++ ){
			tmp = point1[i] - point2[i];
            if( i == 0 ){
                output = tmp*tmp;
            }else{
                output += tmp*tmp;
            }
		}

		return output;
	}

	virtual T operator()( S & point1, S & point2 , int dim){
		T tmp;

		tmp = point1[dim] - point2[dim];

		return tmp*tmp;
	}

};



template< int K, class T, class S, class D >
class KDTree {

public:

	KDTree();
	KDTree( S pts[], D data[] , int num_pts );
	~KDTree();
	void findNearestNeighbors( S & pt, int numberOfneighbors , MinHeap<T, KDNode<S,D> > & soln );
	void assignDistanceMeasurement( KDFunction<K, S, T>* dm );
	void setData( S pts[], D data[] , int num_pts );

private:

	KDNode<S,D>* tree;
	int npts;

	KDFunction<K, S, T>* dist_measurement;


	void splitDataByMedian( int ns, int ne , int dim);
	void setup_kdtree();
	void findNN( int li, int ri, S & pt, int dim, MaxHeap<T, KDNode<S,D> >  &neighbors );

};







template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: KDTree(){
	assignDistanceMeasurement( new L2_Norm<K, S, T>() );
	tree = 0;
}

template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: setData( S pts[], D data[] , int num_pts ){
	tree = new KDNode<S, D>[ num_pts ];
	npts = num_pts;

	for( int i = 0; i < num_pts; i++ ){
		tree[i].point = pts[i];
		tree[i].data  = data[i];
	}
}

template< int K, class T, class S, class D >
KDTree<K, T, S, D> :: KDTree( S pts[], D data[] , int num_pts ){
	setData( pts, data, num_pts );
    L2_Norm<K, S, T>* func = new L2_Norm<K, S, T>();
	assignDistanceMeasurement( func );
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
    
	if( li == ri ){
        
        if( neighbors.getHeapCount() >= neighbors.getArrayLength() ){
            neighbors.pop();
        }
		neighbors.push( (*dist_measurement)(pt, tree[li].point), tree[li] );

	}else{

        int N  = ri - li + 1;
		int ic = (ri + li)/2;
		bool flag = false;

		//cout << ic <<" ( "<< li <<", "<< ri <<", "<< (ic - 1) + (N==2) <<")\n";
		if( pt[dim] < tree[ic].point[dim] ){
			findNN( li, (ic - 1) + (N==2), pt, (dim+1) % K, neighbors );
			flag = false;
		}else{
			findNN( ic+1, ri, pt, (dim+1) % K, neighbors );
			flag = true;
		}


		
		T dist2c = (*dist_measurement)(pt, tree[ic].point);
		if( dist2c < neighbors.getRootKey() ){
			if( neighbors.getHeapCount() >= neighbors.getArrayLength() ){
				neighbors.pop();
			}
			neighbors.push( dist2c, tree[ic] );
		}


		
		T dist2hp = (*dist_measurement)(tree[ic].point, pt, dim);
		if( dist2hp < neighbors.getRootKey() ){
			if( flag ){
				findNN( li, ic-1 + (N==2), pt, (dim+1) % K, neighbors );
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
    
    for(int i = 0; i < neighbors.getHeapCount(); i++ ){
        solution.push( neighbors.getRootKey(), neighbors.pop());
    }
}



template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: assignDistanceMeasurement( KDFunction<K, S, T> * dm ){
	dist_measurement = dm;
}



template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: splitDataByMedian( int ns, int ne , int dim ){
	int N = ne-ns + 1;
	
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


				// Check if we need to swap data from one keep to the other
				if( botHalf.getHeapCount() > topHalf.getHeapCount() + 1 ){
					topHalf.push( botHalf.getRootKey(), botHalf.getRootData() );
					botHalf.pop();

				}else if( topHalf.getHeapCount() + 1 > botHalf.getHeapCount() ){
					botHalf.push( botHalf.getRootKey(), botHalf.getRootData() );
					topHalf.pop();

				}
			}
		}// end for loop

		int index;
		int cnt = ns;
		KDNode<S, D> tmp;
		for( int i = (botHalf.getHeapCount()-1) ; i >= 0; i--, cnt++ ){
			index = botHalf[i];
			tmp = tree[cnt];
			tree[cnt] = tree[index];
			tree[index] = tmp;
		}


		for( int i = 0 ; i < topHalf.getHeapCount(); i++, cnt++ ){
			index = botHalf[i];
			tmp = tree[cnt];
			tree[cnt] = tree[index];
			tree[index] = tmp;
		}

		int median = (ne+ns)/2;

		// Look at left half
		splitDataByMedian( ns, median- 1 + (N==2)   , (dim+1) % K );

		// look at right half
		splitDataByMedian( median + 1, ne , (dim+1) % K );
	}

}

template< int K, class T, class S, class D >
void KDTree<K, T, S, D> :: setup_kdtree(){
	splitDataByMedian( 0, npts-1 , 0 );
}





#endif