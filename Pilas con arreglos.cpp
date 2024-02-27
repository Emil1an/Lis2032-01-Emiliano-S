#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para usar la función isdigit

#define MAX_AUTOS 3
#define MAX_CARACTERISTICAS 100

typedef struct {
    char marca[MAX_CARACTERISTICAS];
    char placas[MAX_CARACTERISTICAS];
    char modelo[MAX_CARACTERISTICAS]; // Cambiado a char[]
    char caracteristicas[MAX_CARACTERISTICAS];
} Auto;

typedef struct Nodo {
    Auto autoEntrante;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *frente;
    Nodo *final;
    int tamano;
} ColaAutos;

void inicializarCola(ColaAutos *cola) {
    cola->frente = NULL;
    cola->final = NULL;
    cola->tamano = 0;
}

int estaVacia(ColaAutos *cola) {
    return cola->tamano == 0;
}

int estaLlena(ColaAutos *cola) {
    return cola->tamano >= MAX_AUTOS;
}

void encolar(ColaAutos *cola, Auto autoNuevo) {
    if (estaLlena(cola)) {
        printf("El estacionamiento está lleno. No se pueden agregar más autos.\n");
        return;
    }

    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo auto.\n");
        return;
    }

    nuevoNodo->autoEntrante = autoNuevo;
    nuevoNodo->siguiente = NULL;

    if (estaVacia(cola)) {
        cola->frente = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
    }

    cola->final = nuevoNodo;
    cola->tamano++;
}

void desencolar(ColaAutos *cola) {
    if (estaVacia(cola)) {
        printf("No hay autos en el estacionamiento para sacar.\n");
        return;
    }

    Nodo *nodoAEliminar = cola->frente;
    printf("Se ha sacado el siguiente auto del estacionamiento:\n");
    printf("Marca: %s, Placas: %s, Modelo: %s, Características: %s\n",
           nodoAEliminar->autoEntrante.marca, nodoAEliminar->autoEntrante.placas,
           nodoAEliminar->autoEntrante.modelo, nodoAEliminar->autoEntrante.caracteristicas);

    cola->frente = cola->frente->siguiente;
    free(nodoAEliminar);
    cola->tamano--;
}

void imprimirCantidadAutos(ColaAutos *cola) {
    printf("Numero de autos en el estacionamiento: %d\n", cola->tamano);
}

void imprimirListaAutos(ColaAutos *cola) {
    printf("Lista de autos en el estacionamiento:\n");
    Nodo *actual = cola->frente;
    while (actual != NULL) {
        printf("Marca: %s, Placas: %s, Modelo: %s, Caracteristicas: %s\n",
               actual->autoEntrante.marca, actual->autoEntrante.placas,
               actual->autoEntrante.modelo, actual->autoEntrante.caracteristicas);
        actual = actual->siguiente;
    }
}

void imprimirPrimerAuto(ColaAutos *cola) {
    if (!estaVacia(cola)) {
        printf("Primer auto que ha entrado:\n");
        printf("Marca: %s, Placas: %s, Modelo: %s, Características: %s\n",
               cola->frente->autoEntrante.marca, cola->frente->autoEntrante.placas,
               cola->frente->autoEntrante.modelo, cola->frente->autoEntrante.caracteristicas);
    } else {
        printf("No hay autos en el estacionamiento.\n");
    }
}

void imprimirUltimoAuto(ColaAutos *cola) {
    if (!estaVacia(cola)) {
        printf("Ultimo auto que ha entrado:\n");
        printf("Marca: %s, Placas: %s, Modelo: %s, Características: %s\n",
               cola->final->autoEntrante.marca, cola->final->autoEntrante.placas,
               cola->final->autoEntrante.modelo, cola->final->autoEntrante.caracteristicas);
    } else {
        printf("No hay autos en el estacionamiento.\n");
    }
}

int tieneDigito(const char *cadena) {
    // Verifica si la cadena contiene al menos un dígito
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (isdigit(cadena[i])) {
            return 1; // La cadena contiene al menos un dígito
        }
    }
    return 0; // La cadena no contiene ningún dígito
}

int main() {
    ColaAutos cola;
    inicializarCola(&cola);
    char opcion;

    do {
        printf("\nMenú:\n");
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
            case 'a': {
                if (estaLlena(&cola)) {
                    printf("El estacionamiento está lleno. No se pueden agregar más autos.\n");
                    break;
                }
                
                Auto nuevoAuto;
                printf("Ingrese la marca del auto: ");
                scanf("%s", nuevoAuto.marca);
                printf("Ingrese las placas del auto: ");
                scanf("%s", nuevoAuto.placas);
                printf("Ingrese el modelo del auto: ");
                scanf("%s", nuevoAuto.modelo);
                // Verificamos si el modelo tiene al menos un dígito
                if (!tieneDigito(nuevoAuto.modelo)) {
                    printf("El modelo debe contener al menos un dígito. Por favor, inténtelo de nuevo.\n");
                    break;
                }
                printf("Ingrese las caracteristicas del auto: ");
                scanf("%s", nuevoAuto.caracteristicas);
                encolar(&cola, nuevoAuto);
                printf("Auto agregado exitosamente.\n");
                break;
            }
            case 'b':
                desencolar(&cola);
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
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, seleccione una opción valida.\n");
        }
    } while (opcion != 'g');

    return 0;
}

