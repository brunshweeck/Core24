//
// Created by bruns on 05/05/2024.
//

#include <core/misc/Literals.h>
#include <core/String.h>
#include <core/Integer.h>
#include <core/Long.h>
#include <core/Complex.h>
#include <core/Throwable.h>
#include <core/misc/Foreign.h>

namespace core
{
    namespace misc
    {
    } // misc

    String operator ""_S(misc::__literal_chr_t const *str, misc::__memory_size_t size)
    {
        gint length = (gint) (size & 0x7fffffff);
        if (length == 0) {
            return String();
        }
        gbool isAscii = true;
        gint i = 0;
        for (; i < length; ++i) {
            if (str[i] < 0) {
                isAscii = false;
                break;
            }
        }
        if (isAscii) {
            ByteArray array = ByteArray(length);
            for (i = 0; i < length; ++i) {
                array.set(i, str[i]);
            }
            return String(array, 0);
        }
        else {
            // utf-8 or latin-1
            // try for latin1
            gint n = 0;
            gint j = 0;
            for (; j < length; ++j) {
                if (str[j] > 0) n += 1;
                else if (str[j] >> 5 == -2) {
                    if (str[j] & 0x1e == 0
                        || j + 1 >= length
                        || str[j + 1] & 0xc0 != 0x80)
                        break;
                    n += 1;
                    j += 1;
                }
                else if (str[j] >> 4 == -2) {
                    if (j + 2 >= length
                        || str[j] == 0xe0 && str[j + 1] & 0xe0 == 0x80
                        || str[j + 1] & 0xc0 != 0x80
                        || str[j + 2] & 0xc0 != 0x80)
                        break;
                    n += 1;
                    j += 2;
                }
                else if (str[j] >> 3 == -2) {
                    if (j + 3 >= length
                        || str[j + 1] & 0xc0 != 0x80
                        || str[j + 2] & 0xc0 != 0x80
                        || str[j + 3] & 0xc0 != 0x80)
                        break;
                    n += 2;
                    j += 3;
                }
                else {
                    break;
                }
            }
            if (j < length) {
                // latin-1
                ByteArray array = ByteArray(length);
                for (i = 0; i < length; ++i) {
                    array.set(i, (gchar) (str[i] & 0xff));
                }
                return String(array, 0);
            }
            {
                // utf-8
                n += i;
                CharArray array = CharArray(j == length ? n : length);
                gint k = 0;
                for (j = 0; j < length; ++j) {
                    if (str[j] < 0) break;
                    array.set(k++, str[j]);
                }
                for (; j < length; ++j) {
                    if (str[j] > 0) {
                        array.set(k++, str[j]);
                    }
                    else if (str[j] >> 5 == -2) {
                        if (str[j] & 0x1e == 0
                            || j + 1 >= length
                            || str[j + 1] & 0xc0 != 0x80) {
                            array.set(k++, '?');
                        }
                        else {
                            array.set(k++,
                                      ((str[j] << 6) ^ str[j + 1]) ^ (0xc0 << 6) ^ (0x80 << 0)
                            );
                        }
                        j += 1;
                    }
                    else if (str[j] >> 4 == -2) {
                        if (j + 2 >= length
                            || str[j] == 0xe0 && str[j + 1] & 0xe0 == 0x80
                            || str[j + 1] & 0xc0 != 0x80
                            || str[j + 2] & 0xc0 != 0x80) {
                            array.set(k++, '?');
                        }
                        else {
                            gchar ch = (str[j] << 12) ^ (str[j + 1] << 6) ^
                                       (str[j + 2] ^ (0xe0 << 12) ^ (0x80 << 6) ^ (0x80 << 0));
                            array.set(k++, 0xd800 <= ch && ch <= 0xdfff ? '?' : ch);
                        }
                        j += 2;
                    }
                    else if (str[j] >> 3 == -2) {
                        if (j + 3 >= length
                            || str[j + 1] & 0xc0 != 0x80
                            || str[j + 2] & 0xc0 != 0x80
                            || str[j + 3] & 0xc0 != 0x80) {
                            array.set(k++, '?');
                        }
                        else {
                            gint ch = ((str[j] << 18) ^ (str[j + 1] << 12) ^ (str[j + 2] << 6) ^ str[j + 3]) ^
                                      ((0xf0 << 18) ^ (0x80 << 12) ^ (0x80 << 6) ^ (0x80 << 0));
                            if (ch <= 0xffff)
                                array.set(k++, '?');
                            else {
                                array.set(k++, (ch >> 10) + 0xd800 - (0x10000 >> 10));
                                array.set(k++, (ch & 0x3ff) + 0xdc00);
                            }
                        }
                        j += 3;
                    }
                    else {
                        array.set(k++, '?');
                    }
                }
                return String(array, 0, k);
            }
        }
    }

