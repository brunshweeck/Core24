//
// Created by bruns on 10/05/2024.
//

#ifndef Core24_LONGARRAY_H
#define Core24_LONGARRAY_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c LongArray wrap the array of primitive
     * type @c glong in the object.
     *
     * @note This class provide the random access to elements.
     *
     */
    class LongArray final : public virtual Object
    {
        CORE_ALIAS(ARRAY, Class<glong>::Pointer);

        static CORE_FAST gint SOFT_ARRAY_LENGHT = 0x7FFFFFFF - 8;

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
         * Construct new @c LongArray instance able to containt
         * the given number of values.
         *
         * @note All value will be initialized with value @c U+0000.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         */
        CORE_EXPLICIT LongArray(gint length);

        /**
         * Construct new @c LongArray instance able to containt
         * the given number of values.
         *
         * @note All value will be initialized with given initial value.
         *
         * @trows NegativeArraySizeException If the given length is negative
         * @param length The number of value to be allocated on this array
         * @param initialValue The value used to initialize all values of
         *          this array.
         */
        CORE_EXPLICIT LongArray(gint length, glong initialValue);

        /**
         * Construct new @c LongArray instance by copy of values
         * of given array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT LongArray(LongArray const& array);

        /**
         * Construct new @c LongArray instance by swaping of content
         * of given array.
         *
         * @note After this construction, the given array will be
         * empty and this array will have the old length of given
         * array.
         *
         * @param array The array used to create this array.
         */
        CORE_IMPLICIT LongArray(LongArray&& array) CORE_NOTHROW;

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
        glong& get(gint index);

        /**
         * Return the value of elements at specified index
         *
         * @param index The index of desired element.
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        glong const& get(gint index) const;

        /**
         * Set value of element at specified index with
         * specified new value
         *
         * @param index The index of desired element.
         * @param newValue The replacement value
         * @throws IndexOutOfBoundsException If the given index out of bounds
         */
        glong set(gint index, glong newValue);

        /**
         * Destroy this array data.
         *
         * @note This operation will clear content firstly.
         */
        ~LongArray() override;

        /**
         * Obtain newly created @c LongArray instance with primitive long array,
         * such as @c int8_t[], @c int32_t[], @c int64_t[], @c int128_t[] (signed and unsigned)
         *
         * @note if the memory size of element type is greater than 8 bytes, the value will be truncate
         *       8 bytes, by narrowing convertion.
         *
         * @tparam T The array type
         * @tparam E The long type
         * @param array The array to be copied
         * @return The new LongArray that contains all values of given array
         */
        template <class T,
                  Class<gbool>::OnlyIf<Class<T>::isArray()>  = true,
                  class E = typename Class<T>::ArrayElement,
                  Class<gbool>::OnlyIf<Class<E>::isIntegral()>  = true
        >
        static LongArray copyOf(T&& array)
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
            default:
                {
                    CORE_FAST gint length = n > SOFT_ARRAY_LENGHT ? SOFT_ARRAY_LENGHT : (gint) n;

                    LongArray longs = LongArray(length);

                    for (int i = 0; i < length; ++i) {
                        longs.set(i, array[i]);
                    }

                    return CORE_CAST(LongArray &&, longs);
                }
            }
        }

        /**
         * Obtains newly created empty array
         *
         * @return empty long array
         */
        static LongArray of();

        static LongArray of(glong v0);

        static LongArray of(glong v0, glong v1);

        static LongArray of(glong v0, glong v1, glong v2);

        static LongArray of(glong v0, glong v1, glong v2, glong v3);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7, glong v8);

        static LongArray of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7, glong v8, glong v9);

        /**
         * Obtain newly created @c LongArray instance with given longs values or code points.
         *
         * @tparam T The arguments types list
         * @param args The values list used to initialize array
         * @return The new LongArray that containt all given values
         */
        template <class... T,
                  Class<gbool>::OnlyIf<
                      Class<Object>::allIsTrue<
                          Class<T>::isInteger()...
                      >()
                  >  = true
        >
        static LongArray of(T&&... args)
        {
            glong array[] = {CORE_FCAST(glong, args)...};

            return copyOf(array);
        }
    };
} // core

#endif // Core24_LONGARRAY_H
