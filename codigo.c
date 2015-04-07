/* 
 * File:   codigo.c
 * Author: braian
 *
 * Created on 24 de marzo de 2015, 01:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define GNUPLOT_PATH "/usr/bin/gnuplot"

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
        printf(" ¡Se ha encontrado un número existente: %i, del metodo Inorden y Preorden!\n", digi);
        (*h) = 0;
    }
}

/*Metodo para Preorden*/
void preorden(NodoArbol* raiz) {
    if (raiz) {
        printf(" %i ", raiz->dato);
        preorden(raiz->Izq);
        preorden(raiz->Der);
    }
}

/*MEtodo para inorden*/
void inorden(NodoArbol* raiz) {
    if (raiz) {
        inorden(raiz -> Izq);
        printf(" %i ", raiz->dato);
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
            printf("%i ", iterador->dato);
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
void metodoBurbuja(int array[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
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

void metodoQuick(int array[], int primero, int ultimo) {
    int i, j, tmp, central;
    int pivote;
    central = (primero + ultimo) / 2;
    NodoLista* aa = buscar(central);
    pivote = primero;
    i = primero;
    j = ultimo;
    if (primero < ultimo) {
        // Asrignar el iníce del peimer elemento como el elemento pivote



        // Ordenamos de forma ascendente con QuickSort
        while (i < j) {
            while (array[i] <= array[pivote] && i < ultimo) {
                i++;
            }
            while (array[j] > array[pivote]) {
                j--;
            }

            if (i < j) {
                // Operación de Cambio
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }

        // Al final de la primera iteración, intercambiar el elemento pivote con el aux2
        tmp = array[pivote];
        array[pivote] = array[j];
        array[j] = tmp;

        // Llamada recursiva a QuickSort.
        metodoQuick(array, primero, j - 1);
        metodoQuick(array, j + 1, ultimo);
    }
}

/*Metodo para graficar con GNuplot*/
void graficar(char* graf, char* titulo) {
    //printf("%s graficas" ,graf);
    FILE *gp;
    gp = popen(GNUPLOT_PATH, "w");
    if (gp == NULL) {
        fprintf(stderr, "No se encuentra %s", GNUPLOT_PATH);
    } else {
        fprintf(gp, "set title '%s' \n", titulo);
        fprintf(gp, "%s \n", graf);
        fflush(gp);
        getchar();
        pclose(gp);
    }
}

/*Metodo main, el orden de entrada en con sola es /.a.out "Ruta del alchivo a analizar"*/
int main(int argc, char* argv[]) {
    NodoArbol* raiz;
    raiz = NULL;
    int array[2000000];
    int h;
    if (argc > 1) {


        FILE* archivo = NULL;
        char* nombreArchivo = argv[1];
        int a = 0;
        int i = 0;
        int n = 0;
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
            n = i;
            end = clock();
            tiempo_ingresar_arbol = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n Ingresar árbol - %lf segundos\n", tiempo_ingresar_arbol);
            fclose(archivo);
            /*Recorrido inorden*/
            clock_t start1, end1;
            double tiempo_recorrido_arbol;
            start1 = clock();
            printf(" Salida Inorden: \n");
            inorden(raiz);
            end1 = clock();

            tiempo_recorrido_arbol = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
            printf(" \n Recorrido arbol - %lf segundos", tiempo_recorrido_arbol);

            /*Ordenamiento burbuja*/
            i = 0;
            int valorBurUltimo = 0;

            archivo = fopen(nombreArchivo, "r");
            while (feof(archivo) == 0) {
                fscanf(archivo, "%d\n", &a);
                insertarDato(a);
                array[i] = a;
                i++;
                valorBurUltimo = a;
            }
            n = i;
            clock_t start2, end2;
            double tiempo_burbuja;
            start2 = clock();
            metodoBurbuja(array, n);

            end2 = clock();
            tiempo_burbuja = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
            printf("\n\n Ordenacion Burbuja - %lf segundos\n", tiempo_burbuja);
            printf(" Salida del Metodo Ordenacion Burbuja: \n");

            for (i = 0; i < n; i++) {
                printf(" %i ", array[i]);

            }
            fclose(archivo);
            cabeza = fin = NULL;
            indice = 0;

            i = 0;
            archivo = fopen(nombreArchivo, "r");
            while (feof(archivo) == 0) {
                fscanf(archivo, "%d\n", &a);
                insertarDato(a);
                array[i] = a;
                i++;
            }
            clock_t start3, end3;
            double tiempo_quicksort;
            start3 = clock();
            metodoQuick(array, 0, fin->id);
            end3 = clock();
            tiempo_quicksort = ((double) (end3 - start3)) / CLOCKS_PER_SEC;
            printf("\n\n Ordenacion Quicksort - %lf segundos\n", tiempo_quicksort);
            printf(" Salida del Metodo Ordenacion Quicksort: \n");
            for (i = 0; i < n; i++) {
                printf(" %i ", array[i]);
            }

            printf("\n\n");
            fclose(archivo);
            char rango[80];
            char rangoBur[80];

            sprintf(rango, "%f", tiempo_recorrido_arbol);
            sprintf(rangoBur, "%f", valorBurUltimo);
            char* tmp11 = " plot [0:";
            char* tmp12 = rangoBur;
            char* tmp13 = "][0:";
            char* tmp14 = rango;
            printf("\n Grafica de comparacíon de tiempos:\n");
            char* tmp2 = "]log(x) title 'Caso Tipico log(n) ',log(x) title 'Caso Ideal log(n) ' ,x title 'Maximo Teorico n ' ,  ";
            char TInOrden[900];
            /*Se en ia como parametro el tiempo en que se reorre el arbol de forma inorden*/
            sprintf(TInOrden, "%2.13f", tiempo_recorrido_arbol);
            char* s1 = malloc(sizeof (char)*(2 * strlen(TInOrden) + strlen(tmp2) + 10));
            strcpy(s1, tmp11);
            strcat(s1, tmp12);
            strcat(s1, tmp13);
            strcat(s1, tmp14);
            strcat(s1, tmp2);
            strcat(s1, TInOrden);
            char* titulo = "Metodo Inorden";
            printf("\n Tiempo del Metodo Inorden: %2.13f segundos", tiempo_recorrido_arbol);
            graficar(s1, titulo);
            /*----------------------------------------------------------------------------------------------------------*/
            /*caso tipico, caso ideal (mejor), maximo teorico (peor caso)*/
             sprintf(rango, "%f", tiempo_burbuja);
            sprintf(rangoBur, "%f", valorBurUltimo);
            char* tmp15 = " plot [0:";
            char* tmp16 = rangoBur;
            char* tmp17 = "][0:";
            char* tmp18 = rango;
            char* tmp3 = "] x*x title 'Caso Tipico n^2 ', x title 'Caso Ideal n ', x*x title 'Maximo Teorico n^2 ', ";
            char TBurbuja[900];
            /*Se envia como parametro el tiempo del metodo de burbuja*/
            sprintf(TBurbuja, "%2.13f", tiempo_burbuja);
            char* s2 = malloc(sizeof (char)*(2 * strlen(TBurbuja) + strlen(tmp3) + 10));
            
            strcpy(s2, tmp15);
            strcat(s2, tmp16);
            strcat(s2, tmp17);
            strcat(s2, tmp18);
            strcat(s2, tmp3);
            strcat(s2, TBurbuja);
            printf("\n Tiempo del Metodo Burbuja: %2.13f segundos", tiempo_burbuja);
            titulo = "Metodo Ordenamiento Burbuja";
            graficar(s2, titulo);
            /*----------------------------------------------------------------------------------------------------------*/


            // Convertimos a char nuestras variables
            sprintf(rango, "%f", tiempo_burbuja);
            sprintf(rangoBur, "%f", valorBurUltimo);
            char* tmp7 = " plot [0:";
            char* tmp8 = rangoBur;
            char* tmp9 = "][0:";
            char* tmp10 = rango;


            char* tmp4 = "]x*log(x) title 'Caso Tipico n*log(n) ', x*log(x) title 'Caso Ideal  n*log(n) ', x*x title 'Maximo Teorico n^2 ', ";
            char TQuicksort[900];
            /*Se envia como parametro el tiempo del metodo Quicksort*/
            sprintf(TQuicksort, "%2.13f", tiempo_quicksort);
            char* s3 = malloc(sizeof (char)*(2 * strlen(TQuicksort) + strlen(tmp4) + 10));
            strcpy(s3, tmp7);
            strcat(s3, tmp8);

            strcat(s3, tmp9);
            strcat(s3, tmp10);

            strcat(s3, tmp4);
            strcat(s3, TQuicksort);
            
            printf("\n Tiempo del Metodo QuickSort: %2.13f segundos", tiempo_quicksort);
            titulo = "Metodo Ordenamiento Quicksort";
            graficar(s3, titulo);
        }
    } else {
        printf("\n Debe ingresar la dirección del archivo a Ordenar despues del archivo de compilación \n\n");
    }


    return 0;
}

