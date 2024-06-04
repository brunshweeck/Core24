//
// Created by bruns on 10/05/2024.
//

#include <core/String.h>
#include <meta/StringUtils.h>
#include <meta/CharacterDataLatin1.h>
#include <core/misc/Precondition.h>
#include <core/misc/Foreign.h>
#include <core/Math.h>
#include <core/Character.h>
#include <core/OutOfMemoryError.h>
#include <core/ArithmeticException.h>
#include <core/IllegalArgumentException.h>
#include <core/XString.h>
#include <core/Boolean.h>
#include <core/Integer.h>
#include <core/Long.h>
#include <core/Float.h>
#include <core/Double.h>

namespace core
{
    using misc::Precondition;
    using misc::Foreign;

    String::Coder String::coding() const
    {
        return COMPACT_STRINGS && coder == LATIN1 ? LATIN1 : UTF16;
    }

    String::String()
    {
        coder = COMPACT_STRINGS ? LATIN1 : UTF16;
        value = StringUtils::newLatin1String(0);
        count = 0;
        hashValue = 0;
        hashIsZero = false;
    }

    String::String(String const &original) : String()
    {
        gint length = original.length();
        if (original.coding() == LATIN1) {
            value = StringUtils::copyOfLatin1(original.value, 0, length);
            coder = LATIN1;
        }
        else {
            value = StringUtils::copyOfUTF16(original.value, 0, length);
            coder = UTF16;
        }
        count = length;
        hashValue = original.hashValue;
        hashIsZero = original.hashIsZero;
    }

    String::String(String &&original) CORE_NOTHROW: String()
    {
        value = original.value;
        count = original.count;
        hashValue = original.hashValue;
        hashIsZero = original.hashIsZero;

        original.count = 0;
        original.value = null;
        original.hashValue = 0;
        original.hashIsZero = true;
    }

    String::String(CharArray const &value) : String(value, 0, value.length())
    {
    }

    String::String(CharArray const &value, gint offset, gint count) : String()
    {
        Precondition::checkIndexFromSize(offset, count, value.length());

        if (count > 0) {
            if (COMPACT_STRINGS) {
                BYTES bytes = StringUtils::inflateUTF16ToLatin1(value.value, offset, count);
                if (bytes != null) {
                    String::value = bytes;
                    String::count = count;
                    String::coder = LATIN1;
                }
                else
                    goto UTF16_STRING;
            }
            else {
UTF16_STRING:
                String::value = StringUtils::copyOfUTF16(value.value, offset, count);
                String::count = count;
                String::coder = UTF16;
            }
        }
    }

    String::String(IntArray const &codePoints, gint offset, gint count) : String()
    {
        Precondition::checkIndexFromSize(offset, count, codePoints.length());

        if (count > 0) {
            if (COMPACT_STRINGS) {
                BYTES bytes = StringUtils::inflateUTF32ToLatin1(codePoints.value, offset, count);
                if (bytes != null) {
                    String::value = bytes;
                    String::count = count;
                    String::coder = LATIN1;
                }
                else
                    goto UTF16_STRING;
            }
            else {
UTF16_STRING:
                String::value = StringUtils::copyOfUTF32ToUTF16(codePoints.value, offset, count, String::count);
                String::coder = UTF16;
            }
        }
    }

    String::String(ByteArray const &ascii, gint hibyte, gint offset, gint count) : String()
    {
        Precondition::checkIndexFromSize(offset, count, ascii.length());

        if (count > 0) {
            if (COMPACT_STRINGS && hibyte == 0) {
                value = StringUtils::copyOfLatin1(ascii.value, offset, count);
                String::coder = LATIN1;
            }
            else {
                value = StringUtils::newUTF16String(count);
                String::coder = UTF16;
                for (int i = 0; i < count; ++i) {
                    StringUtils::writeUTF16CharAt(value, i, (gbyte) (hibyte & 0xff), ascii.value[i]);
                }
            }
            String::count = count;
        }
    }

    String::String(ByteArray const &ascii, gint hibyte) : String(ascii, hibyte, 0, ascii.length())
    {
    }

    String &String::operator=(String const &other)
    {
        if (this != &other) {
            gint length = other.count;
            BYTES bytes = other.coding() == LATIN1
                          ? StringUtils::copyOfLatin1(other.value, 0, length)
                          : StringUtils::copyOfUTF16(other.value, 0, length);
            coder == LATIN1
            ? StringUtils::destroyLatin1String(value, count)
            : StringUtils::destroyUTF16String(value, count);
            count = 0;

            value = bytes;
            count = length;
            hashIsZero = other.hashIsZero;
            hashValue = other.hashValue;
        }
        return *this;
    }

    gint String::length() const
    {
        return count > 0 && value != null ? count : 0;
    }

    gbool String::isEmpty() const
    {
        return count <= 0 || value == null;
    }

    gchar String::charAt(gint index) const
    {
        Precondition::checkIndex(index, count);
        return coder == LATIN1
               ? StringUtils::readLatin1CharAt(value, index)
               : StringUtils::readUTF16CharAt(value, index);
    }

    gint String::codePointAt(gint index) const
    {
        Precondition::checkIndex(index, count);
        return coder == LATIN1
               ? StringUtils::readLatin1CodePointAt(value, index, count)
               : StringUtils::readUTF16CharAt(value, index, count);
    }

