//
// Created by brunshweeck on 25 mai 2024.
//

#include "NumberFormatException.h"

namespace core
{
    NumberFormatException::NumberFormatException()
    {
    }

    NumberFormatException::NumberFormatException(String message): Exception(CORE_CAST(String &&, message))
    {
    }

    void NumberFormatException::selfThrow() const
    {
        throw NumberFormatException(*this);
    }
} // core