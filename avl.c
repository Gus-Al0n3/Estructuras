#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    int altura;
    struct Nodo* izquierdo;
    struct Nodo* derecho;
} Nodo;

// Función para obtener la altura de un nodo
int obtenerAltura(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

// Función para obtener el máximo entre dos números
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Función para crear un nuevo nodo del árbol AVL
Nodo* crearNodo(int dato) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->dato = dato;
    nodo->altura = 1;
    nodo->izquierdo = NULL;
    nodo->derecho = NULL;
    return nodo;
}

// Función para realizar una rotación hacia la derecha en un nodo del árbol AVL
Nodo* rotarDerecha(Nodo* nodo) {
    Nodo* nodoIzquierdo = nodo->izquierdo;
    Nodo* nodoDerechoDelIzquierdo = nodoIzquierdo->derecho;

    // Realizar la rotación
    nodoIzquierdo->derecho = nodo;
    nodo->izquierdo = nodoDerechoDelIzquierdo;

    // Actualizar las alturas
    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    nodoIzquierdo->altura = 1 + maximo(obtenerAltura(nodoIzquierdo->izquierdo), obtenerAltura(nodoIzquierdo->derecho));

    return nodoIzquierdo;
}

// Función para realizar una rotación hacia la izquierda en un nodo del árbol AVL
Nodo* rotarIzquierda(Nodo* nodo) {
    Nodo* nodoDerecho = nodo->derecho;
    Nodo* nodoIzquierdoDelDerecho = nodoDerecho->izquierdo;

    // Realizar la rotación
    nodoDerecho->izquierdo = nodo;
    nodo->derecho = nodoIzquierdoDelDerecho;

    // Actualizar las alturas
    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    nodoDerecho->altura = 1 + maximo(obtenerAltura(nodoDerecho->izquierdo), obtenerAltura(nodoDerecho->derecho));

    return nodoDerecho;
}

// Función para obtener el factor de balance de un nodo
int obtenerFactorBalance(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}

// Función para insertar un valor en el árbol AVL
Nodo* insertar(Nodo* nodo, int dato) {
    // Paso 1: Realizar la inserción en un árbol binario de búsqueda
    if (nodo == NULL) {
        return crearNodo(dato);
    }

    if (dato < nodo->dato) {
        nodo->izquierdo = insertar(nodo->izquierdo, dato);
    } else if (dato > nodo->dato) {
        nodo->derecho = insertar(nodo->derecho, dato);
    } else {
        // No se permiten elementos duplicados
        return nodo;
    }

    // Paso 2: Actualizar la altura del nodo actual
    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    // Paso 3: Obtener el factor de balance del nodo actual
    int factorBalance = obtenerFactorBalance(nodo);

    // Paso 4: Realizar las rotaciones necesarias según el factor de balance
    // Rotación hacia la izquierda
    if (factorBalance > 1 && dato < nodo->izquierdo->dato) {
        return rotarDerecha(nodo);
    }

    // Rotación hacia la derecha
    if (factorBalance < -1 && dato > nodo->derecho->dato) {
        return rotarIzquierda(nodo);
    }

    // Rotación doble hacia la izquierda
    if (factorBalance > 1 && dato > nodo->izquierdo->dato) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    // Rotación doble hacia la derecha
    if (factorBalance < -1 && dato < nodo->derecho->dato) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    // Retornar el nodo actual sin modificaciones
    return nodo;
}

// Función para encontrar el nodo con el valor mínimo en un árbol dado
Nodo* encontrarMinimo(Nodo* nodo) {
    Nodo* actual = nodo;

    while (actual->izquierdo != NULL) {
        actual = actual->izquierdo;
    }

    return actual;
}

