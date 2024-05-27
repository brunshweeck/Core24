//
// Created by brunshweeck on 25 mai 2024.
//

#include "OutOfMemoryError.h"

namespace core
{
    OutOfMemoryError::OutOfMemoryError()
    {
    }

    OutOfMemoryError::OutOfMemoryError(String message) : Error(CORE_CAST(String &&, message))
    {
    }

    void OutOfMemoryError::selfThrow() const
    {
        throw OutOfMemoryError(*this);
    }
} // core