    String operator ""_S(misc::__ucs2_t const *str, misc::__memory_size_t size)
    {
        gint length = (gint) (size & 0x7fffffff);
        gint hibyte = 0;
        gint i = 0;
        for (; i < length; ++i) {
            if (str[i] > 0x7f) {
                if (i > 0 && str[i] >> 8 != hibyte)
                    break;
                hibyte = str[i] >> 8;
            }
        }

        if (i == length) {
            ByteArray array = ByteArray(length);
            for (i = 0; i < length; ++i)
                array.set(i, (gbyte) (str[i] & 0xff));
            return String(array, hibyte);
        }
        else {
            CharArray array = CharArray(length);
            for (i = 0; i < length; ++i)
                array.set(i, str[i]);
            return String(array);
        }
    }

    String operator ""_S(misc::__ucs4_t const *str, misc::__memory_size_t size)
    {
        gint length = (gint) size;
        gint hibyte = 0;
        gint i = 0;
        for (; i < length; ++i) {
            if (str[i] > 0x7f) {
                if (i > 0 && str[i] >> 8 != hibyte)
                    break;
                hibyte = str[i] >> 8;
                if (hibyte > 0xff)
                    break;
            }
        }
        if (i == length) {
            ByteArray array = ByteArray(length);
            for (i = 0; i < length; ++i)
                array.set(i, (gbyte) (str[i] & 0xff));
            return String(array, hibyte);
        }
        else {
            IntArray array = IntArray(length);
            for (i = 0; i < length; ++i)
                array.set(i, str[i] > 0x10ffff ? 63 : (gint) str[i]);
            return String(array, 0, length);
        }
    }

    String operator ""_S(wchar_t const *str, misc::__memory_size_t size)
    {
        return ClassOf(*str)::MEMORY_SIZE == 2
               ? operator ""_S(CORE_CAST(misc::__ucs2_t const *, str), size)
               : operator ""_S(CORE_CAST(misc::__ucs4_t const *, str), size);
    }

