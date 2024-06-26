//
// Created by bruns on 10/05/2024.
//

#include <core/DoubleArray.h>
#include <core/Double.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    DoubleArray::DoubleArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gdouble[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = .0;
            }
        }
    }

    DoubleArray::DoubleArray(gint length, gdouble initialValue)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gdouble[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    DoubleArray::DoubleArray(DoubleArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gdouble[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    DoubleArray::DoubleArray(DoubleArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint DoubleArray::length() const
    {
        return count > 0 ? count : 0;
    }

    gint DoubleArray::isEmpty() const
    {
        return count <= 0;
    }

    gdouble &DoubleArray::get(gint index)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gdouble const &DoubleArray::get(gint index) const
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gdouble DoubleArray::set(gint index, gdouble newValue)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            gdouble oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    DoubleArray::~DoubleArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    DoubleArray DoubleArray::of()
    {
        return DoubleArray(0);
    }

    DoubleArray DoubleArray::of(gdouble v0)
    {
        return DoubleArray(1, v0);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1)
    {
        DoubleArray doubles = DoubleArray(2);

        doubles.value[0] = v0;
        doubles.value[1] = v1;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2)
    {
        DoubleArray doubles = DoubleArray(3);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3)
    {
        DoubleArray doubles = DoubleArray(4);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4)
    {
        DoubleArray doubles = DoubleArray(5);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4,
                                gdouble v5)
    {
        DoubleArray doubles = DoubleArray(6);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;
        doubles.value[5] = v5;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4,
                                gdouble v5, gdouble v6)
    {
        DoubleArray doubles = DoubleArray(7);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;
        doubles.value[5] = v5;
        doubles.value[6] = v6;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4,
                                gdouble v5, gdouble v6, gdouble v7)
    {
        DoubleArray doubles = DoubleArray(8);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;
        doubles.value[5] = v5;
        doubles.value[6] = v6;
        doubles.value[7] = v7;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4,
                                gdouble v5, gdouble v6, gdouble v7, gdouble v8)
    {
        DoubleArray doubles = DoubleArray(9);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;
        doubles.value[5] = v5;
        doubles.value[6] = v6;
        doubles.value[7] = v7;
        doubles.value[8] = v8;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::of(gdouble v0, gdouble v1, gdouble v2, gdouble v3, gdouble v4,
                                gdouble v5, gdouble v6, gdouble v7, gdouble v8, gdouble v9)
    {
        DoubleArray doubles = DoubleArray(10);

        doubles.value[0] = v0;
        doubles.value[1] = v1;
        doubles.value[2] = v2;
        doubles.value[3] = v3;
        doubles.value[4] = v4;
        doubles.value[5] = v5;
        doubles.value[6] = v6;
        doubles.value[7] = v7;
        doubles.value[8] = v8;
        doubles.value[9] = v9;

        return CORE_CAST(DoubleArray &&, doubles);
    }

    DoubleArray DoubleArray::ofRange(gdouble limit)
    {
        return ofRange(0.0, limit);
    }

    DoubleArray DoubleArray::ofRange(gdouble firstValue, gdouble limit)
    {
        return ofRange(firstValue, limit, 1.0);
    }

    DoubleArray DoubleArray::ofRange(gdouble firstValue, gdouble limit, gdouble offsetByValue)
    {
        if (offsetByValue == 0) {
            IllegalArgumentException("Zero offset"_S).throws($ftrace(""_S));
        }
        if(!Double::isFinite(firstValue) || !Double::isFinite(limit) || !Double::isFinite(offsetByValue)) {
            IllegalArgumentException("Non-Finite value"_S).throws($ftrace(""_S));
        }

        if ((offsetByValue < 0 && limit < firstValue) || (offsetByValue > 0 && firstValue < limit)) {

            gdouble count0 = (limit - firstValue) / offsetByValue;

            if(count0 > SOFT_MAX_LENGTH){
                OutOfMemoryError("Number of value in range ["_S + String::valueOf(firstValue) + ", "_S
                                 + String::valueOf(limit) + ") "_S + " with step"_S + String::valueOf(offsetByValue)
                                 + ", exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
            }

            gint count = (gint) count0;

            if (count == 0) {
                count += 1;
            }

            DoubleArray array = DoubleArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gdouble) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(DoubleArray &&, array);
        } else {
            return DoubleArray(0);
        }
    }

    gdouble const &DoubleArray::operator[](gint index) const
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gdouble &DoubleArray::operator[](gint index)
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }
} // core