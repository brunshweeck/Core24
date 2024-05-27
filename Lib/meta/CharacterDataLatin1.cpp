//
// Created by bruns on 19/03/2024.
//

#include "CharacterDataLatin1.h"

namespace core
{
    gint CharacterDataLatin1::properties(gint ch)
    {
        gchar offset = (gchar) ch;
        int props = A[offset];
        return props;
    }

    gint CharacterDataLatin1::propertiesEx(gint ch)
    {
        gchar offset = (gchar) ch;
        int props = B[offset];
        return props;
    }

    gbool CharacterDataLatin1::isDigit(gint ch)
    {
        return '0' <= ch && ch <= '9';
    }

    gbool CharacterDataLatin1::isLowerCase(gint ch)
    {
        return (propertiesEx(ch) & 0x0001) != 0;
    }

    gbool CharacterDataLatin1::isUpperCase(gint ch)
    {
        return (properties(ch) & 0x0002) != 0;
    }

    gbool CharacterDataLatin1::isOtherAlphabetic(gint ch)
    {
        return (propertiesEx(ch) & 0x004) != 0;
    }

    gbool CharacterDataLatin1::isIdeographic(gint ch)
    {
        return (propertiesEx(ch) & 0x008) != 0;
    }

    gint CharacterDataLatin1::type(gint ch)
    {
        return (properties(ch) & 0x1F) != 0;
    }

    gint CharacterDataLatin1::toLowerCase(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if (((val & 0x00020000) != 0) &&
            ((val & 0x07FC0000) != 0x07FC0000)) {
            int offset = val << 5 >> (5 + 18);
            mapChar = ch + offset;
        }
        return mapChar;
    }

    gint CharacterDataLatin1::toUpperCase(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if ((val & 0x00010000) != 0) {
            if ((val & 0x07FC0000) != 0x07FC0000) {
                int offset = val << 5 >> (5 + 18);
                mapChar = ch - offset;
            }
            else if (ch == 0x00B5) {
                mapChar = 0x039C;
            }
        }
        return mapChar;
    }

    gint CharacterDataLatin1::toTitleCase(gint ch)
    {
        return toUpperCase(ch);
    }

    gint CharacterDataLatin1::digit(gint ch, gint radix)
    {
        int value = DIGITS[ch];
        return (value >= 0 && value < radix && radix >= Character::MIN_RADIX
                && radix <= Character::MAX_RADIX) ? value : -1;
    }

    gint CharacterDataLatin1::numericValue(gint ch)
    {
        int val = properties(ch);
        int retval = -1;

        switch (val & 0xC00) {
            default: // cannot occur
            case (0x00000000):         // not numeric
                retval = -1;
                break;
            case (0x00000400):              // simple numeric
                retval = ch + ((val & 0x3E0) >> 5) & 0x1F;
                break;
            case (0x00000800)      :       // "strange" numeric
                retval = -2;
                break;
            case (0x00000C00):           // Java supradecimal
                retval = (ch + ((val & 0x3E0) >> 5) & 0x1F) + 10;
                break;
        }
        return retval;
    }

    gbool CharacterDataLatin1::isWhitespace(gint ch)
    {
        return (properties(ch) & 0x00007000) != 0;
    }

    gbyte CharacterDataLatin1::directionality(gint ch)
    {
        int val = properties(ch);
        gbyte directionality = (gbyte) ((val & 0x78000000) >> 27);

        if (directionality == 0xF) {
            directionality = -1;
        }
        return directionality;
    }

    gbool CharacterDataLatin1::isMirrored(gint ch)
    {
        int props = properties(ch);
        return ((props & 0x80000000) != 0);
    }

    gint CharacterDataLatin1::toUpperCaseEx(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if ((val & 0x00010000) != 0) {
            if ((val & 0x07FC0000) != 0x07FC0000) {
                int offset = val << 5 >> (5 + 18);
                mapChar = ch - offset;
            }
            else {
                switch (ch) {
                    // map overflow characters
                    case 0x00B5 : mapChar = 0x039C;
                        break;
                    default       : mapChar = Character::ERROR;
                        break;
                }
            }
        }
        return mapChar;
    }

    CharArray CharacterDataLatin1::toUpperCaseCharArray(gint ch)
    {
        CharArray upperMap = CharArray::of((gchar) ch);
        if (ch == 0x00DF) {
            return CharArray::copyOf(sharpsMap);
        }
        return upperMap;
    }

    CharacterDataLatin1::CharacterDataLatin1()
    {
    }

    CharacterDataLatin1 CharacterDataLatin1::instance{ };
} // core