    String operator+(String const &lhs, String const &rhs)
    {
        try {
            return lhs.concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, Object const &rhs)
    {
        try {
            return lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(Object const &lhs, String const &rhs)
    {
        try {
            return String::valueOf(lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, gint rhs)
    {
        try {
            return lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, gfloat rhs)
    {
        try {
            return lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, gdouble rhs)
    {
        try {
            return lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, void *rhs)
    {
        try {
            return lhs.concat(("0x"_S + Long::toHexString((glong) rhs)));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, unsigned int rhs)
    {
        try {
            return lhs.concat(Integer::toUnsignedString((gint) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, long rhs)
    {
        try {
            return lhs.concat((ClassOf(rhs)::MEMORY_SIZE == 8
                               ? String::valueOf((glong) rhs)
                               : String::valueOf((gint) rhs)));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, unsigned long rhs)
    {
        try {
            return lhs.concat((ClassOf(rhs)::MEMORY_SIZE == 8
                               ? Long::toUnsignedString((glong) rhs)
                               : Integer::toUnsignedString((gint) rhs)));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, long long rhs)
    {
        try {
            return lhs.concat(String::valueOf((glong) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(String const &lhs, unsigned long long rhs)
    {
        try {
            return lhs.concat(Long::toUnsignedString((glong) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(gint lhs, String const &rhs)
    {
        try {
            return String::valueOf(lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(unsigned int lhs, String const &rhs)
    {
        try {
            return Integer::toUnsignedString((gint) lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(long lhs, String const &rhs)
    {
        try {
            return (ClassOf(lhs)::MEMORY_SIZE == 8
                    ? String::valueOf((glong) lhs)
                    : String::valueOf((gint) lhs)).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(unsigned long lhs, String const &rhs)
    {
        try {
            return (ClassOf(lhs)::MEMORY_SIZE == 8
                    ? Long::toUnsignedString((glong) lhs)
                    : Integer::toUnsignedString((gint) lhs)).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(long long lhs, String const &rhs)
    {
        try {
            return String::valueOf((glong) lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(unsigned long long lhs, String const &rhs)
    {
        try {
            return Long::toUnsignedString((glong) lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(gfloat lhs, String const &rhs)
    {
        try {
            return String::valueOf(lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(gdouble lhs, String const &rhs)
    {
        try {
            return String::valueOf(lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String core::operator+(void *lhs, String const &rhs)
    {
        try {
            return String::valueOf(lhs).concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &operator+=(String &lhs, String const &rhs)
    {
        try {
            return lhs = lhs.concat(rhs);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, gint rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, long rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf((glong) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, long long int rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf((glong) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, misc::__uint32_t rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf((glong) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, unsigned long rhs)
    {
        try {
            return lhs = lhs.concat(Long::toUnsignedString(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, unsigned long long int rhs)
    {
        try {
            return lhs = lhs.concat(Long::toUnsignedString(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, gfloat rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, gdouble rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf(rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String &core::operator+=(String &lhs, long double rhs)
    {
        try {
            return lhs = lhs.concat(String::valueOf((gdouble) rhs));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    Complex operator ""i(misc::__uint64_t im)
    {
        return Complex(0.0, (gdouble) im);
    }

    Complex operator ""_i(misc::__uint64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""I(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""_I(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""j(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""_j(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""J(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator ""_J(misc::__literal_int64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""i(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""_i(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""I(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""_I(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""j(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""_j(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""J(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex core::operator ""_J(misc::__literal_float64_t im)
    {
        return Complex(0, (gdouble) im);
    }

    Complex operator~(Complex const &z)
    {
        return z.conjugate();
    }

    Complex operator-(Complex const &z)
    {
        return z.negate();
    }

    Complex core::operator+(Complex const &z)
    {
        return z;
    }

    Complex core::operator+(Complex const &lhs, Complex const &rhs)
    {
        return Complex::sum(lhs, rhs);
    }

    Complex core::operator-(Complex const &lhs, Complex const &rhs)
    {
        return Complex::sum(lhs, -rhs);
    }

    Complex operator*(Complex const &lhs, Complex const &rhs)
    {
        return Complex::multiply(lhs, rhs);
    }

    Complex operator/(Complex const &lhs, Complex const &rhs)
    {
        return Complex::divide(lhs, rhs);
    }

    Complex &core::operator+=(Complex &lhs, Complex const &rhs)
    {
        return lhs = Complex::sum(lhs, rhs);
    }

    Complex &operator-=(Complex &lhs, Complex const &rhs)
    {
        return lhs = Complex::sum(lhs, -rhs);
    }

    Complex &operator*=(Complex &lhs, Complex const &rhs)
    {
        return lhs = Complex::multiply(lhs, rhs);
    }

    Complex &operator/=(Complex &lhs, Complex const &rhs)
    {
        return lhs = Complex::divide(lhs, rhs);
    }

    gbool operator==(Complex const &lhs, Complex const &rhs)
    {
        return lhs.equals(rhs);
    }

    gbool operator!=(Complex const &lhs, Complex const &rhs)
    {
        return lhs.equals(rhs);
    }
} // core

/*

#include <Windows.h>

using core::null;

static HANDLE handle = HeapCreate(HEAP_CREATE_ENABLE_TRACING | HEAP_CREATE_ENABLE_EXECUTE, 1024, 0);
static CORE_FAST gint initialized = 1234567890;

void *operator new(core::misc::__memory_size_t memorySize)
{
    if (initialized == 1234567890) {
        if (handle == null) {
            handle = GetProcessHeap();
        }
    }

    if(memorySize == (core::misc::__memory_size_t)-1) {
        memorySize -= 1;
    }

    if(memorySize == 0) {
        return null;
    }

    gbool b = HeapLock(handle);
    void *ptr = HeapAlloc(handle, HEAP_ZERO_MEMORY, memorySize + 1);

    if(ptr == null) {
        DWORD error = GetLastError();
        return null;
    }

    if(b) {
        HeapUnlock(handle);
    }
    return ptr;
}

void *operator new[](core::misc::__memory_size_t memorySize)
{
    return operator new(memorySize);
}

void operator delete(void *targetAddress)
{
    if (initialized == 1234567890) {
        gbool b = HeapLock(handle);
        HeapFree(handle, HEAP_FREE_CHECKING_ENABLED, targetAddress);
        if(b) {
            HeapUnlock(handle);
        }
    }
}

void operator delete[](void *targetAddress)
{
    return operator delete(targetAddress);
}
*/
