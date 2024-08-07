#include "List_internal_macros.h"
#include <string.h>

//#define LIST_RETURN_STRUCT true

// INCLUDE(...) << struct members
/* #define __INCLUDE_MEMBER(...) __List_FOREACH(__INCLUDE_MEMBER_, __VA_ARGS__) */
/* #define __IMPLEMENT_MEMBER(...) __List_FOREACH(__IMPLEMENT_MEMBER_, __VA_ARGS__) */

/* #define __INCLUDE_MEMBER_(T, M) \ */
/* void __List_FUNC_MEMBER(T, M, forward)(List l, void (*func)(typeof(((MGX_T_PTR(T))0)->M))); \ */

/* #define __IMPLEMENT_MEMBER_(T, M) \ */
/* void __List_FUNC_MEMBER(T, M, forward)(List l, void (*func)(typeof(((MGX_T_PTR(T))0)->M))) \ */
/* {                                                                                                                            \ */
/*         MGX_T_VAR_PTR(T, start) = (MGX_T_PTR(T))List_start(l);                                                                             \ */
/*         MGX_T_VAR_PTR(T, end) = List_end(l);                                                                                 \ */
/* 	for(; start!=end; start++)                                                                                           \ */
/* 		func(start->M);                                                                                              \ */
/* } */

#define INCLUDE_LIST(...) \
__INCLUDE_LIST (__VA_ARGS__)
/* __INCLUDE_MEMBER(__VA_ARGS__)\ */

/* #define __INCLUDE_LIST(T, ...) \ */
/*                                                                                                                              \ */
/* MGX_IF(__List_RETURN_STRUCT)(                                                                                                \ */
/* __List_RETURN_PTR(T) __List_FUNC(T, push)(List l, MGX_T_VAR(T, e));                                                          \ */
/* __List_RETURN(T) __List_FUNC(T, append)(List l);                                                                             \ */
/* __List_RETURN(T) __List_FUNC(T, pop)(List l);                                                                                \ */
/* ,                                                                                                                            \ */
/*     void* __List_FUNC(T, push)(__List_type(T) l, MGX_T_VAR(T, e));     \ */
/* void* __List_FUNC(T, append)(List l, MGX_T_VAR_PTR(T,array), size_t n);                                                      \ */
/* )                                                                                                                            \ */
/* size_t __List_FUNC(T, rme)(List l, MGX_T_VAR(T, e));                                                                         \ */
/* void __List_FUNC(T, foreach)(List l, void (*func)(MGX_T_PTR(T), void*), void *arg);                                          \ */
/* void __List_FUNC(T, forward)(List l, void (*func)(MGX_T(T)));                                                                \ */
/* __List_RETURN_PTR(T) __List_FUNC(T, finde)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)), MGX_T_VAR_PTR(T, arg));\ */
/* int __List_FUNC(T, findi)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)), MGX_T_VAR_PTR(T, arg));                 \ */
/* void __List_FUNC(T, sort)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)));                                        \ */

#define IMPLEMENT_LIST(...) \
__List_EXPAND(__IMPLEMENT_LIST __MGX_LPAREN MGX_ARG_FIRST(__VA_ARGS__) __MGX_RPAREN)
/* __IMPLEMENT_MEMBER(__VA_ARGS__)\ */


#define __IMPLEMENT_LIST(T) \
__List_STRUCT(T)                                                                                                          \
MGX_IF(__List_RETURN_STRUCT)(                                                                                             \
__List_RETURN_PTR(T) __List_FUNC(T, append)(__List_type l, MGX_T_VAR_PTR(T, array), size_t n)                                    \
{                                                                                                                         \
	return List_append(l, __List_FLAT_PTR(T, array), n);                                                                       \
}                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, push)(List l, MGX_T_VAR(T, e))                                                        \
{                                                                                                                         \
	return List_push(l, __List_FLAT_PTR(T,e));                                                                                 \
}                                                                                                                         \
__List_RETURN(T) __List_FUNC(T, pop)(List l)                                                                              \
{                                                                                                                         \
	return * MGX_IF(__MGX_T_IS_ARRAY(T))((__List_RETURN_PTR(T)), (MGX_T_PTR(T)))List_pop(l);                                   \
}                                                                                                                         \
,                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, end)(List l)                                                                          \
{                                                                                                                         \
	return List_end(l);                                                                                                        \
}                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, start)(List l)                                                                        \
{                                                                                                                         \
	return List_start(l);                                                                                                      \
}                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, at)(List l, long long idx)                                                            \
{                                                                                                                         \
	return List_at(l, idx);                                                                                                    \
}                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, push)(List l, MGX_T_VAR(T, e))                                                        \
{                                                                                                                         \
	return List_push(l, __List_FLAT_PTR(T,e));                                                                                 \
}                                                                                                                         \
__List_RETURN_PTR(T) __List_FUNC(T, append)(List l, MGX_T_VAR_PTR(T, array), size_t n)                                    \
{                                                                                                                         \
	return List_append(l, __List_FLAT_PTR(T, array), n);                                                                       \
}                                                                                                                         \
)                                                                                                                         \
                                                                                                                          \
