#ifndef LISTA_H
#define LISTA_H
#include <string>
using namespace std;


template <typename T>

class Lista
{
    public:
        Lista();
        virtual ~Lista();

        void agregar_elem (const T & nuevo_elem);

        void mostrar () const;

        unsigned int longitud_lista () const;

        void cursor_principio();

        const T & recuperar_elem () const;

        void avanzar_cursor ();

        void vaciar();


;
    private:

        struct nodo{
            T elem;
            nodo * sig;
        };
        nodo * primero;
        nodo * cursor;

        nodo * crear_nodo (const T & elem, nodo * sig);

        unsigned int cant_elem = 0;

};

#endif // LISTA_H
