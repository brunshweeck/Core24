//
// Created by bruns on 05/05/2024.
//

#ifndef Core24_CLASS_H
#define Core24_CLASS_H

#include <core/misc/Literals.h>

namespace core
{
    /**
     * The class @Class wrap multiple statics methods used to
     * determine status of any types and it different template versions.
     *
     * @tparam T The target type
     */
    template <class T>
    class Class CORE_FINAL
    {
        CORE_IMPLICIT Class()
        {
        }

    public:
        // ======================= [ type native versions ] =======================

        // Constant version
        CORE_ALIAS(Constant,) typename misc::TRANSFORM<misc::CONST, T>::T;
        CORE_ALIAS(Mutable,) typename misc::TRANSFORM<misc::CONST | misc::REMOVE, T>::T;

        CORE_ALIAS(Const, Constant);
        CORE_ALIAS(NoConstant, Mutable);
        CORE_ALIAS(NConst, NoConstant);

        // Volatile version
        CORE_ALIAS(Volatile,) typename misc::TRANSFORM<misc::VOL, T>::T;
        CORE_ALIAS(ConstVolatile,) typename misc::TRANSFORM<misc::VOL, Constant>::T;
        CORE_ALIAS(NoVolatile,) typename misc::TRANSFORM<misc::VOL | misc::REMOVE, T>::T;
        CORE_ALIAS(NoConstVolatile,) typename misc::TRANSFORM<misc::VOL | misc::REMOVE, NoConstant>::T;

        CORE_ALIAS(Vol, Volatile);
        CORE_ALIAS(NVol, NoVolatile);
        CORE_ALIAS(NConstVol, NoConstVolatile);
        CORE_ALIAS(NCVol, NConstVol);

        // Pointer version
        CORE_ALIAS(Pointer,) typename misc::TRANSFORM<misc::PTR, T>::T;
        CORE_ALIAS(PointerTarget,) typename misc::TRANSFORM<misc::PTR | misc::REMOVE, T>::T;
        CORE_ALIAS(NoPointer, PointerTarget);

        CORE_ALIAS(Ptr, Pointer);
        CORE_ALIAS(NPtr, NoPointer);

        // References version
        CORE_ALIAS(Reference,) typename misc::TRANSFORM<misc::REF, T>::T;
        CORE_ALIAS(ConstReference,) typename misc::TRANSFORM<misc::REF, Constant>::T;
        CORE_ALIAS(VolReference,) typename misc::TRANSFORM<misc::REF, Volatile>::T;
        CORE_ALIAS(ConstVolReference,) typename misc::TRANSFORM<misc::REF, ConstVolatile>::T;

        CORE_ALIAS(Rvalue,) typename misc::TRANSFORM<misc::RVAL, T>::T;

        CORE_ALIAS(NoReference,) typename misc::TRANSFORM<misc::REF | misc::REMOVE, T>::T;
        CORE_ALIAS(NoConstReference,) typename misc::TRANSFORM<misc::CONST | misc::REMOVE, NoReference>::T;
        CORE_ALIAS(NoVolReference,) typename misc::TRANSFORM<misc::VOL | misc::REMOVE, NoReference>::T;
        CORE_ALIAS(NoConstVolReference,) typename misc::TRANSFORM<misc::CONST | misc::REMOVE, NoVolReference>::T;

        CORE_ALIAS(Ref, Reference);
        CORE_ALIAS(CRef, ConstReference);
        CORE_ALIAS(VRef, VolReference);
        CORE_ALIAS(CVRef, ConstVolReference);
        CORE_ALIAS(NRef, NoReference);
        CORE_ALIAS(NConstRef, NoConstReference);
        CORE_ALIAS(NVolRef, NoVolReference);
        CORE_ALIAS(NConstVolRef, NoReference);
        CORE_ALIAS(NCRef, NConstRef);
        CORE_ALIAS(NVRef, NVolRef);
        CORE_ALIAS(NCVRef, NConstVolRef);

        // Arrays version
        template <glong N>
        CORE_ALIAS(Array,) typename misc::TRANSFORM<misc::ARR, T, N>::T;

        CORE_ALIAS(ArrayElement,) typename misc::TRANSFORM<misc::ARR | misc::REMOVE, T>::T;

        // Slimmed version
        CORE_ALIAS(Slim,) typename misc::TRANSFORM<misc::SLIM, T>::T;

