#ifndef LISTAPROCESOS_H
#define LISTAPROCESOS_H
#include<QString>
#include<qdebug.h>

//--------------------------Nodo--------------------
class Nodo
{

    public:
        //Variables
        int pId;
        QString nombre;
        int tiempo;
        int memoria;
        int estado;
        int valorRestante;

        Nodo *ant;
        Nodo *sig;

        //Constructores
        Nodo() {}

        Nodo(int p_pId, QString p_nombre, int p_tiempo, int p_memoria)
        {
            pId = p_pId;
            nombre = p_nombre;
            tiempo = p_tiempo;
            memoria = p_memoria;
            estado = 0;
        }
};

class ListaProcesos
{
    public:
    //Variables
    int pIdSerial;
    Nodo *inicio;
    Nodo *ultimo;

    //Constructores
    ListaProcesos()
    {
        inicio = NULL;
        ultimo = NULL;
    }

    //Funciones
    bool Vacia()
    {
        return inicio == NULL && ultimo == NULL? true : false;
    }

    int profundidad()
    {
        if (Vacia())
            return 0;

        int contador = 0;

        Nodo *aux;
        aux = inicio;

        while (aux != ultimo)
        {
           contador++;
           aux = aux->sig;
        }
        return contador + 1;
    }

    int sigPId()
    {
        return ++pIdSerial;
    }

    void apilar(Nodo* p_nodo)
    {
        Nodo* tmp = p_nodo;

        if(Vacia())
        {
            inicio = tmp;
            ultimo = tmp;
        }
        else
        {
            ultimo->sig = tmp;
            tmp->ant = ultimo;
            ultimo = tmp;

            ultimo->sig = inicio;
            inicio->ant = ultimo;
        }
    }

    void mostrar()
    {
        Nodo *aux;
        aux = inicio;
        for(int i = 0; i < profundidad(); i++)
        {
            qDebug()<<aux->nombre;

            aux = aux->sig;
        }
    }

    void eliminarNodo(int p_pID)
    {
        Nodo *aux;

        if(p_pID == inicio->pId)
        {
            aux = inicio;
            inicio = aux->sig;
            delete(aux);
        }
        else if(p_pID == ultimo->pId)
        {
            aux = ultimo;
            ultimo = ultimo->ant;
            delete(aux);
        }
        else
        {
            aux = inicio->sig;
            for(int i = 1; i < profundidad(); i++)
            {
                if(aux->pId == p_pID)
                {
                    aux->ant->sig = aux->sig;
                    aux->sig->ant = aux->ant;
                    delete(aux);
                    return;
                }
                aux = aux->sig;
            }
        }
    }
};
#endif // LISTAPROCESOS_H
