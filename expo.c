#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

// Declaración de funciones
void print_menu();
void set_color(char *color);
int getch();
int binary_search(int array[], int size, int target);

// Función principal
int main() {
    // Declaración de variables
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Arreglo de enteros ordenados
    int size = sizeof(array) / sizeof(array[0]); // Tamaño del arreglo
    int target, index;

    // Impresión del menú
    print_menu();

    // Lectura del objetivo
    printf("\nIngrese un número para buscar: ");
    scanf("%d", &target);

    // Búsqueda binaria
    index = binary_search(array, size, target);

    // Impresión del resultado
    if (index != -1) {
        set_color("32"); // Color verde
        printf("\nEl número %d se encuentra en la posición %d\n", target, index);
    } else {
        set_color("31"); // Color rojo
        printf("\nEl número %d no se encuentra en el arreglo\n", target);
    }

    return 0;
}

// Función para imprimir el menú
void print_menu() {
    system("clear"); // Limpiar pantalla

    set_color("31"); 
    printf("==========   CODIGO MORTAL   ==========\n");
    set_color("34"); // Color azul
    printf("========== BUSQUEDA BINARIA ==========\n");
    set_color("0"); // Color predeterminado
    printf("Ingrese un número del 1 al 10 para buscar en el arreglo.\n");

}

// Función para establecer el color de la consola
void set_color(char *color) {
    printf("\033[%sm", color);
}

// Función para leer una tecla sin presionar Enter
int getch() {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

// Función de búsqueda binaria
int binary_search(int array[], int size, int target) {
    int left = 0; // Índice izquierdo del subarreglo
    int right = size - 1; // Índice derecho del subarreglo
    int mid; // Índice medio del subarreglo

    while (left <= right) {
        mid = (left + right) / 2; // Calcular índice medio

        if (array[mid] == target) { // Si el valor medio es igual al objetivo, devolver su índice
            return mid;
        } else if (array[mid] < target) { // Si el valor medio es menor al objetivo, actualizar el índice izquierdo
            left = mid + 1;
        } else { // Si el valor medio es mayor al objetivo, actualizar el índice derecho
            right = mid - 1;
        }
    }

    return -1; // Si no se encuentra el objetivo, devolver -1
}
