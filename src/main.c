#define LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"
#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

void print_char(char value) {
    printf("%c", value);
}

bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    List_int* nums = list_int_create();
    list_int_append(nums, 10);
    list_int_append(nums, 20);
    
    printf("Lista: ");
    list_int_print(nums, print_int); // Usar función concreta para evitar errores
    
    LIST_DESTROY(nums);
    
    List_char *chars = list_char_create();
    LIST_APPEND(chars, 'a');
    LIST_APPEND(chars, 'b');
    LIST_APPEND(chars, 'c');
    LIST_APPEND(chars, 'd');
    LIST_APPEND(chars, 'e');

    printf("Lista: ");
    list_char_print(chars, print_char);

    LIST_DESTROY(chars);
    return 0;
}