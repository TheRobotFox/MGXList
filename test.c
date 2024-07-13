#include "Heap.h"

#include "List.h"
#include "stdio.h"

#include "stdlib.h"

#define DEFAULT_SIZE 50

static int a_larger_b(void *a, void *b)
{
    int ia=*(int*)a, ib=*(int*)b;
    return ia>ib;
}

void print(void*a, void *_)
{
    printf("%d ", *(int*)a);
}

#define PUSH(x) val=x;Heap_add(h,&val);
int main()
{
    /* int val; */
    /* Heap h = Heap_create(sizeof(val), a_larger_b); */

    /* PUSH(7) */
    /* PUSH(3) */
    /* PUSH(9) */
    /* PUSH(8) */
    /* PUSH(4) */
    /* PUSH(6) */
    /* PUSH(5) */
    /* PUSH(10) */
    /* PUSH(2) */
    /* PUSH(1) */
    /* PUSH(0) */

    /* List_foreach(*(List*)h, print, NULL); */
    /* printf("\n"); */
    /* while(Heap_size(h)) */
    /* { */
    /*     Heap_pop(h, &val); */
    /*     printf("%d ", val); */
    /* } */
    /* Heap_free(h); */
    List l = LIST_create(int);
    /* for(int i=0; i<30; i++){ */
    /*     int mod = i%3; */
    /*     List_insert(l, 2, &mod); */
    /* } */
    int a = 1;
    List_push(l, &a);
    List_push(l, &a);
    a=3;
    List_insert(l, 2, &a);
    List_foreach(l, print, NULL);
    printf("\n");
    int d = 0;
    List_rme(l, &d);
    List_foreach(l, print, NULL);
    printf("\n");
    List_free(l);
}
