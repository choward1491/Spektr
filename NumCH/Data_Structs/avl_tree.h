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

#ifndef _avl_tree_h_
#define _avl_tree_h_

#include <vector>
#include <iostream>
using namespace std;


/*===================================
=====================================

		This is a node for the
			AVL Tree Class
		
=====================================
=====================================*/
template<class K, class D>
class AVL_Node {
public:
	K key;
	D data;
	int height;

	AVL_Node<K,D>* left;
	AVL_Node<K,D>* right;

	AVL_Node(K k, D d );
	~AVL_Node();
	void clear();

private:

	void clearHelper( AVL_Node<K,D>* &node );
};










/*===================================
=====================================

		This the AVL Tree Class
		
=====================================
=====================================*/
// <Author> Christian Howard
//
// <Date>   4 / 9 / 2015
//
// <Purpose>
// This data structure is essentially an adaptive binary tree.
// The adaptation is such that the height of the tree will be
// minimized, so searches, removals, etc will remain O(log(N))
// in their computational complexity, where N is the number of
// items in the tree. 
//
// <Possible Uses>
// This tree can be used for any search needs that a typical
// binary tree might be used for. 
//
// Other uses might me sorting data. It generally takes O(N*log(N))
// to push N items into the tree, and then takes O(N) to get
// the sorted list. The net order for sorting data will generally
// be O(N*log(N)) for large N, instead of a normal O(N^2) using
// some for loops for sorting
//
// <Recommended Uses>
// I recommend using this data structure for data that will
// be searched, added to, and removed from. This could be seen
// as a more efficient version of using a linked list and more
// flexible than using an array.

template<class K, class D>
class AVL_Tree {
public:


	/*===========================================
	           Constructors/Destructor
	=============================================*/

	// This is a null constructor
	AVL_Tree():head(0){ num_nodes = 0; }


	// Constructor using array of keys and data,
	// where the known size of these arrays are 
	// num
	AVL_Tree(K keys[], D data[], int num);


	// Constructor using vectors of keys and data
	AVL_Tree(vector<K> keys, vector<D> data);

	// Standard Destructor
	~AVL_Tree();


    
    /*===========================================
     Operator Stuff
     =============================================*/
    AVL_Tree<K,D>& operator=(AVL_Tree<K,D> & tree);
    


	/*===========================================
	       Manipulating and Searching Methods
	=============================================*/

	// Method to push a new key-data pair into the tree
	void push(K key, D data);

	// Method to find the data associated with a key
	D find(K key, bool &found);

	// Method to remove a tree node associated with a key
	D remove( K key , bool &found);


    AVL_Node<K,D>* getRoot(){ return head; }




	/*===========================================
	          Printing Methods
	=============================================*/
	// Method to print data of the tree 
	// from smallest key to largest
	void printIncreasing();






	/*===========================================
	           Getting Methods
	=============================================*/
	// Method to get a vector of the data sorted
	// from smallest key to largest key
	void getItems( vector<D> & ovector );

	// Method to get node associated with max key
	AVL_Node<K,D> getMaxItem();

	// Method to get node associated with min key
	AVL_Node<K,D> getMinItem();

	// Method to get node associated with median key
	AVL_Node<K,D> getMedianItem();
    
    int getNumberNodes(){ return num_nodes; }


private:

	/*===========================================
	           Hidden Data
	=============================================*/
	// Pointer to node that's the head of the tree
	AVL_Node<K,D>* head;

	// Counter for the number of nodes in the tree. This
	// is needed to find the median node in the tree
	int num_nodes;




	/*===========================================
	           Recursive Helpers
	=============================================*/

	// Recursive helper function for pushing new data into the tree
	void pushHelper( AVL_Node<K,D>* &node, K key, D data );

	// Recursive helper function for finding data in tree 
	void findHelper( AVL_Node<K,D>* &node, K key, D* &ptr2obj );

	// Recursive helper function to remove data from tree
	void removeHelper( AVL_Node<K,D>* &node, K key, D &data , bool & found );

	// Helper function that finds replacement nodes for a node beinh removed
	void getReplacementNode( AVL_Node<K,D>* &node, AVL_Node<K,D>* &replacement );

	// Recursive helper function so that the tree's 
	// contents can be printed to the screen
	void printIncreasingHelper(  AVL_Node<K,D>* &node );
    
    void copy( AVL_Node<K,D>* & node, const AVL_Node<K,D>* onode );

    void getItemsHelper(AVL_Node<K,D> * & node, vector<D> & odata);



	/*===========================================
	           Balancing Methods
	=============================================*/
	// Function that finds the factor that shows how unbalanced a subtree is
	int  balanceFactor( AVL_Node<K,D>* &node );

	// Function for balancing a tree who's head node is 'node'
	void balance( AVL_Node<K,D>* &node );

	// Function to update the height of nodes in a tree
	void updateHeight( AVL_Node<K,D>* &node );





