//
// Created by bruns on 10/05/2024.
//

#include <core/FloatArray.h>
#include <core/Float.h>
#include <core/Double.h>
#include <core/IllegalArgumentException.h>
#include <core/OutOfMemoryError.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>

namespace core
{
    FloatArray::FloatArray(gint length)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gfloat[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = .0F;
            }
        }
    }

    FloatArray::FloatArray(gint length, gfloat initialValue)
    {
        if (length < 0) {
            IllegalArgumentException("Negative array size"_S).throws($ftrace(""_S));
        }
        if (length > SOFT_MAX_LENGTH) {
            OutOfMemoryError("Array size exceed SOFT_MAX_LENGTH"_S).throws($ftrace(""_S));
        }
        if (length > 0) {
            value = new gfloat[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = initialValue;
            }
        }
    }

    FloatArray::FloatArray(FloatArray const &array)
    {
        gint length = array.length();
        if (length > 0) {
            value = new gfloat[length];
            count = length;
            for (int i = 0; i < length; ++i) {
                value[i] = array.value[i];
            }
        }
    }

    FloatArray::FloatArray(FloatArray &&array) noexcept
    {
        value = array.value;
        count = array.count;

        array.value = null;
        array.count = 0;
    }

    gint FloatArray::length() const
    {
        return count > 0 ? count : 0;
    }

    gint FloatArray::isEmpty() const
    {
        return count <= 0;
    }

    gfloat &FloatArray::get(gint index)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gfloat const &FloatArray::get(gint index) const
    {
        try {
            misc::Precondition::checkIndex(index, count);

            return value[index];
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gfloat FloatArray::set(gint index, gfloat newValue)
    {
        try {
            misc::Precondition::checkIndex(index, count);

            gfloat oldValue = value[index];
            value[index] = newValue;
            return oldValue;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    FloatArray::~FloatArray()
    {
        if (count > 0) {
            count = 0;
            delete[] value;
            value = null;
        }
    }

    FloatArray FloatArray::of()
    {
        return FloatArray(0);
    }

    FloatArray FloatArray::of(gfloat v0)
    {
        return FloatArray(1, v0);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1)
    {
        FloatArray floats = FloatArray(2);

        floats.value[0] = v0;
        floats.value[1] = v1;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2)
    {
        FloatArray floats = FloatArray(3);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3)
    {
        FloatArray floats = FloatArray(4);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4)
    {
        FloatArray floats = FloatArray(5);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                              gfloat v5)
    {
        FloatArray floats = FloatArray(6);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;
        floats.value[5] = v5;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                              gfloat v5, gfloat v6)
    {
        FloatArray floats = FloatArray(7);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;
        floats.value[5] = v5;
        floats.value[6] = v6;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                              gfloat v5, gfloat v6, gfloat v7)
    {
        FloatArray floats = FloatArray(8);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;
        floats.value[5] = v5;
        floats.value[6] = v6;
        floats.value[7] = v7;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                              gfloat v5, gfloat v6, gfloat v7, gfloat v8)
    {
        FloatArray floats = FloatArray(9);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;
        floats.value[5] = v5;
        floats.value[6] = v6;
        floats.value[7] = v7;
        floats.value[8] = v8;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::of(gfloat v0, gfloat v1, gfloat v2, gfloat v3, gfloat v4,
                              gfloat v5, gfloat v6, gfloat v7, gfloat v8, gfloat v9)
    {
        FloatArray floats = FloatArray(10);

        floats.value[0] = v0;
        floats.value[1] = v1;
        floats.value[2] = v2;
        floats.value[3] = v3;
        floats.value[4] = v4;
        floats.value[5] = v5;
        floats.value[6] = v6;
        floats.value[7] = v7;
        floats.value[8] = v8;
        floats.value[9] = v9;

        return CORE_CAST(FloatArray &&, floats);
    }

    FloatArray FloatArray::ofRange(gfloat limit)
    {
        return ofRange(0.0f, limit);
    }

    FloatArray FloatArray::ofRange(gfloat firstValue, gfloat limit)
    {
        return ofRange(firstValue, limit, 1.0);
    }

    FloatArray FloatArray::ofRange(gfloat firstValue, gfloat limit, gdouble offsetByValue)
    {
        if (offsetByValue == 0) {
            IllegalArgumentException("Zero offset"_S).throws($ftrace(""_S));
        }
        if(!Float::isFinite(firstValue) || !Float::isFinite(limit) || !Double::isFinite(offsetByValue)) {
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

            if (count == 0)
                count += 1;

            FloatArray array = FloatArray(count);

            for (int i = 0; i < count; i++) {
                array.value[i] = (gfloat) (firstValue + offsetByValue * i);
            }

            return CORE_CAST(FloatArray &&, array);
        } else {
            return FloatArray(0);
        }
    }

    gfloat const &FloatArray::operator[](gint index) const
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gfloat &FloatArray::operator[](gint index)
    {
        try{
            return get(index);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }
} // core