// Función para eliminar un valor del árbol AVL
Nodo* eliminar(Nodo* nodo, int dato) {
    // Paso 1: Realizar la eliminación en un árbol binario de búsqueda
    if (nodo == NULL) {
        return nodo;
    }

    if (dato < nodo->dato) {
        nodo->izquierdo = eliminar(nodo->izquierdo, dato);
    } else if (dato > nodo->dato) {
        nodo->derecho = eliminar(nodo->derecho, dato);
    } else {
        // El nodo actual es el nodo a eliminar

        // Nodo con solo un hijo o sin hijos
        if (nodo->izquierdo == NULL || nodo->derecho == NULL) {
            Nodo* hijo = (nodo->izquierdo != NULL) ? nodo->izquierdo : nodo->derecho;

            // Caso: Nodo sin hijos
            if (hijo == NULL) {
                hijo = nodo;
                nodo = NULL;
            } else { // Caso: Nodo con un solo hijo
                *nodo = *hijo;
            }

            free(hijo);
        } else {
            // Nodo con dos hijos: encontrar el sucesor en orden (valor mínimo en el subárbol derecho)
            Nodo* sucesor = encontrarMinimo(nodo->derecho);

            // Copiar el valor del sucesor al nodo actual
            nodo->dato = sucesor->dato;

            // Eliminar el sucesor del subárbol derecho
            nodo->derecho = eliminar(nodo->derecho, sucesor->dato);
        }
    }

    // Si el árbol tiene un solo nodo, no se requieren más operaciones
    if (nodo == NULL) {
        return nodo;
    }

    // Paso 2: Actualizar la altura del nodo actual
    nodo->altura = 1 + maximo(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    // Paso 3: Obtener el factor de balance del nodo actual
    int factorBalance = obtenerFactorBalance(nodo);

    // Paso 4: Realizar las rotaciones necesarias según el factor de balance
    // Rotación hacia la izquierda
    if (factorBalance > 1 && obtenerFactorBalance(nodo->izquierdo) >= 0) {
        return rotarDerecha(nodo);
    }

    // Rotación hacia la derecha
    if (factorBalance < -1 && obtenerFactorBalance(nodo->derecho) <= 0) {
        return rotarIzquierda(nodo);
    }

    // Rotación doble hacia la izquierda
    if (factorBalance > 1 && obtenerFactorBalance(nodo->izquierdo) < 0) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    // Rotación doble hacia la derecha
    if (factorBalance < -1 && obtenerFactorBalance(nodo->derecho) > 0) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    // Retornar el nodo actual sin modificaciones
    return nodo;
}

// Función para imprimir la estructura del árbol binario
void imprimirArbol(Nodo* nodo, int nivel) {
    if (nodo == NULL) {
        return;
    }

    // Imprimir espacios en blanco según el nivel del nodo
    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }

    // Imprimir el valor del nodo
    printf("└── %d\n", nodo->dato);

    // Llamar recursivamente a la función para los subárboles izquierdo y derecho
    imprimirArbol(nodo->izquierdo, nivel + 1);
    imprimirArbol(nodo->derecho, nivel + 1);
}

// Función para realizar el recorrido preorden del árbol
void preorden(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }

    printf("%d ", nodo->dato);
    preorden(nodo->izquierdo);
    preorden(nodo->derecho);
}

// Función para realizar el recorrido enorden del árbol
void enorden(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }

    enorden(nodo->izquierdo);
    printf("%d ", nodo->dato);
    enorden(nodo->derecho);
}

// Función para realizar el recorrido postorden del árbol
void postorden(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }

    postorden(nodo->izquierdo);
    postorden(nodo->derecho);
    printf("%d ", nodo->dato);
}

// Función para buscar un valor en el árbol AVL
int buscar(Nodo* nodo, int dato) {
    if (nodo == NULL) {
        return 0;
    }

    if (dato == nodo->dato) {
        return 1;
    } else if (dato < nodo->dato) {
        return buscar(nodo->izquierdo, dato);
    } else {
        return buscar(nodo->derecho, dato);
    }
}

int main() {
    Nodo* raiz = NULL;
    int opcion, dato;

    do {
        printf("Menu:\n");
        printf("1. Insertar un valor\n");
        printf("2. Eliminar un valor\n");
        printf("3. Imprimir el arbol\n");
        printf("4. Recorrido preorden\n");
        printf("5. Recorrido enorden\n");
        printf("6. Recorrido postorden\n");
        printf("7. Buscar un valor\n");
        printf("8. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el valor a insertar: ");
                scanf("%d", &dato);
                raiz = insertar(raiz, dato);
                printf("Valor insertado correctamente.\n");
                break;
            case 2:
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &dato);
                raiz = eliminar(raiz, dato);
                printf("Valor eliminado correctamente.\n");
                break;
            case 3:
                imprimirArbol(raiz, 0);
                break;
            case 4:
                printf("Recorrido preorden: ");
                preorden(raiz);
                printf("\n");
                break;
            case 5:
                printf("Recorrido enorden: ");
                enorden(raiz);
                printf("\n");
                break;
            case 6:
                printf("Recorrido postorden: ");
                postorden(raiz);
                printf("\n");
                break;
            case 7:
                printf("Ingrese el valor a buscar: ");
                scanf("%d", &dato);
                if (buscar(raiz, dato)) {
                    printf("El valor se encuentra en el arbol.\n");
                } else {
                    printf("El valor no se encuentra en el arbol.\n");
                }
                break;
            case 8:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Por favor, intente nuevamente.\n");
        }
    } while (opcion != 8);

    return 0;
}

