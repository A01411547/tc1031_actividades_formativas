//  Impplementación de Splay Tree en una clase 
//
//  Carolina Herrera Mtz. A01411547
//
//  Actividad 3.3

#ifndef SPLAY_H
#define SPLAY_H

#include <sstream>
#include <iostream>
using namespace std;

template <class T> class SplayTree;


template <class T> class Nodo {


public:

  Nodo (T);
  Nodo (T, Nodo<T>*, Nodo<T>*, Nodo<T>*); 
  Nodo<T>* find(T);
  Nodo<T>* add(T);
  Nodo<T>* remove(T);
  
  
  void preorder(stringstream&) const;
  void inorder(stringstream&) const;
  void removeChilds();
  void print_tree(stringstream&) const;
  

  Nodo<T>* splay(Nodo<T>*, Nodo<T>*);

private:
  Nodo *izq, *der, *padre;
  
  Nodo<T>* raiz_der(Nodo<T>*);
  Nodo<T>* raiz_izq(Nodo<T>*);
  Nodo<T>* sucesor();

  T value;

  friend class SplayTree<T>;
};

template <class T> Nodo<T>::Nodo(T val)  {
  value = val;
  izq = 0;
  der = 0;
  padre = 0;


}

template <class T> Nodo<T>::Nodo(T val, Nodo<T> *le, Nodo<T> *ri, Nodo<T> *p)  {
izq = le;
der = ri;
value = val;
padre = p;

}

template <class T> Nodo<T>* Nodo<T>::add(T val) {

if (val < value) {
  if (izq != 0)    return izq->add(val);
  
  else {
    izq = new Nodo<T>(val);
    izq->padre = this;
    return izq;
  }
  } else {
    if (der != 0)       return der->add(val);
     else {
      der = new Nodo<T>(val);
      der->padre = this;
      return der;
    }
  }
}

template <class T> Nodo<T>* Nodo<T>::sucesor(){
	Nodo<T> *le, *ri;
	
	le = izq;
	ri = der;
	
	if (der == 0){
		if (izq != 0)			izq = 0;
		
	if(le)		          le->padre = 0;
return le;
}
	
	if (der->izq == 0){
		der = der->der;
		if(der)			der->padre = padre;
		if(ri){
			ri->der = 0;
			ri->padre = 0;
		}
  		return ri;
	}
	
	Nodo<T> *p, *c;
	p = der;
	c = der->izq;
	while(c->izq != 0){
		p = c;
		c = c->izq;
	}
	p->izq = c->der;
	if(p->izq != 0) 		p->izq->padre = p;
	c->der = 0;
	return c;
}

template <class T>Nodo<T>* Nodo<T>::remove(T val) {
Nodo<T> *suc, *prev;
if (val < value) {
  if (izq != 0) {
    if (izq->value == val) {
      prev = izq;
      suc = izq->sucesor();
      if (suc != 0) {
      suc->izq = prev->izq;
      suc->der = prev->der;
      suc->padre = prev->padre;
      if (suc->izq)          suc->izq->padre = suc;
      if (suc->der)          suc->der->padre = suc;
      }
      izq = suc;
      delete prev;
      return this;
    } else {
      return izq->remove(val);
    }
  }
} else if (val > value) {
  if (der != 0) {
    if (der->value == val) {
      prev = der;
      suc = der->sucesor();
      if (suc != 0) {
      suc->izq = prev->izq;
      suc->der = prev->der;
      suc->padre = prev->padre;
      if (suc->izq)    suc->izq->padre = suc;
        if (suc->der)  suc->der->padre = suc;
      }
      der = suc;
      delete prev;
      return this;
  } else     return der->remove(val);
      
    }
  }
  return 0;
}

template <class T> Nodo<T>* Nodo<T>::raiz_der(Nodo<T>* x){
  Nodo<T> *y = x->izq;
  x->izq = y->der;
  if(y->der)
    y->der->padre = x;
  y->der = x;
  y->padre = x->padre;
  x->padre = y;
  if (y->padre){
    if (y->padre->izq && y->padre->izq->value == x->value)
      y->padre->izq = y;
    else
      y->padre->der = y;  
  }
  return y;
}

