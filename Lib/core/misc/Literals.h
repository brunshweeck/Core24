//
// Created by bruns on 05/05/2024.
//

#ifndef CORE24_LITERALS_H
#define CORE24_LITERALS_H

#include <core/misc/Templates.h>

CORE_WARNING_PUSH
CORE_WARNING_DISABLE_UDL

namespace core
{
    class Object;

    class String;

    class XString;

    class BooleanArray;

    class ByteArray;

    class ShortArray;

    class IntArray;

    class FloatArray;

    class LongArray;

    class DoubleArray;

    class CharArray;

    class Boolean;

    class Byte;

    class Short;

    class Integer;

    class Long;

    class Float;

    class Double;

    class Complex;

    class Character;

    class CharSequence;

    template<class>
    class Comparable;

    class Number;

    namespace misc
    {
        class Foreign;
    }


    /*
     * This file contains all declaration of literals expression
     * for type of Core24 lib
     */

    /**
     * Obtain newly created @c String with given bytes sequence
     * encoded to utf-8 for mostly compiler or windows-1252 for
     * others such as MSVC compiler (see String::COMPACT_STRINGS).
     *
     * @return A new String
     */
    extern String operator ""_S(misc::__literal_chr_t const *, misc::__memory_size_t);

    /**
     * Obtain newly created @c String with given UTF-16 chars sequence.
     *
     * @return A new String
     */
    extern String operator ""_S(misc::__ucs2_t const *, misc::__memory_size_t);

    /**
     * Obtain newly created @c String with given UTF-32 chars sequence.
     *
     * @return A new String
     */
    extern String operator ""_S(misc::__ucs4_t const *, misc::__memory_size_t);

    /**
     * Obtain newly created @c String with given variable chars sequence.
     * @note wchar_t is encoded in UTF-16 on windows system and
     * UTF-32 for unix systems.
     *
     * @return A new String
     */
    extern String operator ""_S(wchar_t const *, misc::__memory_size_t);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""i(misc::__uint64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""_i(misc::__uint64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""I(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""_I(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""j(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""_j(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""J(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given integer
     *
     * @return A new Complex
     */
    extern Complex operator ""_J(misc::__literal_int64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""i(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""_i(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""I(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""_I(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""j(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""_j(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""J(misc::__literal_float64_t im);

    /**
     * Obtain newly created @c Complex with given floating
     *
     * @return A new Complex
     */
    extern Complex operator ""_J(misc::__literal_float64_t im);

    /**
     * Return the conjugate of given complex number.
     */
    extern Complex operator~(Complex const &z);

    extern Complex operator-(Complex const &z);

    extern Complex operator+(Complex const &z);

#ifndef $trace
#define $trace(...) Trace($(__VA_ARGS__), misc::Foreign::str(CORE_FUNCTION), CORE_FILE ""_S, CORE_LINE)
#define $ftrace(...) Trace($(__VA_ARGS__), misc::Foreign::str(CORE_FUNCTION_SIGNATURE), CORE_FILE ""_S, CORE_LINE)
#endif

    /**
     * Obtain newly created @c String that contains the
     * concatenation of given strings
     */
    extern String operator+(String const &, String const &);

    extern String operator+(String const &, Object const &);

    extern String operator+(Object const &, String const &);

    extern String operator+(String const &, gint);

    extern String operator+(String const &, gfloat);

    extern String operator+(String const &, gdouble);

    extern String operator+(String const &, void *);

    extern String operator+(gint, String const &);

    extern String operator+(gfloat, String const &);

    extern String operator+(gdouble, String const &);

    extern String operator+(void *, String const &);

    // Specials Case.

    extern String operator+(String const &, unsigned int);

    extern String operator+(String const &, long);

    extern String operator+(String const &, unsigned long);

    extern String operator+(String const &, long long);

    extern String operator+(String const &, unsigned long long);

    extern String operator+(unsigned int, String const &);

    extern String operator+(long, String const &);

    extern String operator+(unsigned long, String const &);

    extern String operator+(long long, String const &);

    extern String operator+(unsigned long long, String const &);

    extern String &operator+=(String &lhs, String const &rhs);

    extern String &operator+=(String &lhs, gint rhs);

    extern String &operator+=(String &lhs, long rhs);

    extern String &operator+=(String &lhs, long long rhs);

    extern String &operator+=(String &lhs, misc::__uint32_t rhs);

    extern String &operator+=(String &lhs, unsigned long rhs);

    extern String &operator+=(String &lhs, unsigned long long rhs);

    extern String &operator+=(String &lhs, gfloat rhs);

    extern String &operator+=(String &lhs, gdouble rhs);

    extern String &operator+=(String &lhs, long double rhs);

    extern Complex operator+(Complex const &lhs, Complex const &rhs);
    extern Complex operator-(Complex const &lhs, Complex const &rhs);
    extern Complex operator*(Complex const &lhs, Complex const &rhs);
    extern Complex operator/(Complex const &lhs, Complex const &rhs);

    extern Complex &operator+=(Complex &lhs, Complex const &rhs);
    extern Complex &operator-=(Complex &lhs, Complex const &rhs);
    extern Complex &operator*=(Complex &lhs, Complex const &rhs);
    extern Complex &operator/=(Complex &lhs, Complex const &rhs);

    extern gbool operator==(Complex const &lhs, Complex const &rhs);
    extern gbool operator!=(Complex const &lhs, Complex const &rhs);

} // core

//// no inline, required by [replacement.functions]/3
//extern void *operator new(core::misc::__memory_size_t memorySize);
//// no inline, required by [replacement.functions]/3
//extern void *operator new[](core::misc::__memory_size_t memorySize);
//
//extern void *operator new(core::misc::__memory_size_t memorySize, void* destAddress);
//extern void *operator new[](core::misc::__memory_size_t memorySize, void* destAddress);
//
//extern void operator delete (void* targetAddress);
//extern void operator delete[] (void* targetAddress);
//extern void operator delete (void* targetAddress, void*);
//extern void operator delete[] (void* targetAddress, void*);
//extern void operator delete (void* targetAddress, core::misc::__memory_size_t memorySize);
//extern void operator delete[] (void* targetAddress, core::misc::__memory_size_t memorySize);

CORE_WARNING_POP

#endif // CORE24_LITERALS_H
