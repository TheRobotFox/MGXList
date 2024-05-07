#pragma once
#include "MGX/MGX_base.h"
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

#include "List_gen.h"
//INCLUDE_LIST(char)
//INCLUDE_LIST(short)
//INCLUDE_LIST(int)
//INCLUDE_LIST(long)
//INCLUDE_LIST(size_t)
//INCLUDE_LIST(float)
//INCLUDE_LIST(double)
//INCLUDE_LIST(List)

List 	List_create(size_t element_size);
void	List_free(List l);
void*   List_at(List l, signed long long int index);
size_t 	List_size(List l);
void*	List_start(List l);
void*	List_end(List l);
void	List_shrink(List l);
size_t 	List_capacity(List l);
bool 	List_reserve(List l, size_t capacity);
void    List_reserve_mult(List l, float mult);
void 	List_realloc_callback(List l, F_List_realloc_callback callback, void *arg);
void*	List_finde(List l, bool (*compare)(void*, void*), void* arg);
int	List_findi(List l, bool (*compare)(void*, void*), void* arg);
void*	List_push(List l, const void* element);
void*   List_append(List l, const void *array, size_t n);
void*   List_pop(List l);
bool	List_copy(List a, List b); // copy b into a
void    List_clear(List l);
void*   Buff_find(char *start, char *end, size_t el_size, bool (*compare)(void*, void*), void *arg);
void    List_foreach(List l, void (*func)(void*, void*), void *arg);
void    List_rmi(List l, size_t index);
size_t	List_rme(List l, void *e);
void    List_concat(List a, List b); // cat b to a
void    List_resize(List l, signed long long int size);
void    List_swap(List l, size_t a, size_t b);
void    List_sort(List l, bool (*cmp)(void *a, void *b));

#define LIST(T) List

#define List_GET_REF(T, l, index) (*(MGX_T_PTR(T))List_at(l, index))

#define _LIST(T, func) __List_FUNC(T, func)

#define LIST_get(T) *(MGX_T_PTR(T))List_at
#define LIST_create(T) List_create(sizeof(MGX_T(T)))
#define LIST_push(T) _LIST(T, push)
#define LIST_pop(T) _LIST(T, pop)
#define LIST_append(T) _LIST(T, append)
#define LIST_finde(T) _LIST(T, finde)
#define LIST_findi(T) _LIST(T, findi)
#define LIST_finde(T) _LIST(T, finde)
#define LIST_forward(T) _LIST(T, forward)
#define LIST_forward_m(T, M) __List_FUNC_MEMBER(T,M,forward)
#define LIST_foreach(T) _LIST(T, foreach)
#define LIST_sort(T) _LIST(T, sort)
#define LIST_rme(T) _LIST(T, rme)
#define LIST_at(T) (MGX_T_PTR(T))List_at
#define LIST_start(T) (MGX_T_PTR(T))List_start
#define LIST_end(T) (MGX_T_PTR(T))List_end
#define LIST_rmi(T) List_rmi
#define LIST_reserve(T) List_reserve
#define LIST_reserve_mult(T) List_reserve_mult
#define LIST_reserve_callback(T) List_reserve_callback
#define LIST_size(T) List_size
#define LIST_shrink(T) List_shrink
#define LIST_capacity(T) List_capacity
#define LIST_free(T) List_free
#define LIST_capacity(T) List_capacity
#define LIST_capacity(T) List_capacity
#define LIST_capacity(T) List_capacity
#define LIST_copy(T) List_copy
#define LIST_clear(T) List_clear
#define LIST_concat(T) List_concat
#define LIST_resize(T) List_resize
#define LIST_swap(T) List_swap
#define LIST_LOOP(T, L, ptr) for(T *ptr=List_start(L), *end=List_end(L); ptr!=end; ptr++)
