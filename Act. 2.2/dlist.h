// Autor: Carolina Herrera Mtz. A01411547

#ifndef DLIST_H
#define DLIST_H
#include <sstream>

#include <string>

#include "exception.h"

template <class T> class DList;

template <class T> class DLink {
	private:
		DLink(T);
		DLink(T, DLink<T>*, DLink<T>*);

		T value;
		DLink<T> *next;
		DLink<T> *previous;

		friend class DList<T>;
};


//  O(1)
template <class T> DLink<T>::DLink(T val) : value(val), next(0), previous(0) {}

//  O(1)
template <class T> DLink<T>::DLink(T val, DLink* nxt, DLink<T>* prev) : value(val), next(nxt), previous(prev) {}

template <class T> class DList {
	public:
		DList();
		~DList();
    void clear();
		void add(T) throw (OutOfMemory);
   	void update(int, T) throw (IndexOutOfBounds);
		T remove(int) throw (IndexOutOfBounds);
    int find(T);		
		std::string toStringForward() const;
		std::string toStringBackward() const; 
  	private:
		DLink<T> *head;
		DLink<T> *last;
		int size;
};

//  O(1)
template <class T> DList<T>::DList() : head(0), last(0), size(0) {}

//  O(1) 
template <class T>DList<T>::~DList(){
	clear();
}

//  O(1)
template <class T> void DList<T>::add(T val) throw (OutOfMemory) {
	DLink<T> *newLink;
	newLink = new DLink<T>(val);
	if (newLink == 0) 		throw OutOfMemory();
	if (size == 0){
		newLink -> next = head;  
		newLink -> previous = last;
		head = newLink;
		last = newLink;
		size ++;
		return;
	}
	newLink -> next = NULL;  
	newLink -> previous = last;
	last -> next = newLink;
	last = newLink;
	size++;
}

//   O(n)
template <class T> int DList<T>::find(T val) {
	DLink<T> *p, *q;
	p = head;
	q = last;

	int normal = 0;
  int inverso = (size - 1);
	while (p != 0){	
		if (p -> value == val) 			return normal;
		if (q -> value == val) 			return inverso;
		p = p -> next;
		normal++;
    q = q -> previous;
		inverso--;
	}
	return -1;
}


//  O(n)
template <class T> void DList<T>::update(int index, T val) throw (IndexOutOfBounds) {
	DLink<T> *p;
	int i;
	if (index > size) 		throw OutOfMemory();
	if (index <= size - 1 ){
		p = head;
		i = 0;
		while (p != 0){
			if (i == index){
				p -> value = val;
			}
 			p = p -> next;
			i++;
		}
	} 
else {
	p = last;
	i = size - 1;
	
  while (p != 0){
	  if (i == index){
	    p -> value = val;
	}
	i--;
	p = p -> previous;
  }
}
}


// Complexity O(1)
template <class T> T DList<T>::remove(int index) throw (IndexOutOfBounds){
	int i;
  T aux;
	DLink<T> *p, *q, *r;
	if (index > size) 	throw IndexOutOfBounds();
	else if (index == 0){
		p = head;
		aux = p -> value;
		head = p -> next;
    head -> previous = NULL; 
		delete p;
  }
 else if (index < size-1 ){
  p = head;
	i = 0;
	while ( i <= index-1){
		p = p-> next;
     i++;
	}     		
  q = p -> next;
  r = p -> previous;
  q -> previous = r;
  r -> next = q;
	delete p;
		} 

}


// Complexity O(n)
template <class T> void DList<T>::clear() {
	DLink<T> *p, *q;
	p = head;
	while (p != 0) {
		q = p -> next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T> std::string DList<T>::toStringForward() const {
		std::stringstream aux;
		DLink<T> *p;
		p = head;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->next != 0) {
				aux << ", ";
			}
			p = p->next;
		}
		aux << "]";
		return aux.str();
	}

	template <class T>	std::string DList<T>::toStringBackward() const {
		std::stringstream aux;
		DLink<T> *p;
		p = last;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}

#endif 

