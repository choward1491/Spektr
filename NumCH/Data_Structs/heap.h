#ifndef _heap_h_
#define _heap_h_

#include <vector>
#include <iostream>
using namespace std;


template<class K, class D>
class MinHeap {

public:
	MinHeap();
	MinHeap(int N);
	MinHeap(K keys[], D data[], int N = 20);
	MinHeap(vector<K> keys, vector<D> data);
	~MinHeap();

	D operator[](int index){ if( heap != 0 ){ return heap[index].data; } return D(); }

	K getRootKey();
	D getRootData();
	void push(K key, D data);
	D pop();
	void printKeys();
	int getHeapCount(){ return heap_count; }
    int size(){ return heap_count; }
	int getArrayLength(){ return length_arr; }


private:

	typedef struct Node{
		K key;
		D data;
	}Node;

	Node* heap;
	int length_arr;
	int heap_count;

	void resize();
	void pushHelper(int index);
	void generateHeap();
	void swapDown( int index );

};



template<class K, class D>
K MinHeap<K,D>::getRootKey()
{
	if( heap != 0 ){
		return heap[0].key;
	}
	return K();
}

template<class K, class D>
D MinHeap<K,D>::getRootData()
{
	if( heap != 0 ){
		return heap[0].data;
	}
	return D();
}



template<class K, class D>
MinHeap<K,D>::MinHeap(){
	length_arr = 20;
	heap_count = 0;
	heap = new Node[length_arr];
}

template<class K, class D>
MinHeap<K,D>::MinHeap(int N ){
	length_arr = N;
	heap_count = 0;
	heap = new Node[length_arr];
}

template<class K, class D>
void MinHeap<K,D>::swapDown( int index )
{
	int ir = 2*(index + 1);
	int il = 2*index + 1;
	int ib = 0;

	if( ir >= heap_count && il >= heap_count ){
		return;
	}else if( ir >= heap_count ){
		ib = il;
	}else{
		if( heap[il].key < heap[ir].key ){
			ib = il;
		}else{    ib = ir;    }
	}

	if( heap[ib].key < heap[index].key ){
		Node tmp = heap[ib];
		heap[ib] = heap[index];
		heap[index] = tmp;

		swapDown(ib);
	}

}


template<class K, class D>
void MinHeap<K,D>::generateHeap()
{
	int ic = heap_count/2-1;
	Node tmp;

	for( ; ic >= 0; ic-- ){
		swapDown(ic);
	}

}


template<class K, class D>
void MinHeap<K,D>::printKeys(){

	for( int i = 0; i < heap_count; i++ ){
		cout << "( " << heap[i].key <<" )";
	}

	cout << "\n";

}

template<class K, class D>
MinHeap<K,D>::MinHeap(K keys[], D data[], int N ){
	int n = N + 4;
	heap = new Node[n];
	length_arr = n;
	heap_count = N;

	for( int i = 0; i < N; i++ ){
		heap[i].key  = keys[i];
		heap[i].data = data[i];
	}

	generateHeap();
}

template<class K, class D>
MinHeap<K,D>::MinHeap(vector<K> keys, vector<D> data){
	int N = keys.size();

	heap = new Node[N];
	length_arr = N;
	heap_count = N;

	typename vector<K>::iterator ik = keys.begin();
	typename vector<D>::iterator id = data.begin();

	for( int i = 0 ; ik != keys.end() ; ik++, id++, i++ ){
		heap[i].key  = (*ik);
		heap[i].data = (*id);
	}

	generateHeap();
}


template<class K, class D>
MinHeap<K,D>::~MinHeap(){
	if( heap != 0 ){
		delete [] heap;
		heap = 0;
	}

	length_arr = 0;
	heap_count = 0;
}

template<class K, class D>
void MinHeap<K,D>::push(K key, D data){
	if( length_arr == heap_count ){
		resize();
	}

	Node n = {key, data};
	heap[heap_count] = n;
	heap_count++;

	pushHelper(heap_count-1);
}

template<class K, class D>
D MinHeap<K,D>::pop()
{
	if( heap_count != 0 ){
		D data = heap[0].data;
		heap_count--;
		heap[0] = heap[heap_count];
		swapDown(0);

		return data;
	} else {
		return D();
	}
}

template<class K, class D>
void MinHeap<K,D>::resize(){
	Node* new_heap = new Node[length_arr*2];

	for( int i = 0; i < length_arr; i++ ){
		new_heap[i] = heap[i];
	}

	length_arr *= 2;

	delete [] heap;
	heap = new_heap; 
	new_heap = 0;
}

template<class K, class D>
void MinHeap<K,D>::pushHelper(int index)
{
	if( index != 0 ){
		int parent;
		if( index % 2 == 0 ){
			parent = (index - 2)/2;
		}else{
			parent = (index - 1)/2;
		}

		if( heap[parent].key > heap[index].key ){
			Node tmp = heap[parent];
			heap[parent] = heap[index];
			heap[index] = tmp;

			pushHelper(parent);
		}
	}
}
































