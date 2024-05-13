//
// Created by bruns on 05/05/2024.
//

#ifndef Core24_TEMPLATES_H
#define Core24_TEMPLATES_H

#include <core/misc/Types.h>

namespace core
{
    namespace misc
    {
        class ALWAYS_TRUE
        {
        public:
            static CORE_FAST gint V = 1;
        };

        class ALWAYS_FALSE
        {
        public:
            static CORE_FAST gint V = 0;
        };

        template <class X>
        class ALWAYS
        {
        public:
            CORE_ALIAS(T, X);
        };

        enum REQUEST: glong
        {
            REMOVE = 0x01,
            CONST = 0x02,
            VOL = 0x04,
            REF = 0x08,
            PTR = 0x10,
            RVAL = 0x20,
            ARR = 0x40,
            FUNC = 0x80,
            CLS, METH, PRIM, OBJ, SAME, TEMP, MEMBER, ENUM,
            ABSTRACT, CTOR, ASSIGN, SUPER, CONVERT, COMPLET,
            INT, FLT, CHR, STR, BOOLEAN, CALL, EQ, LT, DTOR,
            FINAL, EMPTY, UNION, POLY, LITERAL, TRIVIAL, VOID,
            SLIM, SIZE
        };

        template <class...>
        CORE_ALIAS(IGNORED, void);

        template <gbool>
        class CONSTANT : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class CONSTANT<false> : public virtual ALWAYS_FALSE
        {
        };

        template <gint R, class... T>
        class TEST : public virtual ALWAYS_FALSE
        {
        };

        template <gint R, class T, glong N = -1>
        class TRANSFORM : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Simalarity ] =======================================
        template <class T>
        class TEST<SAME, T, T> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ Constant   ] =======================================
        template <class T>
        class TEST<CONST, T const> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TRANSFORM<CONST, T> : public virtual ALWAYS<T const>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REMOVE, T const> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Volatile ] =======================================
        template <class T>
        class TEST<VOL, T volatile> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TRANSFORM<VOL, T> : public virtual ALWAYS<T volatile>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REMOVE, T volatile> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ References ] =======================================
        template <class T>
        class TEST<REF, T&> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TEST<REF, T&&> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TEST<RVAL, T&&> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TRANSFORM<REF, T> : public virtual ALWAYS<T&>
        {
        };

        template <class T>
        class TRANSFORM<RVAL, T> : public virtual ALWAYS<T&&>
        {
        };

        template <>
        class TRANSFORM<REF, IGNORED<>> : public virtual ALWAYS<IGNORED<>>
        {
        };

        template <>
        class TRANSFORM<RVAL, IGNORED<>> : public virtual ALWAYS<IGNORED<>>
        {
        };

        template <class T>
        class TRANSFORM<REF | REMOVE, T&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<REF | REMOVE, T&&> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Const-Vol ] =======================================
        template <class T>
        class TRANSFORM<CONST | VOL, T> : public virtual ALWAYS<T const volatile>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REMOVE, T const> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REMOVE, T volatile> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REMOVE, T const volatile> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Const-Ref ] =======================================
        template <class T>
        class TRANSFORM<CONST | REF, T> : public virtual ALWAYS<T const&>
        {
        };

        template <>
        class TRANSFORM<CONST | REF, IGNORED<>> : public virtual ALWAYS<IGNORED<>>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REF | REMOVE, T const> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REF | REMOVE, T&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REF | REMOVE, T&&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REF | REMOVE, T const&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | REF | REMOVE, T const&&> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Vol-Ref ] =======================================
        template <class T>
        class TRANSFORM<VOL | REF, T> : public virtual ALWAYS<T volatile&>
        {
        };

        template <>
        class TRANSFORM<VOL | REF, IGNORED<>> : public virtual ALWAYS<IGNORED<>>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REF | REMOVE, T volatile> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REF | REMOVE, T&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REF | REMOVE, T&&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REF | REMOVE, T volatile&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<VOL | REF | REMOVE, T volatile&&> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Const-Vol-Ref ] =======================================
        template <class T>
        class TRANSFORM<CONST | VOL | REF, T> : public virtual ALWAYS<T const volatile&>
        {
        };

        template <>
        class TRANSFORM<CONST | VOL | REF, IGNORED<>> : public virtual ALWAYS<IGNORED<>>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T volatile> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T&&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T volatile&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const&&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T volatile&&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const volatile> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const volatile&> : public virtual ALWAYS<T>
        {
        };

        template <class T>
        class TRANSFORM<CONST | VOL | REF | REMOVE, T const volatile&&> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Pointers ] =======================================
        template <class T>
        class TEST<PTR, T*> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TEST<PTR, T[]> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<PTR, T[0]> : public virtual ALWAYS_FALSE
        {
        };

        template <class T, glong N>
        class TEST<PTR, T[N]> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TRANSFORM<PTR, T> : public virtual ALWAYS<T*>
        {
        };

        template <class T>
        class TRANSFORM<PTR, T&> : public virtual ALWAYS<T*>
        {
        };

        template <class T>
        class TRANSFORM<PTR, T&&> : public virtual ALWAYS<T*>
        {
        };

        template <class T>
        class TRANSFORM<PTR | REMOVE, T*> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Array ] =======================================
        template <class T>
        class TEST<ARR, T[]> : public virtual ALWAYS_TRUE
        {
        };

        template <class T, glong N>
        class TEST<ARR, T[N]> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TRANSFORM<ARR, T> : public virtual ALWAYS<T[]>
        {
        };

        template <class T>
        class TRANSFORM<ARR, T, 0> : public virtual ALWAYS<T[0]>
        {
        };

        template <class T, glong N>
        class TRANSFORM<ARR, T, N> : public virtual ALWAYS<T[N]>
        {
            CORE_FAST_ASSERT(N >= 0);
        };

        template <class T>
        class TRANSFORM<ARR | REMOVE, T[]> : public virtual ALWAYS<T>
        {
        };

        template <class T, glong N>
        class TRANSFORM<ARR | REMOVE, T[N]> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Templates ] =======================================
        template <template <class...> class T, class... P>
        class TEST<TEMP, T<P...>> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ Statics Functions/ Statics Methods ] =======================================
        template <class T>
        class TEST<FUNC, T> : public virtual TEST<CONST | REMOVE, T const>
        {
        };

        template <class R>
        class TEST<FUNC, R()> : public virtual ALWAYS_TRUE
        {
        };

        template <class R>
        class TEST<FUNC, R(...)> : public virtual ALWAYS_TRUE
        {
        };

        template <class R, class... T>
        class TEST<FUNC, R(T...)> : public virtual ALWAYS_TRUE
        {
        };

        template <class R, class... T>
        class TEST<FUNC, R(T..., ...)> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ class Member ] =======================================
        template <class T, class C>
        class TEST<MEMBER, T C::*> : public virtual ALWAYS_TRUE
        {
        };