    gint String::codePointCount(gint beginIndex, gint endIndex) const
    {
        Precondition::checkIndexFromRange(beginIndex, endIndex, count);
        if (coding() == LATIN1) {
            return endIndex - beginIndex;
        }
        else {
            gint n = 0;
            for (int i = beginIndex; i <= endIndex; ++i) {
                gchar c = StringUtils::readLatin1CodePointAt(value, i);
                if (StringUtils::isSupplementary(c)) {
                    n += 2;
                    i += 1;
                }
                else {
                    n += 1;
                }
            }
            return n;
        }
    }

    void String::toChars(gint beginIndex, gint endIndex, CharArray &dest, gint offset)
    {
        Precondition::checkIndexFromRange(beginIndex, endIndex, count);
        Precondition::checkIndexFromSize(offset, endIndex - beginIndex, dest.length());

        coding() == LATIN1
        ? StringUtils::copyLatin1ToUTF16(value, beginIndex, dest.value, offset, endIndex - beginIndex)
        : StringUtils::copyUTF16(value, beginIndex, dest.value, offset, endIndex - beginIndex);
    }

    void String::toBytes(gint beginIndex, gint endIndex, ByteArray &dest, gint offset)
    {
        Precondition::checkIndexFromRange(beginIndex, endIndex, count);
        Precondition::checkIndexFromSize(offset, endIndex - beginIndex, dest.length());

        coding() == LATIN1
        ? StringUtils::copyLatin1(value, beginIndex, dest.value, offset, endIndex - beginIndex)
        : StringUtils::copyUTF16ToLatin1(value, beginIndex, dest.value, offset, endIndex - beginIndex);
    }

    gbool String::equals(Object const &obj) const
    {
        if (this == &obj)
            return true;
        else if (!Class< String >::hasInstance(obj))
            return false;
        else {
            String const &other = CORE_XCAST(String const, obj);
            Coder const coder = coding();
            gint const count = length();

            if (count != other.length() || coder != other.coding()) {
                return false;
            }

            return coder == LATIN1
                   ? StringUtils::compareToLatin1(value, 0, other.value, 0, count)
                   : StringUtils::compareToUTF16(value, 0, other.value, 0, count);
        }
    }

    gint String::compareTo(String const &other) const
    {
        Coder coder = coding();
        gint count1 = length();
        gint count2 = other.length();

        gint count = count1 < count2 ? count1 : count2;

        gint res = coder == other.coding()
                   ? coder == LATIN1
                     ? StringUtils::compareToLatin1(value, 0, other.value, 0, count)
                     : StringUtils::compareToUTF16(value, 0, other.value, 0, count)
                   : coder == LATIN1
                     ? StringUtils::compareLatin1ToUTF16(value, 0, other.value, 0, count)
                     : StringUtils::compareUTF16ToLatin1(value, 0, other.value, 0, count);

        return count1 == count2
               ? res
               : count1 > count2
                 ? coder == LATIN1
                   ? StringUtils::readLatin1CharAt(value, count)
                   : StringUtils::readUTF16CharAt(value, count)
                 : other.coding() == LATIN1
                   ? -StringUtils::readLatin1CharAt(other.value, count)
                   : -StringUtils::readUTF16CharAt(other.value, count);
    }

    String::~String()
    {
        gint count = length();
        Coder coder = coding();
        if (count > 0) {
            coder == LATIN1
            ? StringUtils::destroyLatin1String(value, count)
            : StringUtils::destroyUTF16String(value, count);
            String::count = 0;
            String::value = StringUtils::newLatin1String(0);
            String::coder = COMPACT_STRINGS ? LATIN1 : UTF16;
        }
    }

