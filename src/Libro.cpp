#include "Libro.h"
#include <string>
#include <iostream>
#include "lista.h"

using namespace std;

Libro::Libro()
{
    //ctor
}

Libro::~Libro()
{
    //dtor
}

Libro::Libro(string isbn, string titulo, string autor, string fechaPublicacion, string paisOrigen, float precio)
{

    this->isbn=isbn;
    this->titulo=titulo;
    this->autor=autor;
    this->fechaPublicacion=fechaPublicacion;
    this->paisOrigen=paisOrigen;
    this->precio=precio;

}

string Libro::devolverIsbn()const {

    return isbn;
}


string Libro::devolverTitulo()const {

    return titulo;
}


string Libro::devolverAutor()const {

    return autor;
}


string Libro::devolverFechaPublicacion()const {
    return fechaPublicacion;

}


string Libro::devolverPaisOrigen()const {

    return paisOrigen;
}


float Libro::devolverPrecio()const {

    return precio;
}

 Lista<string> & Libro::devolverIdiomas ()
{
    return idiomas;
}

void Libro::agg_idioma(string idiom){
    idiomas.agregar_elem(idiom);
}

ostream & operator << (ostream & salida, Libro & l){
    salida <<"ISBN: " << l.devolverIsbn()<<endl;
    salida <<"Titulo Libro: " << l.devolverTitulo()<<endl;
    salida <<"Autor: " << l.devolverAutor()<< endl;
    salida <<"Fecha de publicacion: " << l.devolverFechaPublicacion()<< endl;
    salida <<"Pais de origen: " << l.devolverPaisOrigen() << endl;
    salida <<"Precio: $" << l.devolverPrecio() << endl;
    salida <<"Idiomas: ";

    l.devolverIdiomas().cursor_principio();
    for (unsigned i =0; i < l.devolverIdiomas().longitud_lista(); i++) {
        salida<<l.devolverIdiomas().recuperar_elem()<< ", ";
        l.devolverIdiomas().avanzar_cursor();
    }
    cout<<endl;
    return salida;

}
