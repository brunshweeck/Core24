//
// Created by brunshweeck on 29 mai 2024.
//

#include <core/XString.h>
#include <core/Math.h>
#include <core/IllegalArgumentException.h>
#include <core/misc/Foreign.h>
#include <core/misc/Precondition.h>
#include <core/OutOfMemoryError.h>
#include <meta/StringUtils.h>

namespace core
{

    using misc::Precondition;
    using misc::Foreign;

    XString::Coder XString::coding() const
    {
        return String::COMPACT_STRINGS && (coder == String::LATIN1)
               ? String::LATIN1
               : String::UTF16;
    }

    XString::XString() : XString(16)
    {
    }

    XString::XString(gint capacity) : value(), count(), limit(), coder(), maybeLatin1(false)
    {
        if (capacity < 0) {
            IllegalArgumentException("Negative capacity."_S).throws($ftrace(""_S));
        }

        if (String::COMPACT_STRINGS) {
            coder = String::LATIN1;
            value = StringUtils::newLatin1String(16);
        }
        else {
            coder = String::UTF16;
            value = StringUtils::newUTF16String(16);
        }
        limit = 16;
        count = 0;
    }

    XString::XString(String const &str) : value(), count(), limit(), coder(), maybeLatin1(false)
    {
        gint length = str.length();
        gint capacity = (length < Integer::MAX_VALUE - 16)
                        ? length + 16
                        : Integer::MAX_VALUE;

        Coder coder = str.coding();
        gint count = str.length() + 16;
        if (count < 0)
            count = Integer::MAX_VALUE;

        if (coder == String::LATIN1) {
            XString::coder = String::LATIN1;
            XString::value = StringUtils::newLatin1String(count);
        }
        else {
            XString::coder = String::UTF16;
            XString::value = StringUtils::newUTF16String(count);
        }
        XString::limit = count;
        XString::count = 0;
        XString::append(str);
    }

    XString::XString(CharSequence const &seq) : value(), count(), limit(), coder(), maybeLatin1(false)
    {
        gint count = seq.length();

        if (count < 0) {
            IllegalArgumentException("Negative String length."_S).throws($ftrace(""_S));
        }

        count += 16;
        if (count < 0) {
            count = Integer::MAX_VALUE;
        }

        Coder coder;
        gbool maybeLatin1 = false;
        if (Class< XString >::hasInstance(seq)) {
            XString const &str = CORE_XCAST(XString const, seq);
            coder = str.coding();
            maybeLatin1 |= String::COMPACT_STRINGS && str.maybeLatin1;
        }
        else if (Class< String >::hasInstance(seq)) {
            coder = CORE_XCAST(String const, seq).coding();
        }
        else {
            coder = String::COMPACT_STRINGS ? String::LATIN1 : String::UTF16;
        }
        if (coder == String::LATIN1) {
            XString::coder = String::LATIN1;
            XString::value = StringUtils::newLatin1String(count);
        }
        else {
            XString::coder = String::UTF16;
            XString::value = StringUtils::newUTF16String(count);
        }
        XString::limit = count;
        XString::append(seq);
    }

