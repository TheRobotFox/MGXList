#define __List_LPAREN (
#define __List_RPAREN )
#define __List_COMMA ,

#define __List_EAT(...)
#define __List_EXPAND(...) __VA_ARGS__
#define __List_EXPAND2(...) __VA_ARGS__
#define __List_EXPAND3(...) __VA_ARGS__
#define __List_EXPAND4(...) __VA_ARGS__

#define __List_CAT(A, B) __List_CAT_(A, B)
#define __List_CAT_(A, B) A ## B


#define __List_GET_FIRST(X, ...) X

#define __List_COMP_NAME_struct __List_RPAREN __List_COMP_NAME_MAKE __List_LPAREN struct __List_COMMA
#define __List_COMP_NAME_union __List_COMMA __List_EAT __List_LPAREN
#define __List_COMP_NAME_MAKE(A, B) A ## __ ## B __List_COMMA

#define __List_CAT1_(A, B) A ## B
#define __List_COMP_NAME(x) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_COMP_NAME_, x) __List_RPAREN) x __List_RPAREN)


#define __List_CAT2(A, B) __List_CAT2_(A, B)
#define __List_CAT2_(A, B) A ## B
#define __List_CAT3_(A, B) A ## B
#define __List_CAT4_(A, B) A ## B
#define __List_CAT5(A, B) __List_CAT5_(A, B)
#define __List_CAT5_(A, B) A ## B

#define __List_ARRAY_NAME_ARRAY(T, S) __List_RPAREN __List_CAT2(__List_CAT2(__List_COMP_NAME(T), __), S) __List_COMMA __List_EAT __List_LPAREN
#define __List_ARRAY_NAME(x) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT3_(__List_ARRAY_NAME_, x) __List_RPAREN) __List_COMP_NAME(x) __List_RPAREN)

#define __List_TYPE_NAME(Type) __List_ARRAY_NAME(Type)


#define __List_COMMA_() __List_COMMA
#define __List_LPAREN_() __List_LPAREN
#define __List_RPAREN_() __List_RPAREN
#define __List_CALL() __List_LPAREN __List_RPAREN
#define __List_CALL_LATER __List_CALL __List_CALL __List_CALL()

#define __List_VAR_ARRAY_COMBINE(T,S,N) T N[S]
#define __List_VAR_ARRAY(T, S) __List_RPAREN __List_VAR_ARRAY_COMBINE __List_LPAREN_ __List_CALL_LATER T __List_COMMA_ __List_CALL_LATER S __List_COMMA __List_EAT __List_LPAREN
#define __List_VAR(Type, Name) __List_EXPAND( __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_VAR_, Type) __List_RPAREN) \
                        Type Name __List_EAT __List_LPAREN_ __List_CALL __List_CALL() __List_RPAREN ) __List_COMMA Name __List_RPAREN)

#define __List_VAR_PTR(Type, Name) __List_VAR(Type, (*Name))


#define __List_TYPE_ARRAY(T, S) __List_RPAREN T[S] __List_COMMA __List_EAT __List_LPAREN
#define __List_TYPE(x) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_TYPE_, x) __List_RPAREN) x __List_RPAREN)

#define __List_TYPE_PTR_ARRAY(T, S) __List_RPAREN __List_VAR_PTR __List_LPAREN_  __List_CALL_LATER  ARRAY __List_LPAREN_ __List_CALL_LATER  T __List_COMMA_  __List_CALL_LATER  S __List_RPAREN_  __List_CALL_LATER __List_COMMA_ __List_CALL_LATER __List_RPAREN_  __List_CALL_LATER  __List_COMMA __List_EAT __List_LPAREN
#define __List_TYPE_PTR(x) __List_EXPAND2( __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_TYPE_PTR_, x) __List_RPAREN) x* __List_RPAREN))


#define __List_RETURN_ARRAY(T, S) __List_RPAREN struct __List_PREFIX(ARRAY(T,S)) __List_COMMA __List_EAT __List_LPAREN
#define __List_RETURN(x) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_RETURN_, x) __List_RPAREN) x __List_RPAREN)

#define __List_RETURN_PTR(T) __List_RETURN(T)*

#define __List_STRUCT_ARRAY(T,S) __List_RPAREN struct __List_PREFIX(ARRAY(T,S)) {T array[S];}; __List_COMMA _List_EAT __List_LPAREN
#define __List_STRUCT(T) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT4_(__List_STRUCT_, T __List_RPAREN) __List_RPAREN) )

#define __List_DO_RETURN_ARRAY(T,S) __List_RPAREN  __List_CALL_LATER __List_RETURN(ARRAY(T,S)) _list_tmp_obj; memcpy __List_LPAREN_ __List_CALL_LATER __List_EXPAND4 __List_LPAREN_ __List_CALL_LATER __List_EXPAND3 __List_COMMA __List_EAT __List_LPAREN
#define __List_DO_RETURN(T, val) __List_EXPAND2(__List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EXPAND3 __List_EAT __List_LPAREN __List_EXPAND(__List_CAT4_( __List_DO_RETURN_, T) __List_RPAREN ) __List_LPAREN_ __List_CALL __List_CALL() return val __List_EAT __List_LPAREN_ __List_CALL __List_CALL __List_CALL() __List_RPAREN __List_LPAREN_ __List_CALL __List_CALL() &_list_tmp_obj, &val, sizeof(__List_TYPE(T)) __List_RPAREN_ __List_CALL_LATER; return __List_LPAREN_ __List_CALL __List_CALL __List_CALL() _list_tmp_obj __List_RPAREN_ __List_CALL __List_CALL() __List_RPAREN)))

#define __List_FLAT_ADDR_ARRAY(T,S) __List_RPAREN  __List_COMMA __List_EAT __List_LPAREN
#define __List_FLAT_ADDR(x) __List_EXPAND( __List_GET_FIRST __List_LPAREN __List_EAT __List_LPAREN __List_EXPAND(__List_CAT1_(__List_FLAT_ADDR_, x) __List_RPAREN) & __List_RPAREN)
#define __List_PREFIX(T) __List_CAT5(_List_, __List_TYPE_NAME(T))
#define __List_FUNC(T, Task) __List_CAT(__List_PREFIX(T), _ ## Task)
