//
// Created by bruns on 01/05/2024.
//

#include <iostream>
#include <core/CharArray.h>
#include <core/Class.h>
#include <core/LongArray.h>
#include <core/String.h>
#include <core/misc/Literals.h>

namespace core
{
}

using namespace core;
using namespace core::misc;

class A;

int main()
{
    CharArray chars  = CharArray(30);
    auto      a      = chars.length();
    auto      b      = chars.set(3, a);
    auto      c      = chars.get(3);
    auto      array1 = CharArray::of();
    auto      array2 = CharArray::of(1, 2, 3);
    auto      array3 = CharArray::of('a', u'b', 1);

    wchar_t cs[100] = {1, 2, 3, 4, 5, 6};

    auto array4 = LongArray::copyOf(cs);

    auto array5 = CharArray::copyOf("helloworld!");

    auto &&nil = null;
    auto &&nptr = nullptr;

    auto   value = ByteArray::copyOf(u8"helloworld");
    String str   = String(value, 0);

    auto str2 = u"hello"_S;
    auto str3 = L"hello"_S;
    auto str4 = U"hello"_S;
    auto str5 = "hello"_S;

    std::cout << &value.get(0) << std::endl;

    return 0;
}
