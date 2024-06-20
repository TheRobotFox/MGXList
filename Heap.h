#pragma once
#include "List.h"
#include <stddef.h>

struct _Heap;
typedef struct _Heap* Heap;

Heap Heap_create(size_t element_size, int (*a_larger_b)(void *a, void *b));
int Heap_add(Heap h, void *obj);

size_t Heap_size(Heap h);
void*	Heap_start(Heap h);
void*	Heap_end(Heap h);
bool 	Heap_reserve(Heap h, size_t capacity);
int Heap_rmi(Heap heap, size_t index, void *out);
size_t	Heap_rme(Heap h, void *e);
int Heap_pop(Heap heap, void *out);
void Heap_free(Heap h);

#define HEAP_start(T) (MGX_T_PTR(T))Heap_start
#define HEAP_end(T) (MGX_T_PTR(T))Heap_end
#define HEAP_LOOP(T, L, func) for(T *ptr=HEAP_start(T)(L), *end=HEAP_end(T)(L); ptr!=end; ptr++)
#define HEAP_FORWARD(T, L, func) HEAP_LOOP(T, L, ptr){func(*ptr);}
