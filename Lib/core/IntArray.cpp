//
// Created by bruns on 10/05/2024.
//

#include <core/IntArray.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    IntArray::IntArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gint[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = 0;
            }
        }
    }

    IntArray::IntArray(gint length, gint initialValue)
    {

        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gint[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    IntArray::IntArray(IntArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gint[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    IntArray::IntArray(IntArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint IntArray::length() const
    {
        return count > 0 ? count : 0;
    }

    gint IntArray::isEmpty() const
    {
        return count <= 0;
    }

    gint &IntArray::get(gint index)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint const &IntArray::get(gint index) const
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint IntArray::set(gint index, gint newValue)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            gint oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    IntArray::~IntArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    IntArray IntArray::of()
    {
        return IntArray(0);
    }

    IntArray IntArray::of(gint v0)
    {
        return IntArray(1, v0);
    }

    IntArray IntArray::of(gint v0, gint v1)
    {
        IntArray ints = IntArray(2);

        ints.value[0] = v0;
        ints.value[1] = v1;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2)
    {
        IntArray ints = IntArray(3);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3)
    {
        IntArray ints = IntArray(4);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4)
    {
        IntArray ints = IntArray(5);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4,
                          gint v5)
    {
        IntArray ints = IntArray(6);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;
        ints.value[5] = v5;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4,
                          gint v5, gint v6)
    {
        IntArray ints = IntArray(7);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;
        ints.value[5] = v5;
        ints.value[6] = v6;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4,
                          gint v5, gint v6, gint v7)
    {
        IntArray ints = IntArray(8);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;
        ints.value[5] = v5;
        ints.value[6] = v6;
        ints.value[7] = v7;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4,
                          gint v5, gint v6, gint v7, gint v8)
    {
        IntArray ints = IntArray(9);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;
        ints.value[5] = v5;
        ints.value[6] = v6;
        ints.value[7] = v7;
        ints.value[8] = v8;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::of(gint v0, gint v1, gint v2, gint v3, gint v4,
                          gint v5, gint v6, gint v7, gint v8, gint v9)
    {
        IntArray ints = IntArray(10);

        ints.value[0] = v0;
        ints.value[1] = v1;
        ints.value[2] = v2;
        ints.value[3] = v3;
        ints.value[4] = v4;
        ints.value[5] = v5;
        ints.value[6] = v6;
        ints.value[7] = v7;
        ints.value[8] = v8;
        ints.value[9] = v9;

        return CORE_CAST(IntArray &&, ints);
    }

    IntArray IntArray::ofRange(gint limit)
    {
        return ofRange(0, limit);
    }

    IntArray IntArray::ofRange(gint firstValue, gint limit)
    {
        return ofRange(firstValue, limit, 1);
    }

    IntArray IntArray::ofRange(gint firstValue, gint limit, gint offsetByValue)
    {
        if (offsetByValue == 0) {
            IllegalArgumentException("Zero offset"_S).throws($ftrace(""_S));
        }
        if ((offsetByValue < 0 && limit < firstValue) || (offsetByValue > 0 && firstValue < limit)) {

            gint count = (limit - firstValue) / offsetByValue;

            if (count > SOFT_MAX_LENGTH) {
                OutOfMemoryError("Number of value in range ["_S + String::valueOf(firstValue) + ", "_S
                                 + String::valueOf(limit) + ") "_S + " with step"_S + String::valueOf(offsetByValue)
                                 + ", exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
            }

            if (count == 0)
                count += 1;

            IntArray array = IntArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gint) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(IntArray &&, array);
        } else {
            return IntArray(0);
        }
    }

    gint const &IntArray::operator[](gint index) const
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint &IntArray::operator[](gint index)
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    IntArray &IntArray::operator=(IntArray const &array)
    {
        if(this != &array) {
            gint count1 = length();
            gint count2 = array.length();
            ARRAY a = new gint [count2];
            for (int i = 0; i < count2; ++i) {
                a[i] = array.value[i];
            }
            delete [] value;
            value = a;
            count = count2;
        }
        return *this;
    }

    IntArray &IntArray::operator=(IntArray &&array) CORE_NOTHROW
    {
        if(this != &array) {
            ARRAY a = array.value;
            gint c = array.count;
            array.value = value;
            array.count = c;

            value = a;
            count = c;
        }
        return *this;
    }
} // core