size_t __List_FUNC(T, rme)(List l, MGX_T_VAR(T, e))                                                                       \
{                                                                                                                         \
	return List_rme(l, &e);                                                                                                    \
}                                                                                                                         \
void __List_FUNC(T, foreach)(List l, void (*func)(MGX_T_PTR(T), void*), void *arg)                                        \
{                                                                                                                         \
        MGX_T_VAR_PTR(T, start) = (MGX_T_PTR(T))List_start(l);                                                            \
        MGX_T_VAR_PTR(T, end) = List_end(l);                                                                              \
	for(; start!=end; start++)                                                                                              \
		func(start,arg);                                                                                                  \
}                                                                                                                         \
void __List_FUNC(T, forward)(List l, void (*func)(MGX_T(T)))                                                              \
{                                                                                                                         \
        MGX_T_VAR_PTR(T, start) = (MGX_T_PTR(T))List_start(l);                                                            \
        MGX_T_VAR_PTR(T, end) = List_end(l);                                                                              \
	for(; start!=end; start++)                                                                                              \
		func(*start);                                                                                                     \
}                                                                                                                         \
MGX_WHEN(__List_RETURN_STRUCT)(                                                                                           \
__List_RETURN_PTR(T) __List_FUNC(T, finde)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)), MGX_T_VAR_PTR(T, arg)) \
{                                                                                                                         \
        MGX_T_VAR_PTR(T, start)=(MGX_T_PTR(T))List_start(l);                                                              \
        MGX_T_VAR_PTR(T, end) = List_end(l);                                                                              \
	for(; start!=end; start++)                                                                                              \
		if(compare_equal(start, arg)){                                                                                    \
			return (__List_RETURN_PTR(T))start;                                                                                \
		}                                                                                                                 \
	return NULL;                                                                                                               \
}                                                                                                                         \
)                                                                                                                         \
int __List_FUNC(T, findi)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)), MGX_T_VAR_PTR(T, arg))                    \
{                                                                                                                         \
        MGX_T_VAR_PTR(T, start)=(MGX_T_PTR(T))List_start(l);                                                              \
        MGX_T_VAR_PTR(T, end) = List_end(l);                                                                              \
	for(; start!=end; start++)                                                                                              \
		if(compare_equal(start, arg)){                                                                                    \
			return start-(MGX_T_PTR(T))(MGX_T_PTR(T))List_start(l);                                                            \
		}                                                                                                                 \
	return -1;                                                                                                                 \
}                                                                                                                         \
void __List_FUNC(T, quicksort)(List list, size_t left, size_t right, bool (*cmp)(MGX_T_PTR(T), MGX_T_PTR(T)))                \
{                                                                                                                         \
	if(left>=right)                                                                                                       \
		return;                                                                                                                \
                                                                                                                          \
                              MGX_T_VAR_PTR(T, pivot) = (MGX_T_PTR(T))List_at(list, right);                               \
	size_t l=left, r=right-1;                                                                                             \
                                                                                                                          \
	while(l<r){                                                                                                           \
		for(; l<right && !cmp(pivot, (MGX_T_PTR(T))List_at(list, l))/* pivot>list[l] */; l++);                              \
		for(; r>left && cmp(pivot, (MGX_T_PTR(T))List_at(list, r))/* pivot<list[r] */; r--);                                 \
		if(l<r)                                                                                                           \
			List_swap(list, r, l);                                                                                        \
                                                                                                                          \
	}                                                                                                                     \
	if(cmp(pivot, (MGX_T_PTR(T))List_at(list,l)))                                                                         \
		List_swap(list, right, l);                                                                                        \
                                                                                                                          \
	if(l>0)                                                                                                               \
		__List_FUNC(T, quicksort)(list, left, l-1, cmp);                                                                  \
	__List_FUNC(T, quicksort)(list, l+1, right, cmp);                                                                     \
}                                                                                                                         \
void __List_FUNC(T, sort)(List l, bool (*compare_equal)(MGX_T_PTR(T), MGX_T_PTR(T)))                                         \
{                                                                                                                         \
	if(List_size(l)>1)                                                                                                    \
		__List_FUNC(T, quicksort)(l, 0, List_size(l)-1, compare_equal);                                                   \
}                                                                                                                         \

#define __List_impl_gen(T) __List_type(T) { List __data; MGX_T_VAR_PTR(T, ptype);}; IMPLEMENT_LIST(T)

#define LIST_GEN_IMPL MGX_ARG_FOREACH(__List_impl_gen, LIST_GEN)

