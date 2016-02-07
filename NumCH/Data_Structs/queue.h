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

#ifndef _queue_h_
#define _queue_h_


template<class D>
class Queue{
public:

	Queue();
	~Queue();

	void push(D data);
	D pop();
	int getCount() const { return count; }

private:
	typedef struct Node{
		D data;
		Node* next;
	} Node;

	Node* head;
	Node* tail;
	int count;

	void clear();
	void clearHelper( Node* & node );
};



template<class D>
Queue<D>::Queue(){
	head = 0;
	tail = 0;
	count = 0;
}


template<class D>
void Queue<D>::clearHelper( Node* & node ){
	if( node != 0 ){
		clearHelper(node->next);
		delete node; node = 0;
	}
}


template<class D>
void Queue<D>::clear(){
	clearHelper(head);
	tail = 0;
}


template<class D>
Queue<D>::~Queue(){
	clear();
}

template<class D>
void Queue<D>::push(D data){
	Node* n = new Node;
	n->data = data;
	n->next = 0;

	if( head == 0 ){
		head = n;
	}else{
		tail->next = n;
	}
    count++;
	tail = n;
	n = 0;
}

template<class D>
D Queue<D>::pop(){
	if( head != 0 ){
		D d = head->data;
		Node* y = head;
		head = head->next;
		delete y; y = 0;
        count--;
		return d;
	}else{
		return D();
	}
}



#endif