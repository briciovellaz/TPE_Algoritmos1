#include <cstddef>
#include <iostream>
#include <string>
#include "Lista.h"
#include "Libro.h"
#include "assert.h"

using namespace std;

//========================================== Procesos crear LISTA

template <typename T>
Lista<T>:: Lista()
{
    primero = NULL;
    cant_elem = 0;
}

template <typename T>
Lista<T>:: ~Lista()
{

}

template <typename T>
void Lista<T>:: vaciar(){

    nodo * aux = primero;
    while (primero != NULL){
        aux = primero->sig;
        delete primero;
        primero = aux;
    }
    primero = NULL;

}

template <typename T>
typename Lista<T>:: nodo * Lista<T> :: crear_nodo (const T & elem, nodo * sig) {

    nodo * nuevo = new nodo();
    nuevo ->elem = elem;
    nuevo->sig = primero;

    return nuevo;
}

template <typename T>
void Lista<T>::agregar_elem(const T & nuevo_elem) {

    nodo * nuevo = crear_nodo(nuevo_elem, primero);
    primero = nuevo;
    this->cant_elem ++;
}

template <typename T>
void Lista<T>::mostrar() const{
    cout << cursor->elem << endl;
}


template <typename T>
unsigned int Lista<T>::longitud_lista () const {

    return cant_elem;
}

template <typename T>
void Lista<T> :: cursor_principio() {

    cursor = this ->primero;
}

template <typename T>
const T & Lista <T> :: recuperar_elem () const {

    return cursor->elem;
}

template <typename T>
void Lista<T>:: avanzar_cursor () {

    cursor = cursor->sig;
}

/*template <typename T>
const T & Lista<T>:: recuperar_lista(unsigned int i) const{

    assert (i < longitud_lista ());
    nodo * aux = this ->primero;
    for (unsigned int j=0; j<i; j++){
        aux = aux->sig;
    }
    return aux->elem;
}*/

template class Lista<Libro>;
template class Lista<string>;
