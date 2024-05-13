//
// Created by bruns on 13/05/2024.
//

#ifndef Core24_LONG_H
#define Core24_LONG_H

#include <core/Comparable.h>
#include <core/Number.h>

namespace core
{
    class Long : public virtual Number, public virtual Comparable<Long>
    {
    };
} // core

#endif // Core24_LONG_H
