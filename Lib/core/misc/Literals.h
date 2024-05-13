//
// Created by bruns on 05/05/2024.
//

#ifndef Core24_LITERALS_H
#define Core24_LITERALS_H

#include <core/misc/Templates.h>

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
    class Complex;


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
        extern String operator""_S(misc::__literal_chr_t const*, misc::size_t);

        /**
         * Obtain newly created @c String with given UTF-16 chars sequence.
         *
         * @return A new String
         */
        extern String operator""_S(misc::__ucs2_t const*, misc::size_t);

        /**
         * Obtain newly created @c String with given UTF-32 chars sequence.
         *
         * @return A new String
         */
        extern String operator""_S(misc::__ucs4_t const*, misc::size_t);

        /**
         * Obtain newly created @c String with given variable chars sequence.
         * @note wchar_t is encoded in UTF-16 on windows system and
         * UTF-32 for unix systems.
         *
         * @return A new String
         */
        extern String operator""_S(wchar_t const*, misc::size_t);

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


} // core

#endif // Core24_LITERALS_H
