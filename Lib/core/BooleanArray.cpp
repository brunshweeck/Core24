//
// Created by bruns on 10/05/2024.
//

#include <core/BooleanArray.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    BooleanArray::BooleanArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gbool[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = false;
            }
        }
    }

    BooleanArray::BooleanArray(gint length, gbool initialValue)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gbool[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    BooleanArray::BooleanArray(BooleanArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gbool[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    BooleanArray::BooleanArray(BooleanArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint BooleanArray::length() const
    {
        return count > 0 && count < SOFT_MAX_LENGTH ? count : 0;
    }

    gint BooleanArray::isEmpty() const
    {
        return count <= 0 || count > SOFT_MAX_LENGTH;
    }

    gbool &BooleanArray::get(gint index)
    {
        try{
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gbool const &BooleanArray::get(gint index) const
    {
        try{
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gbool BooleanArray::set(gint index, gbool newValue)
    {
        try{
            misc::Precondition::checkIndex(index, count);

            gbool oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    BooleanArray::~BooleanArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    BooleanArray BooleanArray::of()
    {
        return BooleanArray(0);
    }

    BooleanArray BooleanArray::of(gbool v0)
    {
        return BooleanArray(1, v0);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1)
    {
        BooleanArray bools = BooleanArray(2);

        bools.value[0] = v0;
        bools.value[1] = v1;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2)
    {
        BooleanArray bools = BooleanArray(3);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3)
    {
        BooleanArray bools = BooleanArray(4);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4)
    {
        BooleanArray bools = BooleanArray(5);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                                  gbool v5)
    {
        BooleanArray bools = BooleanArray(6);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;
        bools.value[5] = v5;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                                  gbool v5, gbool v6)
    {
        BooleanArray bools = BooleanArray(7);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;
        bools.value[5] = v5;
        bools.value[6] = v6;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                                  gbool v5, gbool v6, gbool v7)
    {
        BooleanArray bools = BooleanArray(8);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;
        bools.value[5] = v5;
        bools.value[6] = v6;
        bools.value[7] = v7;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                                  gbool v5, gbool v6, gbool v7, gbool v8)
    {
        BooleanArray bools = BooleanArray(9);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;
        bools.value[5] = v5;
        bools.value[6] = v6;
        bools.value[7] = v7;
        bools.value[8] = v8;

        return CORE_CAST(BooleanArray &&, bools);
    }

    BooleanArray BooleanArray::of(gbool v0, gbool v1, gbool v2, gbool v3, gbool v4,
                                  gbool v5, gbool v6, gbool v7, gbool v8, gbool v9)
    {
        BooleanArray bools = BooleanArray(10);

        bools.value[0] = v0;
        bools.value[1] = v1;
        bools.value[2] = v2;
        bools.value[3] = v3;
        bools.value[4] = v4;
        bools.value[5] = v5;
        bools.value[6] = v6;
        bools.value[7] = v7;
        bools.value[8] = v8;
        bools.value[9] = v9;

        return CORE_CAST(BooleanArray &&, bools);
    }
} // core