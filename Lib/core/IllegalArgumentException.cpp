//
// Created by brunshweeck on 25 mai 2024.
//

#include "IllegalArgumentException.h"

namespace core
{
    IllegalArgumentException::IllegalArgumentException()
    {
    }

    IllegalArgumentException::IllegalArgumentException(String message) :
            RuntimeException(CORE_CAST(String &&, message))
    {
    }

    IllegalArgumentException::IllegalArgumentException(String message, const Throwable &cause) :
            RuntimeException(CORE_CAST(String &&, message), cause)
    {
    }

    IllegalArgumentException::IllegalArgumentException(const Throwable &cause) : RuntimeException(cause.toString(),
                                                                                                  cause)
    {
    }

    void IllegalArgumentException::selfThrow() const
    {
        throw IllegalArgumentException(*this);
    }
} // core