template<class K, class D>
class MaxHeap {

public:
	MaxHeap();
	MaxHeap(int N);
	MaxHeap(K keys[], D data[], int N = 20);
	MaxHeap(vector<K> keys, vector<D> data);
	~MaxHeap();

	D operator[](int index){ if( heap != 0 ){ return heap[index].data; } return D(); }

	void push(K key, D data);
	K getRootKey();
	D getRootData();
	D pop();
	void printKeys();
	int getHeapCount(){ return heap_count; }
    int size(){ return heap_count; }
	int getArrayLength(){ return length_arr; }

private:

	typedef struct Node{
		K key;
		D data;
	} Node;

	Node* heap;
	int length_arr;
	int heap_count;

	void resize();
	void pushHelper(int index);
	void generateHeap();
	void swapDown( int index );

};



template<class K, class D>
K MaxHeap<K,D>::getRootKey()
{
	if( heap != 0 ){
		return heap[0].key;
	}
	return K();
}

template<class K, class D>
D MaxHeap<K,D>::getRootData()
{
	if( heap != 0 ){
		return heap[0].data;
	}
	return D();
}



template<class K, class D>
MaxHeap<K,D>::MaxHeap(){
	length_arr = 20;
	heap_count = 0;
	heap = new Node[length_arr];
}

template<class K, class D>
MaxHeap<K,D>::MaxHeap(int N ){
	length_arr = N;
	heap_count = 0;
	heap = new Node[length_arr];
}

template<class K, class D>
void MaxHeap<K,D>::swapDown( int index )
{
	int ir = 2*(index + 1);
	int il = 2*index + 1;
	int ib = 0;

	if( ir >= heap_count && il >= heap_count ){
		return;
	}else if( ir >= heap_count ){
		ib = il;
	}else{
		if( heap[il].key > heap[ir].key ){
			ib = il;
		}else{    ib = ir;    }
	}

	if( heap[ib].key > heap[index].key ){
		Node tmp = heap[ib];
		heap[ib] = heap[index];
		heap[index] = tmp;

		swapDown(ib);
	}

}


template<class K, class D>
void MaxHeap<K,D>::generateHeap()
{
	int ic = heap_count/2-1;
	Node tmp;

	for( ; ic >= 0; ic-- ){
		swapDown(ic);
	}

}


template<class K, class D>
void MaxHeap<K,D>::printKeys(){

	for( int i = 0; i < heap_count; i++ ){
		cout << "( " << heap[i].key <<" )";
	}

	cout << "\n";

}

template<class K, class D>
MaxHeap<K,D>::MaxHeap(K keys[], D data[], int N ){
	int n = N + 4;
	heap = new Node[n];
	length_arr = n;
	heap_count = N;

	for( int i = 0; i < N; i++ ){
		heap[i].key  = keys[i];
		heap[i].data = data[i];
	}

	generateHeap();
}

template<class K, class D>
MaxHeap<K,D>::MaxHeap(vector<K> keys, vector<D> data){
	int N = keys.size();

	heap = new Node[N+10];
	length_arr = N+10;
	heap_count = N;

	typename vector<K>::iterator ik = keys.begin();
	typename vector<D>::iterator id = data.begin();

	for( int i = 0 ; ik != keys.end() ; ik++, id++, i++ ){
		heap[i].key  = (*ik);
		heap[i].data = (*id);
	}

	generateHeap();
}


template<class K, class D>
MaxHeap<K,D>::~MaxHeap(){
	if( heap != 0 ){
		delete [] heap;
		heap = 0;
	}

	length_arr = 0;
	heap_count = 0;
}

template<class K, class D>
void MaxHeap<K,D>::push(K key, D data){
	if( length_arr == heap_count ){
		resize();
	}

	Node n = {key, data};
	heap[heap_count] = n;
	heap_count++;

	pushHelper(heap_count-1);
}

template<class K, class D>
D MaxHeap<K,D>::pop()
{
	if( heap_count != 0 ){
		D data = heap[0].data;
		heap_count--;
		heap[0] = heap[heap_count];
		swapDown(0);

		return data;
	} else {
		return D();
	}
}

template<class K, class D>
void MaxHeap<K,D>::resize(){
	Node* new_heap = new Node[length_arr*2];

	for( int i = 0; i < length_arr; i++ ){
		new_heap[i] = heap[i];
	}

	length_arr *= 2;

	delete [] heap;
	heap = new_heap; 
	new_heap = 0;
}

template<class K, class D>
void MaxHeap<K,D>::pushHelper(int index)
{
	if( index != 0 ){
		int parent;
		if( index % 2 == 0 ){
			parent = (index - 2)/2;
		}else{
			parent = (index - 1)/2;
		}

		if( heap[parent].key < heap[index].key ){
			Node tmp = heap[parent];
			heap[parent] = heap[index];
			heap[index] = tmp;

			pushHelper(parent);
		}
	}
}




#endif