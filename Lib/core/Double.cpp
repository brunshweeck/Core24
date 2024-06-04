//
// Created by brunshweeck on 25 mai 2024.
//

#include <core/Double.h>
#include <core/Long.h>
#include <core/Character.h>
#include <core/NumberFormatException.h>
#include <meta/DoubleConsts.h>
#include <core/misc/Foreign.h>

namespace core
{

//    gdouble const Double::POSITIVE_INFINITY = Double::fromLongBits(0x7FF0000000000000LL);
//    gdouble const Double::NEGATIVE_INFINITY = Double::fromLongBits(0xFFF0000000000000LL);
    gdouble const Double::NaN = Double::fromLongBits(0x7FF8000000000000LL);

    using misc::Foreign;

    String Double::toString(gdouble d)
    {
        if (isNaN(d))
            return "NaN"_S;
        if (isInfinite(d))
            return d < 0.0 ? "infinity"_S : "-infinity"_S;
        glong bits = toRawLongBits(d);
        if (bits == 0LL)
            return "0.0"_S;
        if (bits == DoubleConsts::SIGN_BIT_MASK)
            return "-0.0"_S;
        // find the binary precision
        gint binaryPrecision =
                DoubleConsts::SIGNIFICAND_WIDTH - Long::numberOfTrailingZeros(bits & DoubleConsts::SIGNIF_BIT_MASK);

        // Convert precision to decimal precision (such that f = a * 2^p = b * 10^dp)
        static CORE_FAST gint decimalPrecisions[] = {
                0, 0, 0, 0,       // 2^00 ~ 2^03 = 10^00
                1, 1, 1,          // 2^04 ~ 2^06 = 10^01
                2, 2, 2,          // 2^07 ~ 2^09 = 10^02
                3, 3, 3, 3,       // 2^10 ~ 2^13 = 10^03
                4, 4, 4,          // 2^14 ~ 2^16 = 10^04
                5, 5, 5,          // 2^17 ~ 2^19 = 10^05
                6, 6, 6, 6,       // 2^20 ~ 2^23 = 10^06
                7, 7, 7,          // 2^24 ~ 2^26 = 10^07
                8, 8, 8,          // 2^27 ~ 2^29 = 10^08
                9, 9, 9, 9,       // 2^30 ~ 2^33 = 10^09
                10, 10, 10,       // 2^34 ~ 2^36 = 10^10
                11, 11, 11,       // 2^37 ~ 2^39 = 10^11
                12, 12, 12, 12,   // 2^40 ~ 2^43 = 10^12
                13, 13, 13,       // 2^44 ~ 2^46 = 10^13
                14, 14, 14,       // 2^47 ~ 2^49 = 10^14
                15, 15, 15, 15,   // 2^50 ~ 2^53 = 10^15
                16, 16, 16,       // 2^54 ~ 2^56 = 10^16 (max)
                17, 17, 17,       // 2^57 ~ 2^59 = 10^17
                18, 18, 18, 18,   // 2^60 ~ 2^63 = 10^18
        };

        gint decimalPrecision = decimalPrecisions[binaryPrecision];
        // adjust decimal precision
        static CORE_FAST glong powerOfTeen[] = {
                1LL,
                10LL,
                100LL,
                1000LL,
                10000LL,
                100000LL,
                1000000LL,
                10000000LL,
                100000000LL,
                1000000000LL,
                10000000000LL,
                100000000000LL,
                1000000000000LL,
                10000000000000LL,
                100000000000000LL,
                1000000000000000LL,
                10000000000000000LL
        };
        if (powerOfTeen[decimalPrecision] < (1LL << binaryPrecision))
            decimalPrecision += 1;
        CharArray digits(64);
        gint next = 0;
        if ((bits & DoubleConsts::SIGN_BIT_MASK) != 0) {
            digits[++next] = u'-';
            bits &= DoubleConsts::SIGN_BIT_MASK;
        }
        // we leave one character used for rounding
        gint placeholder = next;
        digits[next++] = '0';
        gdouble uVal = fromLongBits(bits);
        gint exponent = 0;
        gdouble divider = 10; // used to update power of Teen
        gint updater = 1; // used to update exponent
        gint digit = -1; // last digit
        if (uVal < 1) {
            updater = -1;
            divider = 0.1;
        }
        gdouble const tmp = uVal;
        while (uVal >= 10 || uVal < 1) {
            uVal /= divider;
            exponent += updater;
        }
        if (tmp > 1.e+7 || tmp < 1.e-3) {
            // scientific format (x.y x10^z)
            digit = (gint) uVal;
            digits[next++] = Character::forDigit(digit, 10);
            digits[next++] = '.';
            decimalPrecision -= decimalPrecision > 10 ? 2 : 1;
            do {
                uVal = (uVal - digit) * 10;
                digit = (gint) uVal;
                digits[next++] = Character::forDigit(digit, 10);
                decimalPrecision -= 1;
            }
            while (decimalPrecision > 0);
            // round result and remove all trailing zeros
            uVal = (uVal - digit) * 10;
            digit = (gint) uVal;
            if (digit >= 5) {
                // round value and remove all trailing zeros
                gbool finished = false;
                while (!finished && next > 0) {
                    next -= 1;
                    if (digits[next] != '.') {
                        digit = digits[next] - 48;
                        digits[next] = Character::forDigit((digit + 1) % 10, 10);
                        finished = digit != 9;
                    }
                }
            }
            else if (digits[next - 1] == '0') {
                // remove all trailing zeros
                next -= 1;
                while (digits[next] == '0')
                    next -= 1;
                if (digits[next] == '.')
                    next -= 1;
            }
            else {
                // no problems found
                next -= 1;
            }
            next += 1;
            digits[next++] = 'E';
            digits[next++] = exponent < 0 ? '-' : '+';
            exponent = Math::abs(exponent);
            if (exponent >= 1000)
                digits[next++] = Character::forDigit(exponent / 1000, 10);
            if (exponent >= 100)
                digits[next++] = Character::forDigit(exponent % 1000 / 100, 10);
            if (exponent >= 10)
                digits[next++] = Character::forDigit(exponent % 100 / 10, 10);
            digits[next++] = Character::forDigit(exponent % 10, 10);
            digits[next] = 0;
        }
        else {
            // decimal format
            if (tmp < 1) {
                digits[next++] = '0';
                digits[next++] = '.';
                digit = 0;
                uVal = tmp;
            }
            else {
                digit = (gint) uVal;
                digits[next++] = Character::forDigit(digit, 10);
                decimalPrecision -= 1;
                while (exponent > 0) {
                    uVal = (uVal - digit) * 10;
                    digit = (gint) uVal;
                    digits[next++] = Character::forDigit(digit, 10);
                    exponent -= 1;
                    decimalPrecision -= 1;
                }
                digits[next++] = '.';
            }
            do {
                uVal = (uVal - digit) * 10;
                digit = (gint) uVal;
                digits[next++] = Character::forDigit(digit, 10);
                decimalPrecision -= 1;
            }
            while (decimalPrecision > 0);
            // round result and remove all trailing zeros
            uVal = (uVal - digit) * 10;
            digit = (gint) uVal;
            if (digit >= 5) {
                // round value and remove all trailing zeros
                gbool finished = false;
                while (!finished && next > 0) {
                    next -= 1;
                    if (digits[next] != '.') {
                        digit = digits[next] - 48;
                        digits[next] = Character::forDigit((digit + 1) % 10, 10);
                        finished = digit != 9;
                    }
                }
            }
            else if (digits[next - 1] == '0') {
                // remove all trailing zeros
                next -= 1;
                while (digits[next] == '0')
                    next -= 1;
                if (digits[next] == '.')
                    next -= 1;
            }
            else {
                // no problems found
                next -= 1;
            }
        }
        gint begin = 0;
        if (digits[placeholder] == Character::forDigit(0, 10)) {
            // the diskSpace that has be leaved in begin has not used
            if (placeholder > 0) {
                digits[placeholder] = digits[placeholder - 1];
                begin = placeholder;
            }
            else
                begin = 1;
        }
        return String(digits, begin, digits[next + 1] != '.' ? next + 1 : next);
    }

