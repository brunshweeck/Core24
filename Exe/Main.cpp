//
// Created by bruns on 01/05/2024.
//


#include <core/CharArray.h>
#include <core/Class.h>
#include <core/LongArray.h>
#include <core/String.h>

using namespace core;

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

    auto   value = ByteArray::copyOf(u8"helloworld");
    String str   = String(value, 0);

    auto str2 = u"hello"_S;
    auto str3 = L"hello"_S;
    auto str4 = U"hello"_S;
    auto str5 = "hello"_S;

    CORE_FAST auto aaa = '@';
    CORE_FAST gint bbb = aaa;

    auto ia1 = IntArray::ofRange(100);
    auto ia2 = IntArray::ofRange(1, 100);
    auto ia3 = IntArray::ofRange(0, 100, 10);

    String str6 = ""_S + "";

    return 0;
}
