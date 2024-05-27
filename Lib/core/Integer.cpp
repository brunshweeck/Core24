//
// Created by bruns on 13/05/2024.
//

#include <core/Integer.h>
#include <core/String.h>
#include <core/NumberFormatException.h>
#include <core/IllegalArgumentException.h>
#include <core/Long.h>
#include <core/Math.h>
#include <core/misc/Foreign.h>

namespace core
{

    static const CharArray digits = CharArray::of(
            '0', '1', '2', '3', '4', '5', '6', '7', '8',
            '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
            'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
            'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    );

    String Integer::toString(gint i, gint radix)
    {
        if (radix < 2 || radix > 36)
            radix = 10;
        if (radix == 10) {
            return toString(i);
        }

        gbool negative = i < 0;
        if (!negative) {
            i = -i;
        }

        CharArray ca = CharArray(33);
        gint next = 32;

        while (i <= -radix) {
            ca[next--] = digits[-(i % radix)];
            i /= radix;
        }

        ca[next] = digits[-i];

        if (negative) {
            ca[--next] = '-';
        }

        return String(ca, next, 33 - next);
    }

    String Integer::toUnsignedString(gint i, gint radix)
    {
        return Long::toString(toUnsignedLong(i), radix);
    }

    String Integer::toHexString(gint i)
    {
        return toUnsignedString(i, 16);
    }

    String Integer::toOctalString(gint i)
    {
        return toUnsignedString(i, 8);
    }

    String Integer::toBinaryString(gint i)
    {
        return toUnsignedString(i, 2);
    }

    String Integer::toString(gint i)
    {
        return toString(i, 10);
    }

    String Integer::toUnsignedString(gint i)
    {
        return toUnsignedString(i, 10);
    }

    gint Integer::parseInt(const String &s, gint radix)
    {
        if(radix < 2){
            NumberFormatException("Radix less than 2"_S).throws($ftrace(""_S));
        }
        if(radix > 36){
            NumberFormatException("Radix less than 36"_S).throws($ftrace(""_S));
        }

        gbool negative = false;
        gint i = 0, len = s.length();
        gint limit = -Integer::MAX_VALUE;

        if (len > 0) {
            gchar firstChar = s.charAt(0);
            if (firstChar < '0') { // Possible leading "+" or "-"
                if (firstChar == '-') {
                    negative = true;
                    limit = Integer::MIN_VALUE;
                } else if (firstChar != '+') {
                    NumberFormatException().throws($ftrace(""_S));
                }

                if (len == 1) { // Cannot have lone "+" or "-"
                    NumberFormatException().throws($ftrace(""_S));
                }
                i++;
            }
            gint multmin = limit / radix;
            gint result = 0;
            while (i < len) {
                // Accumulating negatively avoids surprises near MAX_VALUE
                gchar c = s.charAt(i++);
                gint digit = Character::digit(s.charAt(i++), radix);
                if (digit < 0 || result < multmin) {
                    NumberFormatException::forInputString(s, radix).throws(__strace());
                }
                result *= radix;
                if (result < limit + digit) {
                    NumberFormatException::forInputString(s, radix).throws(__strace());
                }
                result -= digit;
            }
            return negative ? result : -result;
        } else {
            NumberFormatException::forInputString(s, radix).throws(__strace());
        }
    }

    gint Integer::parseInt(const CharSequence &s, gint beginIndex, gint endIndex, gint radix)
    {
        return 0;
    }

    gint Integer::parseInt(const String &s)
    {
        return 0;
    }

    gint Integer::parseUnsignedInt(const String &s, gint radix)
    {
        return 0;
    }

    gint Integer::parseUnsignedInt(const CharSequence &s, gint beginIndex, gint endIndex, gint radix)
    {
        return 0;
    }

    gint Integer::parseUnsignedInt(const String &s)
    {
        return 0;
    }

    Integer Integer::valueOf(const String &s, gint radix)
    {
        return Integer(0);
    }

    Integer Integer::valueOf(const String &s)
    {
        return Integer(0);
    }

    Integer Integer::valueOf(gint i)
    {
        return Integer(0);
    }

    Integer::Integer(gint value)
    {
    }

    gbyte Integer::byteValue() const
    {
        return (gbyte) value;
    }

    gshort Integer::shortValue() const
    {
        return (gshort) value;
    }

    gint Integer::intValue() const
    {
        return value;
    }

    glong Integer::longValue() const
    {
        return value;
    }

    gfloat Integer::floatValue() const
    {
        return (gfloat) value;
    }

    gdouble Integer::doubleValue() const
    {
        return (gdouble) value;
    }

    String Integer::toString() const
    {
        return toString(value);
    }

    gint Integer::hash() const
    {
        return hash(value);
    }

    gint Integer::hash(gint value)
    {
        return value;
    }

    gbool Integer::equals(const Object &obj) const
    {
        if (this == &obj)
            return true;
        if (!Class< Integer >::hasInstance(obj))
            return false;
        Integer const &v = CORE_XCAST(Integer const, obj);
        return value == v.value;
    }

    Integer Integer::decode(const String &nm)
    {
        return Integer(0);
    }

    gint Integer::compareTo(Integer const &anotherInteger) const
    {
        return compare(value, anotherInteger.value);
    }

    gint Integer::compare(gint x, gint y)
    {
        return x - y;
    }

    gint Integer::compareUnsigned(gint x, gint y)
    {
        return compare(x + MIN_VALUE, y + MIN_VALUE);
    }

    glong Integer::toUnsignedLong(gint x)
    {
        return ((glong) x) & 0xffffffffLL;
    }

    gint Integer::divideUnsigned(gint dividend, gint divisor)
    {
        // In lieu of tricky code, for now just use long arithmetic.
        return (gint) (toUnsignedLong(dividend) / toUnsignedLong(divisor));
    }

    gint Integer::remainderUnsigned(gint dividend, gint divisor)
    {
        // In lieu of tricky code, for now just use long arithmetic.
        return (gint) (toUnsignedLong(dividend) % toUnsignedLong(divisor));
    }

    gint Integer::highestOneBit(gint i)
    {
        return i & (MIN_VALUE >> numberOfLeadingZeros(i));
    }

    gint Integer::lowestOneBit(gint i)
    {
        // HD, Section 2-1
        return i & -i;
    }

    gint Integer::numberOfLeadingZeros(gint i)
    {
        // HD, Count leading 0's
        if (i <= 0)
            return i == 0 ? 32 : 0;
        gint n = 31;
        if (i >= 1 << 16) {
            n -= 16;
            i >>= 16;
        }
        if (i >= 1 << 8) {
            n -= 8;
            i >>= 8;
        }
        if (i >= 1 << 4) {
            n -= 4;
            i >>= 4;
        }
        if (i >= 1 << 2) {
            n -= 2;
            i >>= 2;
        }
        return n - (i >> 1);
    }

    gint Integer::numberOfTrailingZeros(gint i)
    {
        // HD, Count trailing 0's
        i = ~i & (i - 1);
        if (i <= 0) return i & 32;
        gint n = 1;
        if (i > 1 << 16) {
            n += 16;
            i >>= 16;
        }
        if (i > 1 << 8) {
            n += 8;
            i >>= 8;
        }
        if (i > 1 << 4) {
            n += 4;
            i >>= 4;
        }
        if (i > 1 << 2) {
            n += 2;
            i >>= 2;
        }
        return n + (i >> 1);
    }

    gint Integer::bitCount(gint i)
    {
        // HD, Figure 5-2
        i = i - (gint) (((i + 0u) >> 1) & 0x55555555);
        i = (i & 0x33333333) + (gint) (((i + 0u) >> 2) & 0x33333333);
        i = (i + (gint) ((i + 0u) >> 4)) & 0x0f0f0f0f;
        i = i + (gint) ((i + 0u) >> 8);
        i = i + (gint) ((i + 0u) >> 16);
        return i & 0x3f;
    }

    gint Integer::rotateLeft(gint i, gint distance)
    {
        return (i << distance) | (gint) ((i + 0u) >> -distance);
    }

    gint Integer::rotateRight(gint i, gint distance)
    {
        return (gint) ((i + 0u) >> distance) | (i << -distance);
    }

    gint Integer::reverse(gint i)
    {
        // HD, Figure 7-1
        i = (i & 0x55555555) << 1 | (gint) ((i + 0u) >> 1) & 0x55555555;
        i = (i & 0x33333333) << 2 | (gint) ((i + 0u) >> 2) & 0x33333333;
        i = (i & 0x0f0f0f0f) << 4 | (gint) ((i + 0u) >> 4) & 0x0f0f0f0f;

        return reverseBytes(i);
    }

    gint Integer::signum(gint i)
    {
        // HD, Section 2-7
        return (i >> 31) | (gint) ((-i + 0u) >> 31);
    }

    gint Integer::reverseBytes(gint i)
    {
        return (i << 24) |
               ((i & 0xff00) << 8) |
               (((i + 0u) >> 8) & 0xff00) |
               ((i + 0u) >> 24);
    }

    gint Integer::sum(gint a, gint b)
    {
        return a + b;
    }

    gint Integer::max(gint a, gint b)
    {
        return Math::max(a, b);
    }

    gint Integer::min(gint a, gint b)
    {
        return Math::min(a, b);
    }

    Integer::operator gint() const
    {
        return intValue();
    }

    Integer::operator gint &()
    {
        return value;
    }

} // core