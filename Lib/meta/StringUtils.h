//
// Created by bruns on 10/05/2024.
//

#ifndef Core24_STRINGUTILS_H
#define Core24_STRINGUTILS_H

#include <core/String.h>

namespace core
{
    class String::StringUtils CORE_FINAL : public virtual Object
    {
    public:
        CORE_ALIAS(CHARS, Class<gchar>::Pointer);
        CORE_ALIAS(INTS, Class<gint>::Pointer);
        CORE_ALIAS(BYTES, Class<gbyte>::Pointer);

        static void copyLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count);

        static void copyLatin1ToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static void copyLatin1ToUTF16(BYTES val1, gint off1, CHARS val2, gint off2, gint count);

        static void copyLatin1ToUTF32(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static void copyLatin1ToUTF32(BYTES val1, gint off1, INTS val2, gint off2, gint count);

        static void copyUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static void copyUTF16(BYTES val1, gint off1, CHARS val2, gint off2, gint count);
        static void copyUTF16(CHARS val1, gint off1, BYTES val2, gint off2, gint count);

        static void copyUTF16ToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static void copyUTF16ToLatin1(CHARS val1, gint off1, BYTES val2, gint off2, gint count);

        static gint copyUTF16ToUTF32(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static gint copyUTF16ToUTF32(BYTES val1, gint off1, INTS val2, gint off2, gint count);
        static gint copyUTF16ToUTF32(CHARS val1, gint off1, BYTES val2, gint off2, gint count);
        static gint copyUTF16ToUTF32(CHARS val1, gint off1, INTS val2, gint off2, gint count);

        static BYTES copyOfLatin1(BYTES val, gint off, gint count);
        static BYTES copyOfLatin1(BYTES val, gint off, gint count, gint newLength);

        static BYTES copyOfUTF16(BYTES val, gint off, gint count);
        static BYTES copyOfUTF16(BYTES val, gint off, gint count, gint newLength);
        static BYTES copyOfUTF16(CHARS val, gint off, gint count);
        static BYTES copyOfUTF16(CHARS val, gint off, gint count, gint newLength);

        static BYTES copyOfLatin1ToUTF16(BYTES val, gint off, gint count);
        static BYTES copyOfLatin1ToUTF16(BYTES val, gint off, gint count, gint newLength);

        static BYTES copyOfUTF16ToLatin1(BYTES val, gint off, gint count);
        static BYTES copyOfUTF16ToLatin1(BYTES val, gint off, gint count, gint newLength);

        static BYTES copyOfUTF32ToUTF16(INTS val, gint off, gint count, gint& length);

        static BYTES newLatin1String(gint count);
        static BYTES newUTF16String(gint count);

        static gchar readLatin1CharAt(BYTES val, gint index);
        static gchar readLatin1CharAt(BYTES val, gint index, gint count);

        static gchar readUTF16CharAt(BYTES val, gint index);
        static gchar readUTF16CharAt(BYTES val, gint index, gint count);

        static gchar readLatin1CodePointAt(BYTES val, gint index);
        static gchar readLatin1CodePointAt(BYTES val, gint index, gint count);

        static gchar readUTF16CodePointAt(BYTES val, gint index);
        static gchar readUTF16CodePointAt(BYTES val, gint index, gint count);

        static BYTES inflateUTF16ToLatin1(BYTES val, gint off, gint count);
        static BYTES inflateUTF16ToLatin1(CHARS val, gint off, gint count);

        static BYTES inflateUTF32ToLatin1(INTS val, gint off, gint count);

        static void destoryLatin1String(BYTES val, gint count);
        static void destoryUTF16String(BYTES val, gint count);

        static void fillLatin1String(BYTES val, gint off, gint count, gchar value);
        static void fillUTF16String(BYTES val, gint off, gint count, gchar value);

        static void writeLatin1CharAt(BYTES val, gint index, gchar value);
        static void writeUTF16CharAt(BYTES val, gint index, gchar value);
        static void writeUTF16CharAt(BYTES val, gint index, gbyte b1, gbyte b2);

        static gbool isLatin1(gint ch);

        static gbool isHighSurrogate(gint ch);

        static gbool isLowSurrogate(gint ch);

        static gint toCodePoint(gchar high, gchar low);

        static gchar highSurrogate(gint codePoint);

        static gchar lowSurrogate(gint codePoint);

        static gbool isSupplementary(gint codePoint);

        static gint compareToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static gint compareToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static gint compareUTF16ToLatin1(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
        static gint compareLatin1ToUTF16(BYTES val1, gint off1, BYTES val2, gint off2, gint count);
    };
} // core

#endif // Core24_STRINGUTILS_H
