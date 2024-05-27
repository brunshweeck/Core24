//
// Created by bruns on 19/03/2024.
//

#include "CharacterData0E.h"

namespace core
{
    gint CharacterData0E::properties(gint ch)
    {
        gchar offset = (gchar) ch;
        int props = A[Y[X[offset >> 5] | ((offset >> 1) & 0xF)] | (offset & 0x1)];
        return props;
    }

    gint CharacterData0E::propertiesEx(gint ch)
    {
        gchar offset = (gchar) ch;
        int props = B[Y[X[offset >> 5] | ((offset >> 1) & 0xF)] | (offset & 0x1)];
        return props;
    }

    gint CharacterData0E::type(gint ch)
    {
        int props = properties(ch);
        return (props & 0x1F);
    }

    gbool CharacterData0E::isOtherAlphabetic(gint ch)
    {
        int props = propertiesEx(ch);
        return (props & 0x0004) != 0;
    }

    gbool CharacterData0E::isIdeographic(gint ch)
    {
        int props = propertiesEx(ch);
        return (props & 0x0008) != 0;
    }

    gint CharacterData0E::toLowerCase(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if ((val & 0x00020000) != 0) {
            int offset = val << 5 >> (5 + 18);
            mapChar = ch + offset;
        }
        return mapChar;
    }

    gint CharacterData0E::toUpperCase(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if ((val & 0x00010000) != 0) {
            int offset = val << 5 >> (5 + 18);
            mapChar = ch - offset;
        }
        return mapChar;
    }

    gint CharacterData0E::toTitleCase(gint ch)
    {
        int mapChar = ch;
        int val = properties(ch);

        if ((val & 0x00008000) != 0) {
            // There is a titlecase equivalent.  Perform further checks:
            if ((val & 0x00010000) == 0) {
                // The character does not have an uppercase equivalent, so it must
                // already be uppercase; so add 1 to get the titlecase form.
                mapChar = ch + 1;
            }
            else if ((val & 0x00020000) == 0) {
                // The character does not have a lowercase equivalent, so it must
                // already be lowercase; so subtract 1 to get the titlecase form.
                mapChar = ch - 1;
            }
            // else {
            // The character has both an uppercase equivalent and a lowercase
            // equivalent, so it must itself be a titlecase form; return it.
            // return ch;
            //}
        }
        else if ((val & 0x00010000) != 0) {
            // This character has no titlecase equivalent but it does have an
            // uppercase equivalent, so use that (subtract the signed case offset).
            mapChar = toUpperCase(ch);
        }
        return mapChar;
    }

    gint CharacterData0E::digit(gint ch, gint radix)
    {
        int value = -1;
        if (radix >= Character::MIN_RADIX && radix <= Character::MAX_RADIX) {
            int val = properties(ch);
            int kind = val & 0x1F;
            if (kind == Character::DECIMAL_DIGIT_NUMBER) {
                value = ch + ((val & 0x3E0) >> 5) & 0x1F;
            }
            else if ((val & 0xC00) == 0x00000C00) {
                // supradecimal digit
                value = (ch + ((val & 0x3E0) >> 5) & 0x1F) + 10;
            }
        }
        return (value < radix) ? value : -1;
    }

    gint CharacterData0E::numericValue(gint ch)
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
            case (0x00000C00):           // supradecimal
                retval = (ch + ((val & 0x3E0) >> 5) & 0x1F) + 10;
                break;
        }
        return retval;
    }

    gbool CharacterData0E::isDigit(gint ch)
    {
        int props = properties(ch);
        return (props & 0x1F) == Character::DECIMAL_DIGIT_NUMBER;
    }

    gbool CharacterData0E::isLowerCase(gint ch)
    {
        return (propertiesEx(ch) & 0x0001) != 0;
    }

    gbool CharacterData0E::isUpperCase(gint ch)
    {
        return (propertiesEx(ch) & 0x0002) != 0;
    }

    gbool CharacterData0E::isWhitespace(gint ch)
    {
        int props = properties(ch);
        return ((props & 0x00007000) == 0x00004000);
    }

    gbyte CharacterData0E::directionality(gint ch)
    {
        int val = properties(ch);
        gbyte directionality = (gbyte) ((val & 0x78000000) >> 27);
        if (directionality == 0xF) {
            directionality = Character::DIRECTIONALITY_UNDEFINED;
        }
        return directionality;
    }

    gbool CharacterData0E::isMirrored(gint ch)
    {
        int props = properties(ch);
        return ((props & 0x80000000) != 0);
    }

    CharacterData0E::CharacterData0E()
    {
        // THIS CODE WAS AUTOMATICALLY CREATED BY GenerateCharacter:
        CORE_FAST_ASSERT(sizeof(A_DATA) / sizeof(A_DATA[0]) - 1 == (8 * 2));
        int i = 0, j = 0;
        while (i < (8 * 2)) {
            int entry = A_DATA[i++] << 16;
            A[j++] = entry | A_DATA[i++];
        }
    }

    gint CharacterData0E::A[8]{ };
    CharacterData0E CharacterData0E::instance{ };
} // core