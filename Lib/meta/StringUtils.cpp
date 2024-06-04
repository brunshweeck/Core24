//
// Created by bruns on 10/05/2024.
//

#include <meta/StringUtils.h>
#include <core/Character.h>
#include <core/Math.h>

namespace core
{
    void String::StringUtils::copyLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);
        count = Math::max(count, 0);

        if (count == 0) {
            return;
        }
        if (val1 == val2) {
            if (off1 == off2) {
                return;
            }
            if (off2 > off1) {
                for (gint i = count - 1; i >= 0; --i) {
                    gchar c = readLatin1CharAt(val1, i + off1);
                    writeLatin1CharAt(val2, i + off2, c);
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c = readLatin1CharAt(val1, i + off1);
                    writeLatin1CharAt(val2, i + off2, c);
                }
            }
        }
        else {
            for (int i = 0; i < count; ++i) {
                gchar c = readLatin1CharAt(val1, i + off1);
                writeLatin1CharAt(val2, i + off2, c);
            }
        }
    }

    void String::StringUtils::copyLatin1ToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val2);
        copyLatin1ToUTF16(val1, off1, chars, off2, count);
    }

    void String::StringUtils::copyLatin1ToUTF16(BYTES val1, gint off1, CHARS val2, gint off2, gint count)
    {
        for (int i = 0; i < count; ++i) {
            val2[off2++] = (gchar) (val1[off1++] & 0xff);
        }
    }

    void String::StringUtils::copyLatin1ToUTF32(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        INTS codePoints = CORE_FCAST(INTS, val2);
        copyLatin1ToUTF32(val1, off1, codePoints, off2, count);
    }

    void String::StringUtils::copyLatin1ToUTF32(BYTES val1, gint off1, INTS val2, gint off2, gint count)
    {
        for (int i = 0; i < count; ++i) {
            val2[off2++] = val1[off1++] & 0xff;
        }
    }

    void String::StringUtils::copyUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);
        count = Math::max(count, 0);

        if (count == 0) {
            return;
        }
        if (val1 == val2) {
            if (off1 == off2) {
                return;
            }
            if (off2 > off1) {
                for (gint i = count - 1; i >= 0; --i) {
                    gchar c = readUTF16CharAt(val1, i + off1);
                    writeUTF16CharAt(val2, i + off2, c);
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c = readUTF16CharAt(val1, i + off1);
                    writeUTF16CharAt(val2, i + off2, c);
                }
            }
        }
        else {
            for (int i = 0; i < count; ++i) {
                gchar c = readUTF16CharAt(val1, i + off1);
                writeUTF16CharAt(val2, i + off2, c);
            }
        }
    }

    void String::StringUtils::copyUTF16(BYTES val1, gint off1, CHARS val2, gint off2, gint count)
    {
        CHARS chars1 = CORE_FCAST(CHARS, val1);
        for (int i = 0; i < count; ++i) {
            val2[off2++] = chars1[off1++];
        }
    }

    void String::StringUtils::copyUTF16(CHARS val1, gint off1, BYTES val2, gint off2, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val2);
        for (int i = 0; i < count; ++i) {
            chars[off2++] = val1[off1++];
        }
    }

    void String::StringUtils::copyUTF16ToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val1);
        return copyUTF16ToLatin1(chars, off1, val2, off2, count);
    }

    void String::StringUtils::copyUTF16ToLatin1(CHARS val1, gint off1, BYTES val2, gint off2, gint count)
    {
        for (int i = 0; i < count; ++i) {
            val2[off1++] = (gbyte) (val1[off2++] & 0xff);
        }
    }

    gint String::StringUtils::copyUTF16ToUTF32(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val1);
        INTS codePoints = CORE_FCAST(INTS, val2);
        return copyUTF16ToUTF32(chars, off1, codePoints, off2, count);
    }

    gint String::StringUtils::copyUTF16ToUTF32(BYTES val1, gint off1, INTS val2, gint off2, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val1);
        return copyUTF16ToUTF32(chars, off1, val2, off2, count);
    }

    gint String::StringUtils::copyUTF16ToUTF32(CHARS val1, gint off1, BYTES val2, gint off2, gint count)
    {
        INTS codePoints = CORE_FCAST(INTS, val2);
        return copyUTF16ToUTF32(val1, off1, codePoints, off2, count);
    }

    gint String::StringUtils::copyUTF16ToUTF32(CHARS val1, gint off1, INTS val2, gint off2, gint count)
    {
        gint o2 = off2;
        for (int i = 0; i < count - 1; ++i) {
            if (isHighSurrogate(val1[off1])) {
                if (isLowSurrogate(val1[off1 + 1])) {
                    val2[off2++] = toCodePoint(val1[off1], val1[off1 + 1]);
                    i += 1;
                }
                else {
                    val2[off2++] = val1[off1++];
                }
            }
            else {
                val2[off2++] = val1[off1++];
            }
        }
        if (off1 < count) {
            val2[off2++] = val1[off1++];
        }
        return off2 - o2;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfLatin1(BYTES val, gint off, gint count)
    {
        return copyOfLatin1(val, off, count, count);
    }

    String::StringUtils::BYTES String::StringUtils::copyOfLatin1(BYTES val, gint off, gint count, gint newLength)
    {
        BYTES bytes = newLatin1String(newLength);
        copyLatin1(val, off, bytes, 0, count > newLength ? newLength : count);
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16(BYTES val, gint off, gint count)
    {
        return copyOfUTF16(val, off, count, count);
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16(BYTES val, gint off, gint count, gint newLength)
    {
        BYTES bytes = newUTF16String(newLength);
        copyUTF16(val, off, bytes, 0, count > newLength ? newLength : count);
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16(CHARS val, gint off, gint count)
    {
        return copyOfUTF16(val, off, count, count);
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16(CHARS val, gint off, gint count, gint newLength)
    {
        BYTES bytes = newUTF16String(newLength);
        copyUTF16(val, off, bytes, 0, count > newLength ? newLength : count);
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfLatin1ToUTF16(BYTES val, gint off, gint count)
    {
        return copyOfLatin1ToUTF16(val, off, count, count);
    }

    String::StringUtils::BYTES String::StringUtils::copyOfLatin1ToUTF16(BYTES val, gint off, gint count, gint newLength)
    {
        BYTES bytes = newUTF16String(newLength);
        copyLatin1ToUTF16(val, off, bytes, 0, count > newLength ? newLength : count);
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16ToLatin1(BYTES val, gint off, gint count)
    {
        return copyOfUTF16ToLatin1(val, off, count, count);
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF16ToLatin1(BYTES val, gint off, gint count, gint newLength)
    {
        BYTES bytes = newLatin1String(newLength);
        copyUTF16ToLatin1(val, off, bytes, 0, count > newLength ? newLength : count);
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::copyOfUTF32ToUTF16(INTS val, gint off, gint count, gint &length)
    {
        gint n = 0;
        for (int i = 0; i < count; ++i) {
            gint cp = val[i + off];
            n += cp <= 0xffff || cp > 0x10ffff ? 1 : 2;
        }

        BYTES bytes = newUTF16String(n);
        CHARS chars = CORE_FCAST(CHARS, bytes);

        for (int i = 0, j = 0; i < count; ++i) {
            gint cp = val[i + off];
            if (cp >= 0 && cp <= 0xffff) {
                chars[j++] = (gchar) cp;
            }
            else if (cp < 0 || cp > 0x10ffff) {
                chars[j++] = '?';
            }
            else {
                chars[j++] = (cp >> 10) + 0xd800 - (0x10000 >> 10);
                chars[j++] = (cp & 0x3ff) + 0xdc00;
            }
        }
        length = n;
        return bytes;
    }

    static gint EMPTY_STRING[1] = { 0 };

    String::StringUtils::BYTES String::StringUtils::newLatin1String(gint count)
    {
        return (BYTES) newUTF16String((gint)((count + 1LL) >> 1));
    }

    String::StringUtils::BYTES String::StringUtils::newUTF16String(gint count)
    {
        if (count > 0) {
            glong length = count;
            if (length % 8 == 0) length += 7;
            CHARS chars = new gchar[count + (length % 8)];
            for (int i = 0; i < count; i += 2) {
                chars[i] = chars[count--] = 0;
            }
            for (glong i = 0; i < (length % 8) / 2; ++i) {
                chars[count + i] = '0';
            }
            return (BYTES) chars;
        }
        EMPTY_STRING[0] = 0;
        return (BYTES) EMPTY_STRING;
    }

    gchar String::StringUtils::readLatin1CharAt(BYTES val, gint index)
    {
        return val[index];
    }

    gchar String::StringUtils::readLatin1CharAt(BYTES val, gint index, gint count)
    {
        return val[index];
    }

    gchar String::StringUtils::readUTF16CharAt(BYTES val, gint index)
    {
        return ((val[index] & 0xff) << 8) | (val[index] & 0xff);
    }

    gchar String::StringUtils::readUTF16CharAt(BYTES val, gint index, gint count)
    {
        return ((val[index] & 0xff) << 8) | (val[index] & 0xff);
    }

    gchar String::StringUtils::readLatin1CodePointAt(BYTES val, gint index)
    {
        return readLatin1CharAt(val, index);
    }

    gchar String::StringUtils::readLatin1CodePointAt(BYTES val, gint index, gint count)
    {
        return readLatin1CharAt(val, index, count);
    }

    gchar String::StringUtils::readUTF16CodePointAt(BYTES val, gint index)
    {
        return readUTF16CharAt(val, index);
    }

    gchar String::StringUtils::readUTF16CodePointAt(BYTES val, gint index, gint count)
    {
        gchar high = readUTF16CharAt(val, index, count);
        if (0xd800 <= high && high <= 0xdbff && index + 1 < count) {
            gchar low = readUTF16CharAt(val, index + 1, count);
            if (0xdc00 <= low && low <= 0xdfff) {
                return ((high << 10) + low) + 0x10000 - (0xd800 << 10) - 0xdc00;
            }
        }
        return high;
    }

    String::StringUtils::BYTES String::StringUtils::inflateUTF16ToLatin1(BYTES val, gint off, gint count)
    {
        CHARS chars = CORE_FCAST(CHARS, val);
        return inflateUTF16ToLatin1(chars, off, count);
    }

    String::StringUtils::BYTES String::StringUtils::inflateUTF16ToLatin1(CHARS val, gint off, gint count)
    {
        BYTES bytes = newLatin1String(count);
        for (int i = 0; i < count; ++i) {
            if ((val[i] >> 8) != 0) {
                destroyLatin1String(bytes, count);
                bytes = (BYTES) EMPTY_STRING;
                return null;
            }
            else {
                bytes[i] = (gbyte) (val[off++] & 0xff);
            }
        }
        return bytes;
    }

    String::StringUtils::BYTES String::StringUtils::inflateUTF32ToLatin1(INTS val, gint off, gint count)
    {
        BYTES bytes = newLatin1String(count);
        for (int i = 0; i < count; ++i) {
            if (((val[i] + 0u) >> 8) != 0) {
                destroyLatin1String(bytes, count);
                bytes = (BYTES) EMPTY_STRING;
                return null;
            }
            else {
                bytes[i] = (gbyte) (val[off++] & 0xff);
            }
        }
        return bytes;
    }

    void String::StringUtils::destroyLatin1String(BYTES &val, gint count)
    {
        if (val != (BYTES) EMPTY_STRING) {
            if (val[0] != 0) {
                fillLatin1String(val, 0, count, 0);
            }
            delete[] val;
        }
    }

    void String::StringUtils::destroyUTF16String(BYTES &val, gint count)
    {
        if (val != (BYTES) EMPTY_STRING) {
            if (val[0] != 0) {
                fillUTF16String(val, 0, count, 0);
            }
            delete[] val;
        }
    }

    void String::StringUtils::fillLatin1String(BYTES val, gint off, gint count, gchar value)
    {
        for (int i = 0; i < count; ++i) {
            val[off++] = (gbyte) (value & 0xff);
        }
    }

    void String::StringUtils::fillUTF16String(BYTES val, gint off, gint count, gchar value)
    {
        CHARS chars = CORE_FCAST(CHARS, val);
        for (int i = 0; i < count; ++i) {
            chars[off++] = value;
        }
    }

    void String::StringUtils::writeLatin1CharAt(BYTES val, gint index, gchar value)
    {
        val[index] = (gbyte) (value & 0xff);
    }

    void String::StringUtils::writeUTF16CharAt(BYTES val, gint index, gchar value)
    {
        CHARS chars = CORE_FCAST(CHARS, val);
        chars[index] = value;
    }

    void String::StringUtils::writeUTF16CharAt(BYTES val, gint index, gbyte b1, gbyte b2)
    {
        return writeUTF16CharAt(val, index, b1 << 8 | b2);
    }

    gbool String::StringUtils::isLatin1(gint ch)
    {
        return ch >> 8 == 0;
    }

    gbool String::StringUtils::isHighSurrogate(gint ch)
    {
        return Character::isHighSurrogate(ch);
    }

    gbool String::StringUtils::isLowSurrogate(gint ch)
    {
        return Character::isLowSurrogate(ch);
    }

    gint String::StringUtils::toCodePoint(gchar high, gchar low)
    {
        if (Character::isSurrogatePair(high, low))
            return Character::toCodePoint(high, low);
        else
            return Character::ERROR;
    }

    gchar String::StringUtils::highSurrogate(gint codePoint)
    {
        if (isSupplementary(codePoint))
            return Character::highSurrogate(codePoint);
        else
            return 0;
    }

    gchar String::StringUtils::lowSurrogate(gint codePoint)
    {
        if (isSupplementary(codePoint))
            return Character::lowSurrogate(codePoint);
        else
            return 0;
    }

    gbool String::StringUtils::isSupplementary(gint codePoint)
    {
        return Character::isSupplementary(codePoint);
    }

    CORE_ALIAS(LONGS, Class< glong >::Pointer);

    gint String::StringUtils::compareToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        gint i = 0;
        if (count > 7) {
            LONGS lhs = CORE_FCAST(LONGS, val1 + off1);
            LONGS rhs = CORE_FCAST(LONGS, val2 + off2);
            gint n = count >> 3;
            for (; i < n; ++i) {
                if (lhs[i] != rhs[i])
                    break;
            }
            i = i << 3;
        }
        for (; i < count; ++i) {
            if (val1[off1 + i] != val2[off2 + i])
                return val1[off1 + i] - val2[off2 + i];
        }
        return 0;
    }

    gint String::StringUtils::compareToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        gint i = 0;
        if (count > 7) {
            LONGS lhs = CORE_FCAST(LONGS, val1 + off1);
            LONGS rhs = CORE_FCAST(LONGS, val2 + off2);
            gint n = count >> 3;
            for (; i < n; ++i) {
                if (lhs[i] != rhs[i])
                    break;
            }
            i = i << 2;
        }
        CHARS lhs = CORE_FCAST(CHARS, val1);
        CHARS rhs = CORE_FCAST(CHARS, val2);
        for (; i < count; ++i) {
            if (lhs[off1 + i] != rhs[off2 + i])
                return lhs[off1 + i] - rhs[off2 + i];
        }
        return 0;
    }

    gint String::StringUtils::compareUTF16ToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val1, i + off1);
            gchar c2 = readLatin1CharAt(val2, i + off2);
            if (c1 != c2)
                return c1 - c2;
        }
        return 0;
    }

    gint String::StringUtils::compareLatin1ToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count)
    {
        return -compareUTF16ToLatin1(val2, off2, val1, off1, count);
    }

    gint String::StringUtils::readUTF32CharAt(String::BYTES val, gint index)
    {
        gchar hi = readUTF16CharAt(val, index);
        if (Character::isHighSurrogate(hi)) {
            gchar lo = readUTF16CharAt(val, index + 1);
            if (Character::isLowSurrogate(lo)) {
                return toCodePoint(hi, lo);
            }
        }
        return hi;
    }

    gint String::StringUtils::readUTF32CharAt(String::BYTES val, gint index, gint count)
    {
        gchar hi = readUTF16CharAt(val, index);
        if (Character::isHighSurrogate(hi) && index + 1 < count) {
            gchar lo = readUTF16CharAt(val, index + 1);
            if (Character::isLowSurrogate(lo)) {
                return toCodePoint(hi, lo);
            }
        }
        return hi;
    }

    gint String::StringUtils::readUTF32CharAt(String::CHARS val, gint index)
    {
        gchar hi = val[index];
        if (Character::isHighSurrogate(hi)) {
            gchar lo = val[index + 1];
            if (Character::isLowSurrogate(lo)) {
                return toCodePoint(hi, lo);
            }
        }
        return hi;
    }

    gint String::StringUtils::readUTF32CharAt(String::CHARS val, gint index, gint count)
    {
        gchar hi = val[index];
        if (Character::isHighSurrogate(hi) && index + 1 < count) {
            gchar lo = val[index + 1];
            if (Character::isLowSurrogate(lo)) {
                return toCodePoint(hi, lo);
            }
        }
        return hi;
    }

    gint String::StringUtils::readUTF32CharAt(String::INTS val, gint index)
    {
        return val[index];
    }

    gint String::StringUtils::readUTF32CharAt(String::INTS val, gint index, gint count)
    {
        return val[index];
    }

    gint String::StringUtils::indexOfLatin1(String::BYTES val1, gint off1, String::BYTES val2, gint off2, gint count1,
                                            gint count2)
    {
        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        gint count = count1 - count2;

        if (count2 > count1) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readLatin1CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readLatin1CharAt(val1, i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readLatin1CharAt(val1, j + off1);
                c2 = readLatin1CharAt(val2, k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return i + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::indexOfLatin1$UTF16(String::BYTES val1, gint off1, String::BYTES val2, gint off2,
                                                  gint count1, gint count2)
    {
        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        gint count = count1 - count2;

        if (count2 > count1) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readLatin1CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val1, i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readUTF16CharAt(val1, j + off1);
                c2 = readLatin1CharAt(val2, k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return i + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::indexOfUTF16(String::BYTES val1, gint off1, String::BYTES val2, gint off2, gint count1,
                                           gint count2)
    {
        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        gint count = count1 - count2;

        if (count2 > count1) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readUTF16CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val1, i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readUTF16CharAt(val1, j + off1);
                c2 = readUTF16CharAt(val2, k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return i + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfLatin1(String::BYTES val1, gint off1, String::BYTES val2, gint off2,
                                                gint count1, gint count2)
    {
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);

        gint count = count1 - count2;

        if (count1 < count2) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readLatin1CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readLatin1CharAt(val1, -i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readLatin1CharAt(val1, -j + off1);
                c2 = readLatin1CharAt(val2, -k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return -j + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfLatin1$UTF16(String::BYTES val1, gint off1, String::BYTES val2, gint off2,
                                                      gint count1, gint count2)
    {
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);

        gint count = count1 - count2;

        if (count1 < count2) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readLatin1CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val1, -i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readUTF16CharAt(val1, -j + off1);
                c2 = readLatin1CharAt(val2, -k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return -j + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfUTF16(String::BYTES val1, gint off1, String::BYTES val2, gint off2,
                                               gint count1, gint count2)
    {
        count1 = Math::max(count1, 0);
        count2 = Math::max(count2, 0);

        off1 = Math::max(off1, 0);
        off2 = Math::max(off2, 0);

        gint count = count1 - count2;

        if (count1 < count2) {
            return -1;
        }

        if (count2 == 0) {
            return off1;
        }

        gchar c2 = readUTF16CharAt(val2, off2);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val1, -i + off1);
            // Look for first character.
            if (c1 != c2) {
                continue;
            }
            // Found first character, now look at the rest of value
            gint j = i + 1;
            for (int k = 1; k < count2; ++k, ++j) {
                c1 = readUTF16CharAt(val1, -j + off1);
                c2 = readUTF16CharAt(val2, -k + off2);
                if (c1 != c2) {
                    break;
                }
            }

            if (j == i + count2) {
                // Found whole string.
                return -j + off1;
            }
        }
        return -1;
    }

    gint String::StringUtils::numberOfLatin1CodePoints(String::BYTES val, gint off, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);

        return count;
    }

    gint String::StringUtils::numberOfUTF16CodePoints(String::BYTES val, gint off, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);
        gint number = 0;

        for (int i = 0; i < count - 1; ++i) {
            gchar c1 = readUTF16CharAt(val, i);
            if (Character::isHighSurrogate(c1)) {
                gchar c2 = readLatin1CharAt(val, i + 1);
                if (Character::isLowSurrogate(c2)) {
                    number += 2;
                    i += 1;
                    continue;
                }
            }
            number += 1;
        }

        return number;
    }

    gint String::StringUtils::hashLatin1String(String::BYTES val, gint off, gint count)
    {
        gint hash = 0;
        for (int i = 0, n = count; i < count; ++i, --n) {
            gchar c = readLatin1CharAt(val, i + off);
            hash = (hash * 31) ^ (n - 1);
        }
        return hash;
    }

    gint String::StringUtils::hashUTF16String(String::BYTES val, gint off, gint count)
    {
        gint hash = 0;
        for (int i = 0, n = count; i < count; ++i, --n) {
            gchar c = readUTF16CharAt(val, i + off);
            hash = (hash * 31) ^ (n - 1);
        }
        return hash;
    }

    gint String::StringUtils::hashUTF16String(String::CHARS val, gint off, gint count)
    {
        gint hash = 0;
        for (int i = 0, n = count; i < count; ++i, --n) {
            gchar c = val[i + off];
            hash = (hash * 31) ^ (n - 1);
        }
        return hash;
    }

    gint String::StringUtils::hashUTF32String(String::BYTES val, gint off, gint count)
    {
        gint hash = 0;
        for (int i = 0, n = count; i < count; ++i, --n) {
            gchar c = readUTF32CharAt(val, i + off);
            hash = (hash * 31) ^ (n - 1);
        }
        return hash;
    }

    gint String::StringUtils::hashUTF32String(String::INTS val, gint off, gint count)
    {
        gint hash = 0;
        for (int i = 0, n = count; i < count; ++i, --n) {
            gchar c = val[i + off];
            hash = (hash * 31) ^ (n - 1);
        }
        return hash;
    }

    gint String::StringUtils::indexOfLatin1(String::BYTES val, gint off, gchar c2, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);

        if (!isLatin1(c2)) {
            return -1;
        }

        for (int i = 0; i < count; ++i) {
            gchar c1 = readLatin1CharAt(val, i + off);
            if (c1 == c2) {
                return i + off;
            }
        }
        return -1;
    }

    gint String::StringUtils::indexOfLatin1(String::BYTES val, gint off, gint c2, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);

        if (!isLatin1(c2)) {
            return -1;
        }

        return indexOfLatin1(val, off, (gchar) c2, count);
    }

    gint String::StringUtils::indexOfUTF16(String::BYTES val, gint off, gchar c2, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);

        for (int i = 0; i < count; ++i) {
            gchar c1 = readUTF16CharAt(val, i + off);
            if (c1 == c2) {
                return i + off;
            }
        }
        return -1;
    }

    gint String::StringUtils::indexOfUTF16(String::BYTES val, gint off, gint c2, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);

        if (Character::isBmpCodePoint(c2)) {
            return indexOfUTF16(val, off, (gchar) c2, count);
        }

        for (int i = 0; i < count - 1; ++i) {
            gchar c11 = readUTF16CharAt(val, i + off);
            if (Character::isHighSurrogate(c11)) {
                gchar c12 = readUTF16CharAt(val, i + 1 + off);
                if (Character::isLowSurrogate(c12)) {
                    gint c1 = Character::toCodePoint(c11, c12);
                    if (c1 == c2) {
                        return i + off;
                    }
                }
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfLatin1(String::BYTES val, gint off, gchar c2, gint count)
    {
        count = Math::max(count, 0);
        off = Math::clamp(off, 0, count);

        if (!isLatin1(c2)) {
            return -1;
        }

        for (int i = off; i > 0; --i) {
            gchar c1 = readLatin1CharAt(val, i);
            if (c1 == c2) {
                return i + off;
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfLatin1(String::BYTES val, gint off, gint c2, gint count)
    {
        count = Math::max(count, 0);
        off = Math::clamp(off, 0, count);

        if (!isLatin1(c2)) {
            return -1;
        }

        return lastIndexOfLatin1(val, off, (gchar) c2, count);
    }

    gint String::StringUtils::lastIndexOfUTF16(String::BYTES val, gint off, gchar c2, gint count)
    {
        count = Math::max(count, 0);
        off = Math::clamp(off, 0, count);

        for (int i = off; i > 0; --i) {
            gchar c1 = readUTF16CharAt(val, i);
            if (c1 == c2) {
                return i + off;
            }
        }
        return -1;
    }

    gint String::StringUtils::lastIndexOfUTF16(String::BYTES val, gint off, gint c2, gint count)
    {
        count = Math::max(count, 0);
        off = Math::clamp(off, 0, count);

        if (Character::isBmpCodePoint(c2)) {
            return lastIndexOfUTF16(val, off, (gchar) c2, count);
        }

        for (int i = off; i > 1; --i) {
            gchar c11 = readUTF16CharAt(val, i);
            if (Character::isHighSurrogate(c11)) {
                gchar c12 = readUTF16CharAt(val, i + 1);
                if (Character::isLowSurrogate(c12)) {
                    gint c1 = Character::toCodePoint(c11, c12);
                    if (c1 == c2) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    void String::StringUtils::shiftLatin1(String::BYTES val, gint off, gint n, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);
        copyLatin1(val, off, val, off + n, n);
    }

    void String::StringUtils::shiftUTF16(String::BYTES val, gint off, gint n, gint count)
    {
        off = Math::max(off, 0);
        count = Math::max(count, 0);
        copyUTF16(val, off, val, off + n, n);
    }

    void String::StringUtils::copyUTF32ToUTF16(String::INTS val1, gint off1, String::BYTES val2, gint off2, gint count)
    {
        //
    }
} // core
