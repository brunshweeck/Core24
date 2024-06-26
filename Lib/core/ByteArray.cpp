//
// Created by bruns on 10/05/2024.
//

#include <core/ByteArray.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    ByteArray::ByteArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gbyte[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = 0;
            }
        }
    }

    ByteArray::ByteArray(gint length, gbyte initialValue)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gbyte[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    ByteArray::ByteArray(ByteArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gbyte[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    ByteArray::ByteArray(ByteArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint ByteArray::length() const
    {
        return count > 0 && count < SOFT_MAX_LENGTH ? count : 0;
    }

    gint ByteArray::isEmpty() const
    {
        return count <= 0 || count > SOFT_MAX_LENGTH;
    }

    gbyte &ByteArray::get(gint index)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gbyte const &ByteArray::get(gint index) const
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gbyte ByteArray::set(gint index, gbyte newValue)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            gbyte oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    ByteArray::~ByteArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    ByteArray ByteArray::of()
    {
        return ByteArray(0);
    }

    ByteArray ByteArray::of(gbyte v0)
    {
        return ByteArray(1, v0);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1)
    {
        ByteArray bytes = ByteArray(2);

        bytes.value[0] = v0;
        bytes.value[1] = v1;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2)
    {
        ByteArray bytes = ByteArray(3);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3)
    {
        ByteArray bytes = ByteArray(4);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4)
    {
        ByteArray bytes = ByteArray(5);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5)
    {
        ByteArray bytes = ByteArray(6);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;
        bytes.value[5] = v5;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6)
    {
        ByteArray bytes = ByteArray(7);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;
        bytes.value[5] = v5;
        bytes.value[6] = v6;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7)
    {
        ByteArray bytes = ByteArray(8);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;
        bytes.value[5] = v5;
        bytes.value[6] = v6;
        bytes.value[7] = v7;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7, gbyte v8)
    {
        ByteArray bytes = ByteArray(9);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;
        bytes.value[5] = v5;
        bytes.value[6] = v6;
        bytes.value[7] = v7;
        bytes.value[8] = v8;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::of(gbyte v0, gbyte v1, gbyte v2, gbyte v3, gbyte v4,
                            gbyte v5, gbyte v6, gbyte v7, gbyte v8, gbyte v9)
    {
        ByteArray bytes = ByteArray(10);

        bytes.value[0] = v0;
        bytes.value[1] = v1;
        bytes.value[2] = v2;
        bytes.value[3] = v3;
        bytes.value[4] = v4;
        bytes.value[5] = v5;
        bytes.value[6] = v6;
        bytes.value[7] = v7;
        bytes.value[8] = v8;
        bytes.value[9] = v9;

        return CORE_CAST(ByteArray &&, bytes);
    }

    ByteArray ByteArray::ofRange(gbyte limit)
    {
        return ofRange(0, limit);
    }

    ByteArray ByteArray::ofRange(gbyte firstValue, gbyte limit)
    {
        return ofRange(firstValue, limit, 1);
    }

    ByteArray ByteArray::ofRange(gbyte firstValue, gbyte limit, gint offsetByValue)
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

            if (count == 0) {
                count += 1;
            }

            ByteArray array = ByteArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gbyte) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(ByteArray &&, array);
        }
        else {
            return ByteArray(0);
        }
    }

    gbyte const &ByteArray::operator[](gint index) const
    {
        try {
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gbyte &ByteArray::operator[](gint index)
    {
        try {
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }
} // core