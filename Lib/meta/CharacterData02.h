//
// Created by bruns on 19/03/2024.
//

#ifndef CORE24_CHARACTERDATA02_H
#define CORE24_CHARACTERDATA02_H

#include <meta/CharacterData.h>

namespace core {

    /** The CharacterData class encapsulates the large tables found in
        Character. */
    class CharacterData02 final: public virtual CharacterData {
        /* The character properties are currently encoded into 32 bits in the following manner:
            1 bit   mirrored property
            4 bits  directionality property
            9 bits  signed offset used for converting case
            1 bit   if 1, adding the signed offset converts the character to lowercase
            1 bit   if 1, subtracting the signed offset converts the character to uppercase
            1 bit   if 1, this character has a titlecase equivalent (possibly itself)
            3 bits  0  may not be part of an identifier
                    1  ignorable control; may continue a Unicode identifier or Java identifier
                    2  may continue a Java identifier but not a Unicode identifier (unused)
                    3  may continue a Unicode identifier or Java identifier
                    4  is a Java whitespace character
                    5  may start or continue a Java identifier;
                       may continue but not start a Unicode identifier (underscores)
                    6  may start or continue a Java identifier but not a Unicode identifier ($)
                    7  may start or continue a Unicode identifier or Java identifier
                    Thus:
                       5, 6, 7 may start a Java identifier
                       1, 2, 3, 5, 6, 7 may continue a Java identifier
                       7 may start a Unicode identifier
                       1, 3, 5, 7 may continue a Unicode identifier
                       1 is ignorable within an identifier
                       4 is Java whitespace
            2 bits  0  this character has no numeric property
                    1  adding the digit offset to the character code and then
                       masking with 0x1F will produce the desired numeric value
                    2  this character has a "strange" numeric value
                    3  a Java supradecimal digit: adding the digit offset to the
                       character code, then masking with 0x1F, then adding 10
                       will produce the desired numeric value
            5 bits  digit offset
            5 bits  character type

            The encoding of character properties is subject to change at any time.
         */

        CharacterData02();
    public:

        gint properties(gint ch) override;

        gint propertiesEx(gint ch);

        gint type(gint ch) override;

        gbool isOtherAlphabetic(gint ch) override;

        gbool isIdeographic(gint ch) override;

        gint toLowerCase(gint ch) override;

        gint toUpperCase(gint ch) override;

        gint toTitleCase(gint ch) override;

        gint digit(gint ch, gint radix) override;

        gint numericValue(gint ch) override;

        gbool isDigit(gint ch) override;

        gbool isLowerCase(gint ch) override;

        gbool isUpperCase(gint ch) override;

        gbool isWhitespace(gint ch) override;

        gbyte directionality(gint ch) override;

        gbool isMirrored(gint ch) override;

        gint toUpperCaseEx(gint ch) override;

        CharArray toUpperCaseCharArray(gint ch) override;


        /**
         * Finds the character in the uppercase mapping table.
         *
         * @param ch the <code>char</code> to search
         * @return the index location ch in the table or -1 if not found
         */
        gint findInCharMap(gint ch);

        static CharacterData02 instance;

        // The X table has 2048 entries for a total of 4096 bytes.
        static CORE_FAST gchar X[] =
                u""
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\020\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\040\000\000\000\000\000\000\060\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\100\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\120\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\000\000\000\000\140\000\000\000\000\000\000"
                "\000\000\000\000\000\060\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
                "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020";

        // The Y table has 112 entries for a total of 224 bytes.
        static CORE_FAST gchar Y[] =
                u""
                "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\002\002\002"
                "\002\002\002\002\002\002\002\002\002\002\002\002\002\000\000\000\000\000\000"
                "\000\000\000\000\000\000\000\002\002\002\000\000\000\000\000\000\000\000\000"
                "\000\000\000\000\000\000\002\000\002\002\002\002\002\002\002\000\000\000\000"
                "\000\000\000\000\004\002\002\002\002\002\002\002\002\002\002\002\002\002\002"
                "\002\000\000\000\000\000\000\000\000\006\000\000\000\000\000\000\000";

        // The A table has 8 entries for a total of 32 bytes.
        static gint A[8];
        static CORE_FAST gchar A_DATA[] =
                u""
                "\000\u7005\000\u7005\u7800\000\u7800\000\000\u7005\u7800\000\000\u7725\000"
                "\u7005";

        // The B table has 978 entries for a total of 1960 bytes.
        static CORE_FAST gchar B[] =
                u""
                "\070\070\000\000\070\000\070\070";

        // In all, the character property tables require 19688 bytes.


    };

} // core

#endif //CORE24_CHARACTERDATA02_H