#ifdef CORE_COMPILER_CLANG
        template <class T>
        class TEST<MEMBER, T> : public virtual CONSTANT<__is_member_pointer(T)>
        {
        };
#endif


        // ============================ [ Non-Statics Methods ] =======================================


#ifdef CORE_COMPILER_CLANG
        template <class T>
        class TEST<MEMBER, T> : public virtual CONSTANT<__is_member_function_pointer(T)>
        {
        };

#else
        template <class T, class C>
        class TEST<MEMBER, T (C::*)()> : public virtual ALWAYS_TRUE
        {
        };

        template <class T, class C>
        class TEST<MEMBER, T (C::*)(...)> : public virtual ALWAYS_TRUE
        {
        };

        template <class T, class C, class... A>
        class TEST<MEMBER, T (C::*)(A...)> : public virtual ALWAYS_TRUE
        {
        };

        template <class T, class C, class... A>
        class TEST<MEMBER, T (C::*)(A..., ...)> : public virtual ALWAYS_TRUE
        {
        };
#endif

        // ============================ [ Abstracts Class ] =======================================
        template <class T>
        class TEST<ABSTRACT, T> : public virtual CONSTANT<__is_abstract(T)>
        {
        };

        // ============================ [ Enumerations ] =======================================
        template <class T>
        class TEST<ENUM, T> : public virtual CONSTANT<__is_enum(T)>
        {
        };

        // ============================ [ Class ] =======================================
        template <class T>
        class TEST<CLS, T> : public virtual CONSTANT<__is_class(T)>
        {
        };

        // ============================ [ Constructors ] =======================================
        template <class T, class... A>
        class TEST<CTOR, T, A...>
        {
            template <class C, class... P, gint = sizeof C>
            static CONSTANT<__is_constructible(C, P...)> test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

        public:
            static CORE_FAST gint V = decltype(test<T, A...>(0))::V;
        };

        template <class T>
        class TEST<CTOR, T, IGNORED<T>> : public virtual TEST<CTOR, T>
        {
        };

        // ============================ [ Assignable ] =======================================
        template <class T, class V>
        class TEST<ASSIGN, T, V> : public virtual CONSTANT<__is_assignable(T, V)>
        {
        };

        // ============================ [ Super class ] =======================================
        template <class S, class T>
        class TEST<SUPER, S, T> : public virtual CONSTANT<__is_base_of(S, T)>
        {
        };

        // ============================ [ False Declaration ] =======================================
        template <class T, class R = T&&>
        static R declImpl(gint);

        template <class T>
        static T declImpl(...);

        template <class T>
        static decltype(declImpl<T>(0)) decl();

        // ============================ [ Implicitly Convertible ] =======================================
