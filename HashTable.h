#ifndef HASH_TABLE
#define HASH_TABLE

#include <ostream>
#include <stdexcept>
#include <string>
#include <string.h>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/clear/labPRG/Año2/PRA_2324_P1/ListLinked.h"

using namespace std;

template <typename V> 
class HashTable : public Dict <V> {

	private :

		int n; //Numero de elementos almacenados en la tabla hash
		int max; //Tamanyo de la tabla hash
		ListLinked <TableEntry<V>>* table; //Array de ListLinkeds de tipo TableEntry
		
		int h (string key) { 
			
			int length = key.length();
			int suma = 0;
			char ch;
			for (int i = 0; i < length; i ++) {

				ch = key.at(i);
				suma = suma + int (ch);
			}

			return (suma % max);

		}


	public :

		HashTable (int size) { //Metodo constructor

			table = new ListLinked <TableEntry<V>> [size];
			n = 0;
			max = size;

		}

		~HashTable () { //Metodo destructor

			delete [] table;
		}

		int capacity () const { //Capacidad 

			return max;

		}

		void insert (string key, V value) { //Insertar un nuevo key -> value

			int pos = h (key); //Pasa por la función h para saber en que posición

			ListLinked <TableEntry <V>>& slot = table [pos]; //Se accede a la lista que hay en esa posición
                        for (int i = 0; i < slot.size () ; i++) { //Se recorre toda la lista para ver si hay un objeto que tenga la misma key
                                if (slot.get(i).key == key) { //Si lo encuentra lanza un error 

                                        throw runtime_error ("Key ya se encuentra en la tabla");

                                }

                        }	

                       	TableEntry <V> entry = TableEntry <V> (key, value); //Si no lo encuentra crea un objeto tipo table Entry con la (key , value)
                       	table[pos].prepend (entry); //Lo inserta al final de la tabla
                      	n++; //Actualiza el número de elementos
		}

		V search (string key) { //Devuelve el valor correspondiente a key
                                
			int pos = h(key); //Pasa por la función h para saber su posición en la tabla
			ListLinked <TableEntry <V>>& slot = table [pos]; //Se hace lo mismo que en insert
				
			for (int i = 0; i < slot.size () ; i++) {

				if (slot.get(i).key == key) {
					return slot.get(i).value; //Si lo encuentra devolverá el valor de ese elemento

				}

			}

			throw runtime_error ("key no se encuentra en la tabla");

		}

		V remove (string key) { //Elimina un elemento y lo devuelve

			int pos = h(key);

                   	ListLinked <TableEntry <V>>& slot = table [pos];

			for (int i = 0; i < slot.size () ; i++) {

                          	if (slot.get(i).key == key) {
					n--;
                                     	return slot.remove(i).value;

                               }

                        }


			throw runtime_error ("Key no se encuentra en la tabla");

		}

		int entries () { return n; }

		friend ostream& operator << (ostream &out, const HashTable <V> &th) {

                        for (int i = 0; i < th.capacity (); i++) {

                                out << "====== Cubeta " << i << " ======" << endl;
					
				out << "   " << th.table[i] << endl;

				out << "======================" << endl;
                                

                        }

			return out;

		}

		
		V operator [] (string key) {

			return (search(key));
		}	

};

			

#endif
