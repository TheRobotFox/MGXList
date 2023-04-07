#include "List_internal_macros.h"
#include <string.h>

#define INCLUDE_LIST(T)                                                                                                                  \
                                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, push)(List l, __List_VAR(T, e));                                                                     \
List __List_FUNC(T, create)();                                                                                                           \
__List_RETURN(T) __List_FUNC(T, pop)(List l);                                                                                            \
size_t __List_FUNC(T, rme)(List l, __List_VAR(T, e));                                                                                    \
void __List_FUNC(T, foreach)(List l, void (*func)(__List_TYPE_PTR(T)));                                                                  \
void __List_FUNC(T, forward)(List l, void (*func)(__List_TYPE(T)));                                                                      \
__List_RETURN_PTR(T) __List_FUNC(T, find)(List l, bool (*compare_equal)(__List_TYPE_PTR(T), __List_TYPE_PTR(T)), __List_VAR_PTR(T, arg));\
void __List_FUNC(T, sort)(List l, bool (*compare_equal)(__List_TYPE_PTR(T), __List_TYPE_PTR(T)));                                        \

#define IMPLEMENT_LIST(T)                                                                                                                \
__List_STRUCT(T)                                                                                                                         \
List __List_FUNC(T, create)()                                                                                                            \
{                                                                                                                                        \
	return List_create(sizeof(__List_TYPE(T)));                                                                                      \
}                                                                                                                                        \
__List_RETURN_PTR(T) __List_FUNC(T, push)(List l, __List_VAR(T, e))                                                                      \
{                                                                                                                                        \
	return List_push(l, __List_FLAT_ADDR(T)e);                                                                                       \
}                                                                                                                                        \
__List_RETURN(T) __List_FUNC(T, pop)(List l)                                                                                             \
{                                                                                                                                        \
	__List_DO_RETURN(T, *(__List_TYPE_PTR(T))List_pop(l));                                                                           \
}                                                                                                                                        \
size_t __List_FUNC(T, rme)(List l, __List_VAR(T, e))                                                                                     \
{                                                                                                                                        \
	return List_rme(l, &e);                                                                                                          \
}                                                                                                                                        \
void __List_FUNC(T, foreach)(List l, void (*func)(__List_TYPE_PTR(T)))                                                                   \
{                                                                                                                                        \
        __List_VAR_PTR(T, start) = List_start(l);                                                                                        \
        __List_VAR_PTR(T, end) = List_end(l);                                                                                            \
	for(; start!=end; start++)                                                                                                       \
		func(start);                                                                                                             \
}                                                                                                                                        \
void __List_FUNC(T, forward)(List l, void (*func)(__List_TYPE(T)))                                                                       \
{                                                                                                                                        \
        __List_VAR_PTR(T, start) = List_start(l);                                                                                        \
        __List_VAR_PTR(T, end) = List_end(l);                                                                                            \
	for(; start!=end; start++)                                                                                                       \
		func(*start);                                                                                                            \
}                                                                                                                                        \
__List_RETURN_PTR(T) __List_FUNC(T, find)(List l, bool (*compare_equal)(__List_TYPE_PTR(T), __List_TYPE_PTR(T)), __List_VAR_PTR(T, arg)) \
{                                                                                                                                        \
        __List_VAR_PTR(T, start)=List_start(l);							                                         \
        __List_VAR_PTR(T, end) = List_end(l);								                                 \
	for(; start!=end; start++)                                                                                                       \
		if(compare_equal(start, arg)){                                                                                           \
			return (__List_RETURN_PTR(T))start;                                                                              \
		}                                                                                                                        \
	return NULL;                                                                                                                     \
}                                                                                                                                        \
void __List_FUNC(T, quicksort)(List list, size_t left, size_t right, bool (*cmp)(__List_TYPE_PTR(T), __List_TYPE_PTR(T)))                \
{                                                                                                                                        \
	if(left>=right)                                                                                                                  \
		return;                                                                                                                  \
                                                                                                                                         \
	__List_VAR_PTR(T, pivot) = List_at(list, right);                                                                                 \
	size_t l=left, r=right-1;                                                                                                        \
                                                                                                                                         \
	while(l<r){                                                                                                                      \
		for(; l<right && !cmp(pivot, (__List_TYPE_PTR(T))List_at(list, l))/* pivot>list[l] */; l++);                             \
		for(; r>left && cmp(pivot, (__List_TYPE_PTR(T))List_at(list, r))/* pivot<list[r] */; r--);                               \
		if(l<r)                                                                                                                  \
			List_swap(list, r, l);                                                                                           \
                                                                                                                                         \
	}                                                                                                                                \
	if(cmp(pivot, (__List_TYPE_PTR(T))List_at(list,l)))                                                                              \
		List_swap(list, right, l);                                                                                               \
                                                                                                                                         \
	if(l>0)                                                                                                                          \
		__List_FUNC(T, quicksort)(list, left, l-1, cmp);                                                                         \
	__List_FUNC(T, quicksort)(list, l+1, right, cmp);                                                                                \
}												                                         \
void __List_FUNC(T, sort)(List l, bool (*compare_equal)(__List_TYPE_PTR(T), __List_TYPE_PTR(T)))                                         \
{												                                         \
	if(List_size(l)>1)                                                                                                               \
		__List_FUNC(T, quicksort)(l, 0, List_size(l)-1, compare_equal);                                                          \
}
