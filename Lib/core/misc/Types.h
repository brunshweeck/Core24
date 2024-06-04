//
// Created by bruns on 05/05/2024.
//

#ifndef CORE24_TYPES_H
#define CORE24_TYPES_H

#include <core/misc/OS.h>
#include <core/misc/Compiler.h>


namespace core
{
    namespace misc
    {
        extern "C" {
        typedef char               __literal_chr_t;
        typedef unsigned long long __literal_int64_t;
        typedef long double        __literal_float64_t;

        typedef signed char    __int8_t;
        typedef unsigned char  __uint8_t;
        typedef signed short   __int16_t;
        typedef unsigned short __uint16_t;
        typedef signed int     __int32_t;
        typedef unsigned int   __uint32_t;
#if __WORDSIZE == 64
            typedef signed long         __int64_t;
            typedef unsigned long       __uint64_t;
#else
        typedef signed long long   __int64_t;
        typedef unsigned long long __uint64_t;
#endif
        typedef float               __float32_t;
        typedef double              __float64_t;
        typedef char16_t            __ucs2_t;
        typedef char32_t            __ucs4_t;
        typedef bool                __bool_t;
        typedef decltype(sizeof(1)) __memory_size_t;

        typedef _Fcomplex           __cplex32_t;
        typedef _Dcomplex           __cplex64_t;
        typedef _Lcomplex           __cplex64x_t;

        }


#ifndef CORE_ALIAS
#define CORE_ALIAS(A, T) using A = T
#endif


#ifndef CORE_ADD_AS_FRIEND
#define CORE_ADD_AS_FRIEND(T) friend T
#define CORE_ADD_TEMPLATES_AS_FRIEND(T, ...) template<class __VA_ARGS__> CORE_ADD_AS_FRIEND(class T)
#endif

#ifndef STRINGIFY
#define STRINGIFY(x) #x
#endif

#ifndef CORE_FAST_ASSERT
#define CORE_FAST_ASSERT(x) static_assert(x, STRINGIFY(x))
#define CORE_FAST_XASSERT(x, text) static_assert(x, text)
#endif

#ifndef CORE_FAST
#define CORE_FAST CORE_CONSTEXPR
#endif

#define $(...) __VA_ARGS__

#ifndef CORE_CAST
#define CORE_CAST(T, x)  ((T)(x))
#define CORE_FCAST(T, x) T(x)
#define CORE_DCAST(T, x) (dynamic_cast<T>(x))
#define CORE_XCAST(T, x) CORE_DCAST(T &, x)
#endif

#ifndef CORE_IGNORE
#define CORE_IGNORE(x) CORE_CAST(void, x)
#define CORE_HIDE_FIRST(x, y,...) ((CORE_IGNORE(x), (y __VA_ARGS__)))
#endif

#ifndef CORE_FILE
#define CORE_FILE __FILE__
#define CORE_LINE __LINE__
#endif
    } // misc
} // core


/*
 * Define the generic type (g?)
 */

// Generic Boolean (1 byte)
CORE_ALIAS(gbool, core::misc::__bool_t);
// Generic Byte    (1 byte)
CORE_ALIAS(gbyte, core::misc::__int8_t);
// Generic Short   (2 bytes)
CORE_ALIAS(gshort, core::misc::__int16_t);
// Generic Char    (2 bytes)
CORE_ALIAS(gchar, core::misc::__ucs2_t);
// Generic Integer (4 bytes)
CORE_ALIAS(gint, core::misc::__int32_t);
// Generic Float   (4 bytes)
CORE_ALIAS(gfloat, core::misc::__float32_t);
// Generic Long    (8 bytes)
CORE_ALIAS(glong, core::misc::__int64_t);
// Generic Double  (8 bytes)
CORE_ALIAS(gdouble, core::misc::__float64_t);

/**
 *  Check The validity of compiler
 */
CORE_FAST_ASSERT(sizeof(gbool) == 1L);
CORE_FAST_ASSERT(sizeof(gbyte) == 1L);
CORE_FAST_ASSERT(sizeof(gshort) == 2L);
CORE_FAST_ASSERT(sizeof(gchar) == 2L);
CORE_FAST_ASSERT(sizeof(gint) == 4L);
CORE_FAST_ASSERT(sizeof(gfloat) == 4L);
CORE_FAST_ASSERT(sizeof(glong) == 8L);
CORE_FAST_ASSERT(sizeof(gdouble) == 8L);

#ifndef CORE_TRY
#define CORE_TRY(...) try { __VA_ARGS__ }
#define CORE_CATCH(T, ...) catch (T const & ex) { __VA_ARGS__ }
#define CORE_TRY_ONLY(...) try { __VA_ARGS__ } catch(...) {}
#endif

#undef max
#undef min
#undef TRUE
#undef FALSE

#endif // CORE24_TYPES_H
