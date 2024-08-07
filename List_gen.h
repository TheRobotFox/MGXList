
// Generics

#define __List_type(T) struct __List_CAT(__List_type_, MGX_T_NAME(T))

#define __List_GDL_IMPL(T) A(__List_type(T), __List_FUNC, T)
#define __List_GDL_IMPL_TAIL(T) , __List_GDL_IMPL(T)
#define __List_GDL __List_GDL_IMPL(MGX_ARG_FIRST(LIST_GEN))__MGX_ARG_FOREACH(0,__List_GDL_IMPL_TAIL, MGX_ARG_TAIL(LIST_GEN))
#define __List_GET_FUNC(LIST_type, func) MGX_GEN_GET(LIST_type, func, __List_GDL)

#define __List_GDL_LIST_TO_TYPE_M(T, _) T
#define __List_GDL_LIST_TO_TYPE_IMPL(T) A(__List_type(T), __List_GDL_LIST_TO_TYPE_M, T)
#define __List_GDL_LIST_TO_TYPE_IMPL_TAIL(T) , __List_GDL_LIST_TO_TYPE_IMPL(T)
#define __List_GDL_LIST_TO_TYPE __List_GDL_LIST_TO_TYPE_IMPL(MGX_ARG_FIRST(LIST_GEN))MGX_ARG_FOREACH(__List_GDL_LIST_TO_TYPE_IMPL_TAIL, MGX_ARG_TAIL(LIST_GEN))

#define __List_GET_TYPE(LIST_type) MGX_GEN_GET(LIST_type, , __List_GDL_LIST_TO_TYPE)

#define __List_GDL_LIST_TO_TYPE_STR_M(T, _) __List_STR(MGX_T(T))
#define __List_GDL_LIST_TO_TYPE_STR_IMPL(T) A(__List_type(T), __List_GDL_LIST_TO_TYPE_STR_M, T)
#define __List_GDL_LIST_TO_TYPE_STR_IMPL_TAIL(T) , __List_GDL_LIST_TO_TYPE_STR_IMPL(T)
#define __List_GDL_LIST_TO_TYPE_STR __List_GDL_LIST_TO_TYPE_STR_IMPL(MGX_ARG_FIRST(LIST_GEN))MGX_ARG_FOREACH(__List_GDL_LIST_TO_TYPE_STR_IMPL_TAIL, MGX_ARG_TAIL(LIST_GEN))

#define __List_GET_TYPE_STR(LIST_type_STR) MGX_GEN_GET(LIST_type_STR, _, __List_GDL_LIST_TO_TYPE_STR)