    String Double::toHexString(gdouble d)
    {
        if (!isFinite(d))
            return toString(d);
        glong bits = toRawLongBits(d);
        CharArray digits(32);
        gint next = 0;
        gdouble const uVal = fromLongBits(bits & ~DoubleConsts::SIGN_BIT_MASK);
        if ((bits & DoubleConsts::SIGN_BIT_MASK) != 0)
            digits[next++] = '-';
        digits[next++] = '0';
        digits[next++] = 'x';
        digits[next++] = uVal < MIN_NORMAL ? '0' : '1';
        digits[next++] = '.';
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 48) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 44) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 40) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 36) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 32) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 28) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 24) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 20) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 16) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 12) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 8) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 4) & 0xf), 16);
        digits[next++] = Character::forDigit((gint) (((bits & DoubleConsts::SIGNIF_BIT_MASK) >> 0) & 0xf), 16);
        // remove all trailing zero
        while (digits[next - 1] == '0' && digits[next - 2] != '.')
            next -= 1;
        digits[next++] = 'P';
        gint exponent = uVal < MIN_NORMAL ? MIN_EXPONENT : (gint) (((bits & DoubleConsts::EXP_BIT_MASK) >> 52) -
                                                                   DoubleConsts::EXP_BIAS);
        digits[next++] = exponent < 0 ? '-' : '+';
        exponent = Math::abs(exponent);
        if (exponent >= 1000)
            digits[next++] = Character::forDigit(exponent / 1000, 10);
        if (exponent >= 100)
            digits[next++] = Character::forDigit(exponent % 1000 / 100, 10);
        if (exponent >= 10)
            digits[next++] = Character::forDigit(exponent % 100 / 10, 10);
        digits[next++] = Character::forDigit(exponent % 10, 10);
        digits[next] = 0;
        return String(digits, 0, next);
    }

    Double Double::valueOf(String const &s)
    {
        try {
            return valueOf(parseDouble(s));
        }
        catch (NumberFormatException const &ex) { ex.throws($ftrace(""_S)); }
    }

    Double Double::valueOf(gdouble d)
    {
        return d;
    }

    gdouble Double::parseDouble(String const &s)
    {
        if (s.isEmpty())
            NumberFormatException(R"(Invalid number format for input "".)"_S).throws($ftrace(""_S));
        gint len = s.length();
        gdouble sign = +1.0;
        gint base = 10;
        gint next = 0;
        gdouble retVal = 0;
        gchar ch = s.charAt(0);
        switch (ch) {
            case '-':
                sign = -1;
            case '+':
                next += 1;
                if (next == len)
                    NumberFormatException(R"(Invalid number format for input " )"_S + s + R"(".)"_S)
                            .throws($ftrace(""_S));
                ch = s.charAt(next);
            default:
                break;
        }
        switch (ch) {
            case '0':
                next += 1;
                if (next == len)
                    // +0 or -0
                    return 0.0 * sign;
                ch = s.charAt(next);
                if (ch == 'x' || ch == 'X') {
                    // hex format
                    next += 1;
                    base = 16;
                    if (next == len)
                        goto throwIllegalFormat;
                }
                else if (ch == 'b' || ch == 'B') {
                    // binary format 0b...
                    next += 1;
                    if (next == len)
                        goto throwIllegalFormat;
                    // check if is integer
                    if (s.indexOf('.', next) >= 0)
                        goto throwIllegalFormat;
                    base = 2;
                }
                else {
                    // check if is integer
                    if (s.indexOf('.', next) < 0)
                        base = 8;
                }
                break;
            case 'i':
            case 'I':
                // inf or infinity
                if (len - next == 3) {
                    gchar const ch2 = s.charAt(next + 1);
                    gchar const ch3 = s.charAt(next + 2);
                    if ((ch2 == 'n' || ch2 == 'N') && (ch3 == 'f' || ch3 == 'F'))
                        return sign > 0 ? POSITIVE_INFINITY : NEGATIVE_INFINITY;
                }
                else if (len - next == 8) {
                    gchar const ch2 = s.charAt(next + 1);
                    gchar const ch3 = s.charAt(next + 2);
                    gchar const ch4 = s.charAt(next + 3);
                    gchar const ch5 = s.charAt(next + 4);
                    gchar const ch6 = s.charAt(next + 5);
                    gchar const ch7 = s.charAt(next + 6);
                    if ((ch2 == 'n' || ch2 == 'N') && (ch3 == 'f' || ch3 == 'F') && (ch4 == 'i' || ch4 == 'I') &&
                        (ch5 == 'f' || ch5 == 'F') && (ch6 == 'i' || ch6 == 'I') && (ch7 == 'y' || ch7 == 'Y'))
                        return sign > 0 ? POSITIVE_INFINITY : NEGATIVE_INFINITY;
                }
                goto throwIllegalFormat;
            case 'n':
            case 'N':
                // NaN
                if (len - next == 3) {
                    gchar const ch2 = s.charAt(next + 1);
                    gchar const ch3 = s.charAt(next + 2);
                    if ((ch2 == 'a' || ch2 == 'A') && (ch3 == 'n' || ch3 == 'N'))
                        return sign > 0 ? POSITIVE_INFINITY : NEGATIVE_INFINITY;
                }
                goto throwIllegalFormat;
            default:
                break;
        }
        switch (base) {
            case 2:
            case 8:
                // integral formats
                while (next < len) {
                    ch = s.charAt(next);
                    if (ch < '0' || ch > '9')
                        goto throwIllegalFormat;
                    gchar const digit = ch - '0';
                    retVal = retVal * base + digit;
                    next += 1;
                }
                return sign * retVal;
            case 10:
                // decimal format
                while (next < len) {
                    ch = s.charAt(next);
                    gchar digit = -1;
                    if (ch >= '0' && ch <= '9')
                        digit = ch - '0';
                    else if (ch == 'e' || ch == 'E' || ch == '.') {
                        next += 1;
                        gint decimal = 0;
                        gint exponent = 0;
                        gint sign2 = +1;
                        gint count = 0;
                        if (ch == '.') {
                            // decimal part
                            gint maxCount = 9;
                            while (next < len) {
                                ch = s.charAt(next);
                                if (ch == 'e' || ch == 'E')
                                    break;
                                if (ch >= '0' && ch <= '9')
                                    digit = ch - '0';
                                else
                                    goto throwIllegalFormat;
                                if (maxCount > 0) {
                                    if (count < maxCount) {
                                        decimal = decimal * 10 + digit;
                                        count += 1;
                                    }
                                    else if (count == maxCount) {
                                        gint tmp = decimal * 10 + digit;
                                        if (tmp > 0) {
                                            // overflow
                                            maxCount += 1;
                                            decimal = tmp;
                                            count += 1;
                                        }
                                        else if (digit >= 5 && (tmp = decimal + 1) > decimal) {
                                            decimal = tmp;
                                            maxCount = 0;
                                        }
                                    }
                                }
                                next += 1;
                            }
                        }
                        if (ch == 'e' || ch == 'E') {
                            // exponent part
                            next += 1;
                            if (next == len)
                                goto throwIllegalFormat;
                            ch = s.charAt(next);
                            switch (ch) {
                                case '-':
                                    sign2 = -1;
                                case '+':
                                    next += 1;
                                    if (next == len)
                                        goto throwIllegalFormat;
                                default:
                                    break;
                            }
                            while (next < len) {
                                ch = s.charAt(next);
                                if (ch >= '0' && ch <= '9')
                                    digit = ch - '0';
                                else
                                    goto throwIllegalFormat;
                                if (exponent <= 999999)
                                    exponent = exponent * 10 + digit;
                                next += 1;
                            }
                        }
                        return sign * (retVal + Math::pow(decimal, -count)) * Math::pow(10, sign2 * exponent);
                    }
                    else
                        goto throwIllegalFormat;
                    retVal = retVal * 10 + digit;
                    next += 1;
                }
                return sign * retVal;
            case 16: {
                glong bit64 = 0;
                gint shift = PRECISION - 1;
                gbool rounded = false;
                gbool sticky = false;
                gint decimalBitsLen = 0; // after '.'
                gint integerBitsLen = 0; // before '.'
                // hex format
                while (next < len) {
                    ch = s.charAt(next);
                    gchar digit = -1;
                    if (ch >= '0' && ch <= '9')
                        digit = ch - '0';
                    else if (ch >= 'a' && ch <= 'f')
                        digit = ch - 'a';
                    else if (ch >= 'A' && ch <= 'F')
                        digit = ch - 'A';
                    else if (ch == 'p' || ch == 'P' || ch == '.')
                        break;
                    else
                        goto throwIllegalFormat;
                    if (shift == 52) {
                        switch (digit) {
                            case 1:
                                bit64 |= (glong) digit << 52;
                                shift -= 4;
                                integerBitsLen = 0;
                                break;
                            case 2:
                            case 3:
                                bit64 |= (glong) digit << 51;
                                shift -= 5;
                                integerBitsLen = 1;
                                break;
                            case 4:
                            case 5:
                            case 6:
                            case 7:
                                bit64 |= (glong) digit << 50;
                                shift -= 6;
                                integerBitsLen = 2;
                                break;
                            default:
                                bit64 |= (glong) digit << 49;
                                shift -= 7;
                                integerBitsLen = 3;
                                break;
                        }
                    }
                    else if (shift >= 0) {
                        bit64 |= (glong) digit << shift;
                        shift -= 4;
                    }
                    else if (shift >= -4) {
                        switch (shift) {
                            case -1:
                                bit64 |= ((glong) digit & 0xE) >> 1;
                                rounded = (digit & 0x1) != 0;
                                break;
                            case -2:
                                bit64 |= ((glong) digit & 0xC) >> 2;
                                rounded = (digit & 0x2) != 0;
                                sticky = (digit & 0x1) != 0;
                                break;
                            case -3:
                                bit64 |= ((glong) digit & 0x8) >> 3;
                                rounded = (digit & 0x4) != 0;
                                sticky = (digit & 0x3) != 0;
                                break;
                            case -4:
                                rounded = (digit & 0x8) != 0;
                                sticky = (digit & 0x7) != 0;
                                break;
                            default:
                                break;
                        }
                        shift -= 4;
                    }
                    else if (!sticky)
                        sticky |= digit != 0;
                    decimalBitsLen += 1;
                    next += 1;
                }
                {
                    gint digit = 0;
                    next += 1;
                    gint exponent = 0;
                    gint sign2 = +1;
                    if (ch == '.') {
                        // decimal part
                        while (next < len) {
                            ch = s.charAt(next);
                            if (ch == 'p' || ch == 'P')
                                break;
                            if (ch >= '0' && ch <= '9')
                                digit = ch - '0';
                            else if (ch >= 'a' && ch <= 'z')
                                digit = ch - 'a';
                            else if (ch >= 'A' && ch <= 'Z')
                                digit = ch - 'A';
                            else
                                goto throwIllegalFormat;
                            if (shift >= 0) {
                                bit64 |= (glong) digit << shift;
                                shift -= 4;
                            }
                            else if (shift >= -4) {
                                switch (shift) {
                                    case -1:
                                        bit64 |= ((glong) digit & 0xE) >> 1;
                                        rounded = (digit & 0x1) != 0;
                                        break;
                                    case -2:
                                        bit64 |= ((glong) digit & 0xC) >> 2;
                                        rounded = (digit & 0x2) != 0;
                                        sticky = (digit & 0x1) != 0;
                                        break;
                                    case -3:
                                        bit64 |= ((glong) digit & 0x8) >> 3;
                                        rounded = (digit & 0x4) != 0;
                                        sticky = (digit & 0x3) != 0;
                                        break;
                                    case -4:
                                        rounded = (digit & 0x8) != 0;
                                        sticky = (digit & 0x7) != 0;
                                        break;
                                    default:
                                        break;
                                }
                                shift -= 4;
                            }
                            else if (!sticky)
                                sticky |= digit != 0;
                            decimalBitsLen += 1;
                            next += 1;
                        }
                    }
                    if (ch == 'p' || ch == 'P') {
                        // exponent part
                        next += 1;
                        if (next == len)
                            goto throwIllegalFormat;
                        ch = s.charAt(next);
                        switch (ch) {
                            case '-':
                                sign2 = -1;
                            case '+':
                                next += 1;
                                if (next == len)
                                    goto throwIllegalFormat;
                            default:
                                break;
                        }
                        while (next < len) {
                            ch = s.charAt(next);
                            if (ch >= '0' && ch <= '9')
                                digit = ch - '0';
                            else
                                goto throwIllegalFormat;
                            if (exponent <= 999999)
                                exponent = exponent * 10 + digit;
                            next += 1;
                        }
                    }
                    if (bit64 == 0) {
                        retVal = 0.0 * sign;
                        return retVal;
                    }
                    else {
                        glong eBit64 = sign2 * exponent + integerBitsLen + (decimalBitsLen - 1) * 4;
                        if (eBit64 > MAX_EXPONENT) {
                            // overflow
                            retVal = sign < 0 ? NEGATIVE_INFINITY : POSITIVE_INFINITY;
                            return retVal;
                        }
                        else if (sign2 * exponent < 0 && (sign2 * exponent) > MIN_EXPONENT) {
                            // normal
                            eBit64 += DoubleConsts::EXP_BIAS;
                            eBit64 <<= 52;
                            eBit64 &= DoubleConsts::EXP_BIT_MASK;
                        }
                        else if (eBit64 < (MIN_EXPONENT - 52)) {
                            sticky |= rounded;
                            rounded = false;
                            glong var = 53 - (eBit64 - (MIN_EXPONENT - 52) + 1);
                            rounded = (bit64 & (1LL << (var - 1))) != 0;
                            if (var > 1)
                                sticky = sticky || (bit64 & ~((~0) << (var - 1))) != 0;
                            bit64 = bit64 >> var;
                            eBit64 = (glong) (MIN_EXPONENT - 1 + DoubleConsts::EXP_BIAS) << 52;
                        }
                        if (((bit64 & 1) != 0 && rounded && sticky) || (((bit64 & 1) == 0) && rounded))
                            bit64 += 1;
                        if (sign < 0)
                            bit64 |= DoubleConsts::SIGN_BIT_MASK;
                        bit64 |= eBit64;
                        retVal = fromLongBits(bit64);
                        return retVal;
                    }
                }
            }
            default:
                break;
        }
throwIllegalFormat:
        NumberFormatException(R"(Invalid number format for input " )"_S + s + R"(".)"_S).throws($ftrace(""_S));
    }

    gbool Double::isNaN(gdouble v)
    {
        return !isFinite(v) && !isInfinite(v);
    }

    gbool Double::isInfinite(gdouble v)
    {
        return Math::abs(v) > MAX_VALUE;
    }

    gbool Double::isFinite(gdouble d)
    {
        return Math::abs(d) <= MAX_VALUE;
    }

    Double::Double(gdouble value) : value(value)
    {
        //
    }

    Double::Double(String const &s)
    {
        try {
            value = parseDouble(s);
        }
        catch (NumberFormatException const &ex) { ex.throws($ftrace(""_S)); }
    }

    gbool Double::isNaN() const
    {
        return isNaN(value);
    }

    gbool Double::isInfinite() const
    {
        return isInfinite(value);
    }

    String Double::toString() const
    {
        return toString(value);
    }

    gbyte Double::byteValue() const
    {
        return (gbyte) intValue();
    }

    gshort Double::shortValue() const
    {
        return (gshort) intValue();
    }

    gint Double::intValue() const
    {
        return (gint) value;
    }

    glong Double::longValue() const
    {
        return (glong) value;
    }

    gfloat Double::floatValue() const
    {
        return (gfloat) value;
    }

    gdouble Double::doubleValue() const
    {
        return value;
    }

    gint Double::hash() const
    {
        return hash(value);
    }

    gint Double::hash(gdouble value)
    {
        return Long::hash(toLongBits(value));
    }

    gbool Double::equals(Object const &obj) const
    {
        return this == &obj ||
               Class< Double >::hasInstance(obj) && compare(value, CORE_XCAST(Double const, obj).value);
    }

    glong Double::toLongBits(gdouble value)
    {
        return isNaN(value) ? 0x7ff8000000000000LL
                            : toRawLongBits(value);
    }

    glong Double::toRawLongBits(gdouble value)
    {
        return *(Class< glong >::Pointer) &value;
    }

    gdouble Double::fromLongBits(glong bits)
    {
        return *(Class< gdouble >::Pointer) &bits;
    }

    gint Double::compareTo(Double const &anotherDouble) const
    {
        return compare(value, anotherDouble.value);
    }

    gint Double::compare(gdouble d1, gdouble d2)
    {
        return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : ((d1 == d2) ? 0 : (isNaN(d1) ? (isNaN(d2) ? 0 : +1) : -1)));
    }

    gdouble Double::sum(gdouble a, gdouble b)
    {
        return a + b;
    }

    gdouble Double::max(gdouble a, gdouble b)
    {
        return Math::max(a, b);
    }

    gdouble Double::min(gdouble a, gdouble b)
    {
        return Math::min(a, b);
    }

    Double::operator gdouble() const
    {
        return doubleValue();
    }

    Double::operator gdouble &()
    {
        return value;
    }
} // core