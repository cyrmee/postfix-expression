#include <iostream>
#include <string>
#include <new>
using namespace std;

template <typename type>
struct node {
	type data;
	node * next;
};

template <typename type>
class Stack {
public:
	Stack ();
	~Stack ();
	bool isEmpty ();
	void empty ();
	void push (type data);
	type pop ();
	type peek ();
	int getCount () { return count; }
protected:
private:
	node<type> * top;
	int count;
};

template <typename type>
Stack<type>::Stack () {
	top = NULL;
	count = 0;
}

template <typename type>
void Stack<type>::empty () {
	node<type> * p;
	while (top) {
		p = top;
		top = p->next;
		delete p;
	}
	count = 0;
}

template <class type>
Stack<type>::~Stack () {
	Stack<type>::empty ();
}

template <class T>
bool Stack<T>::isEmpty () {
	return top == NULL;
}

template <typename type>
type Stack<type>::peek () {
	return top->data;
}

template <typename type>
void Stack<type>::push (type data) {
	node<type> *p;
	p = new (nothrow) node<type>;
	p->data = data;
	p->next = top;
	top = p;
	count++;
}

template <typename type>
type Stack<type>::pop () {
	type data;
	node<type> *p;
	data = top->data;
	p = top;
	top = top->next;
	delete p;
	count--;
	return data;
}