//
// Created by bruns on 05/05/2024.
//

#include <core/misc/Literals.h>
#include <core/String.h>

namespace core
{
    namespace misc
    {
    } // misc

    String operator ""_S(misc::__literal_chr_t const* str, misc::__memory_size_t size)
    {
        gint length = (gint) (size & 0x7fffffff);
        if (length == 0) {
            return String();
        }
        gbool isAscii = true;
        gint  i       = 0;
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
                gint      k     = 0;
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

    String operator ""_S(misc::__ucs2_t const* str, misc::__memory_size_t size)
    {
        gint length = (gint) (size & 0x7fffffff);
        gint hibyte = 0;
        gint i      = 0;
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

    String operator ""_S(misc::__ucs4_t const* str, misc::__memory_size_t size)
    {
        gint length = (gint) size;
        gint hibyte = 0;
        gint i      = 0;
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

    String operator ""_S(wchar_t const* str, misc::__memory_size_t size)
    {
        return ClassOf(*str)::MEMORY_SIZE == 2
                   ? operator ""_S(CORE_CAST(misc::__ucs2_t const *, str), size)
                   : operator ""_S(CORE_CAST(misc::__ucs4_t const *, str), size);
    }
} // core
