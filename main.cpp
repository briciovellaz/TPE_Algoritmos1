#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <Lista.h>
#include <Libro.h>
#include <algorithm>
#include "assert.h"


using namespace std;

//GRUPO 17: VICENZI HILEN, BRICIO VELLAZ BARBIERI

/**
 * Abre el archivo según el origen, procesa las líneas del mismo y
 * almacena la información resultante en el contenedor pasado por referencia.
 **/
void procesar_archivo_entrada(string origen, Lista<Libro> & libros);


void Opciones();
void Menu (Lista<Libro> libros);
void sinacentos(string &p);
bool compararSigno(string p, string b);
bool compararAsterisco(string p, string b);

//Servicio 1
void existe_libro (Lista<Libro> & libros, string titulo);
//Servicio 2
void listar_por_fecha (Lista<Libro> & libros, string fecha_usuario_1, string fecha_usuario_2 );
//Servicio 3
int cant_libros(Lista<Libro> & libros, string idioma);
bool mismo_idioma(Lista<Libro> & libros, string idioma);
void guardar (Lista<Libro> & libros, string idioma, Libro i, string nro_libros[]);
float busqueda_precio (Lista<Libro> & libros, string nro_libros[], int i);
void ordenar_arreglo(Lista<Libro> & libros, string idioma, string nro_libros[]);
void mostrar_economicos (Lista<Libro> libros, string idioma, int cant_usuario);

int main()
{
    string idioma;
    Lista<Libro> libros;
    setlocale(LC_ALL, ""); //asegurarse que el archivo de texto fue guardado como Ansi y no como Unicode
    procesar_archivo_entrada("libros.csv", libros);
    Menu(libros);
    return 0;
}

//LISTA LOS LIBROS EN UN RANGO DE FECHA CON TODA SU INFORMACION
void listar_por_fecha(Lista<Libro> & libros, string fecha_usuario_1, string fecha_usuario_2 ){

    libros.cursor_principio();
    for (unsigned i=0; i< libros.longitud_lista(); i++){
        Libro l = libros.recuperar_elem();
        if (l.devolverFechaPublicacion() >= fecha_usuario_1){
                if (l.devolverFechaPublicacion() <= fecha_usuario_2){
                    cout<<endl;
                    libros.mostrar();
                    cout<<endl;
                }
        }
        libros.avanzar_cursor();
    }
    cout << endl <<endl;
    cout << "Si no se muestra ningun libro es porque no existe ninguno con esa fecha." << endl << endl;
    cout << endl;
}

int cant_libros(Lista<Libro> & libros, string idioma){
    int tam=0;
    libros.cursor_principio();
    for (unsigned int k=1; k<=libros.longitud_lista();k++) {
        Libro i = libros.recuperar_elem();
        i.devolverIdiomas().cursor_principio();
        for (unsigned int j=1; j<=i.devolverIdiomas().longitud_lista(); j++){
            string idiom=i.devolverIdiomas().recuperar_elem();
            sinacentos(idiom);
            transform(idiom.begin(), idiom.end(), idiom.begin(), ::tolower);
            if (idioma == idiom){
                tam++;
            }
            i.devolverIdiomas().avanzar_cursor();
        }
        libros.avanzar_cursor();
    }
    return tam;

}

bool mismo_idioma(Lista<Libro> & libros, string idioma, Libro i){
    bool esta=false;
    i.devolverIdiomas().cursor_principio();
    for (unsigned int j=1; j<=i.devolverIdiomas().longitud_lista(); j++){
        string idiom=i.devolverIdiomas().recuperar_elem();
        sinacentos(idiom);
        transform(idiom.begin(), idiom.end(), idiom.begin(), ::tolower);
        if (idioma == idiom){
            esta=true;
            j=i.devolverIdiomas().longitud_lista()+1;
        } else {
            i.devolverIdiomas().avanzar_cursor();
        }
    }
    return esta;
}

float busqueda_precio (Lista<Libro> & libros, string nro_libros[], int i){
    libros.cursor_principio();
    for (unsigned int k=1; k<=libros.longitud_lista();k++){
        Libro aux = libros.recuperar_elem();
        if (aux.devolverIsbn()==nro_libros[i]){
            return aux.devolverPrecio();
        } else {
            libros.avanzar_cursor();
        }
    }
}

void ordenar_arreglo(Lista<Libro> & libros, string idioma, string nro_libros[]){
    libros.cursor_principio();
    int h, k;
    int tam= cant_libros(libros, idioma);
    string aux;
    for (h=0; h<tam; h++){
        for (k=0; k<tam-1; k++){
            float precio_1= busqueda_precio(libros, nro_libros, k);
            float precio_2= busqueda_precio(libros, nro_libros, k+1);
            if (precio_1 > precio_2){
                aux= nro_libros[k];
                nro_libros[k]=nro_libros[k+1];
                nro_libros[k+1]=aux;
            }

        }
    }
}

