//
// Created by bruns on 09/05/2024.
//

#include <core/CharArray.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    CharArray::CharArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gchar[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = u'\0';
            }
        }
    }

    CharArray::CharArray(gint length, gchar initialValue)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gchar[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    CharArray::CharArray(CharArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gchar[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    CharArray::CharArray(CharArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint CharArray::length() const
    {
        return count > 0 && count < SOFT_MAX_LENGTH ? count : 0;
    }

    gint CharArray::isEmpty() const
    {
        return count <= 0;
    }

    gchar &CharArray::get(gint index)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gchar const &CharArray::get(gint index) const
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gchar CharArray::set(gint index, gchar newValue)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            gchar oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    CharArray::~CharArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    CharArray CharArray::of()
    {
        return CharArray(0);
    }

    CharArray CharArray::of(gchar v0)
    {
        return CharArray(1, v0);
    }

    CharArray CharArray::of(gchar v0, gchar v1)
    {
        CharArray chars = CharArray(2);

        chars.value[0] = v0;
        chars.value[1] = v1;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2)
    {
        CharArray chars = CharArray(3);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3)
    {
        CharArray chars = CharArray(4);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4)
    {
        CharArray chars = CharArray(5);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5)
    {
        CharArray chars = CharArray(6);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;
        chars.value[5] = v5;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6)
    {
        CharArray chars = CharArray(7);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;
        chars.value[5] = v5;
        chars.value[6] = v6;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7)
    {
        CharArray chars = CharArray(8);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;
        chars.value[5] = v5;
        chars.value[6] = v6;
        chars.value[7] = v7;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7, gchar v8)
    {
        CharArray chars = CharArray(9);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;
        chars.value[5] = v5;
        chars.value[6] = v6;
        chars.value[7] = v7;
        chars.value[8] = v8;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::of(gchar v0, gchar v1, gchar v2, gchar v3, gchar v4,
                            gchar v5, gchar v6, gchar v7, gchar v8, gchar v9)
    {
        CharArray chars = CharArray(10);

        chars.value[0] = v0;
        chars.value[1] = v1;
        chars.value[2] = v2;
        chars.value[3] = v3;
        chars.value[4] = v4;
        chars.value[5] = v5;
        chars.value[6] = v6;
        chars.value[7] = v7;
        chars.value[8] = v8;
        chars.value[9] = v9;

        return CORE_CAST(CharArray &&, chars);
    }

    CharArray CharArray::ofRange(gchar limit)
    {
        return ofRange(0, limit);
    }

    CharArray CharArray::ofRange(gchar firstValue, gchar limit)
    {
        return ofRange(firstValue, limit, 1);
    }

    CharArray CharArray::ofRange(gchar firstValue, gchar limit, gint offsetByValue)
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

            CharArray array = CharArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gchar) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(CharArray &&, array);
        }
        else {
            return CharArray(0);
        }
    }

    gchar const &CharArray::operator[](gint index) const
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gchar &CharArray::operator[](gint index)
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }
} // core
