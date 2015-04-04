/* 
 * File:   codigo.c
 * Author: braian
 *
 * Created on 24 de marzo de 2015, 01:22 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

/*
 * 
 */
struct nodoArbol {
    int dato;
    int fe;
    struct nodoArbol *Izq, *Der;

};

typedef struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */

/*Crea el nodo que se insertará en la lista*/
NodoArbol* crearNodo(int id) {
    NodoArbol * aux;
    aux = (NodoArbol*) malloc(sizeof (NodoArbol));
    aux -> dato = id;
    aux -> Izq = aux -> Der = NULL;
    aux -> fe = 0;
    return aux;
}

/*ROtación izquierda izquierda*/
void rotacionIzqIzq(NodoArbol** n, NodoArbol* n1) {
    (*n) -> Izq = n1 -> Der;
    n1 -> Der = (*n);
    if (n1 -> fe == -1) {
        (*n) -> fe = 0;
        n1 -> fe = 0;
    } else {
        (*n) -> fe = -1;
        n1 -> fe = 1;
    }
    (*n) = n1;
}

/*Rotación Derecha Derecha*/
void rotacionDerDer(NodoArbol** n, NodoArbol * n1) {
    (*n) -> Der = n1 -> Izq;
    n1 -> Izq = (*n);
    if (n1 -> fe == +1) {
        (*n) -> fe = 0;
        n1 -> fe = 0;
    } else {
        (*n) -> fe = +1;
        n1 -> fe = -1;
    }
    (*n) = n1;
}

/*Rotación izquierda derecha*/
void rotacionIzqDer(NodoArbol** n, NodoArbol * n1) {
    NodoArbol* n2;
    n2 = n1 -> Der;
    (*n) -> Izq = n2 -> Der;
    n2 -> Der = *n;
    n1 -> Der = n2 -> Izq;
    n2 -> Izq = n1;
    if (n2 -> fe == +1) {
        n1 -> fe = -1;
    } else {
        n1 -> fe = 0;
    }
    if (n2 -> fe == -1) {
        (*n) -> fe = 1;
    } else {
        (*n) -> fe = 0;
    }
    n2 -> fe = 0;
    (*n) = n2;
}

/*Rotacion Derecha Izquierda*/
void rotacionDerIzq(NodoArbol** n, NodoArbol * n1) {
    NodoArbol* n2;
    n2 = n1 -> Izq;
    (*n) -> Der = n2 -> Izq;
    n2 -> Izq = *n;
    n1 -> Izq = n2 -> Der;
    n2 -> Der = n1;
    if (n2 -> fe == +1) {
        (*n) -> fe = -1;
    } else {
        (*n) -> fe = 0;
    }
    if (n2 -> fe == -1) {
        n1 -> fe = 1;
    } else {
        n1 -> fe = 0;
    }
    n2 -> fe = 0;
    (*n) = n2;
}

/*MEtodo para insertar el elemento*/
void insertar(NodoArbol** raiz, int digi, int* h) {
    NodoArbol* n1;
    if (!(*raiz)) {
        *raiz = crearNodo(digi);
        *h = 1;
    } else if (digi < (*raiz) -> dato) {
        /*Si el dato que entra es menor que el dato de la raiz, entonces lo ingresa en el lado derecho*/
        insertar(&((*raiz) -> Izq), digi, h);
        if (*h) {
            switch ((*raiz)->fe) {
                case 1: (*raiz) -> fe = 0;
                    (*h) = 0;
                    break;
                case 0: (*raiz) -> fe = -1;
                    break;
                case -1:
                    n1 = (*raiz) -> Izq;
                    if (n1 -> fe == -1) {
                        rotacionIzqIzq(raiz, n1);
                    } else {
                        rotacionIzqDer(raiz, n1);
                    }
                    (*h) = 0;
            }
        }
    } else if (digi > (*raiz) -> dato) {
        /*Si el dato que entra es mayor que la raiz, entonces lo ingresa del lado derecho*/
        insertar(&((*raiz) -> Der), digi, h);
        if (*h) {
            switch ((*raiz) -> fe) {
                case 1:
                    n1 = (*raiz) -> Der;
                    if (n1 -> fe == +1) {
                        rotacionDerDer(raiz, n1);
                    } else {
                        rotacionDerIzq(raiz, n1);
                    }
                    (*h) = 0;
                    break;
                case 0: (*raiz) -> fe = +1;
                    break;
                case -1: (*raiz) -> fe = 0;
                    (*h) = 0;
                    break;
            }
        }
    } else {
        /*Si el dato es igual a la raiz, entonces no se admite el digito*/
        printf("¡Se ha ingresado un dígito incorrecto, por favor revise su archivo de entrada!");
        (*h) = 0;
    }
}

/*Metodo para Preorden*/
void preorden(NodoArbol* raiz) {
    if (raiz) {
        printf("%i, ", raiz->dato);
        preorden(raiz->Izq);
        preorden(raiz->Der);
    }
}

/*MEtodo para inorden*/
void inorden(NodoArbol* raiz) {
    if (raiz) {
        inorden(raiz -> Izq);
        printf("%i, ", raiz->dato);
        inorden(raiz -> Der);
    }

}

/*Estructura de Nodos*/
struct strucNodo {
    int dato;
    int id;
    struct strucNodo *siguiente, *anterior;
};
typedef struct strucNodo NodoLista;

