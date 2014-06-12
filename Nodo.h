#ifndef NODO_H
#define NODO_H


using namespace std;

template <class T>
class Nodo
{
    public:
        Nodo<T> * siguiente;
        Nodo<T> * anterior;
        T valor;
        Nodo(T valor);
        virtual ~Nodo();
    protected:
    private:
};

template <class T>
Nodo<T>::Nodo(T valor)
{
    this->valor = valor;
    siguiente = NULL;
    anterior = NULL;
}

template <class T>
Nodo<T>::~Nodo()
{
    //dtor
}

#endif // NODO_H