#ifdef CORE_COMPILER_MSVC
        template <class F, class T>
        class TEST<CONVERT, F, T> : public virtual CONSTANT<__is_convertible_to(F, T)>
        {
        };

#else
        template <class F, class T>
        class TEST<CONVERT, F, T>
        {
            CORE_WARNING_PUSH
            CORE_WARNING_DISABLE_GCC("-Wctor-dtor-privacy")

            template <class X>
            static void call(X)
            {
            }

            template <class A, class B, class = decltype(call<B>(decl<A>()))>
            static ALWAYS_TRUE test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

            CORE_WARNING_POP

        public:
            static CORE_FAST gint V = decltype(test<F, T>(0))::V;
        };
#endif


        // ============================ [ Completes type (Sizable type) ] =======================================
        template <class T>
        class TEST<COMPLET, T>
        {
            template <class C, gint = sizeof(decl<C>())>
            static ALWAYS_TRUE test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

        public:
            static CORE_FAST gint V = decltype(test<T>(0))::V
                                      | TEST<INT, T>::V
                                      | TEST<FLT, T>::V
                                      | TEST<CHR, T>::V
                                      | TEST<BOOLEAN, T>::V
                                      | TEST<STR, T>::V;
        };

        template <>
        class TEST<COMPLET, void> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<COMPLET, T[]> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<COMPLET, T*> : public virtual ALWAYS_TRUE
        {
        };

        template <class T>
        class TEST<COMPLET, T[0]> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ Integers ] =======================================
        template <>
        class TEST<INT, __int8_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __uint8_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __int16_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __uint16_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __int32_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __uint32_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __int64_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, __uint64_t> : public virtual ALWAYS_TRUE
        {
        };

#ifdef __INT128__
        template <>
        class TEST<INT, __int128> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __int128> : public virtual ALWAYS_TRUE
        {
        };

#elif defined(__SIZEOF_INT128__)
        template <>
        class TEST<INT, __int128> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __int128> : public virtual ALWAYS_TRUE
        {
        };

#elif defined(__GLIBCXX_TYPE_INT_N_0)
        template <>
        class TEST<INT, __GLIBCXX_TYPE_INT_N_0> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __GLIBCXX_TYPE_INT_N_0> : public virtual ALWAYS_TRUE
        {
        };

#elif defined(__GLIBCXX_TYPE_INT_N_1)
        template <>
        class TEST<INT, __GLIBCXX_TYPE_INT_N_1> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __GLIBCXX_TYPE_INT_N_1> : public virtual ALWAYS_TRUE
        {
        };

#elif defined(__GLIBCXX_TYPE_INT_N_2)
        template <>
        class TEST<INT, __GLIBCXX_TYPE_INT_N_2> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __GLIBCXX_TYPE_INT_N_2> : public virtual ALWAYS_TRUE
        {
        };

#elif defined(__GLIBCXX_TYPE_INT_N_3)
        template <>
        class TEST<INT, __GLIBCXX_TYPE_INT_N_3> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<INT, unsigned __GLIBCXX_TYPE_INT_N_3> : public virtual ALWAYS_TRUE
        {
        };

