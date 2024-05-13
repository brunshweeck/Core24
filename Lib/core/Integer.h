//
// Created by bruns on 13/05/2024.
//

#ifndef Core24_INTEGER_H
#define Core24_INTEGER_H

#include <core/Number.h>
#include <core/Comparable.h>

namespace core
{
    class Integer : public virtual Number, public virtual Comparable<Integer>
    {
    };
} // core

#endif // Core24_INTEGER_H
