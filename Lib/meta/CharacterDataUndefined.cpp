//
// Created by bruns on 19/03/2024.
//

#include "CharacterDataUndefined.h"

namespace core
{
    int CharacterDataUndefined::properties(int ch)
    {
        return 0;
    }

    int CharacterDataUndefined::type(int ch)
    {
        return Character::UNASSIGNED;
    }

    int CharacterDataUndefined::toLowerCase(int ch)
    {
        return ch;
    }

    int CharacterDataUndefined::toUpperCase(int ch)
    {
        return ch;
    }

    gint CharacterDataUndefined::toTitleCase(gint ch)
    {
        return ch;
    }

    gint CharacterDataUndefined::digit(gint ch, gint radix)
    {
        return -1;
    }

    gint CharacterDataUndefined::numericValue(gint ch)
    {
        return -1;
    }

    gbool CharacterDataUndefined::isDigit(gint ch)
    {
        return false;
    }

    gbool CharacterDataUndefined::isLowerCase(gint ch)
    {
        return false;
    }

    gbool CharacterDataUndefined::isUpperCase(gint ch)
    {
        return false;
    }

    gbool CharacterDataUndefined::isWhitespace(gint ch)
    {
        return false;
    }

    gbyte CharacterDataUndefined::directionality(gint ch)
    {
        return Character::Directionality::DIRECTIONALITY_UNDEFINED;
    }

    gbool CharacterDataUndefined::isMirrored(gint ch)
    {
        return false;
    }

    CharacterDataUndefined::CharacterDataUndefined()
    {
    }

    CharacterDataUndefined CharacterDataUndefined::instance{ };
} // core