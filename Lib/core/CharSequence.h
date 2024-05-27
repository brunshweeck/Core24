//
// Created by bruns on 09/05/2024.
//

#ifndef CORE24_CHARSEQUENCE_H
#define CORE24_CHARSEQUENCE_H

#include <core/Class.h>

namespace core
{
    /**
     * The class @c CharSequence represent the @a readable sequence
     * of chars values. this class provide the uniforme read-only
     *  access to many different kinds of chars sequences.
     *
     * A @c char value represents a character in the @a Basic
     * @a Multilingual @a Plane (@b BMP) or @a surrogate.
     */
    class CharSequence : public virtual Object
    {
    public:
        /**
         * Returns the length of this character sequence.
         * The length is the number of 16-bit chars in the sequence.
         *
         * @return the number of chars in this sequence
         */
        virtual gint length() const = 0;

        /**
         * Returns @c true if this character sequence is empty.
         *
         * @return @c true if @c length() return @c 0, otherwise
         *          @c false
         */
        virtual gbool isEmpty() const;

        /**
         * Returns the char value at the specified index.
         * An index ranges from zero to @c length() - 1.
         * The first <b>char</b> value of the sequence is at
         * index zero, the next at index one, and so on, as
         * for array indexing.
         *
         * If the char value specified by the index is a
         * @c surrogate, the surrogate value is returned.
         *
         * @param index The index of char value returned.
         * @throws IndexOutOfBoundsException
         *     if the @c index argument is negative or not
         *     less than @c length()
         * @return The specified char value at given index
         */
        virtual gchar charAt(gint index) const = 0;
    };
} // core

#endif // CORE24_CHARSEQUENCE_H
