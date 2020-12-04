#ifndef LIST_H
#define LIST_H
#include <sstream>
#include <string>
#include "exception.h"
template <class T> class List;
//clase link que representa un nodo
template <class T> class Link {
	private:
		Link(T);
    Link<T> * next;
		Link(T, Link<T>*);
		T value;		
		friend class List<T>;
};
//constructor con siguiente valor
template <class T> Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {
}
//constructor con 0 sig
template <class T> Link<T>::Link(T val) : value(val), next(0) {
}
//clase lista para iener a los nodos
template <class T> class List {
	public:
		List();
		~List();
    std::string toString() const;
    void clear();
    int find(T);
		void add(T) throw (OutOfMemory);
		void update(int, T) throw (IndexOutOfBounds);
		T remove(int) throw (IndexOutOfBounds);
  private:
    Link<T> *head;
    int size;
};
//constructor list con head apuntado a 0
template <class T> List<T>::List() : head(0), size(0) { 
}
//destructor list
template <class T> List<T>::~List(){
clear();
}
//funcion add  complejidad o(1)
// esta funcion se encarga de agregar un nuevo elemento a los nodos
// anidados 
template <class T> void List<T>::add(T val) throw (OutOfMemory) {
	Link<T> *newL, *p;
	newL = new Link<T>(val);
	if (newL == 0) {
		throw OutOfMemory();
	}
	if (size == 0){
		newL -> next = head;
		head = newL;
		size +=1;
		return;}
	p = head;
	while (p -> next != 0) {
		p = p -> next;}
	newL -> next = 0;
	p -> next = newL;
	size+=1;
}
// complejidad O(n)
// este metodo realiza una busqueda recursiva dentro de los elementos
// anidados 
template <class T> int List<T>::find(T val) {
	int i = 0;
  Link<T> *p;
	p = head;
	while (p != 0){
		if (p -> value == val) {
			return i ;
		}
		i+=1;
		p = p -> next;	}
return -1;
}
// complejidad o(n)
// se realiza un recorrido completo de la lista elemento por elemento
// hasta hallar un elemento dado y poder modificarlo
template <class T> void List<T>::update(int index, T val) throw (IndexOutOfBounds) {
	Link<T> *p;
	p = head;
	if (index > size) {
		throw OutOfMemory();
	}
	int pos = 0;
	while (p != 0){
		if (pos == index) p -> value = val;
		pos+=1;
		p = p -> next;
}
}
// o(1)
// se encarga de localizar un elemento dentro de la lista para eliminarlo
// y entrelazar los apuntadores que lo rodean
template <class T> T List<T>::remove(int index) throw (IndexOutOfBounds){
	Link<T> *p, *q;
	T temp;
	if (index > size) {
		throw IndexOutOfBounds();}
	p = head;
	if (index == 0){
		temp = p -> value;
		head = p -> next;
		delete p;}
	for (int i = 1; i <= index; i++){
		if (index == i){
			q = p -> next;
			temp = q -> value;
			p -> next = q -> next;
			delete q;
		}else{
			p = p -> next;	}
	}
	size-= 1;
	return temp;
}
//o(N)
// esta funcion hace un recorrido completo de la lista
// eliminando cada elemento hallado
template <class T> void List<T>::clear() {
	Link<T> *p, *q;
	p = head;
	while (p != 0) {
		q = p -> next;
		delete p;
		p = q;}
	head = 0;
	size = 0;
}
template <class T> std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;
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
#endif 
