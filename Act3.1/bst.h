#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

template <class T> class BST;

template <class T> class Nodo {
public:
	Nodo(T);
	Nodo(T, Nodo<T>*, Nodo<T>*);
	void add(T);
	void removeChilds();	
	void remove(T);
	void inorder( stringstream&) const;
	void preorder( stringstream&) const;
	void postorder( stringstream&) const;
  bool find(T);
	int whatlevelamI(T);
	void printlevel( stringstream&, int) const;
	int height() const;
  bool ancestors(T,  stringstream&) const;
	void levelorder( stringstream&) const;

private:
	T value;
	Nodo *izq, *der;
	Nodo<T> *sucesor();

	friend class BST<T>;
};


template <class T> Nodo<T>::Nodo(T val, Nodo<T> *le, Nodo<T> *ri)	: value(val), izq(le), der(ri) {}

template <class T> Nodo<T>::Nodo(T val) :
 value(val), izq(0), der(0) {}

//o(log(n) )
template <class T> void Nodo<T>::remove(T val) {
	Nodo<T> * succ, *old;
	if (val < value) {
	if (izq != 0) {
	if (izq->value == val) {
	old = izq;
	succ = izq->sucesor();
	if (succ != 0) {
	succ->izq = old->izq;
	succ->der = old->der;
	}
  izq = succ;
	delete old;}
  else {
	izq->remove(val);
	}
	}
	} else if (val > value) {
	if (der != 0) {
	if (der->value == val) {
	old = der;
	succ = der->sucesor();
	if (succ != 0) {
	succ->izq = old->izq;
	succ->der = old->der;
	}
	der = succ;
	delete old;
	} else {
	der->remove(val);
	}
	}
	}
}
//o(log(n) )
template <class T> bool Nodo<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (izq != 0 && izq->find(val));
	} else if (val > value) {
		return (der != 0 && der->find(val));
	}
}

//o(log(n) )
template <class T> bool Nodo<T>::ancestors(T val,  stringstream &auxiliar) const{

	if (val == value) {
	  return true;
	} else if (val < value) {
		if (auxiliar.tellp() != 1) 			auxiliar << " ";
		
		auxiliar << value;
		return (izq != 0 && izq->ancestors(val,auxiliar));
	} else if (val > value) {
		if (auxiliar.tellp() != 1) {
			auxiliar << " ";
		}
		auxiliar << value;
		return (der != 0 && der->ancestors(val,auxiliar));
	}
}

//o(log(n) )
template <class T> void Nodo<T>::add(T val) {
if (val < value) {
if (izq != 0) {
izq->add(val);
} else {
izq = new Nodo<T>(val);
}
} else {
if (der != 0) 			der->add(val);
else 			der = new Nodo<T>(val);		
	}
}

//o(log(n) )
template <class T> Nodo<T>* Nodo<T>::sucesor() {
	Nodo<T> *le, *ri;
	le = izq;
	ri = der;
	if (izq == 0) {
		if (der != 0) {
			der = 0;
		}
		return ri;
	}
	if (izq->der == 0) {
		izq = izq->izq;
		le->izq = 0;
		return le;
	}
	Nodo<T> *parent, *child;
	parent = izq;
	child = izq->der;
	while (child->der != 0) {
		parent = child;
		child = child->der;}
	parent->der = child->izq;
	child->izq = 0;
	return child;
}


template <class T>
int Nodo<T>::whatlevelamI(T val) {
if (value == val) 		return 1;
else if (val < value) {
if(izq != 0)			return (izq->whatlevelamI(val) )+ 1;
} else if (val > value) {
if (der != 0)
return (der->whatlevelamI(val)) + 1;
}
return -10101010;
}

//o (1)   
template <class T> void Nodo<T>::removeChilds() {
if (der != 0) {
der->removeChilds();
delete der;
der = 0;
}
if (izq != 0) {
izq->removeChilds();
delete izq;
izq = 0;
}  
}

//o(1)
template <class T> void Nodo<T>::inorder( stringstream &auxiliar) const {
if (izq != 0) {
izq->inorder(auxiliar);
}
if (auxiliar.tellp() != 1) {
auxiliar << " ";
}
auxiliar << value;
if (der != 0) {
der->inorder(auxiliar);
}
}

//o(N)
template <class T> void Nodo<T>::preorder( stringstream &auxiliar) const {
auxiliar << value;
if (izq != 0) {
auxiliar << " ";
izq->preorder(auxiliar);
}
if (der != 0) {
auxiliar << " ";
der->preorder(auxiliar);
}
}
//o(n)
template <class T> void Nodo<T>::postorder( stringstream &auxiliar) const {
if (izq != 0) {
izq->postorder(auxiliar);
}

if (der != 0) {
der->postorder(auxiliar);
	}
if (auxiliar.tellp() != 1) {
auxiliar << " ";
	}
auxiliar << value;
}
 // o(n)
