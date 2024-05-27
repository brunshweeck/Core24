//
// Created by bruns on 13/05/2024.
//

#include <core/String.h>
#include <core/Long.h>
#include <core/Integer.h>


namespace core
{
    String Long::toString(glong i, gint radix)
    {
        return String();
    }

    String core::Long::toUnsignedString(glong i, gint radix)
    {
        return String();
    }

    String Long::toHexString(glong i)
    {
        return String();
    }

    String Long::toOctalString(glong i)
    {
        return String();
    }

    String Long::toBinaryString(glong i)
    {
        return String();
    }

    String Long::toString(glong i)
    {
        return String();
    }

    String Long::toUnsignedString(glong i)
    {
        return String();
    }

    glong Long::parseLong(const String &s, gint radix)
    {
        return 0;
    }

    glong Long::parseLong(const CharSequence &s, gint beginIndex, gint endIndex, gint radix)
    {
        return 0;
    }

    glong Long::parseLong(const String &s)
    {
        return 0;
    }

    glong Long::parseUnsignedLong(const String &s, gint radix)
    {
        return 0;
    }

    glong Long::parseUnsignedLong(const CharSequence &s, gint beginIndex, gint endIndex, gint radix)
    {
        return 0;
    }

    glong Long::parseUnsignedLong(const String &s)
    {
        return 0;
    }

    Long Long::valueOf(const String &s, gint radix)
    {
        return Long(0);
    }

    Long Long::valueOf(const String &s)
    {
        return Long(0);
    }

    Long Long::valueOf(glong l)
    {
        return Long(0);
    }

    Long Long::decode(const String &nm)
    {
        return Long(0);
    }

    Long::Long(glong value) : value(value)
    {
    }

    gbyte Long::byteValue() const
    {
        return (gbyte) value;
    }

    gshort Long::shortValue() const
    {
        return (gshort) value;
    }

    gint Long::intValue() const
    {
        return (gint) value;
    }

    glong Long::longValue() const
    {
        return value;
    }

    gfloat Long::floatValue() const
    {
        return (gfloat) value;
    }

    gdouble Long::doubleValue() const
    {
        return (gdouble) value;
    }

    String Long::toString() const
    {
        return toString(value);
    }

    gint Long::hash() const
    {
        return hash(value);
    }

    gint Long::hash(glong value)
    {
        return (gint) ((value) ^ ((value + 0ULL) >> 32));
    }

    gbool Long::equals(const Object &obj) const
    {
        if (this == &obj)
            return true;
        if (!Class<Long>::hasInstance(obj))
            return false;
        Long const lg = CORE_XCAST(Long const, obj);
        return value == lg.value;
    }

    gint Long::compareTo(const Long &anotherLong) const
    {
        return compare(value, anotherLong.value);
    }

    gint Long::compare(glong x, glong y)
    {
        return x > y ? 1 : x < y ? -1 : 0;
    }

    gint Long::compareUnsigned(glong x, glong y)
    {
        return compare(x + MIN_VALUE, y + MIN_VALUE);
    }

    glong Long::divideUnsigned(glong dividend, glong divisor)
    {
        /* See Hacker's Delight (2nd ed), section 9.3 */
        if (divisor >= 0) {
            glong q = (glong) ((dividend + 0uLL) >> 1) / divisor << 1;
            glong r = dividend - q * divisor;
            return (glong) (q + (((r | ~(r - divisor)) + 0uLL) >> (Long::SIZE - 1)));
        }
        return (glong) (((dividend & ~(dividend - divisor)) + 0uLL) >> (Long::SIZE - 1));
    }

