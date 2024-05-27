//
// Created by bruns on 10/05/2024.
//

#include <core/ShortArray.h>

namespace core
{
    ShortArray::ShortArray(gint length)
    {
        if (length > 0) {
            if (length > SOFT_MAX_LENGTH)
                length = SOFT_MAX_LENGTH;
            value = new gshort[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = 0;
            }
        }
    }

    ShortArray::ShortArray(gint length, gshort initialValue)
    {
        if (length > 0) {
            if (length > SOFT_MAX_LENGTH)
                length = SOFT_MAX_LENGTH;
            value = new gshort[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    ShortArray::ShortArray(ShortArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gshort[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    ShortArray::ShortArray(ShortArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint ShortArray::length() const
    {
        return count > 0 ? count : 0;
    }

    gint ShortArray::isEmpty() const
    {
        return count <= 0;
    }

    gshort &ShortArray::get(gint index)
    {
        if (index >= 0 && index < count) {
            return value[index];
        } else {
            throw 0;
        }
    }

    gshort const &ShortArray::get(gint index) const
    {
        if (index >= 0 && index < count) {
            return value[index];
        } else {
            throw 0;
        }
    }

    gshort ShortArray::set(gint index, gshort newValue)
    {
        if (index >= 0 && index < count) {
            gshort oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        } else {
            throw 0;
        }
    }

    ShortArray::~ShortArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    ShortArray ShortArray::of()
    {
        return ShortArray(0);
    }

    ShortArray ShortArray::of(gshort v0)
    {
        return ShortArray(1, v0);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1)
    {
        ShortArray shorts = ShortArray(2);

        shorts.value[0] = v0;
        shorts.value[1] = v1;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2)
    {
        ShortArray shorts = ShortArray(3);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3)
    {
        ShortArray shorts = ShortArray(4);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4)
    {
        ShortArray shorts = ShortArray(5);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4,
                              gshort v5)
    {
        ShortArray shorts = ShortArray(6);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;
        shorts.value[5] = v5;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4,
                              gshort v5, gshort v6)
    {
        ShortArray shorts = ShortArray(7);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;
        shorts.value[5] = v5;
        shorts.value[6] = v6;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4,
                              gshort v5, gshort v6, gshort v7)
    {
        ShortArray shorts = ShortArray(8);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;
        shorts.value[5] = v5;
        shorts.value[6] = v6;
        shorts.value[7] = v7;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4,
                              gshort v5, gshort v6, gshort v7, gshort v8)
    {
        ShortArray shorts = ShortArray(9);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;
        shorts.value[5] = v5;
        shorts.value[6] = v6;
        shorts.value[7] = v7;
        shorts.value[8] = v8;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::of(gshort v0, gshort v1, gshort v2, gshort v3, gshort v4,
                              gshort v5, gshort v6, gshort v7, gshort v8, gshort v9)
    {
        ShortArray shorts = ShortArray(10);

        shorts.value[0] = v0;
        shorts.value[1] = v1;
        shorts.value[2] = v2;
        shorts.value[3] = v3;
        shorts.value[4] = v4;
        shorts.value[5] = v5;
        shorts.value[6] = v6;
        shorts.value[7] = v7;
        shorts.value[8] = v8;
        shorts.value[9] = v9;

        return CORE_CAST(ShortArray &&, shorts);
    }

    ShortArray ShortArray::ofRange(gshort limit)
    {
        return ofRange(0, limit);
    }

    ShortArray ShortArray::ofRange(gshort firstValue, gshort limit)
    {
        return ofRange(firstValue, limit, 1);
    }

    ShortArray ShortArray::ofRange(gshort firstValue, gshort limit, gint offsetByValue)
    {
        if (offsetByValue == 0) {
            throw 0;
        }
        if ((offsetByValue < 0 && limit < firstValue) || (offsetByValue > 0 && firstValue < limit)) {

            gint count = (limit - firstValue) / offsetByValue;

            if (count == 0)
                count += 1;

            ShortArray array = ShortArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gshort) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(ShortArray &&, array);
        } else {
            return ShortArray(0);
        }
    }
} // core