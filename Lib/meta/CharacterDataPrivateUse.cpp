//
// Created by bruns on 19/03/2024.
//

#include "CharacterDataPrivateUse.h"

namespace core
{
    gint CharacterDataPrivateUse::properties(gint ch)
    {
        return 0;
    }

    gint CharacterDataPrivateUse::type(gint ch)
    {
        return (ch & 0xFFFE) == 0xFFFE
               ? Character::UNASSIGNED
               : Character::PRIVATE_USE;
    }

    gint CharacterDataPrivateUse::toLowerCase(gint ch)
    {
        return ch;
    }

    gint CharacterDataPrivateUse::toUpperCase(gint ch)
    {
        return ch;
    }

    gint CharacterDataPrivateUse::toTitleCase(gint ch)
    {
        return ch;
    }

    gint CharacterDataPrivateUse::numericValue(gint ch)
    {
        return -1;
    }

    gbool CharacterDataPrivateUse::isDigit(gint ch)
    {
        return false;
    }

    gbool CharacterDataPrivateUse::isLowerCase(gint ch)
    {
        return false;
    }

    gbool CharacterDataPrivateUse::isUpperCase(gint ch)
    {
        return false;
    }

    gbool CharacterDataPrivateUse::isWhitespace(gint ch)
    {
        return false;
    }

    gbyte CharacterDataPrivateUse::directionality(gint ch)
    {
        return (ch & 0xFFFE) == 0xFFFE
               ? Character::DIRECTIONALITY_UNDEFINED
               : Character::DIRECTIONALITY_LEFT_TO_RIGHT;
    }

    gbool CharacterDataPrivateUse::isMirrored(gint ch)
    {
        return false;
    }

    gint CharacterDataPrivateUse::digit(gint ch, gint radix)
    {
        return -1;
    }

    CharacterDataPrivateUse::CharacterDataPrivateUse()
    {
    }

    CharacterDataPrivateUse CharacterDataPrivateUse::instance{ };
} // core