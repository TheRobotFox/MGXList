#include "Heap.h"
#include "List.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_SIZE 50

struct _Heap
{
    List list;
	int (*a_larger_b)(void *a, void *b);
};

Heap Heap_create(size_t element_size, int (*a_larger_b)(void *a, void *b))
{
    Heap s = malloc(sizeof(struct _Heap));
    s->list = List_create(element_size);
	s->a_larger_b = a_larger_b;
    return s;
}

#define PARENT(x) ((x-1)/2)
int Heap_add(Heap h, void *obj)
{
	size_t insertIdx = List_size(h->list);
    List_push(h->list, NULL);
	while(insertIdx && h->a_larger_b(obj, List_at(h->list, PARENT(insertIdx)))) {
        List_set(h->list, insertIdx, List_at(h->list, PARENT(insertIdx)));
		insertIdx=PARENT(insertIdx);
	}
    List_set(h->list, insertIdx, obj);
    return insertIdx;
}

void Heap_free(Heap heap)
{
    List_free(heap->list);
    free(heap);
}

#define CHILD(x, nth) (x*2+nth)

int Heap_rmi(Heap heap, size_t index, void *out)
{
    if(index>=List_size(heap->list)) return -1;

    if(out)
        memcpy(out, List_at(heap->list, index), List_get_element_size(heap->list));

    List_pop(heap->list);
    void *ins=List_end(heap->list);

    while(CHILD(index, 2)<=List_size(heap->list)) {
        if(heap->a_larger_b(List_at(heap->list, CHILD(index, 1)), List_at(heap->list, CHILD(index,2)))) {
            List_set(heap->list, index, List_at(heap->list, CHILD(index, 1)));
            index=CHILD(index,1);
        } else {
            List_set(heap->list, index, List_at(heap->list, CHILD(index, 2)));
            index=CHILD(index,2);
        }
    }
    if(CHILD(index, 1)<=List_size(heap->list)) {
        List_set(heap->list, index, List_at(heap->list, CHILD(index, 1)));
        index=CHILD(index, 1);
    }

    List_set(heap->list, index, ins);
    return 0;
}

int Heap_pop(Heap heap, void* out)
{
    return Heap_rmi(heap, 0, out);
}

size_t Heap_size(Heap h)
{
    return List_size(h->list);
}
void*	Heap_start(Heap h)
{
    return List_start(h->list);
}
void*	Heap_end(Heap h)
{
    return List_end(h->list);
}
bool 	Heap_reserve(Heap h, size_t capacity)
{
    return List_reserve(h->list, capacity);
}
size_t	Heap_rme(Heap h, void *e)
{
    int index, occur=0;
    while ((index=List_contains(h->list, e))>=0){
        Heap_rmi(h, index, NULL);
        occur++;
    }
    return occur;
}