template <class T> void Nodo<T>::printlevel( stringstream &auxiliar, int level) const {

	if(level == 0){
		if (auxiliar.tellp() != 1) {
				auxiliar << " ";
		}
		auxiliar << value;
	}
	if (izq != 0) {
		izq->printlevel(auxiliar, level -1);
	}
	if (der != 0) {
		der->printlevel(auxiliar, level -1);
	}

}

// o(n)
template <class T> void Nodo<T>::levelorder( stringstream &auxiliar) const {
	int level = height();
	for(int i = 0; i < level; i++){
			printlevel(auxiliar, i);
	}
}


//o(n)
template <class T> int Nodo<T>::height() const {

	int level_izq = 0;
	int level_der = 0;

	if (izq != 0) {
		level_izq = izq->height() + 1;
	}
	if (der != 0) {
		level_der= der->height() +1;
	}
	if (level_izq == 0 && level_der == 0)
		return 1;

	return (level_der > level_izq) ? level_der : level_izq;
}

template <class T> class BST {
private:
	Nodo<T> *raiz;

public:
	BST();
	~BST();
	
	int  whatlevelamI(T) const;
	void remove(T);
  bool empty() const;
	void removeAll();
  void add(T);
	bool find(T) const;
	 string preorder() const;
	 string levelorder() const;
	 string visit();
	 string postorder() const;
  int height() const;
   string inorder() const;
	 string ancestors(T) const;
	
};

template <class T> BST<T>::BST() : raiz(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

// o(1)
template <class T>
bool BST<T>::empty() const {
	return (raiz == 0);
}

//o(logn)
template<class T>
void BST<T>::add(T val) {
	if (raiz != 0) {
		if (!raiz->find(val)) {
			raiz->add(val);
		}
	} else {
		raiz = new Nodo<T>(val);
	}
}

//o(logN)
template <class T>
void BST<T>::remove(T val) {
	if (raiz != 0) {
		if (val == raiz->value) {
			Nodo<T> *succ = raiz->sucesor();
			if (succ != 0) {
				succ->izq = raiz->izq;
				succ->der = raiz->der;
			}
			delete raiz;
			raiz = succ;
		} else 			raiz->remove(val);
		
	}
}

// o(logN)
template <class T> void BST<T>::removeAll() {
	if (raiz != 0) 		raiz->removeChilds();
	
	delete raiz;
	raiz = 0;
}

// o(logN)
template <class T>bool BST<T>::find(T val) const {
	if (raiz != 0) 		return raiz->find(val);
	
	else 		return false;
	
}

// o(logN)
template <class T> int BST<T>::whatlevelamI(T val) const {
	if (raiz != 0) {
	 	int num = raiz->whatlevelamI(val);
		if(num < 0) return -1;
		return num;
	}
	else {
		return -1;
	}
}

// o(logN)
template <class T>  string BST<T>::inorder() const {
	 stringstream auxiliar;

	auxiliar << "[";
	if (!empty()) {
		raiz->inorder(auxiliar);
	}
	auxiliar << "]";
	return auxiliar.str();
}
// o(logN)
template <class T>  string BST<T>::preorder() const {
	 stringstream auxiliar;

	auxiliar << "[";
	if (!empty()) {
		raiz->preorder(auxiliar);
	}
	auxiliar << "]";
	return auxiliar.str();
}
// o(logN)
template <class T>  string BST<T>::postorder() const {
	 stringstream auxiliar;

	auxiliar << "[";
	if (!empty()) {
		raiz->postorder(auxiliar);
	}
	auxiliar << "]";
	return auxiliar.str();
}



// o(logN)
template <class T>  string BST<T>::visit() {
	 stringstream auxiliar;
	auxiliar << preorder() << "\n";
	auxiliar << inorder() << "\n";
	auxiliar << postorder() << "\n";
	auxiliar << levelorder();
	return auxiliar.str();
}

// o(logN)
template <class T>  string BST<T>::levelorder() const {
	 stringstream auxiliar;

	auxiliar << "[";
	if (!empty()) {
		raiz->levelorder(auxiliar);
	}
	auxiliar << "]";
	return auxiliar.str();
}
// o(logN)
template <class T> int BST<T>::height() const {
	return raiz->height();
}

// o(logN)
template <class T>  string BST<T>::ancestors(T val) const {
	 stringstream auxiliar;
	auxiliar << "[";
	if (!empty()) {
		if(!raiz->ancestors(val, auxiliar))
			return "[]";
	}
	auxiliar << "]";
	return auxiliar.str();
}

#endif 
