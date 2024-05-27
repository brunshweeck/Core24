//
// Created by bruns on 14/05/2024.
//

#ifndef CORE24_THROWABLE_H
#define CORE24_THROWABLE_H

#include <exception>
#include <core/String.h>

#include "Trace.h"

namespace core
{
    class Throwable : public virtual Object, public virtual std::exception
    {
        CORE_ALIAS(Cause, Class<Throwable>::Pointer);
        CORE_ALIAS(ByteStream, Class<Class<char>::Const>::Pointer);

    private:
        /**
         * Specific details about the Throwable.  For example, for
         * @c FileNotFoundException, this contains the name of
         * the file that could not be found.
         */
        String detailMessage;

        /**
         * The throwable that caused this throwable to get thrown, or @a itfself if this
         * throwable was not caused by another throwable, or if the causative
         * throwable is unknown.
         *
         */
        Cause origin;

    public:
        /**
         * Constructs a new throwable with @c "" as its detail message.
         * The cause is not initialized.
         */
        Throwable() CORE_NOTHROW;

        /**
         * Constructs a new throwable with the specified detail message.  The
         * cause is not initialized.
         *
         * @param message the detail message. The detail message is saved for
         *          later retrieval by the @c Throwable::message() method.
         */
        CORE_EXPLICIT Throwable(String message) CORE_NOTHROW;

        /**
         * Constructs a new throwable with the specified detail message and
         * cause.
         *
         * @note that the detail message associated with @c cause is @a not automatically
         *       incorporated in this throwable's detail message.
         *
         * @param  message the detail message (which is saved for later retrieval
         *         by the @c Throwable::message() method).
         * @param  cause the cause (which is saved for later retrieval by the
         *         @c Throwable::cause() method).
         *
         */
        CORE_EXPLICIT Throwable(String message, Throwable const& cause) CORE_NOTHROW;

        /**
         * Construct new throwable object instance with another.
         *
         * @param other the throwable object
         */
        CORE_IMPLICIT Throwable(Throwable const& other);

        /**
         * Construct new throwable object instance with another.
         *
         * @param other the throwable object
         */
        CORE_IMPLICIT Throwable(Throwable&& other) CORE_NOTHROW;

        /**
         * Returns the detail message string of this throwable.
         *
         * @return  the detail message string of this @c Throwable instance.
         */
        virtual String message() const;

        /**
         * Creates a localized description of this throwable. Subclasses may
         * override this method in order to produce a locale-specific message.
         * For subclasses that do not override this method, the default
         * implementation returns the same result as @c message().
         *
         * @return  The localized description of this throwable.
         *
         */
        virtual String localizedMessage() const;

        /**
         * Returns the cause of this throwable or @a itself if the
         * cause is nonexistent or unknown.  (The cause is the throwable that
         * caused this throwable to get thrown.)
         *
         * This implementation returns the cause that was supplied via one of
         * the constructors requiring a @c Throwable, or that was set after
         * creation.  While it is typically unnecessary to override this method, a subclass can override
         * it to return a cause set by some other means.  This is appropriate for
         * a "legacy chained throwable" that predates the addition of chained
         * exceptions to @c Throwable.  Note that it is @a not
         * necessary to override any of the @c PrintStackTrace methods,
         * all of which invoke the @c cause method to determine the
         * cause of a throwable.
         *
         * @return  the cause of this throwable or @a itself if the
         *          cause is nonexistent or unknown.
         */
        virtual Throwable& cause() const;

        /**
         * Returns a short description of this throwable.
         * The result is the concatenation of:
         * @li the @a name of the class of this object
         * @li @c ": " (a colon and a space)
         * @li the result of invoking this object's @c localizedMessage() method
         *
         * If @c localizedMessage returns @c "", then just the class name
         * is returned.
         *
         * @return a string representation of this throwable.
         */
        String toString() const override;

        /**
         * Thrown or rethrow this throwable at the specified execution point.
         *
         * @param currentExecutionPoint the current execution point
         */
        CORE_NORETURN void throws(Trace currentExecutionPoint) const;

        /**
         * Thrown this throwable again with ignoring the current execution point.
         *
         * @note this method should be called after call of @c throws method, otherwise it thrown
         *       @c IllegalStateException
         *
         * @throws IllegalStateException if this method is not called after one first call of @c throws method
         */
        CORE_NORETURN void rethrow() const;

    protected:
        /**
         * Thrown the perfect and temporary copy of itself.
         *
         * Example: @code
         *  class MyClass: public virtual Exception
         *  {
         *  protected:
         *      void selfThrow() && override
         *      {
         *          throw MyClass(*this); // ok
         *          // or throw *this; // (deprecated)
         *      }
         *  };
         * @endcode
         *
         * @note All subclass must be override this method to
         *       preserve perfect chaining and this method use
         *       the c++ native @c throw for compatibility with
         *       standard exception.
         */
        CORE_NORETURN virtual void selfThrow() const = 0;

    private:
        /**
         * Print the stacktrace of this throwable on C-String stream.
         *
         * @note this method is only called by standard exception class
         *       during throwing operation.
         *
         * @return stack trace printed into the C-String stream.
         */
        ByteStream what() const CORE_NOTHROW CORE_FINAL;
    };
} // core

#endif // CORE24_THROWABLE_H
