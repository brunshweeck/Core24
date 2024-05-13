//
// Created by bruns on 13/05/2024.
//

#ifndef Core24_SHORT_H
#define Core24_SHORT_H

#include <core/Comparable.h>
#include <core/Number.h>

namespace core
{
    class Short : public virtual Number, public virtual Comparable<Short>
    {
    };
} // core

#endif // Core24_SHORT_H