#endif


        // ============================ [ Floating ] =======================================
        template <>
        class TEST<FLT, __float32_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<FLT, __float64_t> : public virtual ALWAYS_TRUE
        {
        };

#if defined(__FLOAT128__) || defined(__SIZEOF_FLOAT128__) || !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_FLOAT128)

        template <>
        class TEST<FLT, __float128> : public virtual ALWAYS_TRUE
        {
        };

#endif


        // ============================ [ Characters ] =======================================
        template <>
        class TEST<CHR, __int8_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<CHR, __uint8_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<CHR, __ucs2_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<CHR, __ucs4_t> : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class TEST<CHR, wchar_t> : public virtual ALWAYS_TRUE
        {
        };

#if __cpp_lib_char8_t
        template <>
        class TEST<CHR, char8_t> : public virtual ALWAYS_TRUE
        {
        };

#endif
        // ============================ [ Booleans ] =======================================
        template <>
        class TEST<BOOLEAN, __bool_t> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ Condition ] =======================================
        template <class T, class, gbool>
        class IF_OR_ELSE : public virtual ALWAYS<T>
        {
        };

        template <class T, class U>
        class IF_OR_ELSE<T, U, false> : public virtual ALWAYS<U>
        {
        };

        template <class T, gbool Condition>
        class ONLY_IF : public virtual ALWAYS_FALSE
        {
            CORE_FAST_XASSERT(Condition, "Incompatible type");
        };

        template <class T>
        class ONLY_IF<T, true> : public virtual ALWAYS<T>
        {
        };

        // ============================ [ Callable ] =======================================
        template <class R>
        class TEST<CALL, R()> : public virtual ALWAYS_TRUE
        {
        };

        template <class R>
        class TEST<CALL, R(), void> : public virtual ALWAYS_TRUE
        {
        };

        template <class R>
        class TEST<CALL, R(...)> : public virtual ALWAYS_TRUE
        {
        };

        template <class R>
        class TEST<CALL, R(...), void> : public virtual ALWAYS_TRUE
        {
        };

        template <class R, class... A>
        class TEST<CALL, R(A...), A...> : public virtual ALWAYS_TRUE
        {
        };

        template <class R, class... A>
        class TEST<CALL, R(A..., ...), A...> : public virtual ALWAYS_TRUE
        {
        };


        template <class C, class... A>
        class TEST<CALL, C, A...>
        {
            template <class T, class... P>
            static ALWAYS<decltype(CORE_FCAST(decl<T>(), decl<P>()...))> callTest(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE callTest(...) { return {}; }

        public:
            CORE_ALIAS(T, decltype(callTest<C, A...>(0)));
            static CORE_FAST gint V = ~TEST<SAME, T, ALWAYS_FALSE>::V & 0x1;
        };


        template <class R, class C, class I, class... A>
        class TEST<CALL, R C::*, I, A...>
        {
            template <class Cl, class Rt, class... P>
            static ALWAYS<decltype((decl<Rt>().*decl<Cl>())(decl<P>()...))> callTest1(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE callTest1(...) { return {}; }

            template <class Cl, class Rt, class... P>
            static ALWAYS<decltype(((*decl<Rt>()).*decl<Cl>())(decl<P>()...))> callTest2(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE callTest2(...) { return {}; }

            CORE_ALIAS(Obj,) typename TRANSFORM<REF | REMOVE, I>::T;

            CORE_ALIAS(T1, decltype(callTest1<R C::*, Obj, A...>(0)));
            CORE_ALIAS(T2, decltype(callTest2<R C::*, Obj, A...>(0)));

        public:
            CORE_ALIAS(T,) typename IF_OR_ELSE<T1, T2, TEST<SAME, T1, ALWAYS_FALSE>::V>::T;
            static CORE_FAST gint V = ~TEST<SAME, T, ALWAYS_FALSE>::V & 0x1;
        };


        template <class T>
        class TEST<CALL, T, IGNORED<T>> : public virtual TEST<CALL, T>
        {
        };

        // ============================ [ String ] =======================================
        template <class T>
        class TEST<STR, T*> : public virtual TEST<CHR, T>
        {
        };

        template <class T, glong N>
        class TEST<STR, T[N]> : public virtual TEST<CHR, T>
        {
        };

        template <class T>
        class TEST<STR, T[0]> : public virtual TEST<CHR, T>
        {
        };

        template <class T>
        class TEST<STR, T[]> : public virtual ALWAYS_FALSE
        {
            CORE_FAST_XASSERT((TEST<COMPLET, T[]>::V), "Unbounded String type");
        };

        // ============================ [ EQUALITY ] =======================================
        template <class T>
        class TEST<EQ, T>
        {
            template <class A, class = decltype(decl<A>() == decl<A>())>
            static ALWAYS_TRUE test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

        public:
            static CORE_FAST gbool V = decltype(test<T>(0))::V;
        };

        // ============================ [ LESS-THAN ] =======================================
        template <class T>
        class TEST<LT, T>
        {
            template <class A, class = decltype(decl<A>() < decl<A>())>
            static ALWAYS_TRUE test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

        public:
            static CORE_FAST gbool V = decltype(test<T>(0))::V;
        };

        // ============================ [ DESTRUCTIBLE ] =======================================
        template <class T>
        class TEST<DTOR, T>
        {
            template <class A, class = decltype(decl<A>().~A())>
            static ALWAYS_TRUE test(gint) { return {}; }

            template <class...>
            static ALWAYS_FALSE test(...) { return {}; }

        public:
            static CORE_FAST gbool V = decltype(test<T>(0))::V;
        };

        // ============================ [ Prim to Class Models ] =======================================
        // template <> class TRANSFORM<CLS, __bool_t>: public virtual ALWAYS<Boolean> {};
        // template <> class TRANSFORM<CLS, __int8_t>: public virtual ALWAYS<Byte> {};
        // template <> class TRANSFORM<CLS, __uint8_t>: public virtual ALWAYS<Byte> {};
        // template <> class TRANSFORM<CLS, __int16_t>: public virtual ALWAYS<Short> {};
        // template <> class TRANSFORM<CLS, __uint16_t>: public virtual ALWAYS<Short> {};
        // template <> class TRANSFORM<CLS, __int32_t>: public virtual ALWAYS<Integer> {};
        // template <> class TRANSFORM<CLS, __uint32_t>: public virtual ALWAYS<Integer> {};
        // template <> class TRANSFORM<CLS, __int64_t>: public virtual ALWAYS<Long> {};
        // template <> class TRANSFORM<CLS, __uint64_t>: public virtual ALWAYS<Long> {};
        // template <> class TRANSFORM<CLS, __int128>: public virtual ALWAYS<BigInteger> {};
        // template <> class TRANSFORM<CLS, __uint128>: public virtual ALWAYS<BigInteger> {};
        // template <> class TRANSFORM<CLS, __float32_t>: public virtual ALWAYS<Float> {};
        // template <> class TRANSFORM<CLS, __float64_t>: public virtual ALWAYS<Double> {};
        // template <> class TRANSFORM<CLS, __float128>: public virtual ALWAYS<BigDecimal> {};
        // template <> class TRANSFORM<CLS, __ucs2_t>: public virtual ALWAYS<Character> {};
        // template <> class TRANSFORM<CLS, __ucs4_t>: public virtual ALWAYS<Integer> {};
        // template <> class TRANSFORM<CLS, void>: public virtual ALWAYS<Void> {};

        // template <glong N> class TRANSFORM<CLS, __bool_t[N]>: public virtual ALWAYS<BooleanArray> {};
        // template <glong N> class TRANSFORM<CLS, __int8_t[N]>: public virtual ALWAYS<ByteArray> {};
        // template <glong N> class TRANSFORM<CLS, __uint8_t[N]>: public virtual ALWAYS<ByteArray> {};
        // template <glong N> class TRANSFORM<CLS, __int16_t[N]>: public virtual ALWAYS<ShortArray> {};
        // template <glong N> class TRANSFORM<CLS, __uint16_t[N]>: public virtual ALWAYS<ShortArray> {};
        // template <glong N> class TRANSFORM<CLS, __int32_t[N]>: public virtual ALWAYS<IntArray> {};
        // template <glong N> class TRANSFORM<CLS, __uint32_t[N]>: public virtual ALWAYS<IntArray> {};
        // template <glong N> class TRANSFORM<CLS, __int64_t[N]>: public virtual ALWAYS<LongArray> {};
        // template <glong N> class TRANSFORM<CLS, __uint64_t[N]>: public virtual ALWAYS<LongArray> {};
        // template <glong N> class TRANSFORM<CLS, __int128[N]>: public virtual ALWAYS<Array<BigInteger>> {};
        // template <glong N> class TRANSFORM<CLS, __uint128[N]>: public virtual ALWAYS<Array<BigInteger>> {};
        // template <glong N> class TRANSFORM<CLS, __float32_t[N]>: public virtual ALWAYS<FloatArray> {};
        // template <glong N> class TRANSFORM<CLS, __float64_t[N]>: public virtual ALWAYS<DoubleArray> {};
        // template <glong N> class TRANSFORM<CLS, __float128[N]>: public virtual ALWAYS<Array<BigDecimal>> {};
        // template <glong N> class TRANSFORM<CLS, __ucs2_t[N]>: public virtual ALWAYS<CharArray> {};
        // template <glong N> class TRANSFORM<CLS, __ucs4_t[N]>: public virtual ALWAYS<IntArray> {};

        // template <class T> class TRANSFORM<CLS, T const>: public virtual TRANSFORM<CLS, T> {};
        // template <class T> class TRANSFORM<CLS, T &>: public virtual TRANSFORM<CLS, T> {};
        // template <class T> class TRANSFORM<CLS, T &&>: public virtual TRANSFORM<CLS, T> {};
        // template <class T> class TRANSFORM<CLS, T volatile>: public virtual TRANSFORM<CLS, T> {};
        // template <class T> class TRANSFORM<CLS, T const volatile>: public virtual TRANSFORM<CLS, T> {};
        // template <class T> class TRANSFORM<CLS, T *>: public virtual ALWAYS<Object> {};
        // template <class T, glong N> class TRANSFORM<CLS, T[N]>: public virtual ALWAYS<Array<typename TRANSFORM<CLS, T>::T>> {};

        // ============================ [ Class to Prim Models ] =======================================
        // template <> class TRANSFORM<PRIM, Boolean>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Byte>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Short>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Character>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Integer>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Float>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Long>: public virtual ALWAYS<gbool> {};
        // template <> class TRANSFORM<PRIM, Double>: public virtual ALWAYS<gbool> {};

        // template <class E> class TRANSFORM<PRIM, Enum<E>>: public virtual ALWAYS<E> {};

        // ============================ [ All Of ... Is True ] =======================================
        template <gbool...>
        class ALL_IS_TRUE : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class ALL_IS_TRUE<true> : public virtual ALWAYS_TRUE
        {
        };

        template <gbool ... bs>
        class ALL_IS_TRUE<true, bs...> : public virtual ALL_IS_TRUE<bs...>
        {
        };

        template <>
        class ALL_IS_TRUE<false> : public virtual ALWAYS_FALSE
        {
        };

        template <gbool ... bs>
        class ALL_IS_TRUE<false, bs...> : public virtual ALWAYS_FALSE
        {
        };

        // ============================ [ One of ... Is True ] =======================================
        template <gbool...>
        class ONE_IS_TRUE : public virtual ALWAYS_TRUE
        {
        };

        template <>
        class ONE_IS_TRUE<true> : public virtual ALWAYS_TRUE
        {
        };

        template <gbool ... bs>
        class ONE_IS_TRUE<false, bs...> : public virtual ONE_IS_TRUE<bs...>
        {
        };

        template <>
        class ONE_IS_TRUE<false> : public virtual ALWAYS_FALSE
        {
        };

        template <gbool ... bs>
        class ONE_IS_TRUE<true, bs...> : public virtual ALWAYS_TRUE
        {
        };

        // ============================ [ FINAL ] =======================================
        template <class T>
        class TEST<FINAL, T> : public virtual CONSTANT<__is_final(T)>
        {
        };

        // ============================ [ UNION ] =======================================
        template <class T>
        class TEST<UNION, T> : public virtual CONSTANT<__is_union(T)>
        {
        };

        // ============================ [ EMPTY ] =======================================
        template <class T>
        class TEST<EMPTY, T> : public virtual CONSTANT<__is_empty(T)>
        {
        };

        // ============================ [ POLYMORPHIC ] =======================================
        template <class T>
        class TEST<POLY, T> : public virtual CONSTANT<__is_polymorphic(T)>
        {
        };

        // ============================ [ LITERAL ] =======================================
        template <class T>
        class TEST<LITERAL, T> : public virtual CONSTANT<__is_literal_type(T)>
        {
        };

        // ============================ [ TRIVIAL ] =======================================
        template <class T>
        class TEST<TRIVIAL, T> : public virtual CONSTANT<__is_trivial(T)>
        {
        };

        // ============================ [ VOID ] =======================================
        template <class T>
        class TEST<VOID, T> : public virtual TEST<SAME, T, IGNORED<T>>
        {
        };

        // ============================ [ SLIM Style ] =======================================
        template <class T>
        class TEST<SLIM, T const> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<SLIM, T volatile> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<SLIM, T*> : public virtual TEST<SLIM, T>
        {
        };

        template <class T>
        class TEST<SLIM, T const volatile> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<SLIM, T&> : public virtual ALWAYS_FALSE
        {
        };

        template <class T>
        class TEST<SLIM, T&&> : public virtual ALWAYS_FALSE
        {
        };

        template <class T, glong N>
        class TEST<SLIM, T[N]> : public virtual TEST<SLIM, T>
        {
        };

        template <class T>
        class TEST<SLIM, T[0]> : public virtual TEST<SLIM, T>
        {
        };

        template <class T>
        class TEST<SLIM, T[]> : public virtual TEST<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T const> : public virtual TRANSFORM<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T volatile> : public virtual TRANSFORM<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T const volatile> : public virtual TRANSFORM<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T&> : public virtual TRANSFORM<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T&&> : public virtual TRANSFORM<SLIM, T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T*> : public virtual TRANSFORM<PTR, typename TRANSFORM<SLIM, T>::T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T[]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, const T[]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, volatile T[]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, const volatile T[]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, T[0]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, 0>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, const T[0]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, 0>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, volatile T[0]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, 0>
        {
        };

        template <class T>
        class TRANSFORM<SLIM, const volatile T[0]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, 0>
        {
        };

        template <class T, glong N>
        class TRANSFORM<SLIM, T[N]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, N>
        {
        };

        template <class T, glong N>
        class TRANSFORM<SLIM, const T[N]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, N>
        {
        };

        template <class T, glong N>
        class TRANSFORM<SLIM, volatile T[N]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, N>
        {
        };

        template <class T, glong N>
        class TRANSFORM<SLIM, const volatile T[N]> : public virtual TRANSFORM<ARR, typename TRANSFORM<SLIM, T>::T, N>
        {
        };

        // ============================ [ InstanceOf ] =======================================
        template <class T>
        class TEST<SUPER, T> : public virtual ALWAYS_FALSE
        {
        public:
            template <gbool isClass, class S = T>
            class IMPL
            {
            public:
                template <class E>
                static CORE_FAST gbool checkInstance(E&& e)
                {
                    CORE_ALIAS(T1, ) typename TRANSFORM<CONST | VOL | REF | REMOVE, S>::T;
                    CORE_ALIAS(T2, ) typename TRANSFORM<CONST | VOL | REF | REMOVE, E>::T;

                    CORE_ALIAS(S, ) typename TRANSFORM<PTR, T2>::T;
                    CORE_ALIAS(D, ) typename TRANSFORM<PTR, T1>::T;

                    return CORE_DCAST(D, CORE_FCAST(S, &e)) != 0;
                }
            };

            template <class S>
            class IMPL<false, S>
            {
            public:
                template <class E>
                static CORE_FAST gbool checkInstance(E&&)
                {
                    return TEST<SAME, S, E>::V != 0;
                }
            };

            template <class E>
            static CORE_FAST gbool checkValue(E&&)
            {
                return (TEST<CTOR, T, E>::V | TEST<CONVERT, E, T>::V) != 0;
            }
        };

        // ============================ [ SIZE ] =======================================
        template <class T, gbool Condition = TEST<COMPLET, T>::V != 0>
        class MEMORY_SIZE
        {
        public:
            static CORE_FAST gint V = (gint) sizeof T;
        };

        template <class T>
        class MEMORY_SIZE<T, false>
        {
        public:
            static CORE_FAST gint V = 0;
        };

        // ============================ [  ] =======================================
    }
} // core

#endif // Core24_TEMPLATES_H
