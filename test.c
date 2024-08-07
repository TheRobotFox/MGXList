
/* static int a_larger_b(void *a, void *b) */
/* { */
/*     int ia=*(int*)a, ib=*(int*)b; */
/*     return ia>ib; */
/* } */

/* void print(void*a, void *_) */
/* { */
/*     printf("%d ", *(int*)a); */
/* } */

/* #define PUSH(x) val=x;Heap_add(h,&val); */
/* int main(void){ */
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
/* } */


#include "stdio.h"
#define LIST_GEN int, float, PTR(int)
#include "List.h"
LIST_GEN_IMPL

/* IMPLEMENT_LIST(int) */
/* IMPLEMENT_LIST(float) */

void print(int n)
{
    printf("%d\n", n);
}

int main()
{

    LIST(float) f = LIST_create(float);
    LIST_push(f, 1);
    LIST_push(f, 2);
    printf("List<%s> contains %lu elements!\n", LIST_GET_TYPE(f), LIST_size(f));

    LIST(int) i = LIST_create(int);
    LIST_push(i, 1);
    LIST_push(i, 2);
    LIST_push(i, 2);
    printf("List<%s> contains %lu elements!\n", LIST_GET_TYPE(i), LIST_size(i));

    LIST(PTR(int)) p = LIST_create(PTR(int));
    LIST_ITER(i, ptr)
        LIST_push(p, ptr);

    printf("List<%s> contains %lu elements!\n", LIST_GET_TYPE(p), LIST_size(p));

    LIST_FOREACH(p, n)
        (*n)++;

    LIST_FOREACH(i, n)
        printf("%d\n", n);

}
