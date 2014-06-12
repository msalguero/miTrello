#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "Nodo.h"


using namespace std;

template <class T>
class Lista
{
    public:
        int size;
        Nodo<T>*inicio;
        Nodo<T>*fin;
        Lista();
        virtual ~Lista();

        int Insertar(T value, int posicion);
        int Agregar(T value);
        int Localiza(T value);
        T Recupera(int posicion);
        void Siguiente();
        void Anterior();
        void Localiza_Suprime(T value);
        void Imprimir();
        void Anula();
        void Recupera_Suprime(int posicion);
        T Inicio();
        T Fin();
        void iteradorReset();
        bool iteradorEnd();
        T valorIterador();


    protected:
    private:
        Nodo<T>*iterador;

        void Suprime(Nodo<T>*nodo);
        Nodo<T>* RecuperaNodo(int posicion);
        Nodo<T>* LocalizaNodo(T value, int *posicion);
        Nodo<T>* Siguiente(Nodo<T>*nodo);
        Nodo<T>* Anterior(Nodo<T>*nodo);
};

template <class T>
Lista<T>::Lista()
{
    this->inicio=NULL;
    this->fin=NULL;
    size=0;
}

template <class T>
Lista<T>::~Lista()
{
    //dtor
}

template <class T>
int Lista<T>::Insertar(T value, int posicion)
{
    Nodo<T>* nodo= new Nodo<T>(value);
    if(posicion < 0 || posicion>size)
    {
        return -1;
    }
    if(inicio == NULL)
    {
        inicio = nodo;
        fin = nodo;
        size++;
        return 0;
    }
    if(posicion == size)
    {
        fin->siguiente = nodo;
        nodo->anterior= fin;
        fin = nodo;
        size++;
        return 0;
    }
    Nodo<T>*temp= inicio;

    for(int i =0 ; i < posicion;i++)
    {
        if(temp->siguiente == NULL)
            break;
        temp = temp->siguiente;
    }
    if(temp->anterior != NULL)
    {
        temp->anterior->siguiente = nodo;
        nodo->anterior= temp->anterior;
    }else
    {
        inicio = nodo;
    }
    temp->anterior = nodo;
    nodo->siguiente= temp;
    size++;
    return 0;
}

template <class T>
int Lista<T>::Agregar(T value)
{
    return Insertar(value, size);
}

template <class T>
int Lista<T>::Localiza(T value)
{
   int pos=0;
   LocalizaNodo(value, &pos);
   return pos;
}

template <class T>
Nodo<T>* Lista<T>::LocalizaNodo(T value, int *posicion)
{
    *posicion = 0;
    for(Nodo<T>*temp = inicio; temp!= NULL; temp=temp->siguiente)
    {
        if(temp->valor == value)
        {
            return temp;
        }
        (*posicion) ++;
    }
    *posicion = -1;
    return NULL;
}

template <class T>
T Lista<T>::Recupera(int posicion)
{
    Nodo<T>*nodo= RecuperaNodo(posicion);
    if(nodo == NULL)
        return NULL;
    else
        return nodo->valor;
}

template <class T>
Nodo<T>* Lista<T>::RecuperaNodo(int posicion)
{
    if(posicion < 0 || posicion > size)
    {
        return NULL;
    }
    Nodo<T>*temp= inicio;
    for(int i =0; i<posicion ; i ++)
    {
        temp = temp->siguiente;
    }
    return temp;
}

template <class T>
Nodo<T>* Lista<T>::Siguiente(Nodo<T>*nodo)
{
    return nodo->siguiente;
}

template <class T>
Nodo<T>* Lista<T>::Anterior(Nodo<T>*nodo)
{
    return nodo->anterior;
}

template <class T>
void Lista<T>::Imprimir()
{
    if(inicio == NULL)
    {
        cout<< "Lista vacia."<<endl;
    }
    for(Nodo<T>*temp = inicio ; temp!=NULL; temp=temp->siguiente)
    {
        cout<< temp->valor<<endl;
    }
}

template <class T>
void Lista<T>::Anula()
{
    while(inicio != NULL)
    {
        Suprime(inicio);
    }
}

template <class T>
void Lista<T>::Recupera_Suprime(int posicion)
{
    Nodo<T>*nodo = RecuperaNodo(posicion);
    Suprime(nodo);
}

template <class T>
void Lista<T>::Localiza_Suprime(T value)
{
    int pos =0;
    Nodo<T>*nodo= LocalizaNodo(value,&pos);
    Suprime(nodo);
}

template <class T>
void Lista<T>::Suprime(Nodo<T>*nodo)
{
    if(nodo == NULL)
        return;
    if(nodo == inicio && nodo == fin)
    {
        inicio = NULL;
        delete nodo;
        return;
    }
    if(nodo == inicio)
    {
        inicio = inicio->siguiente;
        inicio->anterior= NULL;
        delete nodo;
        size --;
        return;
    }
    if(nodo == fin)
    {
        fin = fin->anterior;
        fin->siguiente= NULL;
        delete nodo;
        size --;
        return;
    }
    if(nodo->anterior!= NULL)
    {
        nodo->anterior->siguiente= nodo->siguiente;
    }
    if(nodo->siguiente!=NULL)
    {
        nodo->siguiente->anterior= nodo->anterior;
    }
    delete nodo;
    size--;
    return;

}

template <class T>
T Lista<T>::Inicio()
{
    return inicio->valor;
}

template <class T>
T Lista<T>::Fin()
{
    return fin->valor;
}

template <class T>
void Lista<T>::iteradorReset()
{
    iterador = inicio;
}

template <class T>
void Lista<T>::Siguiente()
{
    iterador = Siguiente(iterador);
}

template <class T>
void Lista<T>::Anterior()
{
    iterador = Anterior(iterador);
}

template <class T>
bool Lista<T>::iteradorEnd()
{
    if(iterador==NULL)
    {
        return true;
    }else
        return false;
}

template <class T>
T Lista<T>::valorIterador()
{
    return iterador->valor;
}
#endif // LISTA_H
