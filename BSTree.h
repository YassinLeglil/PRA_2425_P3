#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree {

	private :

		int nelem; //Número de elementos

		BSNode <T> *root; //Nodo raíz del ABB
				  
		T search (BSNode <T> *n, T e) const {

			if (n == nullptr) {

				throw runtime_error ("Element not found");

			} else if (n -> elem < e) { // Si el elemento es mayor que n se comprueba el de su derecha

				return search (n -> right, e);

			} else if (n -> elem > e) { // Si el elemento es menor que n se comprueba el de su izquiera

				return search (n -> left, e);

			} else { return n -> elem; //Si es igual se devuelve ese elemento

			}

		}

		BSNode <T> *insert (BSNode <T> *n, T e) {

			if (n == nullptr) { //Si n es null hemos llegado a un lugar donde se puede insertar el elemento 
				return new BSNode (e); 
				
			} else if (n -> elem == e) { //Si el elemento ya existe devuelve un error

				throw runtime_error ("Duplicate Element");

			} else if (n -> elem < e) { //Si el elemento es mayor que el nodo actual

				n -> right = insert (n -> right, e); //Se vuelve a hacer el insert hasta que sea null

			} else {

				n -> left = insert (n -> left, e); //Si el elemento es menor que el nodo actual

			}

			return n; //Devuelve el nodo actual despues de haber realizado la operacion de insert 
				  //En cada nivel de recursion este nodo se actualiza como padre

		}

		void print_inorden (ostream &out, BSNode <T> *n) const {

			if (n != nullptr) { //Si el nodo no es nulo

				print_inorden (out, n -> left); // LLama recursivamente a la funcion hasta que llega a un arbol hoja

				out << n -> elem << "\n"; // Cuando llega al arbol hoja empieza a imprimir todos los del arbol izquierdo

				if (n -> right != nullptr) { //Si el nodo tiene un subarbol derecho llama recursivamente a la funcion.

					print_inorden (out, n -> right);

				}

			}

		}

		BSNode <T> *remove (BSNode <T>* n, T e) {

			if (n == nullptr) { 

				throw runtime_error ("Element Not Found"); //Si n es nula significa que no tiene elementos

			} else if (n -> elem < e) { //Si el elemento es mayor que n se vuelve a comprobar con el de su derecha

				n -> right = remove (n -> right, e);

			} else if (n -> elem > e) { //Si el elemento es menor que n se vuelve a comparar con el de la izquierda

				n -> left = remove (n -> left, e);

			} else { // e == n

				if (n -> left != nullptr && n -> right != nullptr) { //Si el elemento tiene dos descendientes
					
					n -> elem = max (n -> left); //Reemplazará por el elemento máximo del subarbol izquierdo
					n -> left = remove_max (n -> left); //Elimina el elemento de máximo valor del subarbol izquierdo

				} else { //Si el elemento tiene uno o 0 descendientes

					n = (n->left != nullptr)? n->left: n->right;
					

				}

			}

			return n;
		}	

		T max (BSNode <T> *n) const {

			if (n == nullptr) {

				throw runtime_error ("Element not found");

			} else if (n -> right != nullptr) { //Si el desciendete derecho no es nulo se vuelve a comprobar con el descendiente suyo

				return max (n -> right);

			} else { //Si es nulo significa que el elemento más grande es ese

				return n -> elem;

			}

		}


		BSNode <T> *remove_max (BSNode <T> *n) {

			if (n -> right == nullptr) { //Si el descendiente derecho es nulo 

				return n -> left; //Se devuelve su descendiente izquierdo

			} else { //Si el descendiente derecho no es nulo, es decir es el mayor

				n -> right = remove_max(n-> right); //Se hace recursividad hasta encontrar el mayor
				return n; //Se devuelve
			}


		}

		void delete_cascade (BSNode <T> *n) {

			if (n != nullptr) { //Si n no es nulo
				
				n = remove (n, n -> elem); //Actulizara n al elemento por el que se reemplaza
				delete_cascade (n); //Se hace recursivamente hasta que ese elemento sea nulo

			}



		}
						



	public :

		BSTree () { //Método constructor. Crea un ABB vació
			
			nelem = 0;
			root = nullptr;

		}

		int size () const { //Devuelve el número de elementos del ABB
			
			return nelem;

		}

		T search (T e) const { //Devuelve el elemento e de tipo T en el ABB. 
			
			return search (root, e);

		}

		T operator[](T e) const{

				return search(e);
		}

		void insert (T e) { //Inserta el elemento e de tipo T de manera ordenada en el ABB
			
			root = insert (root, e);
			nelem++;

		}

		friend ostream& operator << (ostream &out, BSTree <T> &bst) { //Sobrecarga del operador <<

			bst.print_inorden (out, bst.root); //Raiz de bst
			return out;

		}

		void remove (T e) { //Elimina el elemento e de tipo T del ABB

			remove (root, e);
			nelem--;


		}

		~BSTree() { //Metodo destructor
			
			delete_cascade (root);
			nelem = 0;

		}





};

#endif
