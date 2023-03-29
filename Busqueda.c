/*Explicación:

1 En la función busqueda_binaria, se reciben tres parámetros: el arreglo en el que se va a buscar, el tamaño del arreglo y el elemento que se desea buscar.

2 Se inicializan dos variables, izq y der, que indican los índices izquierdo y derecho del segmento del arreglo en el que se va a buscar. Al principio, izq es el índice 0 y der es el índice n - 1, siendo n el tamaño del arreglo.

3 Se utiliza un bucle while para realizar la búsqueda. Mientras izq sea menor o igual a der, se sigue buscando.

4 Se calcula el índice medio del segmento actual, utilizando la fórmula medio = izq + (der - izq) / 2. Esta fórmula garantiza que medio sea siempre un número entero.

5 Se compara el elemento del arreglo en la posición medio con el elemento que se está buscando. Si son iguales, se ha encontrado el elemento y se retorna la posición medio.

6 Si el elemento del arreglo en la posición medio es menor que el elemento buscado, significa que el elemento buscado está en el segmento de la derecha de medio. Por lo tanto, se actualiza izq a medio + 1.
7 Si el elemento del arreglo en la posición medio es mayor que el elemento buscado, significa que el elemento buscado está en el segmento de la izquierda de medio. Por lo tanto, se actualiza der a medio - 1.

8 Si el elemento no se ha encontrado después de todo el proceso, se retorna -1.

9 En la función main, se crea un arreglo ordenado de números del 1 al 10. Se obtiene su tamaño y se elige un elemento a buscar (en este caso, el número 7).

10 Se llama a la función busqueda_binaria con el arreglo, su tamaño y el elemento*/



#include <stdio.h>

/* Función que implementa la búsqueda binaria. Recibe un arreglo, su tamaño y el elemento a buscar.
   Retorna la posición del elemento si se encuentra en el arreglo, o -1 si no se encuentra. */
int busqueda_binaria(int arr[], int n, int x) {
    // Se inicializan los índices izquierdo y derecho del segmento del arreglo en el que se va a buscar.
    int izq = 0;
    int der = n - 1;
    
    // Se sigue buscando mientras el índice izquierdo sea menor o igual al derecho.
    while (izq <= der) {
        // Se calcula el índice medio del segmento actual.
        int medio = izq + (der - izq) / 2;
        
        // Si el elemento en la posición media es igual al elemento buscado, se ha encontrado y se retorna la posición.
        if (arr[medio] == x) {
            return medio;
        }
        // Si el elemento en la posición media es menor que el elemento buscado, se busca en el segmento de la derecha de medio.
        else if (arr[medio] < x) {
            izq = medio + 1;
        }
        // Si el elemento en la posición media es mayor que el elemento buscado, se busca en el segmento de la izquierda de medio.
        else {
            der = medio - 1;
        }
    }
    // Si el elemento no se encuentra en el arreglo, se retorna -1.
    return -1;
}

int main() {
    // Se crea un arreglo ordenado de números del 1 al 10.
    int arreglo[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Se obtiene el tamaño del arreglo dividiendo el tamaño total del arreglo entre el tamaño de cada elemento.
    int n = sizeof(arreglo) / sizeof(arreglo[0]);
    
    // Se elige un elemento a buscar (en este caso, el número 7).
    int x = 7;
    
    // Se llama a la función de búsqueda binaria y se almacena el resultado.
    int resultado = busqueda_binaria(arreglo, n, x);
    
    // Si el resultado es -1, el elemento no se encuentra en el arreglo.
    if (resultado == -1) {
        printf("El elemento no se encuentra en el arreglo.\n");
    }
    // Si el resultado es diferente de -1, el elemento se encuentra en la posición retornada por la función de búsqueda binaria.
    else {
        printf("El elemento se encuentra en la posición %d del arreglo.\n", resultado);
    }
    
    return 0;
}