        // ======================= [ type conditionnal test ] =======================

        // Irreversible conditions
        /**
         * Enable the template type (@c T), if and only if
         * the condition result is @c true.
         * @code
         *  if (condition) ... else {error}
         *
         *  tempate <class T>
         *  using AlwaysNumber = Class<T>::OnlyIf<Class<Number>::isSuper<T>()>;
         *
         *  AlwaysNumber<Double> // Double
         *  AlwaysNumber<String> // error
         * @endcode
         *
         * @param Condition the condition result
         */
        template <gbool Condition>
        CORE_ALIAS(OnlyIf,) typename misc::ONLY_IF<T, Condition>::T;

        // Reversible conditions
        /**
         * Enable the template type (@c T), if and only if
         * the condition result is @c true.
         * @code
         *  if (condition) ... else ...
         *
         *  tempate <class T>
         *  using AlwaysNumber = Class<T>::IfElse<Class<Number>::isSuper<T>(), Integer>;
         *
         *  AlwaysNumber<Double> // Double
         *  AlwaysNumber<String> // Integer
         * @endcode
         *
         * @param Condition the condition result
         */
        template <gbool Condition, class U>
        CORE_ALIAS(IfElse,) typename misc::IF_OR_ELSE<T, U, Condition>::T;

        // ======================= [ type status ] =======================

        // same types
        template <class To>
        static CORE_FAST gbool isSame()
        {
            return misc::TEST<misc::SAME, T, To>::V != 0;
        }

        // constants types
        static CORE_FAST gbool isConstant()
        {
            return misc::TEST<misc::CONST, T>::V != 0;
        }

        // volatiles types
        static CORE_FAST gbool isVolatile()
        {
            return misc::TEST<misc::VOL, T>::V != 0;
        }

        // pointers types
        static CORE_FAST gbool isPointer()
        {
            return misc::TEST<misc::PTR, T>::V != 0;
        }

        // references types
        static CORE_FAST gbool isReference()
        {
            return misc::TEST<misc::REF, T>::V != 0;
        }

        static CORE_FAST gbool isRvalue()
        {
            return misc::TEST<misc::RVAL, T>::V != 0;
        }

        static CORE_FAST gbool isArray()
        {
            return misc::TEST<misc::ARR, T>::V != 0;
        }

        static CORE_FAST gbool isComplete()
        {
            return misc::TEST<misc::COMPLET, T>::V != 0;
        }

        static CORE_FAST gbool isTemplate()
        {
            return misc::TEST<misc::TEMP, T>::V != 0;
        }

        static CORE_FAST gbool isFunction()
        {
            return misc::TEST<misc::FUNC, T>::V != 0;
        }

        static CORE_FAST gbool isMember()
        {
            return misc::TEST<misc::MEMBER, T>::V != 0;
        }

        static CORE_FAST gbool isFunctionMember()
        {
            return misc::TEST<misc::METH, T>::V != 0;
        }

        static CORE_FAST gbool isAbstract()
        {
            return misc::TEST<misc::ABSTRACT, T>::V != 0;
        }

        static CORE_FAST gbool isEnum()
        {
            return misc::TEST<misc::ENUM, T>::V != 0;
        }

        static CORE_FAST gbool isClass()
        {
            return misc::TEST<misc::CLS, NCVRef>::V != 0 || __is_union(T);
        }

        static CORE_FAST gbool isAggregate()
        {
            return isClass() || isArray();
        }

