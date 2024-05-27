//
// Created by bruns on 13/05/2024.
//

#include <core/Boolean.h>

#include <core/String.h>

namespace core
{
    Boolean::Boolean(gbool value) : value(value)
    {
    }

    gbool Boolean::parseBoolean(String const &s)
    {
        if (s.length() != 4)
            return false;
        return s.equals("true"_S);
    }

    gbool Boolean::booleanValue() const
    {
        return value;
    }

    Boolean Boolean::valueOf(gbool b)
    {
        return b ? TRUE : FALSE;
    }

    Boolean Boolean::valueOf(String const &s)
    {
        return valueOf(parseBoolean(s));
    }

    String Boolean::toString(gbool b)
    {
        return b ? "true"_S : "false"_S;
    }

    String Boolean::toString() const
    {
        return toString(value);
    }

    gint Boolean::hash() const
    {
        return hash(value);
    }

    gint Boolean::hash(gbool value)
    {
        return value ? 1231 : 1237;
    }

    gbool Boolean::equals(Object const &obj) const
    {
        return this == &obj || Class<Boolean>::hasInstance(obj) && value == CORE_XCAST(Boolean const, obj).value;
    }

    gint Boolean::compareTo(Boolean const &other) const
    {
        return compare(value, other.value);
    }

    gint Boolean::compare(gbool x, gbool y)
    {
        return x && y ? 0 : x ? 1 : -1;
    }

    gbool Boolean::logicalAnd(gbool a, gbool b)
    {
        return a && b;
    }

    gbool Boolean::logicalOr(gbool a, gbool b)
    {
        return a || b;
    }

    gbool Boolean::logicalXor(gbool a, gbool b)
    {
        return a != b;
    }
} // core
