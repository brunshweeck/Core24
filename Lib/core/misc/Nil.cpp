//
// Created by bruns on 09/05/2024.
//

#include "Nil.h"

namespace core
{
    namespace misc
    {
        NIL::NIL()
        {
        }

        NIL::NIL(NIL const&)
        {
        }

        NIL::operator void*() const
        {
            return CORE_CAST(void *, 0);
        }

        NIL NIL::INSTANCE;
    } // misc
} // core
