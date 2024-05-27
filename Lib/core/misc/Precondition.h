//
// Created by bruns on 12/05/2024.
//

#ifndef CORE24_PRECONDION_H
#define CORE24_PRECONDION_H
#include <core/Object.h>

namespace core
{
    namespace misc
    {
        /**
         * The class @c Precondition contains utility methods
         * to check if state or arguments are correct.
         */
        class Precondition CORE_FINAL : public virtual Object
        {
        public:
            static void checkIndex(gint index, gint length);

            static void checkIndexFromRange(gint start, gint end, gint length);

            static void checkIndexFromSize(gint start, gint size, gint length);

            static void checkIndexForAdding(gint index, gint length);
        };
    } // misc
} // core

#endif // CORE24_PRECONDION_H
