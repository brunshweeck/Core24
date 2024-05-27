//
// Created by brunshweeck on 25 mai 2024.
//

#include "Error.h"

namespace core
{
    Error::Error()
    {
    }

    Error::Error(String message) CORE_NOTHROW: Throwable(CORE_CAST(String &&, message))
    {
    }

    Error::Error(String message, const Throwable &cause) : Throwable(CORE_CAST(String &&, message), cause)
    {
    }

    Error::Error(const Throwable &cause) : Throwable(cause.toString(), cause)
    {
    }

    void Error::selfThrow() const
    {
        throw Error(*this);
    }
} // core