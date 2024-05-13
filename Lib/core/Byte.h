//
// Created by bruns on 13/05/2024.
//

#ifndef Core24_BYTE_H
#define Core24_BYTE_H

#include <core/Comparable.h>
#include <core/Number.h>

namespace core
{
    class Byte : public virtual Number, public virtual Comparable<Byte>
    {
    };
} // core

#endif // Core24_BYTE_H
