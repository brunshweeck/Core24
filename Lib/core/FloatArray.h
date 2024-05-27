//
// Created by bruns on 10/05/2024.
//

#ifndef CORE24_FLOATARRAY_H
#define CORE24_FLOATARRAY_H

#include <core/Class.h>

namespace core {
    /**
     * The class @c FloatArray wrap the array of primitive
     * type @c gfloat in the object.
     *
     * @note This class provide the random access to elements.
     *
     */
    class FloatArray final : public virtual Object {
        CORE_ALIAS(ARRAY, ClassOf(.0F)::Pointer);

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
         * Construct new @c FloatArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with value @c U+0000.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         */
        CORE_EXPLICIT FloatArray(gint length);

        /**
         * Construct new @c FloatArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with given initial value.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         * @param initialValue The value used to initialize all values of
         *          this array.
         */
        CORE_EXPLICIT FloatArray(gint length, gfloat initialValue);

        /**
         * Construct new @c FloatArray instance by copy of values
         * of given array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT FloatArray(FloatArray const &array);

        /**
         * Construct new @c FloatArray instance by swaping of content
         * of given array.
         *
         * @note After this construction, the given array will be
         * empty and this array will have the old length of given
         * array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT FloatArray(FloatArray &&array) CORE_NOTHROW;

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
        gfloat &get(gint index);

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gfloat const &get(gint index) const;

        /**
         * Set value of element at specified index with
         * specified new value
         *
         * @param index The index of desired element.
         * @param newValue The replacement value
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gfloat set(gint index, gfloat newValue);

        /**
         * Destroy this array data.
         *
         * @note This operation will clear content firstly.
         */
        ~FloatArray() override;

        /**
         * Obtain newly created @c FloatArray instance with primitive float array,
         * such as @c int8_t[], @c int32_t[], @c int64_t[], @c int128_t[] (signed and unsigned) and
         * @c float32_t, @c float64_t, @c float128_t
         *
         * @note if the memory size of element type is greater than 4 bytes, the value will be truncate
         *       4 bytes, by narrowing convertion.
         *
         * @tparam T The array type
         * @tparam E The float type
         * @param array The array to be copied
         * @return The new FloatArray that contains all values of given array
         */
        template<class T,
                Class<gbool>::OnlyIf<Class<T>::isArray()>  = true,
                class E = typename Class<T>::ArrayElement,
                Class<gbool>::OnlyIf<Class<E>::isNumber()>  = true>
        static FloatArray copyOf(T &&array) {
            CORE_FAST glong n = Class<T>::MEMORY_SIZE / Class<E>::MEMORY_SIZE;

            switch (n) {
                case 0:
                    return of();
                case 1:
                    return of(array[0]);
                case 2:
                    return of(array[0], array[1]);
                case 3:
                    return of(array[0], array[1], array[2]);
                case 4:
                    return of(array[0], array[1], array[2], array[3]);
                case 5:
                    return of(array[0], array[1], array[2], array[3], array[4]);
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

                    FloatArray floats = FloatArray(length);

                    for (int i = 0; i < length; ++i) {
                        floats.set(i, array[i]);
                    }

                    return CORE_CAST(FloatArray &&, floats);
                }
            }
        }

        /**
         * Obtains newly created empty array
         *
         * @return empty float array
         */
        static FloatArray of();

        static FloatArray of(gfloat v0);

        static FloatArray of(gfloat v0, gfloat v1);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                             gfloat v5);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                             gfloat v5, gfloat v6);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                             gfloat v5, gfloat v6, gfloat v7);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                             gfloat v5, gfloat v6, gfloat v7, gfloat v8);

        static FloatArray of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                             gfloat v5, gfloat v6, gfloat v7, gfloat v8, gfloat v9);

        /**
         * Obtain newly created @c FloatArray instance with given floats values or code points.
         *
         * @tparam T The arguments types list
         * @param args The values list used to initialize array
         * @return The new FloatArray that contains all given values
         */
        template<class... T>
        static FloatArray of(T &&... args) {
            CORE_FAST_XASSERT(Class<FloatArray>::allIsTrue<Class<T>::isNumber()...>(),
                              "Couldn't create new FloatArray with given values.");

            gfloat array[] = {CORE_FCAST(gfloat, args)...};

            return copyOf(array);
        }

        /**
         * Obtain newly created @c FloatArray instance representing the sequence of floats
         * from @c 0 to @c limit ( @a exclusive) by @a step @c 1.
         *
         * @note The call of @c FloatArray::ofRange(l) produces [0, 1, 2, ..., l-1].
         * For example: @c FloatArray::ofRange(4) produces [0, 1, 2, 3].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static FloatArray ofRange(gfloat limit);

        /**
         * Obtain newly created @c FloatArray instance representing the sequence of floats
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c 1.
         *
         * @note The call of @c FloatArray::ofRange(i,l) produces [i, i+1, i+2, ..., l-1].
         * For example: @c FloatArray::ofRange(1,5) produces [1, 2, 3, 4].
         *
         * @param firstValue the first value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         */
        static FloatArray ofRange(gfloat firstValue, gfloat limit);

        /**
         * Obtain newly created @c FloatArray instance representing the sequence of floats
         * from @c firstValue ( @a inclusive) to @c limit ( @a exclusive) by @a step @c offsetByValue.
         *
         * @note The call of @c FloatArray::ofRange(i,l,k) produces [i, i+k, i+2k, ..., i+nk] (where i+nk < l).
         * For example: @c FloatArray::ofRange(1,8,2) produces [1, 3, 5, 7].
         *
         * @param firstValue the start value of array
         * @param limit the value used as limit value of array such that @code max(this) < limit @endcode
         * @param offsetByValue the value of step.
         */
        static FloatArray ofRange(gfloat firstValue, gfloat limit, gdouble offsetByValue);
    };
} // core

#endif // CORE24_FLOATARRAY_H
