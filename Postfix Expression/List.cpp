#include <iostream>
#include <new>
using namespace std;

template <typename type>
struct node {
	type data;
	node<type> * prev;
	node<type> * next;
};

template <typename type>
class List {
public:
	List ();
	List (string num);
	List (List<type> &src);
	virtual ~List ();

	bool isEmpty ();
	bool isNumber ();
	void display ();
	void insertFirst (type data);
	void insertLast (type data);
	void fromString (string num);

	type removeFirst ();
	type removeLast ();
	void remove (type data);
	string toString ();
	void trim ();
	void empty ();

	node<type> * find (type data);
	node<type> * getHead () { return head; }
	node<type> * getTail () { return tail; }
	List<type> * copy ();

	int count;
	bool isNegative;
	bool isFloat;
protected:
	node<type> * head;
	node<type> * tail;
private:
	bool sorted; //whether the list is sorted or not
};

template <typename type>
List<type>::List () {
	count = 0;
	isNegative = false;
	isFloat = false;
}

template <typename type>
List<type>::List (string num) {
	for (size_t i = 0; i < num.size(); i++) {
		if (num[i] == '-') 
			isNegative = true;
		else if (num[i] == '.')
			isFloat = true;
		insertLast (num[i]);
	}
	if (isNegative) removeFirst ();
}

template <typename type>
List<type>::List (List<type> &src) {
	node<type> * tmp, *p;
	sorted = src.sorted;
	tmp = src.head;
	head = tail = NULL;
	while (tmp) {
		p = new node<type>;
		p->next = p->prev = NULL;
		p->data = tmp->data;
		if (head == NULL) {
			head = tail = p;
		}
		else {
			p->prev = tail;
			tail = tail->next = p;
		}
		tmp = tmp->next;
	}
	isNegative = src.isNegative;
	isFloat = src.isFloat;
	count = src.count;
}

// Checks if a List is Empty
template <typename type>
bool List<type>::isEmpty () {
	return head == NULL;
}

template <typename type>
bool List<type>::isNumber () {
	bool isNumber = false;
	int cntNegSigns = 0, cntDecPts = 0;
	node<type> * p;
	p = head;
	while (p != NULL) {
		if (p->data >= '0' && p->data <= '9' || p->data == '-' || p->data == '.') {
			if (p->data == '.') cntDecPts++;
			else if (p->data == '-') cntNegSigns++;
			isNumber = true;
		}
		else return false;
		p = p->next;
	}
	if (cntDecPts > 1 || cntNegSigns > 1) isNumber = false;
	return isNumber;
}

// Makes a List Empty
template <typename type>
void List<type>::empty () {
	node<type> * p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete p;
	}
	head = tail = NULL;
	isNegative = false;
	isFloat = false;
	count = 0;
}

template <typename type>
void List<type>::fromString (string num) {
	for (size_t i = 0; i < num.size (); i++) {
		if (num[i] == '-')
			isNegative = true;
		else if (num[i] == '.')
			isFloat = true;
		insertLast (num[i]);
	}
	if (isNegative) removeFirst ();
}

// List Destructing Function
template <typename type>
List<type>::~List () {
	List<type>::empty ();
}

// List Displaying Fuction
template <typename type>
void List<type>::display () {
	node<type> * p;
	p = head;
	while (p) {
		cout << p->data;
		p = p->next;
	}
}

template <typename type>
void List<type>::insertFirst (type data) {
	node<type>* p, *before;
	p = new node<type>;
	if (!p) return; //no memory for the new node
	p->data = data;
	if (data == '.') isFloat = true;
	if (data == '-') isNegative = true;
	p->next = p->prev = NULL;
	if (head == NULL) {
		//list is empty. inset the node as the the only node
		head = tail = p;
		count++;
	}
	else {
		before = head;
		p->next = before;
		head = before->prev = p;
		count++;
	}
}

template <typename type>
void List<type>::insertLast (type data) {
	node<type>* p;
	p = new node<type>;
	if (!p) return; //no memory for the new node
	p->data = data;
	if (data == '.') isFloat = true;
	if (data == '-') isNegative = true;
	p->next = p->prev = NULL;
	if (head == NULL) {
		//list is empty. inset the node as the the only node
		head = tail = p;
		count++;
	}
	else {
		p->prev = tail;
		tail = tail->next = p;
		count++;
	}
}

template <typename type>
type List<type>::removeFirst () {
	type temp;
	if (head == NULL) return NULL;
	node<type> * p; //node to delete
	p = head;
	if (p == NULL) return NULL;
	if (head == tail) { //removing only node
		head = tail = NULL;
		count = 0;
	}
	else { //removing first node
		p->next->prev = NULL;
		head = p->next;
		count--;
	}
	temp = p->data;
	delete p;
	return temp;
}

template <typename type>
type List<type>::removeLast () {
	type temp;
	if (head == NULL) return NULL;
	node<type> * p; //node to delete
	p = tail;
	if (p == NULL) return NULL;
	if (head == tail) { //removing only node
		head = tail = NULL;
		count = 0;
	}
	else { //removing first node
		p->prev->next = NULL;
		tail = p->prev;
		count--;
	}
	temp = p->data;
	delete p;
	return temp;
}

template <typename type>
void List<type>::remove (type data) {
	if (head == NULL) return;
	node<type> * p; //node to delete
		p = find (data);
	if (p == NULL) return;
	if (head == tail) {
		head = tail = NULL;
	}
	else if (head == p) {
		p->next->prev = NULL;
		head = p->next;
	}
	else if (tail == p) {
		p->prev->next = NULL;
		tail = p->prev;
	}
	else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;
}

template <typename type>
node<type> * List<type>::find (type data) {
	node<type> * p;
	p = head;
	while (head != NULL) {
		if (p->data == data) break;
		p = p->next;
	}
	return p;
}

template <typename type>
void List<type>::trim () {
	if (head->data == '-') {
		removeFirst ();
		isNegative = true;
	}
	while (head->data == '0') {
		removeFirst ();
	}
	if (isFloat) {
		while (tail->data == '0') {
			removeLast ();
		}
		if (tail->data == '.') {
			removeLast ();
			isFloat = false;
		}
	}
}

template <typename type>
string List<type>::toString () {
	string temp = "";
	node<type> * p;
	p = head;
	while (p) {
		temp += p->data;
		p = p->next;
	}
	return temp;
}

template <typename type>
List<type> * List<type>::copy () {
	return new List<type> (*this);
}