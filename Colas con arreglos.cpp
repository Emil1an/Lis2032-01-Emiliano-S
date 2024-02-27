#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERISTICAS 100
#define MAX_AUTOS 3  // Restricción de 3 autos en el estacionamiento

// Definición de la estructura del auto
typedef struct Auto {
    char marca[50];
    char placas[20];
    char modelo[MAX_CARACTERISTICAS]; // Cambiado a char[]
    char caracteristicas[MAX_CARACTERISTICAS];
    struct Auto* siguiente;
} Auto;

// Definicion de la estructura de la cola
typedef struct {
    Auto* frente;
    Auto* final;
    int tamano;
} ColaAutos;

// Funcion para inicializar la cola
void inicializarCola(ColaAutos* cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->tamano = 0;
}

// Funcion para verificar si la cola está vacía
int estaVacia(ColaAutos* cola) {
    return cola->tamano == 0;
}

// Funcion para verificar si la cola está llena
int estaLlena(ColaAutos* cola) {
    return cola->tamano >= MAX_AUTOS;
}

// Funcion para agregar un auto a la cola
void agregarAuto(ColaAutos* cola, char marca[], char placas[], char modelo[], char caracteristicas[]) {
    if (estaLlena(cola)) {
        printf("El estacionamiento está lleno. No se pueden agregar más autos.\n");
        return;
    }

    Auto* nuevoAuto = (Auto*)malloc(sizeof(Auto));
    if (nuevoAuto == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo auto.\n");
        return;
    }
    strcpy(nuevoAuto->marca, marca);
    strcpy(nuevoAuto->placas, placas);
    strcpy(nuevoAuto->modelo, modelo);
    strcpy(nuevoAuto->caracteristicas, caracteristicas);
    nuevoAuto->siguiente = NULL;

    if (estaVacia(cola)) {
        cola->frente = nuevoAuto;
    } else {
        cola->final->siguiente = nuevoAuto;
    }
    cola->final = nuevoAuto;
    cola->tamano++;
}

// Funcion para sacar un auto de la cola
void sacarAuto(ColaAutos* cola) {
    if (estaVacia(cola)) {
        printf("No hay autos en el estacionamiento para sacar.\n");
        return;
    }

    Auto* autoActual = cola->frente;
    Auto* autoAnterior = NULL;
    while (autoActual->siguiente != NULL) {
        autoAnterior = autoActual;
        autoActual = autoActual->siguiente;
    }

    printf("Se ha sacado el siguiente auto del estacionamiento:\n");
    printf("Marca: %s, Placas: %s, Modelo: %s, Caracteristicas: %s\n",
           autoActual->marca, autoActual->placas, autoActual->modelo, autoActual->caracteristicas);

    free(autoActual);

    if (autoAnterior != NULL) {
        autoAnterior->siguiente = NULL;
        cola->final = autoAnterior;
    } else {
        cola->frente = NULL;
        cola->final = NULL;
    }
    cola->tamano--;
}

// Funcion para imprimir el numero de autos en la cola
void imprimirCantidadAutos(ColaAutos* cola) {
    printf("Numero de autos en el estacionamiento: %d\n", cola->tamano);
}

// Funcion para imprimir la lista de autos en orden
void imprimirListaAutos(ColaAutos* cola) {
    printf("Lista de autos en el estacionamiento:\n");
    Auto* actual = cola->frente;
    while (actual != NULL) {
        printf("Marca: %s, Placas: %s, Modelo: %s, Caracteristicas: %s\n", actual->marca, actual->placas, actual->modelo, actual->caracteristicas);
        actual = actual->siguiente;
    }
}

// Funcion para imprimir el primer auto que entrar
void imprimirPrimerAuto(ColaAutos* cola) {
    if (!estaVacia(cola)) {
        printf("Primer auto que ha entrado:\n");
        printf("Marca: %s, Placas: %s, Modelo: %s, Caracteristicas: %s\n", cola->frente->marca, cola->frente->placas, cola->frente->modelo, cola->frente->caracteristicas);
    } else {
        printf("No hay autos en el estacionamiento.\n");
    }
}

// Funcion para imprimir el último auto que entra
void imprimirUltimoAuto(ColaAutos* cola) {
    if (!estaVacia(cola)) {
        printf("Ultimo auto que ha entrado:\n");
        printf("Marca: %s, Placas: %s, Modelo: %s, Caracteristicas: %s\n", cola->final->marca, cola->final->placas, cola->final->modelo, cola->final->caracteristicas);
    } else {
        printf("No hay autos en el estacionamiento.\n");
    }
}

int main() {
    ColaAutos cola;
    inicializarCola(&cola);
    char marca[50];
    char placas[20];
    char modelo[MAX_CARACTERISTICAS];
    char caracteristicas[MAX_CARACTERISTICAS];
    char opcion;

    do {
        printf("\nMenu:\n");
        printf("a) Agregar un auto\n");
        printf("b) Sacar un auto\n");
        printf("c) Imprimir numero de autos en el estacionamiento\n");
        printf("d) Imprimir lista de autos en el estacionamiento\n");
        printf("e) Imprimir primer auto que ha entrado\n");
        printf("f) Imprimir ultimo auto que ha entrado\n");
        printf("g) Salir\n");
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a':
                printf("Ingrese la marca del auto: ");
                scanf("%s", marca);
                printf("Ingrese las placas del auto: ");
                scanf("%s", placas);
                printf("Ingrese el modelo del auto: ");
                scanf("%s", modelo);
                printf("Ingrese las caracteristicas del auto: ");
                scanf("%s", caracteristicas);
                agregarAuto(&cola, marca, placas, modelo, caracteristicas);
                break;
            case 'b':
                sacarAuto(&cola);
                break;
            case 'c':
                imprimirCantidadAutos(&cola);
                break;
            case 'd':
                imprimirListaAutos(&cola);
                break;
            case 'e':
                imprimirPrimerAuto(&cola);
                break;
            case 'f':
                imprimirUltimoAuto(&cola);
                break;
            case 'g':
                printf("Gracias por usar el programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, seleccione una opcion valida.\n");
        }
    } while (opcion != 'g');

    return 0;
}


