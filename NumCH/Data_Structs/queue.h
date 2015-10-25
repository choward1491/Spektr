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