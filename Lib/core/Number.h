//
// Created by bruns on 09/05/2024.
//

#ifndef Core24_NUMBER_H
#define Core24_NUMBER_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c Number is the superclass of platform
     * classes representing numerics values that are convertible
     * to the primitive types @c gbyte, @c gshort, @c gint, @c glong,
     * @c gfloat, @c gdouble.
     *
     * For platform classes, the conversion is often analogous to a
     * narrowing primitive conversion or a widening primitive conversion
     * for converting between primitive types. Therefore, conversions may
     * lose information about the overall magnitude of a numeric value, may
     * lose precision, and may even return a result of a different sign
     * than the input.
     */
    class Number : public virtual Object
    {
    public:
        /**
         * Returns the value of the specified number as an @c int.
         * @return The numeric value represented by this object
         * after conversion to type @c int
         */
        virtual gint intValue() const = 0;
        /**
         * Returns the value of the specified number as an @c long.
         * @return The numeric value represented by this object
         * after conversion to type @c long
         */
        virtual glong longValue() const = 0;
        /**
         * Returns the value of the specified number as an @c float.
         * @return The numeric value represented by this object
         * after conversion to type @c float
         */
        virtual gfloat floatValue() const = 0;
        /**
         * Returns the value of the specified number as an @c double.
         * @return The numeric value represented by this object
         * after conversion to type @c double
         */
        virtual gdouble doubleValue() const = 0;
        /**
         * Returns the value of the specified number as an @c byte.
         * @return The numeric value represented by this object
         * after conversion to type @c byte
         */
        virtual gbyte byteValue() const;
        /**
         * Returns the value of the specified number as an @c short.
         * @return The numeric value represented by this object
         * after conversion to type @c short
         */
        virtual gshort shortValue() const;
    };
} // core

#endif // Core24_NUMBER_H
