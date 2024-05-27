//
// Created by brunshweeck on 25 mai 2024.
//

#ifndef CORE24_ARITHMETICEXCEPTION_H
#define CORE24_ARITHMETICEXCEPTION_H

#include "RuntimeException.h"

namespace core
{

    /**
     * Thrown when an exceptional arithmetic condition has occurred. For
     * example, an integer "divide by zero" throws an instance of this class.
     */
    class ArithmeticException: public virtual RuntimeException
    {
    public:

        /**
         * Constructs an <b>ArithmeticException</b> with no detail
         * message.
         */
        CORE_IMPLICIT ArithmeticException();

        /**
         * Constructs an <b>ArithmeticException</b> with the specified
         * detail message.
         *
         * @param   s   the detail message.
         */
        CORE_EXPLICIT ArithmeticException(String message);

    protected:
        void selfThrow() const override;
    };

} // core

#endif //CORE24_ARITHMETICEXCEPTION_H
