//
// Created by bruns on 13/05/2024.
//

#include <core/String.h>
#include <core/Short.h>
#include <core/Integer.h>
#include <core/NumberFormatException.h>
#include <core/IllegalArgumentException.h>
#include <core/misc/Foreign.h>

namespace core
{
    String Short::toString(gshort value)
    {
        return Integer::toString(value);
    }

    gshort Short::parseShort(const String &s, gint radix)
    {
        gint i = 0;
        try {
            i = Integer::parseInt(s, radix);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
        if (i < MIN_VALUE || i > MAX_VALUE) {
            NumberFormatException("value out of range"_S).throws($ftrace(""_S));
        }
        return (gshort) i;
    }

    gshort Short::parseShort(const String &s)
    {
        try {
            return parseShort(s, 10);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Short Short::valueOf(const String &s, gint radix)
    {
        try {
            return valueOf(parseShort(s, radix));
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Short Short::valueOf(gshort s)
    {
        return s;
    }

    Short Short::valueOf(const String &s)
    {
        try {
            return valueOf(s, 10);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Short Short::decode(const String &nm)
    {
        gint i = 0;
        try {
            i = Integer::decode(nm);
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
        if (i < MIN_VALUE || i > MAX_VALUE) {
            NumberFormatException("value out of range"_S).throws($ftrace(""_S));
        }
        return (gshort) i;
    }

    Short::Short(gshort value) : value(value)
    {
    }

    gbyte Short::byteValue() const
    {
        return (gbyte) value;
    }

    gshort Short::shortValue() const
    {
        return value;
    }

    gint Short::intValue() const
    {
        return value;
    }

    glong Short::longValue() const
    {
        return value;
    }

    gfloat Short::floatValue() const
    {
        return value;
    }

    gdouble Short::doubleValue() const
    {
        return value;
    }

    String Short::toString() const
    {
        return Object::toString();
    }

    gint Short::hash() const
    {
        return hash(value);
    }

    gint Short::hash(gshort value)
    {
        return value;
    }

    gbool Short::equals(const Object &obj) const
    {
        if (this == &obj) {
            return true;
        }

        if (!ClassOf(*this)::hasInstance(obj)) {
            return false;
        }

        Short const s = CORE_XCAST(Short const, obj);
        return value == s.value;
    }

    gint Short::compareTo(const Short &anotherShort) const
    {
        return compare(value, anotherShort.value);
    }

    gint Short::compare(gshort x, gshort y)
    {
        return x - y;
    }

    gint Short::compareUnsigned(gshort x, gshort y)
    {
        return toUnsignedInt(x) - toUnsignedInt(y);
    }

    gshort Short::reverseBytes(gshort i)
    {
        return (gshort) ((i & 0xff00) >> 8 | i << 8);
    }

    gint Short::toUnsignedInt(gshort x)
    {
        return (gint) (x & 0xffff);
    }

    glong Short::toUnsignedLong(gshort x)
    {
        return (glong) (x & 0xffffL);
    }

    Short::operator gshort() const
    {
        return shortValue();
    }

    Short::operator gshort &()
    {
        return value;
    }
} // core