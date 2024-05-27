//
// Created by bruns on 05/05/2024.
//

#ifndef CORE24_CLASS_H
#define CORE24_CLASS_H

#include <core/misc/Literals.h>
#include <core/misc/Nil.h>

namespace core
{
    /**
     * The class @c Class wrap multiple statics methods used to
     * determine status of any types and it different template versions.
     *
     * @tparam T The target type
     */
    template<class T>
    class Class final : public virtual Object
    {
        CORE_IMPLICIT Class()
        {
        }

    public:
        // ======================= [ type native versions ] =======================

        // Constant version of T
        CORE_ALIAS(Constant,) typename misc::TRANSFORM<misc::CONST, T>::T;

        // Mutable version of T
        CORE_ALIAS(Mutable,) typename misc::TRANSFORM<misc::CONST | misc::REMOVE, T>::T;

        // Constant version of T
        CORE_ALIAS(Const, Constant);

        // Mutable version of T
        CORE_ALIAS(NoConstant, Mutable);

        // Mutable version of T
        CORE_ALIAS(NConst, NoConstant);

        // Volatile version of T
        CORE_ALIAS(Volatile,) typename misc::TRANSFORM<misc::VOL, T>::T;

        // Non-Volatile version of T
        CORE_ALIAS(NoVolatile,) typename misc::TRANSFORM<misc::VOL | misc::REMOVE, T>::T;

        // Constant and Volatile version of T
        CORE_ALIAS(ConstVolatile,) typename misc::TRANSFORM<misc::CONST | misc::VOL, T>::T;

        // Mutable and Non-Volatile version of T
        CORE_ALIAS(NoConstVolatile,) typename misc::TRANSFORM<misc::CONST | misc::VOL | misc::REMOVE, T>::T;

        // Volatile version of T
        CORE_ALIAS(Vol, Volatile);

        // Constant and Volatile version of T
        CORE_ALIAS(CVol, Volatile);

        // Non-Volatile version of T
        CORE_ALIAS(NVol, NoVolatile);

        // Mutable and Non-Volatile version of T
        CORE_ALIAS(NConstVol, NoConstVolatile);

        // Mutable and Non-Volatile version of T
        CORE_ALIAS(NCVol, NConstVol);

        // Pointer version of T
        CORE_ALIAS(Pointer,) typename misc::TRANSFORM<misc::PTR, T>::T;

        // Pointer Target of Pointer type T
        CORE_ALIAS(PointerTarget,) typename misc::TRANSFORM<misc::PTR | misc::REMOVE, T>::T;

        // Non-Pointer version of T
        CORE_ALIAS(NoPointer, PointerTarget);

        // Pointer version of T
        CORE_ALIAS(Ptr, Pointer);

        // Non-Pointer version of T
        CORE_ALIAS(NPtr, NoPointer);

        /**
         * The @c PointerLv represent the multidimesional pointer.
         *
         * Example:
         * @code{c++}
         *  Class<String>::PointerLv<2> => String**
         * @endcode
         *
         * @tparam N the pointer dimension
         */
        template<gint N>
        CORE_ALIAS(PointerLv,) typename misc::TRANSFORM_PTR_LV<T, N>::T;

        // Reference version of T (Left value)
        CORE_ALIAS(Reference,) typename misc::TRANSFORM<misc::REF, T>::T;

        // Constant Reference version of T
        CORE_ALIAS(ConstReference,) typename misc::TRANSFORM<misc::CONST | misc::REF, T>::T;

        // Volatile Reference version of T
        CORE_ALIAS(VolReference,) typename misc::TRANSFORM<misc::VOL | misc::REF, T>::T;

        // Constant and Volatile Reference version of T
        CORE_ALIAS(ConstVolReference,) typename misc::TRANSFORM<misc::CONST | misc::VOL | misc::REF, T>::T;

        // Reference version of T (Right value)
        CORE_ALIAS(Rvalue,) typename misc::TRANSFORM<misc::RVAL, T>::T;

        // Non-Reference version of T
        CORE_ALIAS(NoReference,) typename misc::TRANSFORM<misc::REF | misc::REMOVE, T>::T;

        // Mutable and Non-Reference version of T
        CORE_ALIAS(NoConstReference,) typename misc::TRANSFORM<misc::CONST | misc::REF | misc::REMOVE, T>::T;

        // Non-Volatile and Non-Reference version of T
        CORE_ALIAS(NoVolReference,) typename misc::TRANSFORM<misc::VOL | misc::REF | misc::REMOVE, T>::T;

