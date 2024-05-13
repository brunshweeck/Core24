//
// Created by bruns on 10/05/2024.
//

#include <core/LongArray.h>

namespace core
{
    LongArray::LongArray(gint length)
    {
        if (length > 0) {
            value = new glong[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = 0L;
            }
        }
    }

    LongArray::LongArray(gint length, glong initialValue)
    {
        if (length > 0) {
            value = new glong[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    LongArray::LongArray(LongArray const& array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new glong[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    LongArray::LongArray(LongArray&& array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint LongArray::length() const
    {
        return count > 0 ? count : 0;
    }

    gint LongArray::isEmpty() const
    {
        return count <= 0;
    }

    glong& LongArray::get(gint index)
    {
        if (index >= 0 && index < count) {
            return value[index];
        }
        else {
            throw 0;
        }
    }

    glong const& LongArray::get(gint index) const
    {
        if (index >= 0 && index < count) {
            return value[index];
        }
        else {
            throw 0;
        }
    }

    glong LongArray::set(gint index, glong newValue)
    {
        if (index >= 0 && index < count) {
            glong oldValue = value[index];
            value[index]   = newValue;
            return oldValue;
        }
        else {
            throw 0;
        }
    }

    LongArray::~LongArray()
    {
        if (count > 0) {
            count = 0;
            delete [] value;
            value = null;
        }
    }

    LongArray LongArray::of()
    {
        return LongArray(0);
    }

    LongArray LongArray::of(glong v0)
    {
        return LongArray(1, v0);
    }

    LongArray LongArray::of(glong v0, glong v1)
    {
        LongArray longs = LongArray(2);

        longs.value[0] = v0;
        longs.value[1] = v1;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2)
    {
        LongArray longs = LongArray(3);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3)
    {
        LongArray longs = LongArray(4);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4)
    {
        LongArray longs = LongArray(5);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5)
    {
        LongArray longs = LongArray(6);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;
        longs.value[5] = v5;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6)
    {
        LongArray longs = LongArray(7);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;
        longs.value[5] = v5;
        longs.value[6] = v6;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7)
    {
        LongArray longs = LongArray(8);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;
        longs.value[5] = v5;
        longs.value[6] = v6;
        longs.value[7] = v7;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7, glong v8)
    {
        LongArray longs = LongArray(9);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;
        longs.value[5] = v5;
        longs.value[6] = v6;
        longs.value[7] = v7;
        longs.value[8] = v8;

        return CORE_CAST(LongArray &&, longs);
    }

    LongArray LongArray::of(glong v0, glong v1, glong v2, glong v3, glong v4,
                            glong v5, glong v6, glong v7, glong v8, glong v9)
    {
        LongArray longs = LongArray(10);

        longs.value[0] = v0;
        longs.value[1] = v1;
        longs.value[2] = v2;
        longs.value[3] = v3;
        longs.value[4] = v4;
        longs.value[5] = v5;
        longs.value[6] = v6;
        longs.value[7] = v7;
        longs.value[8] = v8;
        longs.value[9] = v9;

        return CORE_CAST(LongArray &&, longs);
    }
} // core