    glong Long::remainderUnsigned(glong dividend, glong divisor)
    {
        /* See Hacker's Delight (2nd ed), section 9.3 */
        if (divisor >= 0) {
            glong q = (glong) ((dividend + 0uLL) >> 1) / divisor << 1;
            glong r = dividend - q * divisor;
            /*
             * Here, 0 <= r < 2 * divisor
             * (1) When 0 <= r < divisor, the remainder is simply r.
             * (2) Otherwise the remainder is r - divisor.
             *
             * In case (1), r - divisor < 0. Applying ~ produces a long with
             * sign bit 0, so >> produces 0. The returned value is thus r.
             *
             * In case (2), a similar reasoning shows that >> produces -1,
             * so the returned value is r - divisor.
             */
            return r - ((~(r - divisor) >> (Long::SIZE - 1)) & divisor);
        }
        /*
         * (1) When dividend >= 0, the remainder is dividend.
         * (2) Otherwise
         *      (2.1) When dividend < divisor, the remainder is dividend.
         *      (2.2) Otherwise the remainder is dividend - divisor
         *
         * A reasoning similar to the above shows that the returned value
         * is as expected.
         */
        return dividend - (((dividend & ~(dividend - divisor)) >> (Long::SIZE - 1)) & divisor);
    }

    glong Long::highestOneBit(glong i)
    {
        return i & (MIN_VALUE >> numberOfLeadingZeros(i));
    }

    glong Long::lowestOneBit(glong i)
    {
        // HD, Section 2-1
        return i & -i;
    }

    gint Long::numberOfLeadingZeros(glong i)
    {
        int x = (int) ((i + 0uLL) >> 32);
        return x == 0 ? 32 + Integer::numberOfLeadingZeros((int) i)
                      : Integer::numberOfLeadingZeros(x);
    }

    gint Long::numberOfTrailingZeros(glong i)
    {
        int x = (int) i;
        return x == 0 ? 32 + Integer::numberOfTrailingZeros((int) ((i + 0uLL) >> 32))
                      : Integer::numberOfTrailingZeros(x);
    }

    gint Long::bitCount(glong i)
    {
        // HD, Figure 5-2
        i = i - ((glong) ((i + 0uLL) >> 1) & 0x5555555555555555LL);
        i = (i & 0x3333333333333333LL) + ((glong) ((i + 0uLL) >> 2) & 0x3333333333333333LL);
        i = (i + (glong) ((i + 0uLL) >> 4)) & 0x0f0f0f0f0f0f0f0fLL;
        i = i + (glong) ((i + 0uLL) >> 8);
        i = i + (glong) ((i + 0uLL) >> 16);
        i = i + (glong) ((i + 0uLL) >> 32);
        return (int) i & 0x7f;
    }

    glong Long::rotateLeft(glong i, gint distance)
    {
        return (glong) ((i << distance) | ((i + 0uLL) >> -distance));
    }

    glong Long::rotateRight(glong i, gint distance)
    {
        return (glong) (((i + 0uLL) >> distance) | (i << -distance));
    }

    glong Long::reverse(glong i)
    {
        // HD, Figure 7-1
        i = (i & 0x5555555555555555LL) << 1 | (glong) ((i + 0uLL) >> 1) & 0x5555555555555555LL;
        i = (i & 0x3333333333333333LL) << 2 | (glong) ((i + 0uLL) >> 2) & 0x3333333333333333LL;
        i = (i & 0x0f0f0f0f0f0f0f0fLL) << 4 | (glong) ((i + 0uLL) >> 4) & 0x0f0f0f0f0f0f0f0fLL;

        return reverseBytes(i);
    }

    gint Long::signum(glong i)
    {
        // HD, Section 2-7
        return (int) ((i >> 63) | ((-i + 0uLL) >> 63));
    }

    glong Long::reverseBytes(glong i)
    {
        i = (i & 0x00ff00ff00ff00ffLL) << 8 | (glong) ((i + 0uLL) >> 8) & 0x00ff00ff00ff00ffLL;
        return (i << 48) | ((i & 0xffff0000LL) << 16) |
               ((glong) ((i + 0uLL) >> 16) & 0xffff0000LL) | (glong) ((i + 0uLL) >> 48);
    }

    glong Long::sum(glong a, glong b)
    {
        return a + b;
    }

    glong Long::max(glong a, glong b)
    {
        return Math::max(a, b);
    }

    glong Long::min(glong a, glong b)
    {
        return Math::min(a, b);
    }
} // core