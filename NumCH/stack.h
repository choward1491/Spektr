
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