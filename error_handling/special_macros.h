
#define GET_ARG_1(a,...) a
#define GET_ARG_2(a,b,...) b
#define GET_ARG_3(a,b,c,...) c
#define GET_ARG_4(a,b,c,d,...) d
#define GET_ARG_5(a,b,c,d,e,...) e
#define GET_ARG_6(a,b,c,d,e,f,...) f

#define MULTI_CHAR_CONST_8(a,b,c,d,e,f,g,h)     \
        ((((unsigned long long)                 \
        MULTI_CHAR_CONST_4(e,f,g,h)) << 32) |   \
        MULTI_CHAR_CONST_4(a,b,c,d))

#define MULTI_CHAR_CONST_4(a,b,c,d)            \
      ((MULTI_CHAR_CONST_2(c,d) << 16) |       \
        MULTI_CHAR_CONST_2(a,b))

#define MULTI_CHAR_CONST_2(a,b) ((b << 8) | a)

#define EMPTY()

#define EVAL(...)     EVAL1024(        __VA_ARGS__)
#define EVAL1024(...) EVAL512 (EVAL512(__VA_ARGS__))
#define EVAL512(...)  EVAL256 (EVAL256(__VA_ARGS__))
#define EVAL256(...)  EVAL128 (EVAL128(__VA_ARGS__))
#define EVAL128(...)  EVAL64  (EVAL64 (__VA_ARGS__))
#define EVAL64(...)   EVAL32  (EVAL32 (__VA_ARGS__))
#define EVAL32(...)   EVAL16  (EVAL16 (__VA_ARGS__))
#define EVAL16(...)   EVAL8   (EVAL8  (__VA_ARGS__))
#define EVAL8(...)    EVAL4   (EVAL4  (__VA_ARGS__))
#define EVAL4(...)    EVAL2   (EVAL2  (__VA_ARGS__))
#define EVAL2(...)    EVAL1   (EVAL1  (__VA_ARGS__))
#define EVAL1(...)                     __VA_ARGS__

#define DEFER1(m) m EMPTY()
#define DEFER2(m) m EMPTY EMPTY()()
#define DEFER3(m) m EMPTY EMPTY EMPTY()()()
#define DEFER4(m) m EMPTY EMPTY EMPTY EMPTY()()()()

#define IS_PROBE(...) GET_ARG_2(__VA_ARGS__, 0)
#define PROBE() ~, 1

#define CAT(a,b) a ## b

#define NOT(x) IS_PROBE(CAT(_NOT_, x))
#define _NOT_0 PROBE()

#define BOOL(x) NOT(NOT(x))

#define IF_ELSE(condition) _IF_ELSE(BOOL(condition))
#define _IF_ELSE(condition) CAT(_IF_, condition)

#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

#define HAS_ARGS(...) BOOL(GET_ARG_1(_END_OF_ARGUMENTS_ __VA_ARGS__)())
#define _END_OF_ARGUMENTS_() 0

#define MAP(m, first, ...)           \
  m(first)                           \
  IF_ELSE(HAS_ARGS(__VA_ARGS__))(    \
    DEFER2(_MAP)()(m, __VA_ARGS__)   \
  )(                                 \
    /* Do nothing, just terminate */ \
  )
#define _MAP() MAP