    gbool String::startsWith(String const &prefix, gint toffset) const
    {
        if (toffset < 0 || toffset > length() - prefix.length()) {
            return false;
        }

        Coder coder = coding();
        gint count = prefix.length();

        if (coder == prefix.coding()) {
            if (coder == LATIN1) {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readLatin1CharAt(value, i + toffset);
                    gchar c2 = StringUtils::readLatin1CharAt(prefix.value, i);
                    if (c1 != c2) {
                        return false;
                    }
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i + toffset);
                    gchar c2 = StringUtils::readUTF16CharAt(prefix.value, i);
                    if (c1 != c2) {
                        return false;
                    }
                }
            }
        }
        else {
            if (coder == LATIN1) {
                return false;
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i + toffset);
                    gchar c2 = StringUtils::readLatin1CharAt(prefix.value, i);
                    if (c1 != c2) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    gbool String::startsWith(String const &prefix) const
    {
        return startsWith(prefix, 0);
    }

    gbool String::endsWith(String const &suffix) const
    {
        return startsWith(suffix, length() - suffix.length());
    }

    gint String::hash() const
    {
        // The hashValue or hashIsZero fields are subject to a benign data race,
        // making it crucial to ensure that any observable result of the
        // calculation in this method stays correct under any possible read of
        // these fields. Necessary restrictions to allow this to be correct
        // without explicit memory fences or similar concurrency primitives is
        // that we can ever only write to one of these two fields for a given
        // String instance, and that the computation is idempotent and derived
        // from immutable state
        gint hash = hashValue;
        if (hash == 0 && !hashIsZero) {
            gint count = length();
            if (coding() == LATIN1) {
                for (int i = 0; i < count; ++i) {
                    hash = hash * 31 + StringUtils::readLatin1CharAt(value, i);
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    hash = hash * 31 + StringUtils::readUTF16CharAt(value, i);
                }
            }
            hashIsZero = (hashValue = hash) == 0;
        }
        return hash;
    }

    gint String::indexOf(gint ch) const
    {
        return indexOf(ch, 0);
    }

    gint String::indexOf(gint ch, gint fromIndex) const
    {
        fromIndex = Math::max(fromIndex, 0);
        gint count = length();
        if (fromIndex >= count) {
            return -1;
        }
        if (coding() == LATIN1) {
            if (Character::isValidCodePoint(ch) && StringUtils::isLatin1(ch)) {
                for (int i = 0; i < count; ++i) {
                    gbyte c = (gbyte) StringUtils::readLatin1CharAt(value, i);
                    if (c == (gbyte) ch) {
                        return i;
                    }
                }
            }
        }
        else {
            if (Character::isValidCodePoint(ch) && StringUtils::isLatin1(ch)) {
                for (int i = 0; i < count; ++i) {
                    gbyte c = (gbyte) StringUtils::readUTF16CharAt(value, i);
                    if (c == (gbyte) ch) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    gint String::lastIndexOf(gint ch) const
    {
        return lastIndexOf(ch, length() - 1);
    }

    gint String::lastIndexOf(gint ch, gint fromIndex) const
    {
        fromIndex = Math::max(fromIndex, 0);
        gint count = length();
        if (fromIndex >= count) {
            return -1;
        }
        if (coding() == LATIN1) {
            if (Character::isValidCodePoint(ch) && StringUtils::isLatin1(ch)) {
                for (int i = count - 1; i >= 0; --i) {
                    gbyte c = (gbyte) StringUtils::readLatin1CharAt(value, i);
                    if (c == (gbyte) ch) {
                        return i;
                    }
                }
            }
        }
        else {
            if (Character::isValidCodePoint(ch) && StringUtils::isLatin1(ch)) {
                for (int i = count - 1; i >= 0; --i) {
                    gbyte c = (gbyte) StringUtils::readUTF16CharAt(value, i);
                    if (c == (gbyte) ch) {
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    gint String::indexOf(String const &str) const
    {
        return indexOf(str, 0);
    }

    gint String::indexOf(String const &str, gint fromIndex) const
    {
        gint count1 = length();
        gint count2 = str.length();
        fromIndex = Math::clamp(fromIndex, 0, count1);

        if (count2 > count1 - fromIndex) {
            return -1;
        }

        if (count2 == 0) {
            return fromIndex;
        }

        Coder coder = coding();
        if (coder == str.coding()) {
            if (coder == LATIN1) {
                gchar f = StringUtils::readLatin1CharAt(str.value, 0);
                gint count = count1 - count2;
                for (int i = fromIndex; i < count; ++i) {
                    gchar c1 = StringUtils::readLatin1CharAt(value, i);
                    // Look for first character.
                    if (c1 != f) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i + 1;
                    for (int k = 1; k < count2; ++k, ++j) {
                        c1 = StringUtils::readLatin1CharAt(value, j);
                        gchar c2 = StringUtils::readLatin1CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j == i + count2) {
                        // Found whole string.
                        return i;
                    }
                }
            }
            else {
                gchar f = StringUtils::readUTF16CharAt(str.value, 0);
                gint count = count1 - count2;
                for (int i = fromIndex; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    // Look for first character.
                    if (c1 != f) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i + 1;
                    for (int k = 1; k < count2; ++k, ++j) {
                        c1 = StringUtils::readUTF16CharAt(value, j);
                        gchar c2 = StringUtils::readUTF16CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j == i + count2) {
                        // Found whole string.
                        return i;
                    }
                }
            }
        }
        else {
            if (coder == LATIN1) {
                return -1;
            }
            else {
                gchar f = StringUtils::readLatin1CharAt(str.value, 0);
                gint count = count1 - count2;
                for (int i = fromIndex; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    // Look for first character.
                    if (c1 != f) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i + 1;
                    for (int k = 1; k < count2; ++k, ++j) {
                        c1 = StringUtils::readUTF16CharAt(value, j);
                        gchar c2 = StringUtils::readLatin1CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j == i + count2) {
                        // Found whole string.
                        return i;
                    }
                }
            }
        }
        return -1;
    }

    gint String::lastIndexOf(String const &str) const
    {
        return lastIndexOf(str, length() - 1);
    }

    gint String::lastIndexOf(String const &str, gint fromIndex) const
    {
        gint count1 = length();
        gint count2 = str.length();

        if (fromIndex > count1 - count2) {
            fromIndex = count1 - count2;
        }

        if (fromIndex < 0) {
            return -1;
        }

        if (count2 == 0) {
            return fromIndex;
        }

        Coder coder = coding();
        if (coder == str.coding()) {
            if (coder == LATIN1) {
                gchar l = StringUtils::readLatin1CharAt(str.value, count2 - 1);
                gint count = count1 - count2;
                for (int i = count1 - 1; i >= count; --i) {
                    gchar c1 = StringUtils::readLatin1CharAt(value, i);
                    // Look for last character.
                    if (c1 != l) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i - 1;
                    for (int k = count2 - 2; k >= 0; --k, --j) {
                        c1 = StringUtils::readLatin1CharAt(value, j);
                        gchar c2 = StringUtils::readLatin1CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j <= i - count2) {
                        // Found whole string.
                        return j + 1;
                    }
                }
            }
            else {
                gchar l = StringUtils::readUTF16CharAt(str.value, count2 - 1);
                gint count = count1 - count2;
                for (int i = count1 - 1; i >= count; --i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    // Look for last character.
                    if (c1 != l) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i - 1;
                    for (int k = count2 - 2; k >= 0; --k, --j) {
                        c1 = StringUtils::readUTF16CharAt(value, j);
                        gchar c2 = StringUtils::readUTF16CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j <= i - count2) {
                        // Found whole string.
                        return j + 1;
                    }
                }
            }
        }
        else {
            if (coder == LATIN1) {
                return -1;
            }
            else {
                gchar l = StringUtils::readLatin1CharAt(str.value, count2 - 1);
                gint count = count1 - count2;
                for (int i = count1 - 1; i >= count; --i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    // Look for last character.
                    if (c1 != l) {
                        continue;
                    }
                    // Found first character, now look at the rest of value
                    gint j = i - 1;
                    for (int k = count2 - 2; k >= 0; --k, --j) {
                        c1 = StringUtils::readUTF16CharAt(value, j);
                        gchar c2 = StringUtils::readLatin1CharAt(str.value, k);
                        if (c1 != c2) {
                            break;
                        }
                    }
                    if (j <= i - count2) {
                        // Found whole string.
                        return j + 1;
                    }
                }
            }
        }
        return -1;
    }

    String String::subString(gint beginIndex) const
    {
        try {
            return subString(beginIndex, length());
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String String::subString(gint beginIndex, gint endIndex) const
    {
        try {
            Precondition::checkIndexFromRange(beginIndex, endIndex, length());

            gint count1 = length();
            gint count2 = endIndex - beginIndex;

            if (count2 == count1) {
                return *this;
            }

            Coder coder = coding();

            String str;
            if (coder == LATIN1) {
                str.coder = LATIN1;
                str.value = StringUtils::copyOfLatin1(value, beginIndex, count2);
            }
            else {
                str.coder = UTF16;
                str.value = StringUtils::copyOfUTF16(value, beginIndex, count2);
            }
            str.count = count2;

            return str;
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    CharSequence &String::subSequence(gint startIndex, gint endIndex) const
    {
        try {
            return *new String(subString(startIndex, endIndex));
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String String::concat(String const &str) const
    {
        gint count1 = length();
        if (count1 == 0) {
            return str;
        }

        gint count2 = str.length();
        if (count2 == 0) {
            return *this;
        }

        gint count = count1 + count2;
        if (count < 0) {
            OutOfMemoryError("Overflow: String length out of range."_S).throws($ftrace(""_S));
        }

        Coder coder = coding();

        String newStr;
        if (coder == str.coding()) {
            if (coder == LATIN1) {
                newStr.coder = LATIN1;
                newStr.value = StringUtils::copyOfLatin1(value, 0, count1, count);
                StringUtils::copyLatin1(str.value, 0, newStr.value, count1, count2);
            }
            else {
                newStr.coder = UTF16;
                newStr.value = StringUtils::copyOfUTF16(value, 0, count1, count);
                StringUtils::copyUTF16(str.value, 0, newStr.value, count1, count2);
            }
        }
        else {
            newStr.coder = UTF16;
            if (coder == LATIN1) {
                newStr.value = StringUtils::copyOfLatin1ToUTF16(value, 0, count1, count);
                StringUtils::copyUTF16(str.value, 0, newStr.value, count1, count2);
            }
            else {
                newStr.value = StringUtils::copyOfUTF16(value, 0, count1, count);
                StringUtils::copyLatin1ToUTF16(str.value, 0, newStr.value, count1, count2);
            }
        }
        return newStr;
    }

    String String::replace(gchar oldChar, gchar newChar) const
    {
        gint count = length();
        if (count == 0) {
            return *this;
        }

        Coder coder = coding();
        if (coder == LATIN1 && StringUtils::isLatin1(oldChar)) {
            gint i = 0;
            for (i = 0; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                if (c == oldChar) {
                    break;
                }
            }

            if (i < count) {
                String str;
                if (StringUtils::isLatin1(newChar)) {
                    str.coder = LATIN1;
                    str.value = StringUtils::copyOfLatin1(value, 0, i, count);
                    for (; i < count; ++i) {
                        gchar c = StringUtils::readLatin1CharAt(value, i);
                        StringUtils::writeLatin1CharAt(str.value, i, (c == oldChar) ? newChar : c);
                    }
                }
                else {
                    str.coder = UTF16;
                    str.value = StringUtils::copyOfLatin1ToUTF16(value, 0, i, count);
                    for (; i < count; ++i) {
                        gchar c = StringUtils::readLatin1CharAt(value, i);
                        StringUtils::writeUTF16CharAt(str.value, i, (c == oldChar) ? newChar : c);
                    }
                }
                str.count = count;
                return str;
            }
        }
        else if (coder == UTF16) {
            gint i = 0;
            gbool isLatin = true;
            for (i = 0; i < count; ++i) {
                gchar c = StringUtils::readUTF16CharAt(value, i);
                if (c == oldChar) {
                    break;
                }
            }

            if (i < count) {
                String str;
                if (StringUtils::isLatin1(newChar)) {
                    str.coder = UTF16;
                    str.value = StringUtils::copyOfUTF16(value, 0, i, count);
                    for (; i < count; ++i) {
                        gchar c = StringUtils::readUTF16CharAt(value, i);
                        StringUtils::writeUTF16CharAt(str.value, i, (c == oldChar) ? newChar : c);
                    }
                    // try to inflate result
                    StringUtils::BYTES bytes = StringUtils::inflateUTF16ToLatin1(str.value, 0, count);
                    if (bytes != null) {
                        StringUtils::destroyUTF16String(str.value, count);
                        str.coder = LATIN1;
                        str.value = bytes;
                    }
                }
                else {
                    str.coder = UTF16;
                    str.value = StringUtils::copyOfUTF16(value, 0, i, count);
                    for (; i < count; ++i) {
                        gchar c = StringUtils::readUTF16CharAt(value, i);
                        StringUtils::writeUTF16CharAt(str.value, i, (c == oldChar) ? newChar : c);
                    }
                }
                str.count = count;
                return str;
            }
        }
        return *this;
    }

    gbool String::contains(CharSequence const &s) const
    {
        return (Class< String >::hasInstance(s))
               ? indexOf(CORE_XCAST(String const, s)) >= 0
               : indexOf(s.toString()) >= 0;
    }

    String String::replace(CharSequence const &target, CharSequence const &replacement) const
    {
        gint count1 = length();
        if (count1 == 0) {
            return *this;
        }

        String str1 = target.toString();
        gint count2 = target.length();

        String str2 = replacement.toString();
        gint count3 = replacement.length();

        try {
            if (count2 == 0) {
                gint count = Math::addExact(count1, Math::multiplyExact(Math::addExact(count1, 1), count3));
                XString str = XString(count);
                for (int i = 0; i < count1; ++i) {
                    str.append(str2).append(charAt(i));
                }
                str.append(str2);
                return str.toString();
            }
            else if (count2 == 1 && count3 == 1) {
                return replace(str1.charAt(0), str2.charAt(0));
            }
            else {
                Coder coder1 = coding();
                Coder coder2 = str1.coding();
                Coder coder3 = str2.coding();

                if (coder1 == LATIN1 && coder2 == LATIN1 && coder3 == LATIN1) {
                    gint i = 0;
                    if ((i = indexOf(str1)) < 0) {
                        return *this;
                    }

                    IntArray pos = IntArray(16);
                    gint p = 0;
                    pos[0] = i;
                    gint j = 0;
                    i += count2;
                    while ((j = indexOf(str1, i)) >= i) {
                        if (++p == pos.length()) {
                            IntArray pos2 = IntArray(p + (p >> 1));
                            for (int k = 0; k < p; ++k) {
                                pos2[k] = pos[k];
                            }
                            pos = CORE_CAST(IntArray &&, pos2);
                        }

                        pos[p] = j;
                        i = j + count2;
                    }

                    gint count = Math::addExact(count1, Math::multiplyExact(++p, count3 - count2));

                    if (count == 0) {
                        return ""_S;
                    }

                    String str;
                    str.coder = LATIN1;
                    str.value = StringUtils::newLatin1String(count);

                    i = j = 0;
                    for (int k = 0; k < p; ++k) {
                        gint next = pos[k];
                        StringUtils::copyLatin1(value, i, str.value, j, next - i);
                        j += next - i;
                        i = next;
                        StringUtils::copyLatin1(str2.value, 0, str.value, j, count3);
                        i += count2;
                        j += count3;
                    }
                    StringUtils::copyLatin1(value, i, str.value, j, count1 - i);
                    str.count = count;

                    return str;
                }
                else {

                    //  Possible combinations of the arguments/result encodings:
                    //  +---+--------+--------+--------+-----------------------+
                    //  | # | VALUE  | TARGET | REPL   | RESULT                |
                    //  +===+========+========+========+=======================+
                    //  | 1 | Latin1 | Latin1 |  UTF16 | null or UTF16         |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 2 | Latin1 |  UTF16 | Latin1 | null                  |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 3 | Latin1 |  UTF16 |  UTF16 | null                  |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 4 |  UTF16 | Latin1 | Latin1 | null or UTF16         |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 5 |  UTF16 | Latin1 |  UTF16 | null or UTF16         |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 6 |  UTF16 |  UTF16 | Latin1 | null, Latin1 or UTF16 |
                    //  +---+--------+--------+--------+-----------------------+
                    //  | 7 |  UTF16 |  UTF16 |  UTF16 | null or UTF16         |
                    //  +---+--------+--------+--------+-----------------------+
                    if (coder1 == LATIN1 && coder2 == UTF16) {
                        // combinations 2 or 3
                        return *this;
                    }

                    gint i = 0;
                    if ((i = indexOf(str1)) < 0) {
                        return *this;
                    }

                    IntArray pos = IntArray(16);
                    gint p = 0;
                    pos[0] = i;
                    gint j = 0;
                    i += count2;
                    while ((j = indexOf(str1, i)) >= i) {
                        if (++p == pos.length()) {
                            IntArray pos2 = IntArray(p + (p >> 1));
                            for (int k = 0; k < p; ++k) {
                                pos2[k] = pos[k];
                            }
                            pos = CORE_CAST(IntArray &&, pos2);
                        }

                        pos[p] = j;
                        i = j + count2;
                    }

                    gint count = Math::addExact(count1, Math::multiplyExact(++p, count3 - count2));

                    if (count == 0) {
                        return ""_S;
                    }

                    String str;
                    str.coder = UTF16;
                    str.value = StringUtils::newUTF16String(count);

                    i = j = 0;
                    for (int k = 0; k < p; ++k) {
                        gint next = pos[k];
                        if (coder1 == LATIN1) {
                            StringUtils::copyLatin1ToUTF16(value, i, str.value, j, next - i);
                        }
                        else {
                            StringUtils::copyUTF16(value, i, str.value, j, next - i);
                        }
                        j += next - i;
                        i = next;
                        if (coder3 == LATIN1) {
                            StringUtils::copyLatin1ToUTF16(str2.value, 0, str.value, j, count3);
                        }
                        else {
                            StringUtils::copyUTF16(str2.value, 0, str.value, j, count3);
                        }
                        i += count2;
                        j += count3;
                    }
                    if (coder1 == LATIN1) {
                        StringUtils::copyLatin1ToUTF16(value, i, str.value, j, count1 - i);
                    }
                    else {
                        StringUtils::copyUTF16(value, i, str.value, j, count1 - i);
                    }

                    if (coder2 == UTF16 && coder3 == LATIN1) {
                        // combination 6
                        // try to inflate result
                        StringUtils::BYTES bytes = StringUtils::inflateUTF16ToLatin1(str.value, 0, count);
                        if (bytes != null) {
                            StringUtils::destroyUTF16String(str.value, count);
                            str.coder = LATIN1;
                            str.value = bytes;
                        }
                    }

                    str.count = count;

                    return str;
                }
            }
        }
        catch (ArithmeticException const &ex) {
            OutOfMemoryError("Overflow: String required length exceed implementation limits"_S).throws($ftrace(""_S));
        }
    }

    String String::toLowerCase() const
    {
        gint count = length();
        gint coder = coding();

        String str;
        if (coder == LATIN1) {
            int i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                gchar c2 = CharacterDataLatin1::instance.toLowerCase(c);
                if (c != c2) {
                    break;
                }
            }
            if (i == count) {
                return *this;
            }
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, 0, i, count);
            for (int j = i; j < count; ++j) {
                gchar c = StringUtils::readLatin1CharAt(value, j);
                gchar c2 = CharacterDataLatin1::instance.toLowerCase(c);
                if (!StringUtils::isLatin1(c2)) {
                    // restart operation
                    StringUtils::destroyLatin1String(str.value, count);
                    str.value = StringUtils::copyOfLatin1ToUTF16(value, 0, i);
                    str.coder = UTF16;
                    for (int k = i; k < count; ++k) {
                        gchar c = StringUtils::readLatin1CharAt(value, j);
                        gchar c2 = CharacterDataLatin1::instance.toLowerCase(c);
                        StringUtils::writeUTF16CharAt(str.value, k, c2);
                    }
                    break;
                }
                StringUtils::writeLatin1CharAt(str.value, j, c2);
            }
            str.count = count;
        }
        else {
            int i = 0;
            for (; i < count;) {
                gint c = StringUtils::readUTF32CharAt(value, i);
                gint c2 = Character::toLowerCase(c);
                if (c != c2) {
                    break;
                }
                i += Character::charCount(c);
            }
            if (i == count) {
                return *this;
            }
            str.coder = LATIN1;
            str.value = StringUtils::copyOfUTF16(value, 0, i, count);
            gint k = 0;
            for (int j = i; j < count;) {
                gint c = StringUtils::readUTF32CharAt(value, j);
                gint c2 = Character::toLowerCase(c);
                if (Character::isSupplementary(c2)) {
                    StringUtils::writeUTF16CharAt(str.value, k + 0, Character::highSurrogate(c2));
                    StringUtils::writeUTF16CharAt(str.value, k + 1, Character::lowSurrogate(c2));
                    k += 2;
                }
                else {
                    StringUtils::writeUTF16CharAt(str.value, j + 1, (gchar) c2);
                    k += 1;
                }
                j += Character::charCount(c);
            }
            str.count = k;
        }
        return str;
    }

    String String::toUpperCase() const
    {
        gint count = length();
        gint coder = coding();

        String str;
        if (coder == LATIN1) {
            int i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                gchar c2 = CharacterDataLatin1::instance.toUpperCase(c);
                if (c != c2) {
                    break;
                }
            }
            if (i == count) {
                return *this;
            }
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, 0, i, count);
            for (int j = i; j < count; ++j) {
                gchar c = StringUtils::readLatin1CharAt(value, j);
                gchar c2 = CharacterDataLatin1::instance.toUpperCase(c);
                if (!StringUtils::isLatin1(c2)) {
                    // restart operation
                    StringUtils::destroyLatin1String(str.value, count);
                    str.value = StringUtils::copyOfLatin1ToUTF16(value, 0, i);
                    str.coder = UTF16;
                    for (int k = i; k < count; ++k) {
                        gchar c = StringUtils::readLatin1CharAt(value, j);
                        gchar c2 = CharacterDataLatin1::instance.toUpperCase(c);
                        StringUtils::writeUTF16CharAt(str.value, k, c2);
                    }
                    break;
                }
                StringUtils::writeLatin1CharAt(str.value, j, c2);
            }
            str.count = count;
        }
        else {
            int i = 0;
            for (; i < count;) {
                gint c = StringUtils::readUTF32CharAt(value, i);
                gint c2 = Character::toUpperCase(c);
                if (c != c2) {
                    break;
                }
                i += Character::charCount(c);
            }
            if (i == count) {
                return *this;
            }
            str.coder = LATIN1;
            str.value = StringUtils::copyOfUTF16(value, 0, i, count);
            gint k = 0;
            for (int j = i; j < count;) {
                gint c = StringUtils::readUTF32CharAt(value, j);
                gint c2 = Character::toUpperCase(c);
                if (Character::isSupplementary(c2)) {
                    StringUtils::writeUTF16CharAt(str.value, k + 0, Character::highSurrogate(c2));
                    StringUtils::writeUTF16CharAt(str.value, k + 1, Character::lowSurrogate(c2));
                    k += 2;
                }
                else {
                    StringUtils::writeUTF16CharAt(str.value, j + 1, (gchar) c2);
                    k += 1;
                }
                j += Character::charCount(c);
            }
            str.count = k;
        }
        return str;
    }

    String String::trim() const
    {
        gint count = length();
        Coder coder = coding();
        if (coder == LATIN1) {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                if (c > ' ') {
                    break;
                }
            }
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readLatin1CharAt(value, j - 1);
                if (c > ' ') {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
        else {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readUTF16CharAt(value, i);
                if (c > ' ') {
                    break;
                }
            }
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readUTF16CharAt(value, j - 1);
                if (c > ' ') {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
    }

    String String::strip() const
    {
        gint count = length();
        Coder coder = coding();
        if (coder == LATIN1) {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                if (c == ' ' || c == '\t' || !CharacterDataLatin1::instance.isWhitespace(c)) {
                    break;
                }
            }
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readLatin1CharAt(value, j - 1);
                if (c == ' ' || c == '\t' || !CharacterDataLatin1::instance.isWhitespace(c)) {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
        else {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readUTF16CharAt(value, i);
                if (c == ' ' || c == '\t' || !Character::isWhitespace(c)) {
                    break;
                }
            }
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readUTF16CharAt(value, j - 1);
                if (c == ' ' || c == '\t' || !Character::isWhitespace(c)) {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
    }

    String String::stripLeading() const
    {
        gint count = length();
        Coder coder = coding();
        if (coder == LATIN1) {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                if (c == ' ' || c == '\t' || !CharacterDataLatin1::instance.isWhitespace(c)) {
                    break;
                }
            }
            gint j = count;
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
        else {
            // skip all leading spaces
            gint i = 0;
            for (; i < count; ++i) {
                gchar c = StringUtils::readUTF16CharAt(value, i);
                if (c == ' ' || c == '\t' || !Character::isWhitespace(c)) {
                    break;
                }
            }
            gint j = count;
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
    }

    String String::stripTrailing() const
    {
        gint count = length();
        Coder coder = coding();
        if (coder == LATIN1) {
            // skip all leading spaces
            gint i = 0;
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readLatin1CharAt(value, j - 1);
                if (c == ' ' || c == '\t' || !CharacterDataLatin1::instance.isWhitespace(c)) {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
        else {
            // skip all leading spaces
            gint i = 0;
            // skip all trailing spaces
            gint j = count;
            for (; j > i; --j) {
                gchar c = StringUtils::readUTF16CharAt(value, j - 1);
                if (c == ' ' || c == '\t' || !Character::isWhitespace(c)) {
                    break;
                }
            }
            String str;
            str.coder = LATIN1;
            str.value = StringUtils::copyOfLatin1(value, i, j - i);
            return str;
        }
    }

    gbool String::isBlank() const
    {
        gint count = length();
        Coder coder = coding();
        gint i = 0;
        if (coder == LATIN1) {
            for (; i < count; ++i) {
                gchar c = StringUtils::readLatin1CharAt(value, i);
                if (c == ' ' || c == '\t' || !CharacterDataLatin1::instance.isWhitespace(c)) {
                    break;
                }
            }
        }
        else {
            for (; i < count; ++i) {
                gchar c = StringUtils::readUTF16CharAt(value, i);
                if (c == ' ' || c == '\t' || !Character::isWhitespace(c)) {
                    break;
                }
            }
        }
        return i == count;
    }

    String String::translateEscapes() const
    {
        gint count = length();
        Coder coder = coding();

        if (count == 0) {
            return ""_S;
        }

        CharArray ca = CharArray(count);
        gint i = 0;
        for (int j = 0; j < count;) {
            gchar c = charAt(j++);
            if (c == '\\') {
                c = j == count ? '\0' : charAt(j++);
                switch (c) {
                    case 'b':
                        c = '\b';
                        break;
                    case 'f':
                        c = '\f';
                        break;
                    case 'n':
                        c = '\n';
                        break;
                    case 'r':
                        c = '\r';
                        break;
                    case 's':
                        c = ' ';
                        break;
                    case '\'':
                    case '\"':
                    case '\\':
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7': {
                        gint n = Math::min(j + (c < '3' ? 2 : 1), count);
                        gint code = Character::digit(c, 8);
                        while (j < n) {
                            c = charAt(j);
                            gint d = Character::digit(c, 8);
                            if (d < 0) {
                                break;
                            }
                            j += 1;
                            code = code << 3 | d;
                        }
                        c = (gchar) code;
                        break;
                    }
                    case '\n':
                        continue;
                    case '\r':
                        if (j < count && charAt(j) == '\n') {
                            j += 1;
                        }
                        continue;
                    default:
                        IllegalArgumentException("Invalid escape sequence: \""_S + valueOf(c) + "\" (U+"_S
                                                 + Integer::toHexString(c) + ")"_S).throws($ftrace(""_S));
                }
            }
            ca[i++] = c;
        }
        return String(ca, 0, i);
    }

    String String::toString() const
    {
        return *this;
    }

    String String::valueOf(Object const &obj)
    {
        return obj.toString();
    }

    String String::valueOf(CharArray const &data, gint offset, gint count)
    {
        return String(data, offset, count);
    }

    String String::valueOf(gbool b)
    {
        return Boolean::toString(b);
    }

    String String::valueOf(gchar c)
    {
        return Character::toString(c);
    }

    String String::valueOf(gint i)
    {
        return Integer::toString(i);
    }

    String String::valueOf(glong l)
    {
        return Long::toString(l);
    }

    String String::valueOf(gfloat f)
    {
        return Float::toString(f);
    }

    String String::valueOf(gdouble d)
    {
        return Double::toString(d);
    }

    String String::repeat(gint nb) const
    {
        if (nb < 0) {
            IllegalArgumentException("Negative number of repetition"_S).throws($ftrace(""_S));
        }

        if (nb == 1) {
            return *this;
        }

        gint count = length();
        if (count == 0 || nb == 0) {
            return ""_S;
        }

        Coder coder = coding();

        try {
            gint count2 = Math::multiplyExact(count, nb);
            String str;
            if (coder == LATIN1) {
                str.coder = LATIN1;
                str.value = StringUtils::newLatin1String(count2);
                for (int i = 0; i < nb; ++i) {
                    StringUtils::copyLatin1(value, 0, str.value, count * i, count);
                }
            }
            else {
                str.coder = UTF16;
                str.value = StringUtils::newUTF16String(count2);
                for (int i = 0; i < nb; ++i) {
                    StringUtils::copyUTF16(value, 0, str.value, count * i, count);
                }
            }
            str.count = count2;
            return str;
        }
        catch (ArithmeticException const &ex) {
            OutOfMemoryError("Overflow: Required String length exceeds implementation limit"_S).throws($ftrace(""_S));
        }
    }

    String String::valueOf(CharArray const &data)
    {
        return valueOf(data, 0, data.length());
    }

    CharArray String::toChars() const
    {
        gint count = length();
        Coder coder = coding();

        CharArray ca = CharArray(count);
        if (coder == LATIN1) {
            StringUtils::copyLatin1ToUTF16(value, 0, ca.value, 0, count);
        }
        else {
            StringUtils::copyUTF16(value, 0, ca.value, 0, count);
        }
        return ca;
    }

    String String::mixedConcat(String::BYTES bytes, gint count2) const
    {
        gint count1 = length();
        Coder coder = coding();
        try {
            gint count = Math::addExact(count1, count2);

            String str;
            if (coder == LATIN1) {
                str.coder = LATIN1;
                str.value = StringUtils::copyOfLatin1(value, 0, count1, count);
                StringUtils::copyLatin1(bytes, 0, str.value, count, count2);
            }
            else {
                str.coder = UTF16;
                str.value = StringUtils::copyOfUTF16(value, 0, count1, count);
                StringUtils::copyLatin1ToUTF16(bytes, 0, str.value, count1, count2);
            }
            str.count = count;
            return str;
        }
        catch (ArithmeticException const &ex) {
            OutOfMemoryError("Overflow: Required String length exceed implementation limit."_S).throws($ftrace(""_S));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String String::mixedConcat(String::CHARS chars, gint count2) const
    {
        gint count1 = length();
        Coder coder = coding();

        try {
            gint count = Math::addExact(count1, count2);

            BYTES bytes = StringUtils::inflateUTF16ToLatin1(chars, 0, count2);
            if (bytes != null) {
                String str = mixedConcat(bytes, count2);
                StringUtils::destroyLatin1String(bytes, count2);
                return str;
            }

            String str;
            if (coder == LATIN1) {
                str.coder = UTF16;
                str.value = StringUtils::copyOfLatin1ToUTF16(value, 0, count1, count);
            }
            else {
                str.coder = UTF16;
                str.value = StringUtils::copyOfUTF16(value, 0, count1, count);
            }
            StringUtils::copyUTF16(bytes, 0, str.value, count1, count2);
            str.count = count;
            return str;
        }
        catch (ArithmeticException const &ex) {
            OutOfMemoryError("Overflow: Required String length exceed implementation limit."_S).throws($ftrace(""_S));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String String::mixedConcat(String::INTS codePoints, gint count2) const
    {
        gint count1 = length();
        Coder coder = coding();

        try {
            gint count = Math::addExact(count1, count2);

            BYTES bytes = StringUtils::inflateUTF32ToLatin1(codePoints, 0, count2);
            if (bytes != null) {
                String str = mixedConcat(bytes, count2);
                StringUtils::destroyLatin1String(bytes, count2);
                return str;
            }

            gint n = 0;
            for (int i = 0; i < count2; ++i) {
                gint c = codePoints[i];
                if (Character::isValidCodePoint(c) && Character::isSupplementary(c)) {
                    n += 2;
                }
                else {
                    n += 1;
                }
            }

            if (n > count2) {
                count = Math::addExact(count, n - count2);
            }

            String str;
            if (coder == LATIN1) {
                str.coder = UTF16;
                str.value = StringUtils::copyOfLatin1ToUTF16(value, 0, count1, count);
            }
            else {
                str.coder = UTF16;
                str.value = StringUtils::copyOfUTF16(value, 0, count1, count);
            }
            for (int i = 0, j = count1; i < count2; ++i) {
                gint c = codePoints[i];
                if (Character::isSupplementary(c)) {
                    gchar hi = Character::highSurrogate(c);
                    gchar lo = Character::lowSurrogate(c);
                    StringUtils::writeUTF16CharAt(str.value, j++, hi);
                    StringUtils::writeUTF16CharAt(str.value, j++, lo);
                }
                else {
                    StringUtils::writeUTF16CharAt(str.value, j++, (gchar) c);
                }
            }
            str.count = count;
            return str;
        }
        catch (ArithmeticException const &ex) {
            OutOfMemoryError("Overflow: Required String length exceed implementation limit."_S).throws($ftrace(""_S));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

} // core