	/*===========================================
	           Tree Rotation Methods
	=============================================*/
	// Functions for rotating subtrees in the AVL Tree
	// to help ensure proper balance and search
	// complexity
	void rotateLeft( AVL_Node<K,D>* &node );
	void rotateRight( AVL_Node<K,D>* &node );
	void rotateLeftRight( AVL_Node<K,D>* &node );
	void rotateRightLeft( AVL_Node<K,D>* &node );


};




/*====================================================
|
|
|
|
|
|          Generate code for the AVL Tree Node
|
|
|
|
|
======================================================*/


/*====================================================
Constructor for AVL Node
======================================================*/
template<class K, class D>
AVL_Node<K,D>::AVL_Node(K k, D d ){
	key = k;
	data = d;
	height = 0;
	left = 0;
	right = 0;
}


/*====================================================
Recursive Memory clearing helper function
======================================================*/
template<class K, class D>
void AVL_Node<K,D>::clearHelper( AVL_Node<K,D>* &node ){
	if( node == 0 ){

	}else if (node->left == 0 && node-> right == 0) {
		delete node;
		node = 0;
	}else{
		if ( node->left != 0 ){
			clearHelper(node->left);
		}

		if (node->right != 0 ){
			clearHelper(node->right);
		}

		delete node;
		node = 0;
	}
}


/*====================================================
Clear method to free up memory associated with this node
======================================================*/
template<class K, class D>
void AVL_Node<K,D>::clear(){
	clearHelper( left );
	clearHelper( right );

	height = 0;
}


/*====================================================
Destructor declaration
======================================================*/
template<class K, class D>
AVL_Node<K,D>::~AVL_Node(){
	clear();
}


















/*====================================================
|
|
|
|
|
|          Generate code for the AVL Tree 
|
|
|
|
|
======================================================*/
template<class K, class D>
AVL_Tree<K, D>::AVL_Tree(K keys[], D data[], int num){
	head = 0;

	for( int i = 0; i < num; i++ ){
		pushHelper( head, keys[i], data[i] );
	}

	num_nodes = num;
}

template<class K, class D>
AVL_Tree<K, D>::AVL_Tree(vector<K> keys, vector<D> data){
	head = 0;

	if( keys.size() == data.size() ){
		typename vector<K>::iterator ik;
		typename vector<D>::iterator id;
		for( ik = keys.begin(), id = data.begin(); ik != keys.end(); ik++, id++ ){
			pushHelper( head, (*ik), (*id) );
		}
		num_nodes = keys.size();
	}

}


template<class K, class D>
AVL_Tree<K, D>::~AVL_Tree(){

	if( head != 0 ){
		head->clear();
		delete head; head = 0;
		num_nodes = 0;
	}
}


template<class K, class D>
void AVL_Tree<K, D>::pushHelper( AVL_Node<K,D>* &node, K key, D data ){
	if ( node == 0 ) {
		node = new AVL_Node<K,D>(key, data);
		num_nodes++;
	} else {
		if( key < node->key ){
			pushHelper(node->left, key, data);
		}else{
			pushHelper(node->right, key, data);
		}

		updateHeight(node);
		balance(node);
		
	}
}

template<class K, class D>
void AVL_Tree<K, D>::push(K key, D data){
	pushHelper(head, key, data);
}


template<class K, class D>
void AVL_Tree<K, D>::copy( AVL_Node<K,D>* & node, const AVL_Node<K,D>* onode ){
    if (onode == 0) {
        node = 0;
    }else{
        node = new AVL_Node<K, D>( onode->key, onode->data );
        copy( node->left  , onode->left );
        copy( node->right , onode->right );
    }
}





template<class K, class D>
AVL_Tree<K,D>& AVL_Tree<K, D>::operator=(AVL_Tree<K,D> & tree){
    if ( this != &tree ){
        if ( head != 0 ) {
            head->clear();
            delete head; head = 0;
            num_nodes = 0;
        }
        
        num_nodes = tree.getNumberNodes();
        copy( head, tree.getRoot() );
    }
    
    return *this;
}






template<class K, class D>
void AVL_Tree<K, D>::findHelper( AVL_Node<K,D>* &node, K key, D* &ptr2obj ){
	if ( node == 0 ) {
		ptr2obj = 0;
	}else{
		if ( key == node->key ){
			ptr2obj = &node->data;
		}else if( key < node->key ){
			findHelper( node->left, key, ptr2obj );
		}else{
			findHelper( node->right, key, ptr2obj );
		}
	}
}

template<class K, class D>
D AVL_Tree<K, D>::find(K key, bool &found){
	D* obj = 0;
	findHelper(head, key, obj);

	if ( obj == 0 ){
		found = false;
		return D();
	}else{
		found = true;
		return D(*obj);
	}
}


