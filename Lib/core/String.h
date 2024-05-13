//
// Created by bruns on 10/05/2024.
//

#ifndef Core24_STRING_H
#define Core24_STRING_H
#include <core/ByteArray.h>
#include <core/CharArray.h>
#include <core/CharSequence.h>
#include <core/Comparable.h>
#include <core/IntArray.h>

namespace core
{
    class String final : public virtual CharSequence, public virtual Comparable<String>
    {
        CORE_ALIAS(ARRAY, Class<gbyte>::Pointer);
        CORE_ALIAS(BYTES, Class<gbyte>::Pointer);
        CORE_ALIAS(CHARS, Class<gchar>::Pointer);
        CORE_ALIAS(INTS, Class<gint>::Pointer);
        class StringUtils;

    private:
        /**
         * The array used for characters storage.
         */
        ARRAY value = null;

        /**
         * The number of 16 bits characters on this String.
         */
        gint count = 0;

        /**
         * The identifier of the encoding used to encode
         * the bytes in the @c value field.
         */
        enum Coder { LATIN1 = 0, UTF16 = 1 } coder = LATIN1;

        /**
         * Cache of hash value for the String
         */
        gint mutable hashValue = 0;

        /**
         * Cache if the hash has been calculated as actually being zero,
         * enabling us to avoid recalculating this.
         */
        gbool mutable hashIsZero = false;

        /**
         * If String compaction is disabled, the bytes in @c value field
         * are always encoded in UTF16.
         */
        static CORE_FAST gbool COMPACT_STRINGS = CORE_HAS_COMPACT_STRINGS;


        Coder coding() const;

    public:
        /**
         * Initializes a newly created @c String object so that it represents
         * an empty character sequence.  Note that use of this constructor is
         * unnecessary since Strings are immutable.
         */
        CORE_IMPLICIT String();

        /**
         * Initializes a newly created @c String object so that it represents
         * the same sequence of characters as the argument; in other words, the
         * newly created string is a copy of the argument string.
         *
         * @param  original A @c String
         */
        CORE_IMPLICIT String(String const& original);

        /**
         * Initializes a newly created @c String object so that it represents
         * the same sequence of characters as the argument; in other words, the
         * newly created string is a copy of the argument string.
         *
         * @note After this operation the original String will be empty.
         *
         * @param  original A @c String
         */
        CORE_IMPLICIT String(String&& original) CORE_NOTHROW;

        /**
         * Allocates a new @c String so that it represents the sequence of
         * characters currently contained in the character array argument. The
         * contents of the character array are copied; subsequent modification of
         * the character array does not affect the newly created string.
         *
         * @param  value The initial value of the string
         */
        CORE_EXPLICIT String(CharArray const& value);

        /**
         * Allocates a new @c String that contains characters from a subarray
         * of the character array argument. The @c offset argument is the
         * index of the first character of the subarray and the @c count
         * argument specifies the length of the subarray. The contents of the
         * subarray are copied; subsequent modification of the character array does
         * not affect the newly created string.
         *
         * @param  value Array that is the source of characters
         * @param  offset The initial offset
         * @param  count The length
         *
         * @throws  IndexOutOfBoundsException
         *          If @c offset is negative, @c count is negative, or
         *          @c offset is greater than @c value.length() - count
         */
        CORE_EXPLICIT String(CharArray const& value, gint offset, gint count);

        /**
         * Allocates a new @c String that contains characters from a subarray
         * of the @a Unicode code point array argument.  The @c offset argument
         * is the index of the first code point of the subarray and the @c count
         * argument specifies the length of the subarray.  The contents of the
         * subarray are converted to @c chars; subsequent modification of the @c int
         * array does not affect the newly created string.
         *
         * @param  codePoints Array that is the source of Unicode code points
         * @param  offset The initial offset
         * @param  count The length
         * @throws  IllegalArgumentException
         *          If any invalid Unicode code point is found in @c codePoints
         * @throws  IndexOutOfBoundsException
         *          If @c offset is negative, @c count is negative, or
         *          @c offset is greater than @c codePoints.length - count
         */
        CORE_EXPLICIT String(IntArray const& codePoints, gint offset, gint count);