    gint XString::compareTo(XString const &another) const
    {
        gint count1 = length();
        gint count2 = another.length();
        gint count = Math::min(count1, count2);
        Coder coder = coding();

        if (coder == another.coding()) {
            if (coder == String::LATIN1) {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readLatin1CharAt(value, i);
                    gchar c2 = StringUtils::readLatin1CharAt(another.value, i);
                    if (c1 != c2) {
                        return c1 - c2;
                    }
                }
                if (count1 == count2) {
                    return 0;
                }
                else if (count1 < count2) {
                    for (int i = count1; i < count2; ++i) {
                        gchar c2 = StringUtils::readLatin1CharAt(another.value, i);
                        if (c2 != 0) {
                            return -c2;
                        }
                    }
                }
                else {
                    for (int i = count2; i < count1; ++i) {
                        gchar c1 = StringUtils::readLatin1CharAt(value, i);
                        if (c1 != 0) {
                            return c1;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    gchar c2 = StringUtils::readUTF16CharAt(another.value, i);
                    if (c1 != c2) {
                        return c1 - c2;
                    }
                }
                if (count1 == count2) {
                    return 0;
                }
                else if (count1 < count2) {
                    for (int i = count1; i < count2; ++i) {
                        gchar c2 = StringUtils::readUTF16CharAt(another.value, i);
                        if (c2 != 0) {
                            return -c2;
                        }
                    }
                }
                else {
                    for (int i = count2; i < count1; ++i) {
                        gchar c1 = StringUtils::readUTF16CharAt(value, i);
                        if (c1 != 0) {
                            return c1;
                        }
                    }
                }
            }
        }
        else {
            if (coder == String::LATIN1) {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readLatin1CharAt(value, i);
                    gchar c2 = StringUtils::readUTF16CharAt(another.value, i);
                    if (c1 != c2) {
                        return c1 - c2;
                    }
                }
                if (count1 == count2) {
                    return 0;
                }
                else if (count1 < count2) {
                    for (int i = count1; i < count2; ++i) {
                        gchar c2 = StringUtils::readUTF16CharAt(another.value, i);
                        if (c2 != 0) {
                            return -c2;
                        }
                    }
                }
                else {
                    for (int i = count2; i < count1; ++i) {
                        gchar c1 = StringUtils::readLatin1CharAt(value, i);
                        if (c1 != 0) {
                            return c1;
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < count; ++i) {
                    gchar c1 = StringUtils::readUTF16CharAt(value, i);
                    gchar c2 = StringUtils::readLatin1CharAt(another.value, i);
                    if (c1 != c2) {
                        return c1 - c2;
                    }
                }
                if (count1 == count2) {
                    return 0;
                }
                else if (count1 < count2) {
                    for (int i = count1; i < count2; ++i) {
                        gchar c2 = StringUtils::readLatin1CharAt(another.value, i);
                        if (c2 != 0) {
                            return -c2;
                        }
                    }
                }
                else {
                    for (int i = count2; i < count1; ++i) {
                        gchar c1 = StringUtils::readUTF16CharAt(value, i);
                        if (c1 != 0) {
                            return c1;
                        }
                    }
                }
            }
        }
        return count1 - count2;
    }

    gint XString::length() const
    {
        return count == 0 || value == null || limit < count ? 0 : count;
    }

    gint XString::capacity() const
    {
        return limit == 0 || limit < count || value == null ? 0 : limit;
    }

    void XString::ensureCapacity(gint minLimit)
    {
        try {
            gint oldLimit = capacity();
            gint count = length();
            Coder coder = coding();
            if (minLimit - oldLimit > 0) {
                gint newLimit = newCapacity(minLimit);
                if (coder == String::LATIN1) {
                    ARRAY newValue = StringUtils::copyOfLatin1(value, 0, count, newLimit);
                    XString::count = 0;
                    StringUtils::destroyLatin1String(value, count);
                    XString::value = newValue;
                }
                else {
                    ARRAY newValue = StringUtils::copyOfUTF16(value, 0, count, newLimit);
                    XString::count = 0;
                    StringUtils::destroyUTF16String(value, count);
                    XString::value = newValue;
                }
                XString::limit = newLimit;
                XString::count = count;
            }
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint XString::newCapacity(gint minLimit) const
    {
        gint oldLimit = capacity();
        gint count = length();
        Coder coder = coding();
        minLimit = Math::max(minLimit, 0);

        gint minGrowth = minLimit - oldLimit;
        gint prefGrowth = oldLimit + (2 << coder);

        gint prefLimit = oldLimit + Math::max(minGrowth, prefGrowth);
        if (prefLimit < 0 || prefLimit > SOFT_MAX_LENGTH) {
            // Huge limit
            prefLimit = oldLimit + minLimit;
            if (prefLimit < 0) {
                OutOfMemoryError("Overflow: Required String length exceed implementation limit"_S).throws(
                        $ftrace(""_S));
            }
            if (prefLimit < SOFT_MAX_LENGTH) {
                prefLimit = SOFT_MAX_LENGTH;
            }
        }

        return prefLimit;
    }

    void XString::trimToSize()
    {
        gint limit = capacity();
        gint count = length();
        Coder coder = coding();
        if (count < limit) {
            if (coder == String::LATIN1) {
                ARRAY a = StringUtils::copyOfLatin1(value, 0, count);
                XString::count = 0;
                StringUtils::destroyLatin1String(value, count);

                XString::value = a;
                XString::limit = XString::count = count;
            }
            else {
                ARRAY a = StringUtils::copyOfUTF16(value, 0, count);
                XString::count = 0;
                StringUtils::destroyUTF16String(value, count);

                XString::value = a;
                XString::limit = XString::count = count;
            }
        }
    }

    void XString::setLength(gint newLength)
    {
        if (newLength < 0) {
            IllegalArgumentException("Negative String length"_S).throws($ftrace(""_S));
        }

        gint limit = capacity();
        gint count = length();
        Coder coder = coding();

        try {
            if (count < newLength) {
                ensureCapacity(newLength);
                if (coder == String::LATIN1) {
                    StringUtils::fillLatin1String(value, count, newLength - count, 0);
                }
                else {
                    StringUtils::fillUTF16String(value, count, newLength - count, 0);
                }
                XString::count = newLength;
            }
            else if (count > newLength) {
                XString::maybeLatin1 = true;
                StringUtils::fillUTF16String(value, newLength, count - newLength, 0);
            }
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gchar XString::charAt(gint index) const
    {
        gint count = length();
        Coder coder = coding();
        try {
            Precondition::checkIndex(index, count);
            if (coder == String::LATIN1) {
                return StringUtils::readLatin1CharAt(value, index);
            }
            else {
                return StringUtils::readUTF16CharAt(value, index);
            }
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint XString::codePointAt(gint index) const
    {
        gint count = length();
        Coder coder = coding();
        try {
            Precondition::checkIndex(index, count);
            if (coder == String::LATIN1) {
                return StringUtils::readLatin1CodePointAt(value, index);
            }
            else {
                return StringUtils::readUTF16CodePointAt(value, index);
            }
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    void XString::toChars(gint srcBegin, gint srcEnd, CharArray &dst, gint dstBegin) const
    {
        gint count = length();
        Coder coder = coding();
        gint count2 = srcEnd - srcBegin;
        try {
            Precondition::checkIndexFromRange(srcBegin, srcEnd, count);
            Precondition::checkIndexFromSize(dstBegin, count2, dst.length());

            if (coder == String::LATIN1) {
                StringUtils::copyLatin1ToUTF16(value, srcBegin, dst.value, dstBegin, count2);
            }
            else {
                StringUtils::copyUTF16(value, srcBegin, dst.value, dstBegin, count2);
            }
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    void XString::setCharAt(gint index, gchar ch)
    {
        gint count = length();
        Coder coder = coding();
        try {
            Precondition::checkIndex(index, count);
            if (coder == String::LATIN1) {
                StringUtils::writeLatin1CharAt(value, index, ch);
            }
            else {
                StringUtils::writeUTF16CharAt(value, index, ch);
            }
        }
        catch (Exception const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(Object const &obj)
    {
        try {
            return append(String::valueOf(obj));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(String const &str)
    {
        try {
            return append(str, 0, str.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(XString const &str)
    {
        try {
            return append(str, 0, str.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(CharSequence const &s)
    {
        try {
            return append(s, 0, s.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(CharSequence const &s, gint start, gint end)
    {
        gint count = length();
        Coder coder = coding();
        gint count2 = end - start;
        try {
            Precondition::checkIndexFromRange(start, end, s.length());
            ensureCapacity(count + count2);
            gint limit = capacity();

            if (Class< String >::hasInstance(s)) {
                String const &str = CORE_XCAST(String const, s);
                if (coder == str.coding()) {
                    if (coder == String::LATIN1) {
                        StringUtils::copyLatin1(str.value, start, value, count, count2);
                    }
                    else {
                        StringUtils::copyUTF16(str.value, start, value, count, count2);
                    }
                }
                else {
                    if (coder == String::LATIN1) {
                        // Convert to UTF16
                        ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count, limit);
                        StringUtils::copyUTF16(str.value, start, a, count, count2);

                        XString::count = 0;
                        StringUtils::destroyLatin1String(value, count);

                        XString::value = a;
                    }
                    else {
                        StringUtils::copyLatin1ToUTF16(str.value, start, value, count, count2);
                    }
                }
            }
            else if (Class< XString >::hasInstance(s)) {
                XString const &str = CORE_XCAST(XString const, s);
                if (coder == str.coding()) {
                    if (coder == String::LATIN1) {
                        StringUtils::copyLatin1(str.value, start, value, count, count2);
                    }
                    else {
                        StringUtils::copyUTF16(str.value, start, value, count, count2);
                    }
                }
                else {
                    if (coder == String::LATIN1) {
                        // Convert to UTF16
                        ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count, limit);
                        StringUtils::copyUTF16(str.value, start, a, count, count2);

                        XString::count = 0;
                        StringUtils::destroyLatin1String(value, count);

                        XString::value = a;
                    }
                    else {
                        StringUtils::copyLatin1ToUTF16(str.value, start, value, count, count2);
                    }
                }
                XString::maybeLatin1 |= str.maybeLatin1;
            }
            else {
                // Appends characters
                if (coder == String::LATIN1) {
                    for (int i = 0; i < count2; ++i) {
                        gchar c = s.charAt(start + i);
                        if (!StringUtils::isLatin1(c)) {
                            // Convert to UTF16
                            ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count + i, limit);
                            for (int j = i; j < count2; ++j) {
                                gchar c = s.charAt(start + j);
                                StringUtils::writeUTF16CharAt(value, count + j, c);
                            }

                            XString::count = 0;
                            StringUtils::destroyLatin1String(value, count + i);
                            break;
                        }
                        StringUtils::writeLatin1CharAt(value, count + i, c);
                    }
                }
                else {
                    for (int i = 0; i < count2; ++i) {
                        gchar c = s.charAt(start + i);
                        StringUtils::writeUTF16CharAt(value, count + i, c);
                    }
                }
            }

            XString::count = count + count2;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(CharArray const &str)
    {
        try {
            return append(str, 0, str.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(CharArray const &str, gint offset, gint len)
    {
        gint count = length();
        Coder coder = coding();
        try {
            Precondition::checkIndexFromSize(offset, len, str.length());
            ensureCapacity(count + len);
            if (coder == String::LATIN1) {
                for (int i = 0; i < len; ++i) {
                    gchar c = str[offset + i];
                    if (!StringUtils::isLatin1(c)) {
                        // Convert to UTF16
                        ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count + i, limit);
                        for (int j = i; j < len; ++j) {
                            gchar c = str[offset + j];
                            StringUtils::writeUTF16CharAt(value, count + j, c);
                        }

                        XString::count = 0;
                        StringUtils::destroyLatin1String(value, count + i);
                        break;
                    }
                    StringUtils::writeLatin1CharAt(value, count + i, c);
                }
            }
            else {
                StringUtils::copyUTF16(str.value, offset, value, count, len);
            }
            XString::count = count + len;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(gbool b)
    {
        gint count = length();
        Coder coder = coding();
        try {
            if (b) {
                ensureCapacity(count + 4);
                if (coder == String::LATIN1) {
                    StringUtils::writeLatin1CharAt(value, count + 0, 't');
                    StringUtils::writeLatin1CharAt(value, count + 1, 'r');
                    StringUtils::writeLatin1CharAt(value, count + 2, 'u');
                    StringUtils::writeLatin1CharAt(value, count + 3, 'e');
                }
                else {
                    StringUtils::writeUTF16CharAt(value, count + 0, 't');
                    StringUtils::writeUTF16CharAt(value, count + 1, 'r');
                    StringUtils::writeUTF16CharAt(value, count + 2, 'u');
                    StringUtils::writeUTF16CharAt(value, count + 3, 'e');
                }
            }
            else {
                ensureCapacity(count + 5);
                if (coder == String::LATIN1) {
                    StringUtils::writeLatin1CharAt(value, count + 0, 'f');
                    StringUtils::writeLatin1CharAt(value, count + 1, 'a');
                    StringUtils::writeLatin1CharAt(value, count + 2, 'l');
                    StringUtils::writeLatin1CharAt(value, count + 3, 's');
                    StringUtils::writeLatin1CharAt(value, count + 3, 'e');
                }
                else {
                    StringUtils::writeUTF16CharAt(value, count + 0, 'f');
                    StringUtils::writeUTF16CharAt(value, count + 1, 'a');
                    StringUtils::writeUTF16CharAt(value, count + 2, 'l');
                    StringUtils::writeUTF16CharAt(value, count + 3, 's');
                    StringUtils::writeUTF16CharAt(value, count + 3, 'e');
                }
            }
            XString::count = count + 5;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(gchar c)
    {
        gint count = length();
        Coder coder = coding();
        try {
            ensureCapacity(count + 1);
            gint limit = capacity();
            if (coder == String::LATIN1) {
                if (!StringUtils::isLatin1(c)) {
                    ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count, limit);
                    StringUtils::writeUTF16CharAt(a, count, c);

                    XString::count = 0;
                    StringUtils::destroyLatin1String(value, count);

                    XString::value = a;
                }
                else {
                    StringUtils::writeLatin1CharAt(value, count, c);
                }
            }
            else {
                StringUtils::writeUTF16CharAt(value, count, c);
            }
            XString::count = count + 1;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(gint i)
    {
        try {
            return append(String::valueOf(i));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(glong l)
    {
        try {
            return append(String::valueOf(l));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(gfloat f)
    {
        try {
            return append(String::valueOf(f));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::append(gdouble d)
    {
        try {
            return append(String::valueOf(d));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::remove(gint start, gint end)
    {
        gint count = length();
        Coder coder = coding();
        if (end > count) {
            end = count;
        }
        gint count2 = end - start;
        try {
            Precondition::checkIndexFromRange(start, end, count);
            if (count2 > 0) {
                if (coder == String::LATIN1) {
                    StringUtils::copyLatin1(value, end, value, start, count - end);
                    StringUtils::fillLatin1String(value, count - end, count2, 0);
                }
                else {
                    StringUtils::copyUTF16(value, end, value, start, count - end);
                    StringUtils::fillUTF16String(value, count - end, count2, 0);
                }
                XString::count = count - count2;
                XString::maybeLatin1 = true;
            }
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::appendCodePoint(gint codePoint)
    {
        try {
            if (Character::isBmpCodePoint(codePoint)) {
                return append((gchar) codePoint);
            }
            else {
                return append(Character::toChars(codePoint));
            }
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::deleteCharAt(gint index)
    {
        gint count = length();
        try {
            Precondition::checkIndex(index, count);
            gchar c = charAt(index);
            remove(index, index + 1);
            XString::maybeLatin1 = !StringUtils::isLatin1(c);
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::replace(gint start, gint end, String const &str)
    {
        gint count = length();
        Coder coder = coding();
        gint count2 = end - start;
        gint count3 = str.length();

        try {
            Precondition::checkIndexFromRange(start, end, count);
            if (count3 == 0) {
                return remove(start, end);
            }

            gint count4 = count3 - count2;
            ensureCapacity(count + count4);
            // Shift trailing characters
            if (count4 != 0) {
                if (coder == String::LATIN1) {
                    StringUtils::copyLatin1(value, end, value, end + count4, count4);
                }
                else {
                    StringUtils::copyUTF16(value, end, value, end + count4, count4);
                }
            }
            // Insert string characters
            if (coder == str.coding()) {
                if (coder == String::LATIN1) {
                    StringUtils::copyLatin1(str.value, 0, value, start, count3);
                }
                else {
                    StringUtils::copyUTF16(str.value, 0, value, start, count3);
                }
            }
            else {
                if (coder == String::LATIN1) {
                    // Convert to UTF16
                    ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count, limit);
                    StringUtils::copyUTF16(str.value, 0, a, start, count3);

                    XString::count = 0;
                    StringUtils::destroyLatin1String(value, count);

                    XString::value = a;
                }
                else {
                    StringUtils::copyLatin1ToUTF16(str.value, 0, value, start, count3);
                }
            }

            XString::count = count + count4;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String XString::subString(gint start) const
    {
        try {
            return subString(start, count);
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    CharSequence &XString::subSequence(gint start, gint end) const
    {
        try {
            return *new String(subString(start, end));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    String XString::subString(gint start, gint end) const
    {
        gint count = length();
        Coder coder = coding();
        gint count2 = end - start;
        try {
            Precondition::checkIndexFromRange(start, end, count);
            String str;
            if (coder == String::LATIN1) {
                str.coder = String::LATIN1;
                str.value = StringUtils::copyOfLatin1(value, start, count2);
            }
            else {
                if (XString::maybeLatin1) {
                    str.coder = String::LATIN1;
                    str.value = StringUtils::inflateUTF16ToLatin1(value, start, count2);
                    if (value != null) {
                        str.count = count2;
                        return str;
                    }
                }
                else {
                    str.coder = String::UTF16;
                    str.value = StringUtils::copyOfUTF16(value, start, count2);
                }
            }
            str.count = count2;
            return str;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint index, CharArray const &str, gint offset, gint len)
    {
        gint count = length();
        Coder coder = coding();
        try {
            Precondition::checkIndexFromSize(index, len, count);
            Precondition::checkIndexFromSize(offset, len, str.length());
            ensureCapacity(count + len);
            if (coder == String::LATIN1) {
                // Shift
                StringUtils::copyLatin1(value, index, value, index + len, count - index);
                // Insert
                for (int i = 0; i < len; ++i) {
                    gchar c = str[offset + i];
                    if (!StringUtils::isLatin1(c)) {
                        // Convert to UTF16
                        ARRAY a = StringUtils::copyOfLatin1ToUTF16(value, 0, count + len, limit);
                        for (int j = i; j < len; ++j) {
                            gchar c = str[offset + j];
                            StringUtils::writeUTF16CharAt(value, index + j, c);
                        }

                        XString::count = 0;
                        StringUtils::destroyLatin1String(value, count + len);
                        XString::value = a;
                        break;
                    }
                    StringUtils::writeLatin1CharAt(value, index + i, c);
                }
            }
            else {
                // Shift
                StringUtils::copyUTF16(value, index, value, index + len, count - index);
                // Insert
                StringUtils::copyUTF16(str.value, offset, value, index, len);
            }
            XString::count = count + len;
            return *this;
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint index, Object const &obj)
    {
        try {
            return insert(index, String::valueOf(obj));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint index, String const &str)
    {
        try {
            return insert(index, str, 0, str.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint offset, CharArray const &str)
    {
        try {
            return insert(offset, str, 0, str.length());
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint dstOffset, CharSequence const &s)
    {
        try {
            return insert(dstOffset, s, 0, s.length());
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    XString &XString::insert(gint dstOffset, CharSequence const &s, gint start, gint end)
    {
        // RAS
    }

    XString &XString::insert(gint offset, gbool b)
    {
        try {
            return insert(offset, String::valueOf(b));
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    XString &XString::insert(gint offset, gchar c)
    {
        try {
            return insert(offset, String::valueOf(c));
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    XString &XString::insert(gint offset, gint i)
    {
        try {
            return insert(offset, String::valueOf(i));
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    XString &XString::insert(gint offset, glong l)
    {
        try {
            return insert(offset, String::valueOf(l));
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    XString &XString::insert(gint offset, gfloat f)
    {
        try {
            return insert(offset, String::valueOf(f));
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    XString &XString::insert(gint offset, gdouble d)
    {
        try {
            return insert(offset, String::valueOf(d));
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    gint XString::indexOf(String const &str) const
    {
        try {
            return indexOf(str, 0);
        }
        catch (Throwable const &ex) {
            ex.throws($ftrace(""_S));
        }
    }

    gint XString::indexOf(String const &str, gint fromIndex) const
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
            if (coder == String::LATIN1) {
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
            if (coder == String::LATIN1) {
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

    gint XString::lastIndexOf(String const &str) const
    {
        try {
            return lastIndexOf(str, count);
        }
        catch (Throwable const &ex) { ex.throws($ftrace(""_S)); }
    }

    gint XString::lastIndexOf(String const &str, gint fromIndex) const
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
            if (coder == String::LATIN1) {
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
            if (coder == String::LATIN1) {
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

    XString &XString::reverse()
    {
        gint count = length() >> 1;
        Coder coder = coding();

        if (coder == String::LATIN1) {
            for (int i = 0, j = count-1; i < count; ++i, --j) {
                gchar c01 = StringUtils::readLatin1CharAt(value, i);
                gchar c10 = StringUtils::readLatin1CharAt(value, j);

                StringUtils ::readLatin1CharAt(value, i, c10);
                StringUtils ::readLatin1CharAt(value, j, c01);
            }
        }
        else {
            for (int i = 0, j = count-1; i < count; ++i, --j) {
                gchar c01 = StringUtils::readLatin1CharAt(value, i);
                gchar c10 = StringUtils::readLatin1CharAt(value, j);

                StringUtils ::readLatin1CharAt(value, i, c10);
                StringUtils ::readLatin1CharAt(value, j, c01);
            }
        }

        return *this;
    }

    String XString::toString() const
    {
        gint count = length();
        Coder coder = coding();
        gbool maybeLatin1 = XString::maybeLatin1;

        String str;
        if(coder == String::LATIN1) {
            str.coder = String::LATIN1;
            str.value = StringUtils::copyOfLatin1(value, 0, count);
        }else {
            if(String::COMPACT_STRINGS && maybeLatin1) {
                str.coder = String::LATIN1;
                str.value = StringUtils::inflateUTF16ToLatin1(value, 0, count);
                if(value != null) {
                    goto End;
                }
            }
            str.coder = String::UTF16;
            str.value = StringUtils::copyOfUTF16(value, 0, count);
        }
        End:
        str.count = count;
        return str;
    }

} // core