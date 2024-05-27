//
// Created by bruns on 14/05/2024.
//

#include "Throwable.h"

namespace core
{
    Throwable::Throwable() CORE_NOTHROW: origin(this)
    {
    }

    Throwable::Throwable(String message) CORE_NOTHROW:
            detailMessage(CORE_CAST(String &&, message)), origin(this)
    {
    }

    Throwable::Throwable(String message, const Throwable &cause) CORE_NOTHROW:
            detailMessage(CORE_CAST(String &&, message)), origin(this)
    {
        origin = &CORE_CAST(Throwable &, cause);
    }

    Throwable::Throwable(Throwable const &other) : Object(other),
                                                   std::exception(other),
                                                   detailMessage(other.detailMessage),
                                                   origin(other.origin)
    {
        if (other.origin == &other)
            origin = this;
    }

    Throwable::Throwable(Throwable &&other) noexcept: Object(other),
                                                      std::exception(other),
                                                      detailMessage(CORE_CAST(String &&, other.detailMessage)),
                                                      origin(other.origin)
    {
        if (other.origin == &other)
            origin = this;
    }

    String Throwable::message() const
    {
        return detailMessage;
    }

    String Throwable::localizedMessage() const
    {
        return message();
    }

    Throwable &Throwable::cause() const
    {
        return origin == null || origin == this ? CORE_CAST(Throwable &, *this) : *origin;
    }

    String Throwable::toString() const
    {
        return localizedMessage();
    }

    void Throwable::throws(Trace currentExecutionPoint) const
    {
        CORE_IGNORE(currentExecutionPoint);
        rethrow();
    }

    void Throwable::rethrow() const
    {
        selfThrow();
    }

    void Throwable::selfThrow() const
    {
        CORE_UNREACHABLE();
    }

    Throwable::ByteStream Throwable::what() const CORE_NOTHROW
    {
        return "";
    }
} // core
