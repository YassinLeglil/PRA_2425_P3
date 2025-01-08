#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict : public Dict <V> {

	private :

		BSTree <TableEntry <V>> *tree; //ABB con elementos de tipo TableEntry <V> para gestionar los elementos de un diccionario
	
	public :

		BSTreeDict () { //Constructor
			
			tree = new BSTree <TableEntry <V>> (); //Objeto dinámico de tipo BSTree

		}

		~BSTreeDict () { //Método destructor. Libera la memoria dinamica ocupada por el ABB Tree
			
			delete tree; 

		}

		friend ostream& operator << (ostream &out, const BSTreeDict <V> &bs) { //Sobrecarga global del operador <<

			out << *(bs.tree) << endl;
		       	return out;	

		}

		void insert (string key, V value) { //Inserta el par key - value en el arbol
			
			TableEntry <V> entry = TableEntry <V> (key, value); //Objeto de tipo TableEntry
			tree -> insert (entry);	//Insertar el par en el arbol ABB	

		}

		V search (string key) { //Busca el valor correspondiente a key
			
			TableEntry <V> entry = TableEntry <V> (key); //Objeto de tipo TableEntry		
			return tree -> search (entry).value;

		}

		V remove (string key) { //Elimina el par key - value en el ABB

			TableEntry <V> entry = TableEntry <V> (key); //Objeto de tipo TableEntry
			return tree -> remove (entry);

		}

		int entries () {

			return tree -> size ();

		}





};


#endif