template <class T> Nodo<T>* Nodo<T>::raiz_izq(Nodo<T>* x){
  Nodo<T> *y = x->der;
  x->der = y->izq;
  if(y->izq)
    y->izq->padre = x;
  y->izq = x;
  y->padre = x->padre;
  x->padre = y;
  if (y->padre) {
    if (y->padre->izq && y->padre->izq->value == x->value)
      y->padre->izq = y;
    else
      y->padre->der = y;  
  }
  return y;
}


template <class T> void Nodo<T>::inorder(stringstream &aux) const {
  if (izq != 0) {
    izq->inorder(aux);
  }
  if (aux.tellp() != 1) {
    aux << " ";
  }
  aux << value;
  if (der != 0) {
    der->inorder(aux);
  }
}

template <class T> void Nodo<T>::preorder(stringstream &aux) const {
	aux << value;
	if (izq != 0) {
		aux << " ";
		izq->preorder(aux);
	}
	if (der != 0) {
		aux << " ";
		der->preorder(aux);
	}
}

template <class T> Nodo<T>* Nodo<T>::find(T val) {
  if (val == value)    return this;
   else if (val < value) {
    if (izq != 0)    return izq->find(val);
  else    return this;
  } else if (val > value) {
    if (der != 0)      return der->find(val);
    else      return this;
  }
return 0;
}

template <class T> Nodo<T>* Nodo<T>::splay(Nodo<T>* root,Nodo<T>* x) { 
  while (x->padre != 0){
	
    if(x->padre->value == root->value) {
      if(x->padre->izq && x->padre->izq->value == x->value)         raiz_der(x->padre);
       else         raiz_izq(x->padre);
      
	} else{
        Nodo<T>*p = x->padre; 
        Nodo<T>*g = p->padre; 
		
    if(p->izq && g->izq && x->value == p->izq->value && p->value == g->izq->value){
		      raiz_der(g);
          raiz_der(p);
        } 
    else if (p->der && g->der && 	x->value == p->der->value && p->value == g->der->value){
		      raiz_izq(g);
          raiz_izq(p);
 } 
    else if (p->izq && g-> der && x->value == p->izq->value && p->value == g->der->value){
		      raiz_der(p);
          raiz_izq(g);    } 
    else {
		  raiz_izq(p);
      raiz_der(g);
      }
     }
    }
    return x;
}




template <class T> class SplayTree {


public:
  SplayTree();
  
  string inorder() const;
  string print_tree() const;
  string preorder() const;
  
  bool find (T);
  bool empty() const;
  void add(T);
  
  void remove (T);
  
  int size();

private:
  Nodo<T> *root;

};

template <class T> SplayTree<T>::SplayTree()  {

  root = 0;
}

template <class T> bool SplayTree<T>::empty() const {
  
  if (root == 0 ) return true ;
  else return false;
}
 
template <class T> void SplayTree<T>::add(T val) {
  if ( root != 0) {
    Nodo<T>* added = root->add(val);
    root = root->splay(root,added);
  } 
  else     root = new Nodo<T>(val);
  
}
template <class T> string SplayTree<T>::preorder() const {
  stringstream aux;

  aux << "[";
  if (!empty()) {
    root->preorder(aux);
  }
  aux << "]";
  return aux.str();
}

template <class T>
int SplayTree<T>::size(){
	return 0;
}

template <class T> void SplayTree<T>::remove(T val) {
  if (root != 0) {
    if (val == root->value) {
      Nodo<T> *suc = root->sucesor();
      if (suc != 0) {
        suc->izq = root->izq;
        suc->der = root->der;
        suc->padre = 0;
        if (suc->izq)
          suc->izq->padre = suc;
        if (suc->der)
          suc->der->padre = suc;
      }
      delete root;
      root = suc;
    } else {
      Nodo<T>* p = root->remove(val);
      root = root->splay(root,p);
    }
  }
}

template <class T> bool SplayTree<T>::find(T val) {
  if (root != 0) {
    Nodo<T>* found = root->find(val);
    root = root->splay(root,found);
    return (root->value == val);
  } else {
    return false;
  }
}

template <class T> string SplayTree<T>::inorder() const {
  stringstream aux;

  aux << "[";
  if (!empty()) {
    root->inorder(aux);
  }
  aux << "]";
  return aux.str();
}



#endif