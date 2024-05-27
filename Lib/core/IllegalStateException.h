//
// Created by brunshweeck on 25 mai 2024.
//

#ifndef CORE24_ILLEGALSTATEEXCEPTION_H
#define CORE24_ILLEGALSTATEEXCEPTION_H

#include <core/RuntimeException.h>

namespace core
{

    class IllegalStateException: public virtual RuntimeException
    {
    public:
        /**
         * Constructs an IllegalStateException with no detail message.
         * A detail message is a String that describes this particular exception.
         */
        CORE_IMPLICIT IllegalStateException();

        /**
         * Constructs an IllegalStateException with the specified detail
         * message.  A detail message is a String that describes this particular
         * exception.
         *
         * @param s the String that contains a detailed message
         */
        CORE_EXPLICIT IllegalStateException(String message);

        /**
         * Constructs a new exception with the specified detail message and
         * cause.
         *
         * <p>Note that the detail message associated with <b>cause</b> is
         * <i>not</i> automatically incorporated in this exception's detail
         * message.
         *
         * @param  message the detail message (which is saved for later retrieval
         *         by the <b style="color:orange;">Throwable#message()</b> method).
         * @param  cause the cause (which is saved for later retrieval by the
         *         <b style="color:orange;">Throwable#cause()</b> method).
         *
         */
        CORE_EXPLICIT IllegalStateException(String message, Throwable const &cause);

        /**
         * Constructs a new exception with the specified cause and a detail
         * message of <b>(cause==null ? null : cause.toString())</b> (which
         * typically contains the class and detail message of <b>cause</b>).
         * This constructor is useful for exceptions that are little more than
         * wrappers for other throwables (for example, <b style="color:orange;">
         * java.security.PrivilegedActionException</b>).
         *
         * @param  cause the cause (which is saved for later retrieval by the
         *         <b style="color:orange;">Throwable#cause()</b> method).  (A <b>null</b> value is
         *         permitted, and indicates that the cause is nonexistent or
         *         unknown.)
         *
         */
        CORE_EXPLICIT IllegalStateException(Throwable const &cause);

    protected:
        void selfThrow() const override;
    };

} // core

#endif //CORE24_ILLEGALSTATEEXCEPTION_H
