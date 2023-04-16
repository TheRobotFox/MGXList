#include "MGX/MGX_type.h"

#define __List_CAT(A, B) __List_CAT_(A, B)
#define __List_CAT_(A, B) A ## B


#define __List_FLAT_PTR(T, e) (__MGX_T_FORWARD_RECURSIVE(__List_FLATTEN, T, e))
#define __List_FLATTEN_ARRAY(A, S) *A
#define __List_FLATTEN_COMP(T, e) __List_FLATTEN(T, e)
#define __List_FLATTEN(T, e) (&e)
#define __List_STRUCT(T) MGX_WHEN(__MGX_T_IS_ARRAY(T))(struct MGX_T_NAME(T) {MGX_T_VAR(T, array);};)
#define __List_RETURN(T) MGX_IF(__MGX_T_IS_ARRAY(T))(struct MGX_T_NAME(T), T)
#define __List_RETURN_PTR(T) __List_RETURN(T)*
#define __List_PREFIX(T) __List_CAT(_List_, MGX_T_NAME(T))
#define __List_FUNC(T, Task) __List_CAT(__List_PREFIX(T), _ ## Task)
#define __List_RETURN_STRUCT __MGX_OR(__MGX_NOT(__MGX_T_IS_ARRAY(T)), LIST_RETURN_STRUCT)
