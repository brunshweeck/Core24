//
// Created by brunshweeck on 25 mai 2024.
//

#include "Exception.h"

namespace core
{
    Exception::Exception()
    {
    }

    Exception::Exception(String message) CORE_NOTHROW: Throwable(CORE_CAST(String &&, message))
    {
    }

    Exception::Exception(String message, const Throwable &cause) : Throwable(CORE_CAST(String &&, message), cause)
    {
    }

    Exception::Exception(const Throwable &cause) : Throwable(cause.toString(), cause)
    {
    }

    void Exception::selfThrow() const
    {
        throw Exception(*this);
    }
} // core