//
// Created by brunshweeck on 26 mai 2024.
//

#include "Foreign.h"
#include <meta/StringUtils.h>
#include <core/Math.h>
#include <core/Integer.h>
#include <core/Long.h>
#include <core/Float.h>
#include <core/Double.h>

namespace core
{
    namespace misc
    {
        Foreign::Foreign()
        {
        }

        String Foreign::strLatin1(glong ptr, glong offset, glong count)
        {
            CORE_ALIAS(BYTES, Class<gbyte>::Pointer);
            CORE_ALIAS(Utils, String::StringUtils);
            String str;
            BYTES bytes = CORE_CAST(BYTES, ptr);
            if (bytes != null && offset >= 0 && count > 0) {
                gint len = Math::clamp(count, 0, Integer::MAX_VALUE - 8);
                if (String::COMPACT_STRINGS) {
                    str.value = Utils::copyOfLatin1(bytes, (gint) offset, len);
                    str.coder = String::LATIN1;
                } else {
                    str.value = Utils::copyOfLatin1ToUTF16(bytes, (gint) offset, len);
                    str.coder = String::UTF16;
                }
                str.count = len;
            }
            return str;
        }

        String Foreign::strUtf8(glong ptr, glong offset, glong count)
        {
            CORE_ALIAS(BYTES, Class<gbyte>::Pointer);
            CORE_ALIAS(Utils, String::StringUtils);
            BYTES bytes = CORE_CAST(BYTES, ptr);
            gint len = Math::clamp(count, 0, Integer::MAX_VALUE - 8);
            if (bytes != null && offset >= 0 && count > 0) {
                CharArray ca = CharArray(len);
                gint size = 0;
                for (int i = 0; i < count && size < len;) {
                    if (bytes[i] >= 0) {
                        ca.set(size++, bytes[i++]);
                    } else if (bytes[i] >> 5 == -2) {
                        if ((bytes[i] & 0x1e) == 0 || i + 1 >= count || (bytes[i + 1] & 0xc0) != 0x80) {
                            ca.set(size++, '?');
                        } else {
                            ca.set(size++, ((bytes[i] << 6) ^ bytes[i + 1]) ^ (0xc0 << 6) ^ (0x80 << 0));
                        }
                        i += 2;
                    } else if (bytes[i] >> 4 == -2) {
                        if (i + 2 >= count
                            || bytes[i] == (gbyte) 0xe0 && (bytes[i + 1] & 0xe0) == 0x80
                            || (bytes[i + 1] & 0xc0) != 0x80
                            || (bytes[i + 2] & 0xc0) != 0x80) {
                            ca.set(size++, '?');
                        } else {
                            gchar ch = (bytes[i] << 12) ^ (bytes[i + 1] << 6) ^
                                       (bytes[i + 2] ^ (0xe0 << 12) ^ (0x80 << 6) ^ (0x80 << 0));
                            ca.set(size++, 0xd800 <= ch && ch <= 0xdfff ? '?' : ch);
                        }
                        i += 3;
                    } else if (bytes[i] >> 3 == -2) {
                        if (i + 3 >= count || (bytes[i + 1] & 0xc0) != 0x80
                            || (bytes[i + 2] & 0xc0) != 0x80 || (bytes[i + 3] & 0xc0) != 0x80) {
                            ca.set(size++, '?');
                        } else {
                            gint ch = ((bytes[i] << 18) ^ (bytes[i + 1] << 12) ^ (bytes[i + 2] << 6) ^ bytes[i + 3]) ^
                                      ((0xf0 << 18) ^ (0x80 << 12) ^ (0x80 << 6) ^ (0x80 << 0));
                            if (ch <= 0xffff)
                                ca.set(size++, '?');
                            else {
                                ca.set(size++, (ch >> 10) + 0xd800 - (0x10000 >> 10));
                                ca.set(size++, (ch & 0x3ff) + 0xdc00);
                            }
                        }
                        i += 4;
                    } else {
                        ca.set(size++, '?');
                        i += 1;
                    }
                }
                return String(ca, 0, size);
            }
            return ""_S;
        }

        String Foreign::strUtf16(glong ptr, glong offset, glong count)
        {
            String str;
            CORE_ALIAS(CHARS, Class<gchar>::Pointer);
            CORE_ALIAS(Utils, String::StringUtils);
            CHARS chars = CORE_CAST(CHARS, ptr);
            count /= 2;
            offset /= 2;
            if (chars != null && offset >= 0 && count > 0) {
                gint len = Math::clamp(count, 0, Integer::MAX_VALUE - 8);
                gint off = Math::clamp(offset, 0, Integer::MAX_VALUE - 8);
                if (String::COMPACT_STRINGS) {
                    str.value = Utils::inflateUTF16ToLatin1(chars, off, len);
                    if (str.value == null) {
                        str.value = Utils::copyOfUTF16(chars, off, len);
                        str.coder = String::UTF16;
                    } else {
                        str.coder = String::LATIN1;
                    }
                } else {
                    str.value = Utils::copyOfUTF16(chars, off, len);
                    str.coder = String::UTF16;
                }
                str.count = len;
            }
            return str;
        }

        String Foreign::strUtf32(glong ptr, glong offset, glong count)
        {
            String str;
            CORE_ALIAS(INTS, Class<gint>::Pointer);
            CORE_ALIAS(Utils, String::StringUtils);
            INTS chars = CORE_CAST(INTS, ptr);
            count /= 2;
            offset /= 2;
            if (chars != null && offset >= 0 && count > 0) {
                gint len = Math::clamp(count, 0, Integer::MAX_VALUE - 8);
                gint off = Math::clamp(offset, 0, Integer::MAX_VALUE - 8);
                if (String::COMPACT_STRINGS) {
                    str.value = Utils::inflateUTF32ToLatin1(chars, off, len);
                    if (str.value == null) {
                        str.value = Utils::copyOfUTF32ToUTF16(chars, off, len, len);
                        str.coder = String::UTF16;
                    } else {
                        str.coder = String::LATIN1;
                    }
                } else {
                    str.value = Utils::copyOfUTF32ToUTF16(chars, off, len, len);
                    str.coder = String::UTF16;
                }
                str.count = len;
            }
            return str;
        }

        String Foreign::i2str(gint i, gint radix, gbool unsignedNumber)
        {
            return unsignedNumber
                   ? Integer::toUnsignedString(i, radix)
                   : Integer::toString(i, radix);
        }

        String Foreign::l2str(glong i, gint radix, gbool unsignedNumber)
        {
            return unsignedNumber
                   ? Long::toUnsignedString(i, radix)
                   : Long::toString(i, radix);
        }

        String Foreign::f2str(gfloat i, gint precision)
        {
            return Float::toString(i);
        }

        String Foreign::d2str(gdouble i, gint precision)
        {
            return Double::toString(i);
        }
    } // misc
} // core