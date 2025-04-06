#define LINKED_LIST_IMPLEMENTATION
#include "circular_linked_list.h"
#include <stdio.h>
#include <assert.h>

// Funciones para imprimir
void print_int(int value) { printf("%d", value); }
void print_char(char value) { printf("%c", value); }

// Función especial para verificar circularidad
void verify_circularity_int(List_int* list) {
    if (!list || !list->head) {
        printf("Lista vacía\n");
        return;
    }
    
    printf("Verificando circularidad: ");
    printf("Tail->next apunta a head? %s\n", 
           list->tail->next == list->head ? "Si" : "No");
}

int main() {
    // Pruebas con enteros
    List_int* nums = list_int_create();
    list_int_append(nums, 10);
    list_int_append(nums, 20);
    list_int_append(nums, 30);
    
    printf("--- Lista de enteros ---\n");
    list_int_print(nums, print_int); // Salida: [10, 20]
    verify_circularity_int(nums);    // Debe mostrar "Sí"
    
    // Destrucción usando MACRO
    LIST_DESTROY(nums);

    // Pruebas con caracteres
    List_char* chars = list_char_create();
    LIST_APPEND(chars, 'X');
    LIST_APPEND(chars, 'Y');
    LIST_APPEND(chars, 'Z');
    
    printf("\n--- Lista de caracteres ---\n");
    list_char_print(chars, print_char); // Salida: [X, Y]
    
    // Destrucción usando MACRO
    LIST_DESTROY(chars);
    
    return 0;
}