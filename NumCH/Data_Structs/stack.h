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


#ifndef _stack_h_
#define _stack_h_



template<class D>
class Stack {
public:
	Stack();
	~Stack();

	void push(D data);
	D pop();
	int getCount(){ return count; }

private:
	typedef struct Node{
		D data;
		Node* next;
	} Node;


	Node* head;
	int count;

	


	void remove();
	void removeHelper(Node* & node);
};



template<class D>
Stack<D>::Stack(){
	head = 0;
	count = 0;
}

template<class D>
void Stack<D>::remove()
{
	removeHelper(head);
}


template<class D>
void Stack<D>::removeHelper(Node* & node)
{
	if( node != 0 ){
		removeHelper(node->next);
		delete node; node = 0;
	}
}



template<class D>
Stack<D>::~Stack(){
	remove();
}



template<class D>
void Stack<D>::push(D data){
	Node* n = new Node;
		  n->data = data;

	if( head == 0 ){
		n->next = 0;
		head = n;
		n = 0;
	}else{
		n->next = head;
		head = n;
		n = 0;
	}

	count++;
}



template<class D>
D Stack<D>::pop(){
	if( head != 0 ){
		Node* y = head;
		head = y->next;
		y->next = 0;

		D output = y->data;
		delete y; y = 0;

		count--;

		return output;
	}else{
		return D();
	}
}



#endif