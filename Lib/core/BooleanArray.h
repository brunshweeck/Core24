//
// Created by bruns on 10/05/2024.
//

#ifndef CORE24_BOOLEANARRAY_H
#define CORE24_BOOLEANARRAY_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c BooleanArray wrap the array of primitive
     * type @c gbool in the object.
     *
     * @note This class provide the random access to elements.
     *
     */
    class BooleanArray final : public virtual Object
    {
        CORE_ALIAS(ARRAY, ClassOf(false)::Pointer);

    public:
        /**
         * The maximum number of value supported by array.
         */
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
         * Construct new @c BooleanArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with value @c U+0000.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         */
        CORE_EXPLICIT BooleanArray(gint length);

        /**
         * Construct new @c BooleanArray instance able to contains
         * the given number of values.
         *
         * @note All value will be initialized with given initial value.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         * @param initialValue The value used to initialize all values of
         *          this array.
         */
        CORE_EXPLICIT BooleanArray(gint length, gbool initialValue);

        /**
         * Construct new @c BooleanArray instance by copy of values
         * of given array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT BooleanArray(BooleanArray const &array);

        /**
         * Construct new @c BooleanArray instance by swaping of content
         * of given array.
         *
         * @note After this construction, the given array will be
         * empty and this array will have the old length of given
         * array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT BooleanArray(BooleanArray &&array) CORE_NOTHROW;

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
        gbool &get(gint index);

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gbool const &get(gint index) const;

        /**
         * Set value of element at specified index with
         * specified new value
         *
         * @param index The index of desired element.
         * @param newValue The replacement value
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        gbool set(gint index, gbool newValue);

        /**
         * Destroy this array data.
         *
         * @note This operation will clear content firstly.
         */
        ~BooleanArray() override;

        /**
         * Obtain newly created @c BooleanArray instance with primitive bool array,
         * such as @c gbool[]
         *
         * @tparam T The array type
         * @tparam E The bool type
         * @param array The array to be copied
         * @return The new BooleanArray that contains all values of given array
         */
        template<class T,
                Class<gbool>::OnlyIf<Class<T>::isArray()>  = true,
                class E = typename Class<T>::ArrayElement,
                Class<gbool>::OnlyIf<Class<E>::isBoolean()>  = true>
        static BooleanArray copyOf(T &&array)
        {
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

                    BooleanArray bools = BooleanArray(length);

                    for (int i = 0; i < length; ++i) {
                        bools.set(i, array[i]);
                    }

                    return CORE_CAST(BooleanArray &&, bools);
                }
            }
        }

        /**
         * Obtains newly created empty array
         *
         * @return empty bool array
         */
        static BooleanArray of();

        static BooleanArray of(gbool v0);

        static BooleanArray of(gbool v0, gbool v1);

        static BooleanArray of(gbool v0, gbool v1, gbool v2);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                               gbool v5);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                               gbool v5, gbool v6);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                               gbool v5, gbool v6, gbool v7);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                               gbool v5, gbool v6, gbool v7, gbool v8);

        static BooleanArray of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                               gbool v5, gbool v6, gbool v7, gbool v8, gbool v9);

        /**
         * Obtain newly created @c BooleanArray instance with given bools values or code points.
         *
         * @tparam T The arguments types list
         * @param args The values list used to initialize array
         * @return The new BooleanArray that contains all given values
         */
        template<class... T>
        static BooleanArray of(T &&... args)
        {
            CORE_FAST_XASSERT(Class<BooleanArray>::allIsTrue<Class<T>::isBoolean()...>(),
                              "Couldn't create new BooleanArray with given values.");

            gbool array[] = {CORE_FCAST(gbool, args)...};

            return copyOf(array);
        }
    };
} // core

#endif // CORE24_BOOLEANARRAY_H
