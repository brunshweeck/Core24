//
// Created by brunshweeck on 25 mai 2024.
//

#include <core/IndexOutOfBoundsException.h>
#include <core/Integer.h>
#include <core/Long.h>

namespace core
{
    IndexOutOfBoundsException::IndexOutOfBoundsException()
    {
    }

    IndexOutOfBoundsException::IndexOutOfBoundsException(String message) : Exception(CORE_CAST(String &&, message))
    {
    }

    IndexOutOfBoundsException::IndexOutOfBoundsException(gint index) : Exception(Integer::toString(index))
    {
    }

    IndexOutOfBoundsException::IndexOutOfBoundsException(glong index) : Exception(Long::toString(index))
    {
    }

    void IndexOutOfBoundsException::selfThrow() const
    {
        throw IndexOutOfBoundsException(*this);
    }
} // core