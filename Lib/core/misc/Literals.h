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

    namespace misc {
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
        extern String operator""_S(misc::__literal_chr_t const*, misc::__memory_size_t);

        /**
         * Obtain newly created @c String with given UTF-16 chars sequence.
         *
         * @return A new String
         */
        extern String operator""_S(misc::__ucs2_t const*, misc::__memory_size_t);

        /**
         * Obtain newly created @c String with given UTF-32 chars sequence.
         *
         * @return A new String
         */
        extern String operator""_S(misc::__ucs4_t const*, misc::__memory_size_t);

        /**
         * Obtain newly created @c String with given variable chars sequence.
         * @note wchar_t is encoded in UTF-16 on windows system and
         * UTF-32 for unix systems.
         *
         * @return A new String
         */
        extern String operator""_S(wchar_t const*, misc::__memory_size_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""i(misc::__uint64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""_i(misc::__uint64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""I(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""_I(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""j(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""_j(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""J(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given integer
         *
         * @return A new Complex
         */
        extern Complex const operator""_J(misc::__literal_int64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""i(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""_i(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""I(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""_I(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""j(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""_j(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""J(misc::__literal_float64_t);

        /**
         * Obtain newly created @c Complex with given floating
         *
         * @return A new Complex
         */
        extern Complex const operator""_J(misc::__literal_float64_t);

#ifndef $trace
#define $trace(...) Trace($(__VA_ARGS__), misc::Foreign::str(CORE_FUNCTION), CORE_FILE ""_S, CORE_LINE)
#define $ftrace(...) Trace($(__VA_ARGS__), misc::Foreign::str(CORE_FUNCTION_SIGNATURE), CORE_FILE ""_S, CORE_LINE)
#endif


} // core

CORE_WARNING_POP

#endif // CORE24_LITERALS_H