        static CORE_FAST gbool isDestructible()
        {
            return misc::TEST<misc::DTOR, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isFinal()
        {
            return misc::TEST<misc::FINAL, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isEmpty()
        {
            return misc::TEST<misc::EMPTY, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isLiteral()
        {
            return misc::TEST<misc::LITERAL, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isPolymorphic()
        {
            return misc::TEST<misc::POLY, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isTrivial()
        {
            return misc::TEST<misc::TRIVIAL, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isInteger()
        {
            return misc::TEST<misc::INT, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isFloating()
        {
            return misc::TEST<misc::FLT, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isNumber()
        {
            return isInteger() || isFloating();
        }

        static CORE_FAST gbool isIntegral()
        {
            return isInteger() || isEnum() || isCharacter() || isBoolean();
        }

        static CORE_FAST gbool isBoolean()
        {
            return misc::TEST<misc::BOOLEAN, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isVoid()
        {
            return misc::TEST<misc::VOID, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isPrimitive()
        {
            return isVoid() || isString() || isCharacter() || isBoolean() || isNumber() || isArray() || isPointer();
        }

        static CORE_FAST gbool isCharacter()
        {
            return misc::TEST<misc::CHR, NCVRef>::V != 0;
        }

        static CORE_FAST gbool isString()
        {
            return misc::TEST<misc::STR, NCVRef>::V != 0
                   || isArray() && Class<ArrayElement>::isCharacter()
                   || isPointer() && Class<PointerTarget>::isCharacter();
        }

        /**
         * Check if this template type (@c T) has no qualifiers: @c const, @c &, @c && and @c volatile
         * @return @c true if @c T has no qualifiers: @c const, @c &, @c && and @c volatile
         */
        static CORE_FAST gbool isSlimmed()
        {
            return misc::TEST<misc::SLIM, T>::V != 0;
        }

        static CORE_FAST gbool supportEQ()
        {
            return misc::TEST<misc::EQ, T>::V != 0;
        }

        static CORE_FAST gbool supportLT()
        {
            return misc::TEST<misc::LT, T>::V != 0;
        }

        static CORE_FAST gbool isConstructible()
        {
            return misc::TEST<misc::CTOR, NCVRef, misc::IGNORED<T>>::V != 0;
        }

        template <class... Args>
        static CORE_FAST gbool isConstructible()
        {
            return misc::TEST<misc::CTOR, NCVRef, Args...>::V != 0;
        }

        template <class To>
        static CORE_FAST gbool isAssignable()
        {
            return misc::TEST<misc::ASSIGN, T, To>::V != 0;
        }

        template <class ExtendsClass>
        static CORE_FAST gbool isSuper()
        {
            return misc::TEST<misc::SUPER, T, ExtendsClass>::V != 0;
        }

        template <class SuperClass>
        static CORE_FAST gbool isExtends()
        {
            return misc::TEST<misc::SUPER, SuperClass, T>::V != 0;
        }

        template <class To>
        static CORE_FAST gbool isConvertible()
        {
            return misc::TEST<misc::CONVERT, T, To>::V != 0
                   || Class<To>::isVoid() && (isArray() || isVoid() || isFunction())
                   || isSame<To>() && !isArray();
        }

        static CORE_FAST gbool isCallable()
        {
            return misc::TEST<misc::CALL, T, misc::IGNORED<T>>::V != 0;
        }

        template <class... Args>
        static CORE_FAST gbool isCallable()
        {
            return misc::TEST<misc::CALL, T, Args...>::V != 0;
        }

        template <class ExtendsClass>
        static CORE_FAST gbool hasInstance(ExtendsClass&& x)
        {
            CORE_ALIAS(CHECKER,) typename misc::TEST<misc::SUPER, NCVRef>::
                template IMPL<isClass() && Class<ExtendsClass>::isClass()>;

            return isSuper<ExtendsClass>() ||
                   Class<Slim>::template isSame<Class<ExtendsClass>::Slim>() ||
                   CHECKER::checkInstance(x);
        }

        template <gbool ... Conditions>
        static CORE_FAST gbool allIsTrue()
        {
            return misc::ALL_IS_TRUE<Conditions...>::V != 0;
        }

        template <gbool ... Conditions>
        static CORE_FAST gbool oneIsTrue()
        {
            return misc::ONE_IS_TRUE<Conditions...>::V != 0;
        }

        static CORE_FAST gint MEMORY_SIZE = misc::MEMORY_SIZE<T>::V;

        template <class ...Args>
        CORE_ALIAS(ReturnType, ) typename misc::TEST<misc::CALL, T, Args...>::T;

        // ======================= [ type instantiation ] =======================

        template <class... Args>
        static CORE_FAST NCVRef newInstance(Args... args)
        {
            CORE_FAST_ASSERT(!isVoid() && isConstructible<Args...>());
            return NCVRef{args...};
        }

        // ======================= [ type compatibility ] =======================
        CORE_ALIAS(Prim,) typename misc::TRANSFORM<misc::PRIM, NCVRef>::T;

        CORE_ALIAS(Cls,) typename misc::TRANSFORM<misc::CLS, NCVRef>::T;
    };


#ifndef ClassOf
#define ClassOf(x) Class<decltype(x)>
#endif
} // core

#endif // Core24_CLASS_H
