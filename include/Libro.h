#ifndef LIBRO_H
#define LIBRO_H
#include <string>
#include <iostream>
#include "lista.h"

using namespace std;

class Libro
{
    public:
        Libro();
        Libro(string isbn, string titulo, string autor, string fechaPublicacion, string paisOrigen, float precio);
        virtual ~Libro();
        string devolverIsbn()const;
        string devolverTitulo()const;
        string devolverAutor()const;
        string devolverFechaPublicacion()const;
        string devolverPaisOrigen()const;
        float devolverPrecio()const;
        Lista<string> & devolverIdiomas();

        void agg_idioma (string idiom);



    private:
        string isbn;
        string titulo;
        string autor;
        string fechaPublicacion;
        string paisOrigen;
        float precio;
        Lista<string> idiomas;

};
ostream & operator << (ostream & salida, Libro & l);
#endif // LIBRO_H