        /**
         * Allocates a new @c String constructed from a subarray of an array
         * of 8-bit integer values.
         *
         * The @c offset argument is the index of the first byte of the
         * subarray, and the @c count argument specifies the length of the
         * subarray.
         *
         * Each @c gbyte in the subarray is converted to a @c gchar as
         * specified in the @c String(ByteArray,int) constructor.
         *
         * @note This method does not properly convert bytes into characters.
         *       The recommanded way to do this is via the @c String constructors
         *       that take a @c Charset, @a charset @a name, or that use
         *       the @a default @a charset.
         *
         * @param  ascii The bytes to be converted to characters.
         * @param  hibyte The top 8 bits of each 16-bit Unicode code unit.
         * @param  offset The initial offset
         * @param  count The length
         *
         * @throws  IndexOutOfBoundsException
         *          If @c offset is negative, @c count is negative, or
         *          @c offset is greater than @c ascii.length - count
         */
        CORE_EXPLICIT String(ByteArray const& ascii, gint hibyte, gint offset, gint count);

        /**
         * Allocates a new @c String containing characters constructed from
         * an array of 8-bit integer values. Each character @c c in the
         * resulting string is constructed from the corresponding component
         * @c b in the byte array such that:
         * @code{c++}
         *  c == (gchar)(((hibyte & 0xff) << 8) | (b & 0xff))
         * @endcode
         *
         * @note This method does not properly convert bytes into characters.
         *       The recommanded way to do this is via the @c String constructors
         *       that take a @c Charset, @a charset @a name, or that use
         *       the @a default @a charset.
         *
         * @param  ascii The bytes to be converted to characters
         * @param  hibyte The top 8 bits of each 16-bit Unicode code unit
         */
        CORE_EXPLICIT String(ByteArray const& ascii, gint hibyte);

        /**
         * Set this String content with given String.
         *
         * @param other A @c String
         * @return itself
         */
        String& operator=(String const& other);

        /**
         * Return the length of this String. The length
         * is equals to the number of unicode code unit in this String
         *
         * @return The length of chars sequence represented by this String
         */
        gint length() const override;

        /**
         * Return @c true if value returned by @c length() is @c 0.
         *
         * @return @c true if @c length() is @c 0.
         */
        gbool isEmpty() const override;

        /**
         * Returns the @c char value at the specified index.
         * An index ranges from @c 0 to @c length() - 1.
         * The first @c char value of the sequence is at index @c 0,
         * the next at index @c 1, and so on, as for array indexing.
         *
         * If the @c char value specified by the index is a @a surrogate, the surrogate
         * value is returned.
         *
         * @param index the index of the @c char value.
         * @throws IndexOutOfBoundsException if the @c index argument is negative or
         *                                    not less than the length of this string.
         * @return the @c char value at the specified index of this string.
         */
        gchar charAt(gint index) const override;
        /**
         * Returns the character (Unicode code point) at the specified
         * index. The index refers to @c char values
         * (Unicode code units) and ranges from @c 0 to @c length()-1.
         *
         * If the @c char value specified at the given index
         * is in the high-surrogate range, the following index is less
         * than the length of this @c String, and the
         * @c char value at the following index is in the
         * low-surrogate range, then the supplementary code point
         * corresponding to this surrogate pair is returned. Otherwise,
         * the @c char value at the given index is returned.
         *
         * @param      index the index to the @c char values
         * @return     the code point value of the character at the
         *             @c index
         * @throws     IndexOutOfBoundsException  if the @c index
         *             argument is negative or not less than the length of this
         *             string.
         */
        gint codePointAt(gint index) const;

        /**
         * Returns the number of Unicode code points in the specified text
         * range of this @c String. The text range begins at the
         * specified @c beginIndex and extends to the
         * @c char at index @c endIndex - 1. Thus the
         * length (in @c chars) of the text range is
         * @c endIndex-beginIndex. Unpaired surrogates within
         * the text range count as one code point each.
         *
         * @param beginIndex the index to the first @c char of
         *                   the text range.
         * @param endIndex the index after the last @c char of
         *                 the text range.
         * @return the number of Unicode code points in the specified text
         *         range
         * @throws IndexOutOfBoundsException if the @c beginIndex is negative,
         *         or @c endIndex is larger than the length of this @c String,
         *         or @c beginIndex is larger than @c endIndex.
         */
        gint codePointCount(gint beginIndex, gint endIndex) const;

