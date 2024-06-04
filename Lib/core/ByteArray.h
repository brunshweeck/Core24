//
// Created by bruns on 10/05/2024.
//

#ifndef CORE24_BYTEARRAY_H
#define CORE24_BYTEARRAY_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c ByteArray wrap the array of primitive
     * type @c gbyte in the object.
     *
     * @note This class provide the random access to elements.
     *
     */
    class ByteArray final : public virtual Object
    {
        CORE_ALIAS(ARRAY, Class< gbyte >::Pointer);
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
         * Construct new @c ByteArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with value @c U+0000.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         */
        CORE_EXPLICIT ByteArray(gint length);

        /**
         * Construct new @c ByteArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with given initial value.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         * @param initialValue The value used to initialize all values of
         *          this array.
         */
        CORE_EXPLICIT ByteArray(gint length, gbyte initialValue);

        /**
         * Construct new @c ByteArray instance by copy of values
         * of given array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT ByteArray(ByteArray const &array);

        /**
         * Construct new @c ByteArray instance by swaping of content
         * of given array.
         *
         * @note After this construction, the given array will be
         * empty and this array will have the old length of given
         * array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT ByteArray(ByteArray &&array) CORE_NOTHROW;

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
        gbyte &get(gint index);

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gbyte const &get(gint index) const;

        /**
         * Set value of element at specified index with
         * specified new value
         *
         * @param index The index of desired element.
         * @param newValue The replacement value
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gbyte set(gint index, gbyte newValue);

        /**
         * Destroy this array data.
         *
         * @note This operation will clear content firstly.
         */
        ~ByteArray() override;

        /**
         * Obtain newly created @c ByteArray instance with primitive byte array,
         * such as @c int8_t[], @c int32_t[], @c int64_t[], @c int128_t[] (signed and unsigned)
         *
         * @note if the memory size of element type is greater than 1 byte, the value will be truncate
         *       1 byte, by narrowing convertion.
         *
         * @tparam T The array type
         * @tparam E The byte type
         * @param array The array to be copied
         * @return The new ByteArray that contains all values of given array
         */
        template<class T,
                Class< gbool >::OnlyIf< Class< T >::isArray() > = true,
                class E = typename Class< T >::ArrayElement,
                Class< gbool >::OnlyIf< Class< E >::isInteger() || Class< E >::isCharacter() && sizeof(E) == 1 > = true>
        static ByteArray copyOf(T &&array)
        {
            CORE_FAST glong n = Class< T >::MEMORY_SIZE / Class< E >::MEMORY_SIZE;

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

                    ByteArray bytes = ByteArray(length);

                    for (int i = 0; i < length; ++i) {
                        bytes.set(i, array[i]);
                    }

                    return CORE_CAST(ByteArray &&, bytes);
                }
            }
        }

        /**
         * Obtains newly created empty array
         *
         * @return empty byte array
         */
        static ByteArray of();

        static ByteArray of(gbyte v0);

        static ByteArray of(gbyte v0, gbyte v1);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7, gbyte v8);

        static ByteArray of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7, gbyte v8, gbyte v9);

        /**
         * Obtain newly created @c ByteArray instance with given bytes values or code points.
         *
         * @tparam T The arguments types list
         * @param args The values list used to initialize array
         * @return The new ByteArray that contains all given values
         */
        template<class... T>
        static ByteArray of(T &&...args)
        {
            CORE_FAST_XASSERT(Class< ByteArray >::allIsTrue< (Class< T >::isInteger() ||
                                                              Class< T >::isCharacter() && sizeof(T) == 1)... >(),
                              "Couldn't create new ByteArray with given values.");

            gbyte array[] = { CORE_FCAST(gbyte, args)... };

            return copyOf(array);
        }

        /**
         * Obtain newly created @c ByteArray instance representing the sequence of bytes
         * from @c 0 to @c limit ( @a exclusive) by @a step @c 1.
         * 
         * @note The call of @c ByteArray::ofRange(l) produces [0, 1, 2, ..., l-1].
         * For example: @c ByteArray::ofRange(4) produces [0, 1, 2, 3].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static ByteArray ofRange(gbyte limit);

        /**
         * Obtain newly created @c ByteArray instance representing the sequence of bytes
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c 1.
         * 
         * @note The call of @c ByteArray::ofRange(i,l) produces [i, i+1, i+2, ..., l-1].
         * For example: @c ByteArray::ofRange(1,5) produces [1, 2, 3, 4].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static ByteArray ofRange(gbyte firstValue, gbyte limit);

        /**
         * Obtain newly created @c ByteArray instance representing the sequence of bytes
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c offsetByValue.
         * 
         * @note The call of @c ByteArray::ofRange(i,l,k) produces [i, i+k, i+2k, ..., i+nk] (where i+nk < l).
         * For example: @c ByteArray::ofRange(1,8,2) produces [1, 3, 5, 7].
         *
         * @param firstValue the start value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         * @param offsetByValue the value of step.
         */
        static ByteArray ofRange(gbyte firstValue, gbyte limit, gint offsetByValue);

        gbyte const &operator[](gint index) const;

        gbyte &operator[](gint index);
    };
} // core

#endif // CORE24_BYTEARRAY_H