void guardar (Lista<Libro> & libros, string idioma, string nro_libros[]) {
    libros.cursor_principio();
    int j=0;
    for (unsigned int k=1; k<=libros.longitud_lista();k++){
        Libro i = libros.recuperar_elem();
        if (mismo_idioma(libros, idioma, i)){

            nro_libros[j]=i.devolverIsbn();
            j++;
            cout<<endl;
        }
        libros.avanzar_cursor();
    }
}

void mostrar_economicos (Lista<Libro> libros, string idioma, int cant_usuario){
    string nro_libros[100];
    guardar(libros,idioma, nro_libros);
    ordenar_arreglo(libros,idioma,nro_libros);
    unsigned int j=0;
    while (j<cant_usuario){
        libros.cursor_principio();
        for (unsigned int k=1; k<=libros.longitud_lista();k++){
            Libro i = libros.recuperar_elem();
            if (mismo_idioma(libros, idioma, i)){
                if (i.devolverIsbn() == nro_libros[j]){
                libros.mostrar();
                }
            }
            libros.avanzar_cursor();
        }
        j++;
    }
}

//MUESTRA SI EXISTE EL LIBRO EN LA BOOKSTORE CON LA OPCION DE USAR COMODINES
void sinacentos(string &p) {
    int j;
    j=p.length();
    for(int i=0;i<j; i++){
        if (p[i]=='á'){
            p[i]= 'a';
            ;
        }
        else if (p[i]=='é'){
            p[i]= 'e';
            ;
        }
        else if (p[i]=='í'){
            p[i]= 'i';
            ;
        }
        else if (p[i]=='ó'){
            p[i]= 'o';
            ;
        }
        else if (p[i]=='ú'){
            p[i]= 'u';
            ;
        }
        else if (p[i]=='ñ'){
            p[i]= 'n';
            ;
        }
    }
}

bool compararAsterisco(string p, string b){
    unsigned int e=0;
    unsigned int h=0;
    for(unsigned int i=0;i<p.length(); i++){
        if (p[i]==b[h]){
            e++;
            h++;
        }else
        {
            if ((b[h]=='*')&&((h!=b.length()))){
                h++;
                e++;
            }else
                {
                    if(h==b.length())
                    {
                            e=p.length();
                    }
                }
        }
    }
    if (e == p.length()){
        return true;
    }
    else return false;
}

bool compararSigno(string p, string b){
    int j,i,e;
    e=1;
    j = p.length();
    for(i=0;i<j; i++){
        if (p[i]==b[i]){
            e++;
            ;
        } else{
                if (b[i]=='?'){
                e++;
                }
        }
    }
    if (e == j)
        return true;
    else
        return false;
    }


void existe_libro (Lista<Libro> & libros, string nombre){
    libros.cursor_principio();
    std::string t_usuario = nombre;
    t_usuario.erase(std::remove(t_usuario.begin(), t_usuario.end(), ' '), t_usuario.end());
    sinacentos(nombre);
    transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
    for (unsigned int i=0; i < libros.longitud_lista() ; i++){
        Libro l = libros.recuperar_elem();
        std::string word =l.devolverTitulo();
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        sinacentos(word);
        if ((compararSigno(word, nombre))||(compararAsterisco(word, nombre))){
            cout<<endl<< "Resultado/s: "<<endl<<"En caso de que el libro no exista en la bookstore no se mostrara ninguno."<<endl<<endl;
            libros.mostrar();
            libros.avanzar_cursor();
        } else {
            libros.avanzar_cursor();
        }

    }
    /*if (esta != true){
        cout<<endl;
        cout << "El libro no existe dentro de la bookstore"<< endl;
        cout<<endl;
    }
    else if (esta=true){
        cout<<endl;
        cout<<"El libro existe dentro de la bookstore"<< endl<<endl;
    }*/
}


//========================= MENU PARA OPERAR CON SUS OPCIONES =========================
void Opciones() {
    cout<< "BOOKSTORE" << endl;
    cout << endl;
    cout << "1. Buscar libro" << endl;
    cout << "2. Lista de libros en un rango de fechas"<< endl;
    cout << "3. Libros mas economicos"<< endl;
    cout << "4. Salir"<< endl;
    cout<< endl;
}

