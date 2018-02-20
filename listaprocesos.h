#ifndef LISTAPROCESOS_H
#define LISTAPROCESOS_H
#include<QString>
#include<qdebug.h>
#include<QMessageBox>

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

        while (aux != NULL)
        {
           contador++;
           aux = aux->sig;
        }
        return contador;
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
            ultimo->sig = NULL;
        }
    }

    void mostrar()
    {
        if(Vacia())
            return;

        Nodo *aux;
        aux = inicio;
        while (aux->sig != NULL)
        {
            QMessageBox mm;
            QString ss = "pid:" + QString::number(aux->pId) + " nombre" + aux->nombre + " T" + QString::number(aux->tiempo)+ " M" + aux->memoria;
            mm.setText(ss);
            mm.exec();

            aux = aux->sig;
        }
    }

    void limpiarLista()
    {
        Nodo *aux;
        Nodo *aux2;
        aux = inicio;
        for(int i = 0; i < profundidad(); i++)
        {
            aux2 = aux;
            delete(aux2);
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

    void ordenaTipo(int p_tipoOrden)
    {
        if(Vacia())
            return;

        switch (p_tipoOrden) {
        case 0:
           ordernaMemoria();
            break;
        case 1:
            ordernaTiempo();
            break;
        default:
            break;
        }
    }

    void ordernaTiempo()
    {
        if(Vacia())
            return;

        Nodo *actual , *siguiente;
        QString nombre;
        int tiempo;
        int memoria;
        int pid;

            actual = inicio;
            while(actual->sig != NULL)
            {
                 siguiente = actual->sig;

                 while(siguiente!=NULL)
                 {
                      if(siguiente->tiempo < actual->tiempo)
                      {
                          nombre = actual->nombre;
                          tiempo = actual->tiempo;
                          memoria = actual->memoria;
                          pid = actual->pId;

                          actual->nombre = siguiente->nombre;
                          actual->tiempo = siguiente->tiempo;
                          actual->memoria = siguiente->memoria;
                          actual->pId = siguiente->pId;

                          siguiente->nombre = nombre;
                          siguiente->tiempo = tiempo;
                          siguiente->memoria = memoria;
                          siguiente->pId = pid;
                      }
                      else if(actual->tiempo == siguiente->tiempo)
                      {
                          if(actual->pId > siguiente->pId)
                          {
                              nombre = actual->nombre;
                              tiempo = actual->tiempo;
                              memoria = actual->memoria;
                              pid = actual->pId;

                              actual->nombre = siguiente->nombre;
                              actual->tiempo = siguiente->tiempo;
                              actual->memoria = siguiente->memoria;
                              actual->pId = siguiente->pId;

                              siguiente->nombre = nombre;
                              siguiente->tiempo = tiempo;
                              siguiente->memoria = memoria;
                              siguiente->pId = pid;
                          }

                      }
                      siguiente = siguiente->sig;
                 }
                 actual = actual->sig;
                 siguiente = actual->sig;
            }
    }

    void ordernaMemoria()
    {
        Nodo *actual , *siguiente;
        QString nombre;
        int tiempo;
        int memoria;
        int pid;

            actual = inicio;
            while(actual->sig != NULL)
            {
                 siguiente = actual->sig;

                 while(siguiente!=NULL)
                 {
                      if(actual->memoria < siguiente->memoria)
                      {
                          nombre = actual->nombre;
                          tiempo = actual->tiempo;
                          memoria = actual->memoria;
                          pid = actual->pId;

                          actual->nombre = siguiente->nombre;
                          actual->tiempo = siguiente->tiempo;
                          actual->memoria = siguiente->memoria;
                          actual->pId = siguiente->pId;

                          siguiente->nombre = nombre;
                          siguiente->tiempo = tiempo;
                          siguiente->memoria = memoria;
                          siguiente->pId = pid;
                      }
                      else if(actual->memoria == siguiente->memoria)
                      {
                          if(actual->pId > siguiente->pId)
                          {
                              nombre = actual->nombre;
                              tiempo = actual->tiempo;
                              memoria = actual->memoria;
                              pid = actual->pId;

                              actual->nombre = siguiente->nombre;
                              actual->tiempo = siguiente->tiempo;
                              actual->memoria = siguiente->memoria;
                              actual->pId = siguiente->pId;

                              siguiente->nombre = nombre;
                              siguiente->tiempo = tiempo;
                              siguiente->memoria = memoria;
                              siguiente->pId = pid;
                          }

                      }
                      siguiente = siguiente->sig;
                 }
                 actual = actual->sig;
                 siguiente = actual->sig;
            }
    }
};
#endif // LISTAPROCESOS_H
