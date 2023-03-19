#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct _List* List;

enum E_CALLBACK_MSG
{
    CM_NOTHING,
    CM_NO_REALLOC,
    CM_PRE_REALLOC,
    CM_POST_REALLOC,
};

typedef void (*F_List_realloc_callback)(List l, enum E_CALLBACK_MSG msg, void *arg);
typedef void (*F_List_forward_handler)(void (*)(void*), void *e);


// warning append -> push

List 	List_create(size_t element_size);
void    List_reserve_mult(List l, float mult);
void	List_free(List l);
void*   List_get(List l, signed long long int index);
size_t 	List_size(List l);
void*	List_start(List l);
void*	List_end(List l);
void	List_shrink(List l);
size_t 	List_capacity(List l);
bool 	List_reserve(List l, size_t capacity);
void 	List_reserve_callback(List l, F_List_realloc_callback callback, void *arg);
void*	List_find(List l, bool (*compare)(void*, void*), void* arg);
void*	List_push(List l, const void* element);
void*   List_append(List l, const void *array, size_t n);
void*   List_pop(List l);
bool	List_copy(List a, List b); // copy b into a
void    List_clear(List l);
void*   Buff_find(char *start, char *end, size_t el_size, bool (*compare)(void*, void*), void *arg);
void    List_foreach(List l, void (*func)(void*));
void    List_forward(List l, void (*func)(void*));
void    List_rmi(List l, size_t index);
size_t	List_rme(List l, void *e);
void    List_concat(List a, List b); // cat b to a
void    List_resize(List l, signed long long int size);
void    List_swap(List l, size_t a, size_t b);
void    List_sort(List l, bool (*cmp)(void *a, void *b));
