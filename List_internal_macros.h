#include "MGX/MGX_type.h"

#define __List_CAT(A, B) __List_CAT_(A, B)
#define __List_CAT_(A, B) A ## B
#define __List_EXPAND(...) __VA_ARGS__
#define __List_STR_(x) #x
#define __List_STR(x) __List_STR_(x)

#define __List_FLAT_PTR(T, e) (__MGX_T_FORWARD_RECURSIVE(__List_FLATTEN, T, e))
#define __List_FLATTEN_ARRAY(A, S) *A
#define __List_FLATTEN_COMP(e, T) e
#define __List_FLATTEN_PTR(e) e
#define __List_FLATTEN(T, e) (&e)
#define __List_STRUCT(T) MGX_WHEN(__MGX_T_IS_ARRAY(T))(struct MGX_T_NAME(T) {MGX_T_VAR(T, array);};)
#define __List_RETURN(T) MGX_IF(__MGX_T_IS_ARRAY(T))(struct MGX_T_NAME(T), MGX_T(T))
#define __List_RETURN_PTR(T) __List_RETURN(T)*
#define __List_PREFIX(T) __List_CAT(_List_, MGX_T_NAME(T))
#define __List_FUNC(T, Task) __List_CAT(__List_PREFIX(T), _ ## Task)
#define __List_RETURN_STRUCT MGX_OR(MGX_NOT(__MGX_T_IS_ARRAY(T)), LIST_RETURN_STRUCT)
#define __List_FORWARDHANDLER(I, M, T, ...) M(T, MGX_ARG_GET_N(I, __VA_ARGS__))
#define __List__FOREACH(PARGS, M, ...) MGX_FOR(PARGS, MGX_ARG_COUNT(__VA_ARGS__), MGX_INC, __MGX_ARG_FORWARD, PARGS, M, __VA_ARGS__)
#define __List_FOREACH(M, ...) __List_ (1, __List_FORWARDHANDLER, __VA_ARGS__)

#ifdef __GNUC__
#define __List_FUNC_MEMBER(T, M, Task) __List_CAT(__List_CAT(__List_PREFIX(T), __##M), _## Task)
#else
#define __List_FUNC_MEMBER(T, M, Task)
#endif