        // Mutable, Non-Volatile and Non-Reference version of T
        CORE_ALIAS(NoConstVolReference,)
                typename misc::TRANSFORM<misc::CONST | misc::VOL | misc::REF | misc::REMOVE, T>::T;

        // Reference version of T
        CORE_ALIAS(Ref, Reference);

        // Constant Reference version of T
        CORE_ALIAS(CRef, ConstReference);

        // Volatile Reference version of T
        CORE_ALIAS(VRef, VolReference);

        // Constant Volatile Reference version of T
        CORE_ALIAS(CVRef, ConstVolReference);

        // Non-Reference version of T
        CORE_ALIAS(NRef, NoReference);

        // Mutable and Non-Reference version of T
        CORE_ALIAS(NConstRef, NoConstReference);

        // Non-Volatile version of T
        CORE_ALIAS(NVolRef, NoVolReference);

        // Mutable Non-Volatile and Non-Reference version of T
        CORE_ALIAS(NConstVolRef, NoConstVolReference);

        // Mutable and Non-Reference version of T
        CORE_ALIAS(NCRef, NConstRef);

        // Mutable and Non-Reference version of T
        CORE_ALIAS(NVRef, NVolRef);

        // Mutable Non-Volatile and Non-Reference version of T
        CORE_ALIAS(NCVRef, NConstVolRef);

        // Arrays version of T
        template<glong N>
        CORE_ALIAS(Array,) typename misc::TRANSFORM<misc::ARR, NRef, N>::T;

        /// Array Element type of Array type @c T
        CORE_ALIAS(ArrayElement,) typename misc::TRANSFORM<misc::ARR | misc::REMOVE, NRef>::T;

        /**
        * @c Matrix represent the multidimesional array.
         *
         * Example:
         * @code{c++}
         *  Class<String>::Matrix<2, 3> => String[2][3]
         * @endcode
         *
         * tparam N... the sizes of all dimensions
         */
        template<gint ...N>
        CORE_ALIAS(Matrix,) typename misc::TRANSFORM_ARR_LV<NRef, N...>::T;

        /**
         * Slim version of T.
         * This version is recursive @c Mutable, recursive @c NoVolatile,
         * and recursive @c NoReference version of @c T
         */
        CORE_ALIAS(Slim,) typename misc::TRANSFORM<misc::SLIM, NCVRef>::T;

        // ======================= [ type conditionnal test ] =======================

        // Irreversible conditions
        /**
         * Enable the template type (@c T), if and only if
         * the condition result is @c true.
         * @code
         *  if (condition) ... else {error}
         *
         *  template <class T>
         *  using AlwaysNumber = Class<T>::OnlyIf<Class<Number>::isSuper<T>()>;
         *
         *  AlwaysNumber<Double> // Double
         *  AlwaysNumber<String> // error
         * @endcode
         *
         * @param Condition the condition result
         */
        template<gbool Condition>
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
        template<gbool Condition, class U>
        CORE_ALIAS(IfElse,) typename misc::IF_OR_ELSE<T, U, Condition>::T;

        // ======================= [ type status ] =======================

