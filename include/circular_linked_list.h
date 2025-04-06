#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Macro para declarar estructuras y prototipos
#define LIST_CREATE(TYPE) \
    _Generic((TYPE){0}, \
        int:    list_int_create, \
        float:  list_float_create, \
        char:   list_char_create \
    )()

#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##_create(TYPE); \
    Node_##TYPE* node_##TYPE##_destroy(Node_##TYPE*); \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos); \
    bool list_##TYPE##_get(const List_##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##_length(const List_##TYPE* list); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)); \
    bool list_##TYPE##_contains(const List_##TYPE* list, TYPE data); \
    bool list_##TYPE##_remove(List_##TYPE* list, TYPE data);

// ----------------------------
// Macro para implementación (Circular)
// ----------------------------
#define LIST_DESTROY(list) _Generic((list), \
    List_int*:    list_int_destroy, \
    List_float*:  list_float_destroy, \
    List_char*:   list_char_destroy \
)(list)

#define LIST_APPEND(list, value) _Generic((list), \
    List_int*:    list_int_append, \
    List_float*:  list_float_append, \
    List_char*:   list_char_append \
)(list, value)
#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data) { \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        if (!new_node) return NULL; \
        new_node->data = data; \
        new_node->next = new_node; /* Circular: se apunta a sí mismo */ \
        return new_node; \
    } \
    \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (!list || !list->head) return; \
        Node_##TYPE* current = list->head->next; \
        while (current != list->head) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list->head); \
        free(list); \
    } \
    \
    bool list_##TYPE##_insert(List_##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        \
        if (list->length == 0) { /* Lista vacía */ \
            list->head = list->tail = new_node; \
        } else if (pos == 0) { /* Insertar al inicio */ \
            new_node->next = list->head; \
            list->head = new_node; \
            list->tail->next = new_node; /* Mantener circularidad */ \
        } else if (pos == list->length) { /* Insertar al final */ \
            new_node->next = list->head; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { /* Insertar en posición intermedia */ \
            Node_##TYPE* prev = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                prev = prev->next; \
            } \
            new_node->next = prev->next; \
            prev->next = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    \
    bool list_##TYPE##_remove_at(List_##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        \
        Node_##TYPE* to_delete = NULL; \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            list->tail->next = list->head; /* Actualizar circularidad */ \
            if (list->length == 1) { \
                list->head = list->tail = NULL; \
            } \
        } else { \
            Node_##TYPE* prev = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                prev = prev->next; \
            } \
            to_delete = prev->next; \
            prev->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = prev; \
            } \
        } \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !list->head || !print_fn) return; \
        Node_##TYPE* current = list->head; \
        do { \
            print_fn(current->data); \
            current = current->next; \
            if (current != list->head) printf(" -> "); \
        } while (current != list->head); \
        printf(" (head)\n"); \
    } \
// ----------------------------
// Declaración para tipos concretos
// ----------------------------
DECLARE_LINKED_LIST(int)
DECLARE_LINKED_LIST(char)
DECLARE_LINKED_LIST(float)

// ----------------------------
// Implementación para tipos concretos
// ----------------------------
#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif