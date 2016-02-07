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

#ifndef _hash_table_h_
#define _hash_table_h_

/* This will be a HashTable with fairly flexible functionality.

K = key type
D = data type
S = Data structure being used in table. This function must have 
	the following public methods defined:

	- void push( K key, D data )
	- D find(K key, bool &found )
	- D remove(K key, bool & found)
*/
template< class K, class D, class S >
class HashTable {

public:
	HashTable();
	HashTable( int (*f)(K key, int size), int table_size = 19 );
    HashTable<K,D,S>& operator= (const HashTable<K,D,S>& table );
    
	~HashTable();

	void push(K key, D data);
	D find(K key, bool & found );
	D remove(K key, bool & found );
	int getNumberOfItemsInTable() const { return num_items; }
    int getLengthTable() const { return t_size; }
    S operator[](int i) const{ return table[i]; }
    S& operator[](int i) { return table[i]; }
    
    
    // function pointer to hash function
    // This function must return a positive integer between
    // the values of 0 and (size-1)
    int (*hashfunc)(K key, int size);

private:

	// Hash Table array
	S* table;

	// length of table
	int t_size;

	// number of items in table
	int num_items;

	// function to expand/shrink hash table if there's a certain
	// size of elements within the table
	void transformTable( int flag );
	
};



template< class K, class D, class S >
HashTable<K,D,S>& HashTable<K,D,S>::operator= (const HashTable<K,D,S>& tab ){
    if (this != &tab ) {
        if ( table != 0 ) {
            delete [] table;
        }
        t_size = tab.getLengthTable();
        num_items = tab.getNumberOfItemsInTable();
        table = new S[t_size];
        
        for (int i = 0; i < t_size; i++) {
            S tmp = tab[i];
            table[i] = tmp;
        }
        
        hashfunc = tab.hashfunc;
    }
    
    return *this;
}



template< class K, class D, class S >
HashTable<K,D,S>::HashTable(){
	table = 0;
	t_size = 0;
	hashfunc = 0;
	num_items = 0;
}




template< class K, class D, class S >
HashTable<K,D,S>::HashTable( int(*hf)(K key, int size), int table_size ){
	hashfunc = hf;
	t_size = table_size;
	table = new S[t_size];
	num_items = 0;
}


template< class K, class D, class S >
HashTable<K,D,S>::~HashTable()
{
	delete [] table; table = 0;
	t_size = 0;
	hashfunc = 0;
	num_items = 0;
}




template< class K, class D, class S >
void HashTable<K,D,S>::push(K key, D data)
{
	int index = hashfunc(key, t_size);
	table[index].push(key, data);
	num_items++;
}




template< class K, class D, class S >
D HashTable<K,D,S>::find(K key, bool & found)
{
	int index = hashfunc(key, t_size);
	return table[index].find(key, found);
}




template< class K, class D, class S >
D HashTable<K,D,S>::remove(K key, bool & found )
{
	int index = hashfunc(key, t_size);
	return table[index].remove(key, found );
}




template< class K, class D, class S >
void HashTable<K,D,S>::transformTable( int flag )
{

}


#endif