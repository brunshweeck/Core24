//
// Created by bruns on 01/05/2024.
//

#include <core/Class.h>

namespace core {}

using namespace core;

class A;

int main()
{
    CORE_FAST gint argc = 128;
    CORE_FAST Class<gint>::CRef a = argc;
    CORE_FAST gbool b = ClassOf(2)::oneIsTrue<true, false>();
    return 0;
}
