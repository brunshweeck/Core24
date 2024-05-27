//
// Created by bruns on 13/05/2024.
//

#include <core/Byte.h>
#include <core/String.h>
#include <core/Integer.h>
#include <core/NumberFormatException.h>
#include <core/IllegalArgumentException.h>
#include <core/misc/Foreign.h>
#include "Byte.h"

namespace core
{
    String Byte::toString(gbyte value)
    {
        return Integer::toString(value);
    }

    Byte Byte::valueOf(gbyte b)
    {
        return b;
    }

    gbyte Byte::parseByte(String const &s, gint radix)
    {
        gint i = 0;
        try {
            i = Integer::parseInt(s, radix);
        } catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
        if (i < MIN_VALUE || i > MAX_VALUE) {
            NumberFormatException("value out of range"_S).throws($ftrace(""_S));
        }
        return (gbyte) i;
    }

    gbyte Byte::parseByte(String const &s)
    {
        try {
            return parseByte(s, 10);
        } catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Byte Byte::valueOf(String const &s, gint radix)
    {
        try {
            return valueOf(parseByte(s, radix));
        } catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Byte Byte::valueOf(String const &s)
    {
        try {
            return valueOf(s, 10);
        } catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Byte Byte::decode(String const &nm)
    {
        gint i = 0;
        try {
            i = Integer::decode(nm);
        } catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
        if (i < MIN_VALUE || i > MAX_VALUE) {
            NumberFormatException("value out of range"_S).throws($ftrace(""_S));
        }
        return (gbyte) i;
    }

    Byte::Byte(gbyte value) : value(value)
    {
    }

    gbyte Byte::byteValue() const
    {
        return value;
    }

    gshort Byte::shortValue() const
    {
        return (gshort) intValue();
    }

    gint Byte::intValue() const
    {
        return (gint) value;
    }

    glong Byte::longValue() const
    {
        return (glong) value;
    }

    gfloat Byte::floatValue() const
    {
        return (gfloat) value;
    }

    gdouble Byte::doubleValue() const
    {
        return (gdouble) value;
    }

    String Byte::toString() const
    {
        return toString(value);
    }

    gint Byte::hash() const
    {
        return hash(value);
    }

    gint Byte::hash(gbyte value)
    {
        return (gint) value;
    }

    gbool Byte::equals(Object const &obj) const
    {
        return this == &obj || Class<Byte>::hasInstance(obj) && value == CORE_XCAST(Byte const, obj).value;
    }

    gint Byte::compareTo(Byte const &anotherByte) const
    {
        return compare(value, anotherByte.value);
    }

    gint Byte::compare(gbyte x, gbyte y)
    {
        return x - y;
    }

    gint Byte::compareUnsigned(gbyte x, gbyte y)
    {
        return toUnsignedInt(x) - toUnsignedInt(y);
    }

    gint Byte::toUnsignedInt(gbyte x)
    {
        return x & 0xff;
    }

    glong Byte::toUnsignedLong(gbyte x)
    {
        return x & 0xffLL;
    }

    Byte::operator gbyte() const
    {
        return byteValue();
    }

    Byte::operator gbyte &()
    {
        return value;
    }

} // core