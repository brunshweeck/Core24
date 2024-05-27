//
// Created by brunshweeck on 25 mai 2024.
//

#include "IllegalStateException.h"

namespace core
{
    IllegalStateException::IllegalStateException()
    {
    }

    IllegalStateException::IllegalStateException(String message) : Exception(CORE_CAST(String &&, message))
    {
    }

    IllegalStateException::IllegalStateException(String message, const Throwable &cause) :
            Exception(CORE_CAST(String &&, message), cause)
    {
    }

    IllegalStateException::IllegalStateException(const Throwable &cause) : Exception(cause.toString(), cause)
    {
    }

    void IllegalStateException::selfThrow() const
    {
        throw IllegalStateException(*this);
    }
} // core