        /**
         * Test if type @c T is same to specified type @c To
         *
         * @tparam To the type to be test.
         */
        template<class To>
        static CORE_FAST gbool isSame()
        {
            return misc::TEST<misc::SAME, NCVRef, typename Class<To>::NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is constant. in other word,
         * this method test if type @c T have qualifier
         * @c const.
         */
        static CORE_FAST gbool isConstant()
        {
            return misc::TEST<misc::CONST, NVRef>::V != 0;
        }

        /**
         * Test if type @c T is volatile. in other word,
         * this method test if type @c T have qualifier
         * @c volatile.
         */
        static CORE_FAST gbool isVolatile()
        {
            return misc::TEST<misc::VOL, NCRef>::V != 0;
        }

        /**
         * Test if type @c T is pointer. in other word,
         * this method test if type @c T have qualifier
         * @c *.
         */
        static CORE_FAST gbool isPointer()
        {
            return misc::TEST<misc::PTR, T>::V != 0;
        }

        /**
         * Test if type @c T is reference. in other word,
         * this method test if type @c T have qualifier
         * @c & or qualifier @c &&.
         */
        static CORE_FAST gbool isReference()
        {
            return misc::TEST<misc::REF, NCVol>::V != 0;
        }

        /**
         * Test if type @c T is reference (rvalue). in other word,
         * this method test if type @c T have qualifier
         * @c &&.
         */
        static CORE_FAST gbool isRvalue()
        {
            return misc::TEST<misc::RVAL, NCVol>::V != 0;
        }

        /**
         * Test if type @c T is array. in other word,
         * this method test if type @c T have qualifier
         * @c [N] where N is length of @c T.
         */
        static CORE_FAST gbool isArray()
        {
            return misc::TEST<misc::ARR, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is complete type.
         * The complete type is type that definition
         * found or type that have size.
         */
        static CORE_FAST gbool isComplete()
        {
            return misc::TEST<misc::COMPLET, NRef>::V != 0;
        }

        /**
         * Test if type @c T is template. in other word,
         * this method test if type @c T is defined like
         * this : template <...> class T;
         */
        static CORE_FAST gbool isTemplate()
        {
            return misc::TEST<misc::TEMP, NRef>::V != 0;
        }

        /**
         * Test if type @c T is function. in other word,
         * this method test if type @c T have signature
         * @c R(*)(A...) or @c R(*)(A...) where R is return
         * type and A is arguments types or @c T is lambda
         * function without capture list.
         */
        static CORE_FAST gbool isFunction()
        {
            return misc::TEST<misc::FUNC, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is class member.
         */
        static CORE_FAST gbool isMember()
        {
            return misc::TEST<misc::MEMBER, NRef>::V != 0;
        }

        /**
         * Test if type @c T is function member. in other word,
         * this method test if type @c T is non static method.
         */
        static CORE_FAST gbool isFunctionMember()
        {
            return misc::TEST<misc::METH, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is abstract class. in other
         * words, one or more methods of class T is pure
         * virtual
         */
        static CORE_FAST gbool isAbstract()
        {
            return misc::TEST<misc::ABSTRACT, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is enum type.
         */
        static CORE_FAST gbool isEnum()
        {
            return misc::TEST<misc::ENUM, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is class or union type.
         */
        static CORE_FAST gbool isClass()
        {
            return misc::TEST<misc::CLS, NCVRef>::V != 0 || __is_union(T);
        }

        /**
         * Test if type @c T is able to content others values.
         */
        static CORE_FAST gbool isAggregate()
        {
            return isClass() || isArray();
        }

        /**
         * Test if type @c T is destructible. in other word,
         * this method test if type @c T define destructor
         * method.
         */
        static CORE_FAST gbool isDestructible()
        {
            return misc::TEST<misc::DTOR, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is not inheritable.
         */
        static CORE_FAST gbool isFinal()
        {
            return misc::TEST<misc::FINAL, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is empty. in other word,
         * this method test if type @c T have not content
         * (fields, methods, etc...)
         */
        static CORE_FAST gbool isEmpty()
        {
            return misc::TEST<misc::EMPTY, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is literal type.
         */
        static CORE_FAST gbool isLiteral()
        {
            return misc::TEST<misc::LITERAL, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is polymorphic type.
         */
        static CORE_FAST gbool isPolymorphic()
        {
            return misc::TEST<misc::POLY, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is trivial type.
         */
        static CORE_FAST gbool isTrivial()
        {
            return misc::TEST<misc::TRIVIAL, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is integer number type.
         */
        static CORE_FAST gbool isInteger()
        {
            // TEST<INT, signed int>::V = 1
            // TEST<INT, unsigned int>::V = 1
            // TEST<INT, int>::V = 0
            return (misc::TEST<misc::INT, NCVRef>::V
                    | misc::TEST<misc::SAME, NCVRef, int>::V
                    | misc::TEST<misc::SAME, NCVRef, long>::V
                    | misc::TEST<misc::SAME, NCVRef, long long>::V) != 0;
        }

        /**
         * Test if type @c T is floating/decimal number type.
         */
        static CORE_FAST gbool isFloating()
        {
            return misc::TEST<misc::FLT, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is integer or floating number type.
         */
        static CORE_FAST gbool isNumber()
        {
            return isInteger() || isFloating();
        }

        /**
         * Test if type @c T is integral type
         * (integer number, enumeration type, characters, boolean).
         */
        static CORE_FAST gbool isIntegral()
        {
            return isInteger() || isEnum() || isCharacter() || isBoolean();
        }

        /**
         * Test if type @c T is boolean type.
         */
        static CORE_FAST gbool isBoolean()
        {
            return misc::TEST<misc::BOOLEAN, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is void type.
         */
        static CORE_FAST gbool isVoid()
        {
            return misc::TEST<misc::VOID, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is primitive type.
         */
        static CORE_FAST gbool isPrimitive()
        {
            return isVoid() || isString() || isCharacter() || isBoolean() || isNumber() || isArray() || isPointer();
        }

        /**
         * Test if type @c T is character type.
         */
        static CORE_FAST gbool isCharacter()
        {
            // TEST<CHR, signed char>::V = 1
            // TEST<CHR, unsigned char>::V = 1
            // TEST<CHR, char>::V = 0
            return (misc::TEST<misc::CHR, NCVRef>::V
                    | misc::TEST<misc::SAME, NCVRef, char>::V) != 0;
        }

        /**
         * Test if type @c T is string type.
         */
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

        /**
         * Test if type @c T support operator equals.
         */
        static CORE_FAST gbool supportEQ()
        {
            return misc::TEST<misc::EQ, NRef>::V != 0;
        }

        /**
         * Test if type @c T support operator less than.
         */
        static CORE_FAST gbool supportLT()
        {
            return misc::TEST<misc::LT, NRef>::V != 0;
        }

        /**
         * Test if type @c T is default constructible.
         */
        static CORE_FAST gbool isConstructible()
        {
            return misc::TEST<misc::CTOR, NCVRef, misc::IGNORED<T>>::V != 0;
        }

        /**
         * Test if type @c T is constructible with specified arguments types.
         *
         * @tparam Args the arguments types
         */
        template<class... Args>
        static CORE_FAST gbool isConstructible()
        {
            return misc::TEST<misc::CTOR, NCVRef, Args...>::V != 0;
        }

        /**
         * Test if type @c T is assignable to specified type.
         *
         * @tparam To the expected type.
         */
        template<class To>
        static CORE_FAST gbool isAssignable()
        {
            return misc::TEST<misc::ASSIGN, T, To>::V != 0;
        }

        /**
         * Test if type @c T is base class of specified type @c ExtendsClass.
         *
         * @tparam ExtendsClass the derived class
         */
        template<class ExtendsClass>
        static CORE_FAST gbool isSuper()
        {
            return misc::TEST<misc::SUPER, NCVRef, ExtendsClass>::V != 0;
        }

        /**
         * Test if type @c T is derived class of specified type @c SuperClass.
         *
         * @tparam SuperClass the base class
         */
        template<class SuperClass>
        static CORE_FAST gbool isExtends()
        {
            return misc::TEST<misc::SUPER, SuperClass, NCVRef>::V != 0;
        }

        /**
         * Test if type @c T is implicitly convertible to specified type @c ExtendsClass.
         *
         * @tparam To the target class
         */
        template<class To>
        static CORE_FAST gbool isConvertible()
        {
            return misc::TEST<misc::CONVERT, T, To>::V != 0
                   || Class<To>::isVoid() && (isArray() || isVoid() || isFunction())
                   || isSame<To>() && !isArray();
        }

        /**
         * Test if type @c T is callable without argument
         */
        static CORE_FAST gbool isCallable()
        {
            return misc::TEST<misc::CALL, T, misc::IGNORED<T>>::V != 0;
        }

        /**
         * Test if type @c T is callable with specified argument types
         *
         * @tparam Args the argument type list
         */
        template<class... Args>
        static CORE_FAST gbool isCallable()
        {
            return misc::TEST<misc::CALL, T, Args...>::V != 0;
        }

        /**
         * Test if specified value of type @c ExtendsClass is instance of type @c T
         *
         * @tparam ExtendsClass the expected value type
         *
         * @param x the value to be test
         */
        template<class ExtendsClass>
        static CORE_FAST gbool hasInstance(ExtendsClass &&x)
        {
            CORE_ALIAS(CHECKER,) typename misc::TEST<misc::SUPER, NCVRef>::
            template IMPL<isClass() && Class<ExtendsClass>::isClass()>;

            return isSuper<ExtendsClass>() ||
                   Class<Slim>::template isSame<typename Class<ExtendsClass>::Slim>() ||
                   CHECKER::checkInstance(x);
        }

        template<gbool ...Conditions>
        static CORE_FAST gbool allIsTrue()
        {
            return misc::ALL_IS_TRUE<Conditions...>::V != 0;
        }

        template<gbool ...Conditions>
        static CORE_FAST gbool oneIsTrue()
        {
            return misc::ONE_IS_TRUE<Conditions...>::V != 0;
        }

        static CORE_FAST gint MEMORY_SIZE = misc::MEMORY_SIZE<T>::V;

        template<class... Args>
        CORE_ALIAS(ReturnType,) typename misc::TEST<misc::CALL, T, Args...>::T;

        // ======================= [ type compatibility ] =======================
        CORE_ALIAS(Prim,) typename misc::TRANSFORM<misc::PRIM, NCVRef>::T;

        CORE_ALIAS(Obj,) typename misc::TRANSFORM<misc::CLS, NCVRef>::T;
    };


#ifndef ClassOf

    /**
     * The auto type.
     */
#define ClassOf(x) Class<decltype(x)>
#endif
} // core

#endif // CORE24_CLASS_H
