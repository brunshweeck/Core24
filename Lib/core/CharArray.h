//
// Created by bruns on 09/05/2024.
//

#ifndef CORE24_CHARARRAY_H
#define CORE24_CHARARRAY_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c CharArray wrap the array of primitive
     * type @c gchar in the object.
     *
     * @note This class provide the random access to elements.
     *
     */
    class CharArray final : public virtual Object
    {
        CORE_ALIAS(ARRAY, Class< gchar >::Pointer);
        CORE_ADD_AS_FRIEND(String);
        CORE_ADD_AS_FRIEND(XString);

        static CORE_FAST gint SOFT_MAX_LENGTH = (gint) ((1LL << 31) - (1LL << 3) - 1);

    private:
        /**
         * The field used to store this array values
         */
        ARRAY value = null;

        /**
         * The field used to store number of values on this array
         */
        gint count = 0;

    public:
        /**
         * Construct new @c CharArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with value @c U+0000.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         */
        CORE_EXPLICIT CharArray(gint length);

        /**
         * Construct new @c CharArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with given initial value.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         * @param initialValue The value used to initialize all values of
         *          this array.
         */
        CORE_EXPLICIT CharArray(gint length, gchar initialValue);

        /**
         * Construct new @c CharArray instance by copy of values
         * of given array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT CharArray(CharArray const &array);

        /**
         * Construct new @c CharArray instance by swaping of content
         * of given array.
         *
         * @note After this construction, the given array will be
         * empty and this array will have the old length of given
         * array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT CharArray(CharArray &&array) CORE_NOTHROW;

        /**
         * Return the number of values on this array
         *
         * @return The number of values on this array
         */
        gint length() const;

        /**
         * Test if this array has no element.
         *
         * @return @c true if this array has no element
         */
        gint isEmpty() const;

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gchar &get(gint index);

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gchar const &get(gint index) const;

        /**
         * Set value of element at specified index with
         * specified new value
         *
         * @param index The index of desired element.
         * @param newValue The replacement value
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gchar set(gint index, gchar newValue);

        /**
         * Destroy this array data.
         *
         * @note This operation will clear content firstly.
         */
        ~CharArray() override;

        /**
         * Obtain newly created @c CharArray instance with primitive char array,
         * such as @c char[], @c char8_t[], @c char16_t[], @c char32_t[], @c wchar_t[]
         *
         * @note if the memory size of element type is greater than 2 bytes, the value will be truncate
         *       to 2 bytes, by narrowing convertion.
         *
         * @tparam T The array type
         * @tparam CharT The char type
         * @param array The array to be copied
         * @return The new CharArray that contains all values of given array
         */
        template<class T,
                Class< gbool >::OnlyIf< Class< T >::isArray() >  = true,
                class CharT = typename Class< T >::ArrayElement,
                Class< gbool >::OnlyIf< Class< CharT >::isCharacter() >  = true
        >
        static CharArray copyOf(T &&array)
        {
            CORE_FAST glong n = Class< T >::MEMORY_SIZE / Class< CharT >::MEMORY_SIZE;

            switch (n) {
                case 0:return of();
                case 1:return of(array[0]);
                case 2:return of(array[0], array[1]);
                case 3:return of(array[0], array[1], array[2]);
                case 4:return of(array[0], array[1], array[2], array[3]);
                case 5:return of(array[0], array[1], array[2], array[3], array[4]);
                case 6:
                    return of(array[0], array[1], array[2], array[3], array[4],
                              array[5]);
                case 7:
                    return of(array[0], array[1], array[2], array[3], array[4],
                              array[5], array[6]);
                case 8:
                    return of(array[0], array[1], array[2], array[3], array[4],
                              array[5], array[6], array[7]);
                case 9:
                    return of(array[0], array[1], array[2], array[3], array[4],
                              array[5], array[6], array[7], array[8]);
                case 10:
                    return of(array[0], array[1], array[2], array[3], array[4],
                              array[5], array[6], array[7], array[8], array[9]);
                default: {
                    CORE_FAST gint length = n > SOFT_MAX_LENGTH ? SOFT_MAX_LENGTH : (gint) n;

                    CharArray chars = CharArray(length);

                    for (int i = 0; i < length; ++i) {
                        chars.set(i, array[i]);
                    }

                    return CORE_CAST(CharArray &&, chars);
                }
            }
        }

        /**
         * Obtains newly created empty array
         *
         * @return empty char array
         */
        static CharArray of();

        static CharArray of(gchar v0);

        static CharArray of(gchar v0, gchar v1);

        static CharArray of(gchar v0, gchar v1, gchar v2);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7, gchar v8);

        static CharArray of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7, gchar v8, gchar v9);

        /**
         * Obtain newly created @c CharArray instance with given chars values or code points.
         *
         * @tparam T The arguments types list
         * @param args The characters (or unicode code points) list used to initialize array
         * @return The new CharArray that contains all given values
         */
        template<class... T>
        static CharArray of(T &&... args)
        {
            CORE_FAST_XASSERT(Class< CharArray >::allIsTrue< (Class< T >::isCharacter() | Class< T >::isInteger() &&
                                                              sizeof(T) <= 4)... >(),
                              "Couldn't create new CharArray with given values.");

            gchar array[] = { CORE_FCAST(gchar, args)... };

            return copyOf(array);
        }

        /**
         * Obtain newly created @c CharArray instance representing the sequence of chars
         * from @c 0 to @c limit ( @a exclusive) by @a step @c 1.
         *
         * @note The call of @c CharArray::ofRange(l) produces [0, 1, 2, ..., l-1].
         * For example: @c CharArray::ofRange(4) produces [0, 1, 2, 3].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static CharArray ofRange(gchar limit);

        /**
         * Obtain newly created @c CharArray instance representing the sequence of chars
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c 1.
         *
         * @note The call of @c CharArray::ofRange(i,l) produces [i, i+1, i+2, ..., l-1].
         * For example: @c CharArray::ofRange(1,5) produces [1, 2, 3, 4].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static CharArray ofRange(gchar firstValue, gchar limit);

        /**
         * Obtain newly created @c CharArray instance representing the sequence of chars
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c offsetByValue.
         *
         * @note The call of @c CharArray::ofRange(i,l,k) produces [i, i+k, i+2k, ..., i+nk] (where i+nk < l).
         * For example: @c CharArray::ofRange(1,8,2) produces [1, 3, 5, 7].
         *
         * @param firstValue the start value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         * @param offsetByValue the value of step.
         */
        static CharArray ofRange(gchar firstValue, gchar limit, gint offsetByValue);

        gchar const &operator[](gint index) const;

        gchar &operator[](gint index);
    };
} // core

#endif // CORE24_CHARARRAY_H
