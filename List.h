#pragma once
#include "MGX/MGX_base.h"
#include <stddef.h>
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

#include "List_template.h"

//INCLUDE_LIST(char)
//INCLUDE_LIST(short)
//INCLUDE_LIST(int)
//INCLUDE_LIST(long)
//INCLUDE_LIST(size_t)
//INCLUDE_LIST(float)
//INCLUDE_LIST(double)
//INCLUDE_LIST(List)

void	List_free(List l);
size_t 	List_size(List l);
void	List_shrink(List l);
size_t 	List_capacity(List l);
void    List_clear(List l);
bool 	List_reserve(List l, size_t capacity);
void    List_reserve_mult(List l, float mult);
void 	List_realloc_callback(List l, F_List_realloc_callback callback, void *arg);
void List_shift(List l, int index, int amount);
void    List_rmi(List l, size_t index);
void    List_swap(List l, size_t a, size_t b);
void    List_reverse(List l);
void    List_calloc(List l, size_t size);
size_t List_get_element_size(List l);

List 	List_create(size_t element_size);
void*   List_at(List l, signed long long int index);
void*	List_start(List l);
void*	List_end(List l);
void*	List_finde(List l, bool (*compare)(const void*, const void*), const void* arg);
int	List_findi(List l, bool (*compare)(const void*, const void*), const void* arg);
void*	List_push(List l, const void* element);
void*	List_insert(List l, int index, const void* element);
void*   List_append(List l, const void *array, size_t n);
void*   List_pop(List l);
bool	List_copy(List a, List b); // copy b into a
void*   Buff_find(char *start, const char *end, size_t el_size, bool (*compare)(const void*, const void*), const void *arg);
void    List_foreach(List l, void (*func)(void*, void*), void *arg);
size_t	List_rme(List l, void *e);
void    List_concat(List a, List b); // cat b to a
void    List_resize(List l, signed long long int size);
void    List_sort(List l, bool (*cmp)(void *a, void *b));
void*   List_set(List l, size_t index, const void *e);
int       List_contains(List l, void *e);


#define List_GET_REF(T, l, index) (*(MGX_T_PTR(T))List_at(l, index))

#define _LIST(T, func) __List_FUNC(T, func)

#ifdef LIST_GEN
#include "MGX/MGX_gen.h"
#include "List_gen.h"

#define LIST(T) __List_type(T)

#define LIST_GET_TYPE(LIST) __List_GET_TYPE_STR(LIST)
#define LIST_create(TYPE) (__List_type(TYPE)){List_create(sizeof(TYPE))}
#define LIST_at(LIST, index) (MGX_T_PTR(__List_GET_TYPE(LIST)))List_at(LIST.__data, index)
#define LIST_start(LIST) (MGX_T_PTR(__List_GET_TYPE(LIST)))List_start(LIST.__data)
#define LIST_end(LIST) (MGX_T_PTR(__List_GET_TYPE(LIST)))List_start(LIST.__data)
#define LIST_get(LIST) *LIST_at(LIST)
#define LIST_push(LIST, element) __List_GET_FUNC(LIST, push)(LIST.__data, element)
#define LIST_pop(LIST) __List_GET_FUNC(LIST, pop)(LIST->__data)
#define LIST_append(LIST)
#define LIST_finde(LIST)
#define LIST_findi(LIST)
#define LIST_finde(LIST)
#define LIST_forward(LIST)
#define LIST_forward_m(LIST)
#define LIST_foreach(LIST)
#define LIST_sort(LIST)
#define LIST_rme(LIST)
#define LIST_rmi(LIST)
#define LIST_reserve(LIST)
#define LIST_reserve_mult(LIST)
#define LIST_reserve_callback(LIST)
#define LIST_size(LIST) List_size(LIST.__data)
#define LIST_shrink(LIST)
#define LIST_capacity(LIST)
#define LIST_free(LIST)
#define LIST_capacity(LIST)
#define LIST_copy(LIST)
#define LIST_clear(LIST)
#define LIST_concat(LIST)
#define LIST_resize(LIST)
#define LIST_swap(LIST)
#define LIST_LOOP(T, L, ptr) for(T *ptr=LIST_start(T)(L); ptr!=LIST_end(T)(L); ptr++)
#define LIST_FORWARD(T, L, func) LIST_LOOP(T, L, ptr){func(*ptr);}

#else

#define LIST_GET_TYPE(LIST) "LIST_GEN NOT DEFINED"

#define LIST_get(T) *(MGX_T_PTR(T))List_at
#define LIST_create(T) List_create(sizeof(MGX_T(T)))
#define LIST_push(T) _LIST(T, push)
#define LIST_pop(T) (MGX_T_PTR(T))List_pop
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
#define LIST_copy(T) List_copy
#define LIST_clear(T) List_clear
#define LIST_concat(T) List_concat
#define LIST_resize(T) List_resize
#define LIST_swap(T) List_swap
#define LIST_LOOP(T, L, ptr) for(T *ptr=LIST_start(T)(L); ptr!=LIST_end(T)(L); ptr++)
#define LIST_FORWARD(T, L, func) LIST_LOOP(T, L, ptr){func(*ptr);}

#define LIST(T) List

#endif
