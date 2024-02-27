#include <stdio.h>

#define MAX_SIZE 100 //Representa El tama�o m�ximo de los arreglos

// Funci�n para mostrar un arreglo
void displayArray(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Funci�n para insertar un elemento en un arreglo
void insertElement(int arr[], int *size, int element, int position) {
    if (*size >= MAX_SIZE) {
        printf("El arreglo est� lleno. No se puede insertar m�s elementos.\n");
        return;
    }
    
    if (position < 0 || position > *size) {
        printf("Posicion inv�lida.\n");
        return;
    }
    
    for (int i = *size; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    
    arr[position] = element;
    (*size)++;
    printf("Elemento insertado con �xito.\n");
}

// Funci�n para eliminar un elemento de un arreglo
void deleteElement(int arr[], int *size, int position) {
    if (*size == 0) {
        printf("El arreglo est� vac�o. No se puede eliminar ning�n elemento.\n");
        return;
    }
    
    if (position < 0 || position >= *size) {
        printf("Posicion inv�lida.\n");
        return;
    }
    
    for (int i = position; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    
    (*size)--;
    printf("Elemento eliminado con �xito.\n");
}

// Funci�n para fusionar dos arreglos
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int result[], int *resultSize) {
    *resultSize = size1 + size2;
    for (int i = 0; i < size1; i++) {
        result[i] = arr1[i];
    }
    for (int i = 0; i < size2; i++) {
        result[size1 + i] = arr2[i];
    }
    printf("Los arreglos han sido fusionados con �xito.\n");
}

int main() {
    int arr1[MAX_SIZE], arr2[MAX_SIZE], result[MAX_SIZE];
    int size1 = 0, size2 = 0, resultSize = 0;
    int choice, element, position;
    
    while (1) {
        printf("\nMen�:\n");
        printf("1. Insertar elemento en arreglo\n");
        printf("2. Eliminar elemento de arreglo\n");
        printf("3. Fusionar arreglos\n");
        printf("4. Mostrar arreglos\n");
        printf("5. Salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Ingrese el elemento a insertar: ");
                scanf("%d", &element);
                printf("Ingrese la posici�n de inserci�n: ");
                scanf("%d", &position);
                insertElement(arr1, &size1, element, position);
                break;
            case 2:
                printf("Ingrese la posici�n del elemento a eliminar: ");
                scanf("%d", &position);
                deleteElement(arr1, &size1, position);
                break;
            case 3:
                printf("Ingrese los elementos del primer arreglo (terminar con -1):\n");
                for (int i = 0; ; i++) {
                    scanf("%d", &element);
                    if (element == -1) break;
                    arr1[i] = element;
                    size1++;
                }
                printf("Ingrese los elementos del segundo arreglo (terminar con -1):\n");
                for (int i = 0; ; i++) {
                    scanf("%d", &element);
                    if (element == -1) break;
                    arr2[i] = element;
                    size2++;
                }
                mergeArrays(arr1, size1, arr2, size2, result, &resultSize);
                break;
            case 4:
                printf("Arreglo 1: ");
                displayArray(arr1, size1);
                printf("Arreglo 2: ");
                displayArray(arr2, size2);
                printf("Resultado de la fusi�n: ");
                displayArray(result, resultSize);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opci�n inv�lida. Por favor, ingrese una opci�n v�lida.\n");
        }
    }
    
    return 0;
}