        /**
         * Copies characters from this string into the destination character
         * array.
         *
         * The first character to be copied is at index @c beginIndex;
         * the last character to be copied is at index @c endIndex-1
         * (thus the total number of characters to be copied is @c endIndex- @c beginIndex).
         * The characters are copied into the subarray of @c dest starting at index @c offset
         * and ending at index: @code offset + (endIndex-beginIndex) - 1 @endcode
         *
         * @param beginIndex index of the first character in the string to copy.
         * @param endIndex   index after the last character in the string to copy.
         * @param dest       the destination array.
         * @param offset     the start offset in the destination array.
         * @throws IndexOutOfBoundsException If any of the following is true:
         *            @li @c beginIndex is negative.
         *            @li @c beginIndex is greater than @c endIndex
         *            @li @c endIndex is greater than the length of this string
         *            @li @c offset is negative
         *            @li @c offset + (endIndex - beginIndex) is larger than @c dest.length()
         */
        void toChars(gint beginIndex, gint endIndex, CharArray& dest, gint offset);

        /**
         * Copies characters from this string into the destination byte array. Each
         * byte receives the 8 low-order bits of the corresponding character. The
         * eight high-order bits of each character are not copied and do not
         * participate in the transfer in any way.
         *
         * The first character to be copied is at index @c beginIndex; the
         * last character to be copied is at index @c endIndex-1.  The total
         * number of characters to be copied is @c endIndex - @c beginIndex. The
         * characters, converted to bytes, are copied into the subarray of @c 
         * dest starting at index @c offset and ending at index:
         * @code offset + (endIndex-beginIndex) - 1 @endcode
         *
         * @note  This method does not properly convert characters into
         * bytes.  The recommanded way to do this is via the @c toBytes() method,
         * which uses the default charset.
         *
         * @param  beginIndex Index of the first character in the string to copy
         * @param  endIndex Index after the last character in the string to copy
         * @param  dest The destination array
         * @param  offset The start offset in the destination array
         * @throws  IndexOutOfBoundsException If any of the following is true:
         *            @li @c beginIndex is negative
         *            @li @c beginIndex is greater than @c endIndex
         *            @li @c endIndex is greater than the length of this String
         *            @li @c offset is negative
         *            @li @c offset+(endIndex-beginIndex) is larger than @c dest.length()
         */
        void toBytes(gint beginIndex, gint endIndex, ByteArray& dest, gint offset);

        /**
         * Compares this string to the specified object.  The result is @c true
         * if and only if the argument is not @c null and is a @c String object
         * that represents the same sequence of characters as this object.
         *
         * For finer-grained String comparison, refer to @a text::Collator.
         *
         * @param  obj The object to compare this @c String against
         * @return  @c true if the given object represents a @c String
         *          equivalent to this string, @c false otherwise
         */
        gbool equals(Object const& obj) const override;

        /**
         * Compares two strings lexicographically.
         * The comparison is based on the Unicode value of each character in
         * the strings. The character sequence represented by this
         * @c String object is compared lexicographically to the
         * character sequence represented by the argument string. The result is
         * a negative integer if this @c String object lexicographically precedes
         * the argument string. The result is a positive integer if this @c String
         * object lexicographically follows the argument string. The result is zero
         * if the strings are equal; @c compareTo returns @c 0 exactly when
         * the @c equals(Object) method would return @c true.
         * 
         * This is the definition of lexicographic ordering. If two strings are
         * different, then either they have different characters at some index
         * that is a valid index for both strings, or their lengths are different,
         * or both. If they have different characters at one or more index
         * positions, let @a k be the smallest such index; then the string
         * whose character at position @a k has the smaller value, as
         * determined by using the @c < operator, lexicographically precedes the
         * other string. In this case, @c compareTo returns the
         * difference of the two character values at position @c k in
         * the two string -- that is, the value:
         * @code this.charAt(k)-anotherString.charAt(k) @endcode
         * If there is no index position at which they differ, then the shorter
         * string lexicographically precedes the longer string. In this case,
         * @c compareTo returns the difference of the lengths of the
         * strings -- that is, the value:
         * @code this.length()-anotherString.length() @endcode
         *
         * For finer-grained String comparison, refer to @c text::Collator.
         *
         * @param   anotherString   the @c String to be compared.
         * @return  the value @c 0 if the argument string is equal to
         *          this string; a value less than @c 0 if this string
         *          is lexicographically less than the string argument; and a
         *          value greater than @c 0 if this string is
         *          lexicographically greater than the string argument.
         */
        gint compareTo(String const& anotherString) const override;

        ~String() override;
    };
} // core

#endif // Core24_STRING_H
