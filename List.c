#include "List.h"
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* IMPLEMENT_LIST(char) */
/* IMPLEMENT_LIST(short) */
/* IMPLEMENT_LIST(int) */
/* IMPLEMENT_LIST(long) */
/* IMPLEMENT_LIST(size_t) */
/* IMPLEMENT_LIST(float) */
/* IMPLEMENT_LIST(double) */
/* IMPLEMENT_LIST(List) */

struct _List{
	char *data;
	size_t size;
	size_t max;
	size_t element_size;
	float reserve_mult;
	F_List_realloc_callback callback;
	void *callback_arg;
};

List List_create(size_t element_size)
{
	List l = (List)malloc(sizeof(struct _List));
	l->element_size = element_size;
	l->data=(char*)malloc(l->element_size);
	l->size=0;
	l->max=1;
	l->reserve_mult=2;
	l->callback=NULL;

	return l->data ? l : NULL;
}

void List_free(List l)
{
	free(l->data);
	free(l);
}

static inline void* _List_at(List l, signed long long int index)
{
	if(!l->size) return List_start(l);
	if(index<0){
		index*=-1;
		index%=l->size;
		index=(l->size-index)%l->size;
	}

	return l->data+(l->element_size*index);
}

void* List_at(List l, signed long long int index)
{
	if(index<(signed long long)l->size && l->data)
		return _List_at(l,index);
	return NULL;
}
static void _List_shift(List l, int index, int amount)
{
	int list_size = List_size(l);
	if(index>=list_size) return List_resize(l, list_size+amount);;

	if(amount>0){
		List_resize(l, list_size+amount);
		memmove(List_at(l, index+amount), List_at(l, index), (list_size-index)*l->element_size);
	} else {
		memmove(List_at(l, index), List_at(l, index-amount), (list_size-index+amount)*l->element_size);
		List_resize(l, list_size+amount);
	}
}
void List_shift(List l, int index, int amount)
{
	if(index>=(int)l->size || (int)l->size+amount<0)
		return;
	_List_shift(l, index, amount);
}
void* List_insert(List l, int index, const void* element)
{
	if(index>(int)l->size)
		List_resize(l, index);
    _List_shift(l, index, 1);
	return List_set(l, index, element);
}
void* List_start(List l){return l->data;}
void* List_end(List l){return l->data+(l->size*l->element_size);}

void List_shrink(List l)
{
	if(l->max!=l->size) {
		if(l->callback)
			l->callback(l, CM_PRE_REALLOC, l->callback_arg);

		l->data=(char*)realloc(l->data,l->size*l->element_size);
		l->max=l->size;

		if(l->callback)
			l->callback(l, CM_POST_REALLOC, l->callback_arg);
	}
}

size_t List_size(List l){return l->size;}
size_t List_capacity(List l){return l->max;}

void List_reserve_mult(List l, float mult) { l->reserve_mult=mult; }

void List_realloc_callback(List l, F_List_realloc_callback callback, void *arg)
{
	l->callback=callback;
	l->callback_arg=arg;
}

bool List_reserve(List l, size_t capacity)
{
	if(capacity>l->max) {

		if(l->callback)
			l->callback(l, CM_PRE_REALLOC, l->callback_arg);

		l->data=(char*)realloc(l->data,capacity*l->element_size);
		l->max=capacity;

		if(l->callback)
			l->callback(l, CM_POST_REALLOC, l->callback_arg);

	}

	return !(l->data);
}

void List_clear(List l)
{
	l->size=0;
}
void *Buff_find(char *start, const char *end, size_t el_size, bool (*compare)(const void*, const void*), const void *arg)
{
	for(; start!=end; start+=el_size)
	{
		if(compare(start,arg))
				return start;
	}
	return NULL;
}
void *List_finde(List l, bool (*compare)(const void*, const void*), const void *arg)
{
	return Buff_find((char*)List_start(l),(char*)List_end(l),l->element_size,compare,arg);
}

int List_findi(List l, bool (*compare)(const void*, const void*), const void *arg)
{
	void* e = List_finde(l, compare, arg);
	if(e==NULL)
		return -1;
	return ((size_t)e-(size_t)List_start(l))/l->element_size;
}

