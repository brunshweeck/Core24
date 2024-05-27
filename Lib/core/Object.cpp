//
// Created by bruns on 08/05/2024.
//

#include <core/Object.h>
#include <core/Class.h>

#include "String.h"

namespace core
{
    Object::Object()
    {
    }

    Object::~Object()
    {
    }

    gbool Object::equals(Object const &obj) const
    {
        return this == &obj;
    }

    gint Object::hash() const
    {
        return CORE_FCAST(glong, this);
    }

    String Object::toString() const
    {
        return "<object>"_S;
    }

    misc::NIL &null = misc::NIL::INSTANCE;
} // core