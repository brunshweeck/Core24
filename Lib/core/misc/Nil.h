//
// Created by bruns on 09/05/2024.
//

#ifndef Core24_NIL_H
#define Core24_NIL_H

#include <core/Object.h>

namespace core
{
    namespace misc
    {
        /**
         * The class @c NIL define the null pointer address.
         */
        class NIL CORE_FINAL : public virtual Object
        {
        private:
            /**
             * Construct new NIL instance
             */
            CORE_IMPLICIT NIL();

            /**
             * NIL value is not copyable
             */
            NIL(NIL const&);

        public:
            /**
             * Return null pointer to void
             */
            CORE_IMPLICIT operator void*() const;

            /**
             * Return null pointer
             * @tparam T The type of pointer target type
             */
            template <class T>
            CORE_IMPLICIT operator T*() const { return (T*) CORE_CAST(void *, INSTANCE); }

            /**
             * The single instance of this class
             */
            static NIL INSTANCE;
        };
    } // misc
} // core


#endif // Core24_NIL_H