template<class K, class D>
void AVL_Tree<K, D>::getReplacementNode( AVL_Node<K,D>* &node, AVL_Node<K,D>* &replacement ){
	if( node == 0 ){
		replacement = 0;

	}else if (node->left == 0 && node->right == 0) {
		replacement = node;
		node = 0;

	}else{

		AVL_Node<K,D>* r = 0;
		getReplacementNode(node->right, r);

		if( r == 0 ){
			getReplacementNode( node->left, r);
		}
        
        if( r == 0 ){
			r->right = node->right;
			r->left = node->left;
			node->right = 0;
			node->left  = 0;
		}

		replacement = node;
		node = r;
		r = 0;
		updateHeight(node);
		balance(node);
		
		
	}
}

template<class K, class D>
void AVL_Tree<K, D>::removeHelper( AVL_Node<K,D>* &node, K key, D &out_data , bool &found ){
	if( node == 0 ){
		out_data = D();
		found = false;
	}else if( key == node->key ){
		AVL_Node<K,D>* r = 0;
		out_data = D(node->data);
		getReplacementNode(node, r);
		delete r; r = 0;
		num_nodes--;
		found = true;
	}else{
		if( key < node->key ){
			removeHelper(node->left, key, out_data, found);
		}else{
			removeHelper(node->right, key, out_data, found);
		}
	}
}


template<class K, class D>
D AVL_Tree<K, D>::remove( K key , bool &found ){
	D data;
	removeHelper(head, key, data, found);
	return data;
}










template<class K, class D>
void AVL_Tree<K, D>::getItems( vector<D> & ovector ){
    getItemsHelper(head, ovector);
}


template<class K, class D>
void AVL_Tree<K, D>::getItemsHelper(AVL_Node<K,D> * & node, vector<D> & odata){
    if (node != 0) {
        if (node->left == 0 && node->right == 0) {
            odata.push_back(node->data);
        }else{
            getItemsHelper(node->left, odata);
            odata.push_back(node->data);
            getItemsHelper(node->right, odata);
        }
    }
}


template<class K, class D>
AVL_Node<K,D> AVL_Tree<K, D>::getMaxItem(){

}


template<class K, class D>
AVL_Node<K,D> AVL_Tree<K, D>::getMinItem(){

}


template<class K, class D>
AVL_Node<K,D> AVL_Tree<K, D>::getMedianItem(){

}









template<class K, class D>
void AVL_Tree<K, D>::updateHeight( AVL_Node<K,D>* &node ){
	int h1 = 0, h2 = 0;

	if ( node->left != 0 ){
		h1 = node->left->height;
	}

	if ( node->right != 0 ){
		h2 = node->right->height;
	}

	node->height = max(h1, h2) + 1;
}

template<class K, class D>
int AVL_Tree<K, D>::balanceFactor( AVL_Node<K,D>* &node ){
	int h1 = -1, h2 = -1;

	if ( node->left != 0 ){
		h1 = node->left->height;
	}

	if ( node->right != 0 ){
		h2 = node->right->height;
	}

	return h2 - h1;
}

template<class K, class D>
void AVL_Tree<K, D>::rotateLeft( AVL_Node<K,D>* &node ){
	AVL_Node<K,D>* y = node->right;
	node->right = y->left;
	y->left = node;

	updateHeight(node);
	updateHeight(y);
	node = y;
	y = 0;
}

template<class K, class D>
void AVL_Tree<K, D>::rotateRight( AVL_Node<K,D>* &node ){
	AVL_Node<K,D>* y = node->left;
	node->left = y->right;
	y->right = node;

	updateHeight(node);
	updateHeight(y);
	node = y;
	y = 0;
}

template<class K, class D>
void AVL_Tree<K, D>::rotateLeftRight( AVL_Node<K,D>* &node ){
	rotateLeft(node->left);
	rotateRight(node);
}

template<class K, class D>
void AVL_Tree<K, D>::rotateRightLeft( AVL_Node<K,D>* &node ){
	rotateRight(node->right);
	rotateLeft(node);
}

template<class K, class D>
void AVL_Tree<K, D>::balance( AVL_Node<K,D>* &node ){
	int bfc = balanceFactor(node);

	if (bfc == 2){
		int bf2 = balanceFactor(node->right);
		if (bf2 == -1) {
			rotateRightLeft(node);
		}else{
			rotateLeft(node);
		}
	}else if( bfc == -2 ){
		int bf2 = balanceFactor(node->left);
		if (bf2 == -1) {
			rotateRight(node);
		}else{
			rotateLeftRight(node);
		}
	}
}

template<class K, class D>
void AVL_Tree<K,D>::printIncreasingHelper(AVL_Node<K,D>* &node){
	if( node == 0 ){

	}else if( node->right == 0 && node->left == 0 ){
		cout << "( "<< node->data <<") ";
	}else{
		printIncreasingHelper(node->left);
		cout << "( "<< node->data <<") ";
		printIncreasingHelper(node->right);
	}
}

template<class K, class D>
void AVL_Tree<K,D>::printIncreasing(){
	printIncreasingHelper(head);
}


#endif