//Author:Carolina Herrera Mtz
#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <list>

template <class T>
class Sorts 
{
public:	
	void ordenaSeleccion(std::vector<T>&);
	void ordenaBurbuja(std::vector<T>&);
	void ordenaMerge(std::vector<T>&);
	int busqSecuencial(const std::vector<T>&,int); 
	int busqBinaria(const std::vector<T>&,int);

private:
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
  void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void swap(std::vector<T>&, int, int);
	int binary_compare(const std::vector<T>&,int,int,int);
};

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v) {
	int pos;
	for (int i = v.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (v[j] > v[pos]) pos = j;
		}
		if (pos != i) swap(v, i, pos);	
	}
}
//complejidad (n^2)
template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
	for (int i = v.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) swap(v, j, j + 1);
		}
	}
}

// orden: n*log2(n)
template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size() - 1);
}


// (O(log n))
template <class T>
int Sorts<T>::busqBinaria(const std::vector<T>&v,int key) {
	return binary_compare(v, 0,v.size() - 1, key);
}

// o(n)
template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T>&v,int key){
	for (int i = 0; i < v.size(); i++) {
		if (key == v[i]) return i;
	}
	return (-1);
}

template <class T>
int Sorts<T>::binary_compare(const std::vector<T>&v,int inf,int sup,int key) { 
	int med;

	if (inf <= sup) {
		med = (sup + inf) / 2;
		if (key == v[med]) {
			return med;
		} else if (key < v[med]) {
			return binary_compare(v, inf, med - 1, key);
		} else if (key > v[med]) {
			return binary_compare(v, med + 1, sup, key);
		}
	}
	return inf;
}


template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int inf, int med, int sup) {
	int i, j, k;
	i = inf;
	j = (med+1);
	k = inf;

	while (i <= med &&j <= sup) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > med) {
		for (; j <= sup; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= med; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int inf, int sup) {
	int med;
	if ( (sup - inf) < 1 )  return;
	med = (sup + inf) / 2;
	mergeSplit(A, B, inf, med);
	mergeSplit(A, B, (med + 1), sup);
	mergeArray(A, B, inf, med, sup);
	copyArray(A, B, inf, sup);
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int inf, int sup) {
	for (int i = inf; i <= sup; i++) 	A[i] = B[i];
	
}

//O(n)

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}
#endif 