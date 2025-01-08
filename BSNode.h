#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

using namespace std;

template <typename T>
class BSNode {

	public :

		T elem; // Elemento de tipo T almacenado en el nodo
		BSNode <T> *left; //Puntero al nodo sucesor izquierdo
		BSNode <T> *right; //Puntero al nodo sucesor derecho

		//Métodos

		BSNode (T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr) : elem {elem} {}

		friend ostream& operator << (ostream &out, const BSNode<T> &nodo){ 

		 	out << "Elem => " << nodo.elem << endl;
			return out;

		}

};

#endif