void* List_append(List l, const void *array, size_t n)
{
	if(l->size+n>l->max)
	{
		if(List_reserve(l, l->max+n*l->element_size))
			return 0;
	}
	void *ptr=_List_at(l,l->size);
	l->size+=n;
	if(array)
		memcpy(ptr, array, n*l->element_size);
	return ptr;
}

void* List_push(List l, const void *element)
{
	if(l->size>=l->max)
	{
		if(List_reserve(l, l->max*l->reserve_mult))
			return 0;
	}
	void *ptr=_List_at(l,l->size);
	l->size++;
	if(element)
		memcpy(ptr,element,l->element_size);
	return ptr;
}

void* List_pop(List l)
{
	if(l->size==0)
		return NULL;
	return _List_at(l, --l->size);
}

bool List_copy(List a, List b)
{
	if(a->element_size!=b->element_size)
		return 2;
	if(List_reserve(a,List_size(b)))
		return 1;
	a->size=b->size;
	memcpy(List_start(a),List_start(b),(uint8_t*)List_end(b)-(uint8_t*)List_start(b));
	return 0;
}

void List_foreach(List l, void (*func)(void*, void*), void *arg)
{
	for(char *start=(char *)List_start(l), *end=(char*)List_end(l); start!=end; start+=l->element_size){
		func(start, arg);
	}
}

void List_rmi(List l, size_t index)
{
	if(index>=l->size)
		return;
	_List_shift(l, index, -1);
}

size_t List_rme(List l, void *e)
{
	size_t size = List_size(l),
		   skip=0;

	for(size_t i=0; i<size-skip; i++)
	{
		for(size_t j=i+skip; j<size; j++)
		{
				if(memcmp(_List_at(l, j), e, l->element_size)==0){
					skip++;
					continue;
				}
				break;
		}
		if(i+skip<size)
			memcpy(_List_at(l,i), _List_at(l, i+skip), l->element_size);
	}
	l->size-=skip;
	return skip;
}

void List_concat(List a, List b)
{
	List_reserve(a, a->size+b->size);
	memcpy(List_end(a), List_start(b), (uint8_t*)List_end(b)-(uint8_t*)List_start(b));
	a->size+=b->size;
}

void List_resize(List l, signed long long int size)
{
	if(size<0){
		if(l->size>0)
			l->size+=size;
		return;
	}
	if(size>(signed long long int)l->max)
		List_reserve(l, size);
	l->size=size;
}

size_t List_get_element_size(List l)
{
	return l->element_size;
}
void* List_set(List l, size_t index, const void *e){
	void *p = _List_at(l,index);
	if(e)
		memcpy(p, e, l->element_size);
	return  p;
}
void List_swap(List l, size_t a, size_t b)
{
	void *tmp=malloc(l->element_size);
	memcpy(tmp, _List_at(l,a), l->element_size);
	List_set(l, a, _List_at(l, b));
	List_set(l, b, tmp);
	free(tmp);
}

static void quick_sort(List list, size_t left, size_t right, bool (*cmp)(void *a, void *b))
{
	if(left>=right)
		return;

	void *pivot = _List_at(list, right);
	size_t l=left, r=right-1;

	while(l<r){
		for(; l<right && !cmp(pivot, _List_at(list, l))/* pivot>list[l] */; l++);
		for(; r>left && cmp(pivot, _List_at(list, r))/* pivot<list[r] */; r--);
		if(l<r)
			List_swap(list, r, l);

	}
	if(cmp(pivot, _List_at(list,l)))
		List_swap(list, right, l);

	if(l>0)
		quick_sort(list, left, l-1, cmp);
	quick_sort(list, l+1, right, cmp);
}

void List_sort(List l, bool (*cmp)(void *a, void *b))
{
	if(List_size(l)>1)
		quick_sort(l, 0, List_size(l)-1, cmp);
}

void List_calloc(List l, size_t size)
{
  l->data = calloc(size, l->element_size);
  l->max = size;
}

void List_reverse(List l) {
  for (size_t i = 0; i < l->size / 2; i++)
	  List_swap(l,i,l->size-1-i);
}

int List_contains(List l, void *e)
{
	for (size_t i=0; i<l->size; i++) {
		if(memcmp(_List_at(l, i), e, l->element_size)==0)
			return i;
	}
	return -1;
}
