//
// Created by bruns on 10/05/2024.
//

#include <core/String.h>
#include <meta/StringUtils.h>

#include "misc/Precondition.h"

namespace core
{
    using namespace misc;

    String::Coder String::coding() const
    {
        return COMPACT_STRINGS && coder == LATIN1 ? LATIN1 : UTF16;
    }

    String::String()
    {
        coder      = COMPACT_STRINGS ? LATIN1 : UTF16;
        value      = StringUtils::newLatin1String(0);
        count      = 0;
        hashValue  = 0;
        hashIsZero = false;
    }

    String::String(String const& original): String()
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
        count      = length;
        hashValue  = original.hashValue;
        hashIsZero = original.hashIsZero;
    }

    String::String(String&& original) CORE_NOTHROW : String()
    {
        value      = original.value;
        count      = original.count;
        hashValue  = original.hashValue;
        hashIsZero = original.hashIsZero;

        original.count      = 0;
        original.value      = null;
        original.hashValue  = 0;
        original.hashIsZero = true;
    }

    String::String(CharArray const& value): String(value, 0, value.length())
    {
    }

    String::String(CharArray const& value, gint offset, gint count): String()
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

    String::String(IntArray const& codePoints, gint offset, gint count): String()
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

    String::String(ByteArray const& ascii, gint hibyte, gint offset, gint count): String()
    {
        Precondition::checkIndexFromSize(offset, count, ascii.length());

        if (count > 0) {
            if (COMPACT_STRINGS && hibyte == 0) {
                value         = StringUtils::copyOfLatin1(ascii.value, offset, count);
                String::coder = LATIN1;
            }
            else {
                value         = StringUtils::newUTF16String(count);
                String::coder = UTF16;
                for (int i = 0; i < count; ++i) {
                    StringUtils::writeUTF16CharAt(value, i, (gbyte) (hibyte & 0xff), ascii.value[i]);
                }
            }
            String::count = count;
        }
    }

    String::String(ByteArray const& ascii, gint hibyte): String(ascii, hibyte, 0, ascii.length())
    {
    }

    String& String::operator=(String const& other)
    {
        if (this != &other) {
            gint  length = other.count;
            BYTES bytes  = other.coding() == LATIN1
                              ? StringUtils::copyOfLatin1(other.value, 0, length)
                              : StringUtils::copyOfUTF16(other.value, 0, length);
            coder == LATIN1
                ? StringUtils::destoryLatin1String(value, count)
                : StringUtils::destoryUTF16String(value, count);
            count = 0;

            value      = bytes;
            count      = length;
            hashIsZero = other.hashIsZero;
            hashValue  = other.hashValue;
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

    void String::toChars(gint beginIndex, gint endIndex, CharArray& dest, gint offset)
    {
        Precondition::checkIndexFromRange(beginIndex, endIndex, count);
        Precondition::checkIndexFromSize(offset, endIndex - beginIndex, dest.length());

        coding() == LATIN1
            ? StringUtils::copyLatin1ToUTF16(value, beginIndex, dest.value, offset, endIndex - beginIndex)
            : StringUtils::copyUTF16(value, beginIndex, dest.value, offset, endIndex - beginIndex);
    }

    void String::toBytes(gint beginIndex, gint endIndex, ByteArray& dest, gint offset)
    {
        Precondition::checkIndexFromRange(beginIndex, endIndex, count);
        Precondition::checkIndexFromSize(offset, endIndex - beginIndex, dest.length());

        coding() == LATIN1
            ? StringUtils::copyLatin1(value, beginIndex, dest.value, offset, endIndex - beginIndex)
            : StringUtils::copyUTF16ToLatin1(value, beginIndex, dest.value, offset, endIndex - beginIndex);
    }

    gbool String::equals(Object const& obj) const
    {
        if (this == &obj)
            return true;
        else if (!Class<String>::hasInstance(obj))
            return false;
        else {
            String const& other = CORE_XCAST(String const, obj);
            Coder const   coder = coding();
            gint const    count = length();

            if (count != other.length() || coder != other.coding()) {
                return false;
            }

            return coder == LATIN1
                       ? StringUtils::compareToLatin1(value, 0, other.value, 0, count)
                       : StringUtils::compareToUTF16(value, 0, other.value, 0, count);
        }
    }

    gint String::compareTo(String const& other) const
    {
        Coder coder  = coding();
        gint  count1 = length();
        gint  count2 = other.length();

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
        if (count > 0) {
            coder == LATIN1
                ? StringUtils::destoryLatin1String(value, count)
                : StringUtils::destoryUTF16String(value, count);
            count = 0;
            value = StringUtils::newLatin1String(0);
            coder = COMPACT_STRINGS ? LATIN1 : UTF16;
        }
    }
} // core