void Menu (Lista<Libro> libros){
    char opcion;
    string fecha_usuario_1;
    string fecha_usuario_2;
    string nombre;
    string idioma;
    int n;
    bool salir=false;
    do {
        system("cls");
        //cout << "Hay " << libros.longitud_lista() << " libros disponibles." << endl<<endl;
        Opciones();
        cout<< "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        cout << endl;
        switch (opcion) {
            case '1':
                cout<<endl;
                cout<< "Titulo del libro: "<< endl;
                getline(cin,nombre);
                nombre.erase(std::remove(nombre.begin(), nombre.end(), ' '), nombre.end());
                existe_libro(libros, nombre);
                cout<< "Ingrese cualquier caracter para volver al inicio."<<endl;
                cin>>opcion;
                break;

            case '2':
                cout<<endl;
                cout<<"Ingrese fecha inicio: ";
                cin>>fecha_usuario_1;
                cout<<endl;
                cout<<"Ingrese fecha final: ";
                cin>>fecha_usuario_2;
                cout<<endl;
                while (fecha_usuario_2 < fecha_usuario_1){
                    cout<<"La fecha final tiene que ser mayor a la fecha inicial"<<endl;
                    cout<<"Ingrese fecha inicio: ";
                    cin>>fecha_usuario_1;
                    cout<<endl;
                    cout<<"Ingrese fecha final: ";
                    cin>>fecha_usuario_2;
                    cout<<endl;
                }
                listar_por_fecha(libros, fecha_usuario_1, fecha_usuario_2);
                cout<< "Ingrese cualquier caracter para volver al inicio."<<endl;
                cin>>opcion;
                break;
            case '3':
                cout<<"Ingrese idioma: ";
                cin>>idioma;
                cout<<"Ingrese cantidad de libros: ";
                cin>>n;
                transform(idioma.begin(), idioma.end(), idioma.begin(), ::tolower);
                mostrar_economicos(libros,idioma,n);
                cout<< "Ingrese cualquier caracter para volver al inicio."<<endl;
                cin>>opcion;
                break;
            case '4':
                cout<< "Quiere salir del programa? Ingrese 'S' para aceptar o cualquier otro caracter para volver." << endl;
                cin >> opcion;
                if (opcion == 'S' || opcion == 's') {
                    cout << endl;
                    salir=true;
                    libros.vaciar();
                    break;
                }
                break;

           default:{
                cout<<"Por favor ingrese una opcion valida(1-4)."<<endl;
                cout<<endl;
                cout<< "Ingrese cualquier caracter para volver a intentar."<<endl;
                cin>>opcion;
                }

        }

    } while (opcion!=4&&!salir);
    cout << "Salio de la BOOKSTORE";
    cout << endl;
    return;
}


//============================== PROCESADOR DE ARCHIVOS ==============================
//Comentarios: atoi y atof requieren un char * para converter a número, usamos c_str de la clase string.
void procesar_archivo_entrada(string origen, Lista<Libro> & libros)
{
    Libro l;
    ifstream archivo(origen);
    if (!archivo.is_open())
        cout << "No se pudo abrir el archivo: " << origen << endl;
    else {
        string linea;
        getline(archivo, linea);
        int cantidad_libros = atoi(linea.c_str());
        cout << "Hay " << cantidad_libros << " libros." << endl<<endl;

        //Leemos de una linea completa por vez (getline).
        Lista<string> idiom;
        Lista<Libro> economicos;
        int nroLibro = 1;
        while (getline(archivo, linea)) {
            //Primer posición del separador ;
            int pos_inicial = 0;
            int pos_final = linea.find(';');

            //Informacion entre pos_inicial y pos_final
            string isbn = linea.substr(pos_inicial, pos_final);

            //Segunda posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string titulo = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Tercera posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string autor = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Cuarta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string fechaPublicacion = linea.substr(pos_inicial, pos_final - pos_inicial);

             //Quinta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            string paisOrigen = linea.substr(pos_inicial, pos_final - pos_inicial);

            //Sexta posición del separador ;
            pos_inicial = pos_final + 1;
            pos_final = linea.find(';', pos_inicial);
            float precio = atof(linea.substr(pos_inicial, pos_final - pos_inicial).c_str());

            //Crea libro
            Libro l= Libro(isbn, titulo, autor, fechaPublicacion, paisOrigen, precio);

            //Crea lista de idiomas dentro del libro l
            pos_inicial = pos_final + 2;
            pos_final = linea.size()-1;
            string idiomas = linea.substr(pos_inicial, pos_final - pos_inicial);
            int pos_inicial_coma = 0, pos_final_coma = 0;
            //separa los idiomas del string de arriba cada vez que encuentra una coma
            while (pos_final_coma != -1) {
                pos_final_coma = idiomas.find(' ,', pos_inicial_coma);
                string idioma = idiomas.substr(pos_inicial_coma, pos_final_coma - pos_inicial_coma);
                pos_inicial_coma = pos_final_coma + 1;
                //agrega a la lista de idiomas un solo idioma quedando en un solo nodo
                idioma.erase(std::remove(idioma.begin(), idioma.end(), ' '), idioma.end());
                l.agg_idioma(idioma);
            }

/*
            // el siguiente código de prueba separa los diferentes idiomas en un arreglo de 10 posiciones
            string listaIdiomas[10];
            int pos_inicial_idiomas = 0, pos_final_idiomas = 0;
            int nroIdioma = 0;
            while (pos_final_idiomas != -1) {
                pos_final_idiomas = idiomas.find(',', pos_inicial_idiomas);
                listaIdiomas[nroIdioma] = idiomas.substr(pos_inicial_idiomas, pos_final_idiomas - pos_inicial_idiomas);
                pos_inicial_idiomas = pos_final_idiomas + 1;
                nroIdioma++;
            }*/

            nroLibro++;
            libros.agregar_elem(l);

        }
    }
}