/*Se inicializan las variables a usar*/
NodoLista* cabeza = NULL;
NodoLista* fin = NULL;
int indice = 0;

/*Metodo para insertar en la lista*/
void insertarDato(int valor) {
    NodoLista *nuevo = NULL;
    /*Asignamos valores*/
    nuevo = (NodoLista*) malloc(sizeof (NodoLista));
    nuevo -> dato = valor;
    nuevo -> id = indice;
    indice = indice + 1;
    /*Inicializamos apuntadores a NULL*/
    nuevo -> siguiente = NULL;
    nuevo ->anterior = NULL;
    /*En caso de que este vacia la lista, se crea el primer nodo*/
    if (cabeza == NULL) {
        cabeza = nuevo;
        fin = nuevo;
    } else {
        /*De no estar vacia, actulizamos los apuntadores*/
        nuevo ->anterior = fin;
        fin->siguiente = nuevo;
        fin = nuevo;
    }
}

/*Metodo para contar los elementos que existen en la lista*/
int contar() {
    int contador = 0;
    if (cabeza != NULL) {
        NodoLista *iterador = cabeza;
        while (iterador != NULL) {
            contador = contador + 1;
            iterador = iterador ->siguiente;
        }
    }
    return contador;
}

/*Metodo para bsucar*/
NodoLista* buscar(int valor) {
    if (cabeza != NULL) {
        NodoLista *iterador = cabeza;
        while (iterador != NULL) {
            if (iterador->id == valor) {
                return iterador;
            }
            iterador = iterador->siguiente;
        }
    }
    return NULL;
}

/*Metodo para mostarar los elementos*/
void mostrar() {
    int contador = 1;
    if (cabeza != NULL) {
        NodoLista *iterador = cabeza;
        while (iterador != NULL) {
            printf("%i,", iterador->dato);
            iterador = iterador ->siguiente;
            contador = contador + 1;
        }
    } else {
        printf("La lista esta vacia");

    }
}


/*MEtodo de Ordenamiento Burbuja*/

/*Consiste en un numero de iteraciones igual al tamaño de la lista de elementos,
 verifica con el siguiente del dato actual, si este es mayo: modifica el dato actual por el
 dato siguiente, y el actual lo convierte en el siguiente, caso contrario: continua con las
 iteracion es hasta concluir el ciclo*/
void metodoBurbuja() {
    int aux;
    int cambios = 0;
    int control = 1;
    int longitud = contar();
    int i;
    NodoLista* iterador;
    while (control == 1) {
        iterador = cabeza;
        cambios = 0;
        for (i = 1; i < longitud; i++) {
            if (iterador->siguiente->dato < iterador->dato) {
                aux = iterador->siguiente->dato;
                iterador->siguiente->dato = iterador->dato;
                iterador->dato = aux;
                cambios = 1;
            }
            iterador = iterador->siguiente;
        }
        if (cambios == 0) {
            control = 0;
        }
    }

}

/*Metodo de Ordenamiento QuickSort*/

/*Se toma un elemento x de una posición cualquiera del arregloen este caso el centro.
Se trata de ubicar a x en la posición correcta del arreglo, de tal forma que todos 
 * los elementos que se encuentran a su izquierda sean menores o iguales a x y todos 
 * los elementos que se encuentren a su derecha sean mayores o iguales a x.
Se repiten los pasos anteriores pero ahora para los conjuntos de datos que se encuentran 
 * a la izquierda y a la derecha de la posición correcta de x en el arreglo.*/

void metodoQuick(NodoLista* a, int primero, int ultimo) {
    int i, j, central;
    int pivote;
    central = (primero + ultimo) / 2;
    NodoLista* aa = buscar(central);
    pivote = aa -> dato;
    i = primero;
    j = ultimo;
    do {
        NodoLista* b = buscar(i);
        NodoLista* c = buscar(j);
        while (b ->dato < pivote) {
            i++;
            b = buscar(i);
        }
        while (c->dato > pivote) {
            j--;
            c = buscar(j);
        }
        if (i <= j) {
            int tmp;
            NodoLista* d = buscar(i);
            NodoLista* e = buscar(j);
            tmp = d ->dato;
            d->dato = e->dato;
            e->dato = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (primero < j) {
        metodoQuick(a, primero, j);
    }
    if (i < ultimo) {
        metodoQuick(a, i, ultimo);
    }
}

/*Metodo main, el orden de entrada en con sola es /.a.out "Ruta del alchivo a analizar"*/
int main(int argc, char* argv[]) {
    NodoArbol* raiz;
    raiz = NULL;
    int h;
    if (argc > 1) {
        FILE* archivo = NULL;
        char* nombreArchivo = argv[1];
        int a = 0;
        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL) {
            printf("\n ----Archivo no disponible \n\n");
        } else {
            clock_t start, end;
            double tiempo_ingresar_arbol;
            start = clock();
            while (feof(archivo) == 0) {
                fscanf(archivo, "%d\n", &a);
                insertar(&raiz, a, &h);
            }
            end = clock();
            tiempo_ingresar_arbol = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n Ingresar árbol - %lf segundos \n", tiempo_ingresar_arbol);
            fclose(archivo);






        }
    } else {
        printf("\n Se necestia la direccion de archivo de entrada \n\n");
    }


    return 0;
}

