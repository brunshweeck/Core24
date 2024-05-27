//
// Created by brunshweeck on 25 mai 2024.
//

#include "ArithmeticException.h"

namespace core
{
    ArithmeticException::ArithmeticException()
    {
    }

    ArithmeticException::ArithmeticException(String message) : Exception(CORE_CAST(String &&, message))
    {
    }

    void ArithmeticException::selfThrow() const
    {
        throw ArithmeticException(*this);
    }
} // core