//
// Created by brunshweeck on 25 mai 2024.
//

#include "RuntimeException.h"

namespace core
{
    RuntimeException::RuntimeException()
    {
    }

    RuntimeException::RuntimeException(String message) : Exception(CORE_CAST(String &&, message))
    {
    }

    RuntimeException::RuntimeException(String message, const Throwable &cause) :
            Exception(CORE_CAST(String &&, message), cause)
    {
    }

    RuntimeException::RuntimeException(const Throwable &cause) : Exception(cause.toString(), cause)
    {
    }

    void RuntimeException::selfThrow() const
    {
        throw RuntimeException(*this);
    }
} // core