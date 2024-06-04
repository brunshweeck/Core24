//
// Created by bruns on 10/05/2024.
//

#ifndef CORE24_STRING_H
#define CORE24_STRING_H

#include <core/ByteArray.h>
#include <core/CharArray.h>
#include <core/CharSequence.h>
#include <core/Comparable.h>
#include <core/IntArray.h>

namespace core
{
    class String final : public virtual CharSequence, public virtual Comparable< String >
    {
        CORE_ALIAS(ARRAY, Class< gbyte >::Pointer);
        CORE_ALIAS(BYTES, Class< gbyte >::Pointer);
        CORE_ALIAS(CHARS, Class< gchar >::Pointer);
        CORE_ALIAS(INTS, Class< gint >::Pointer);

        CORE_ADD_AS_FRIEND(::core::misc::Foreign);
        CORE_ADD_AS_FRIEND(::core::XString);

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
        enum Coder
        {
            LATIN1 = 0, UTF16 = 1
        } coder = LATIN1;

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
        CORE_IMPLICIT String(String const &original);

        /**
         * Initializes a newly created @c String object so that it represents
         * the same sequence of characters as the argument; in other words, the
         * newly created string is a copy of the argument string.
         *
         * @note After this operation the original String will be empty.
         *
         * @param  original A @c String
         */
        CORE_IMPLICIT String(String &&original) CORE_NOTHROW;

        /**
         * Allocates a new @c String so that it represents the sequence of
         * characters currently contained in the character array argument. The
         * contents of the character array are copied; subsequent modification of
         * the character array does not affect the newly created string.
         *
         * @param  value The initial value of the string
         */
        CORE_EXPLICIT String(CharArray const &value);

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
        CORE_EXPLICIT String(CharArray const &value, gint offset, gint count);

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
        CORE_EXPLICIT String(IntArray const &codePoints, gint offset, gint count);

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
        CORE_EXPLICIT String(ByteArray const &ascii, gint hibyte, gint offset, gint count);

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
        CORE_EXPLICIT String(ByteArray const &ascii, gint hibyte);

        /**
         * Set this String content with given String.
         *
         * @param other A @c String
         * @return itself
         */
        String &operator=(String const &other);

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
        void toChars(gint beginIndex, gint endIndex, CharArray &dest, gint offset);

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
         * bytes.  The recommended way to do this is via the @c toBytes() method,
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
        void toBytes(gint beginIndex, gint endIndex, ByteArray &dest, gint offset);

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
        gbool equals(Object const &obj) const override;

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
        gint compareTo(String const &anotherString) const override;

        /**
         * Tests if the substring of this string beginning at the
         * specified index starts with the specified prefix.
         *
         * @param   prefix    the prefix.
         * @param   toffset   where to begin looking in this string.
         * @return  @c true if the character sequence represented by the
         *          argument is a prefix of the substring of this object starting
         *          at index @c toffset; @c false otherwise.
         *          The result is @c false if @c toffset is
         *          negative or greater than the length of this
         *          @c String object; otherwise the result is the same
         *          as the result of the expression
         *          <pre>
         *          this.subString(toffset).startsWith(prefix)
         *          </pre>
         */
        gbool startsWith(String const &prefix, gint toffset) const;

        /**
         * Tests if this string starts with the specified prefix.
         *
         * @param   prefix   the prefix.
         * @return  @c true if the character sequence represented by the
         *          argument is a prefix of the character sequence represented by
         *          this string; @c false otherwise.
         *          Note also that @c true will be returned if the
         *          argument is an empty string or is equal to this
         *          @c String object as determined by the
         *          @c equals(Object) method.
         */
        gbool startsWith(String const &prefix) const;

        /**
         * Tests if this string ends with the specified suffix.
         *
         * @param   suffix   the suffix.
         * @return  @c true if the character sequence represented by the
         *          argument is a suffix of the character sequence represented by
         *          this object; @c false otherwise. Note that the
         *          result will be @c true if the argument is the
         *          empty string or is equal to this @c String object
         *          as determined by the @c equals(Object) method.
         */
        gbool endsWith(String const &suffix) const;

        /**
         * Returns a hash code for this string. The hash code for a
         * @c String object is computed as
         * @code{c++}
         * s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
         * @endcode
         * using @c int arithmetic, where @c s[i] is the
         * <i>i</i>th character of the string, @c n is the length of
         * the string, and @c ^ indicates exponentiation.
         * (The hash value of the empty string is zero.)
         *
         * @return  a hash code value for this object.
         */
        gint hash() const override;

        /**
         * Returns the index within this string of the first occurrence of
         * the specified character. If a character with value
         * @c ch occurs in the character sequence represented by
         * this @c String object, then the index (in Unicode
         * code units) of the first such occurrence is returned. For
         * values of @c ch in the range from 0 to 0xFFFF
         * (inclusive), this is the smallest value <i>k</i> such that:
         * @code{c++}
         * this.charAt(<i>k</i>) == ch
         * @endcode
         * is true. For other values of @c ch, it is the
         * smallest value <i>k</i> such that:
         * @code{c++}
         * this.codePointAt(<i>k</i>) == ch
         * @endcode
         * is true. In either case, if no such character occurs in this
         * string, then @c -1 is returned.
         *
         * @param   ch   a character (Unicode code point).
         * @return  the index of the first occurrence of the character in the
         *          character sequence represented by this object, or
         *          @c -1 if the character does not occur.
         */
        gint indexOf(gint ch) const;

        /**
         * Returns the index within this string of the first occurrence of the
         * specified character, starting the search at the specified index.
         * <p>
         * If a character with value @c ch occurs in the
         * character sequence represented by this @c String
         * object at an index no smaller than @c fromIndex, then
         * the index of the first such occurrence is returned. For values
         * of @c ch in the range from 0 to 0xFFFF (inclusive),
         * this is the smallest value <i>k</i> such that:
         * @code{c++}
         * (this.charAt(<i>k</i>) == ch) @c && (<i>k</i> &gt;= fromIndex)
         * @endcode
         * is true. For other values of @c ch, it is the
         * smallest value <i>k</i> such that:
         * @code{c++}
         * (this.codePointAt(<i>k</i>) == ch) @c && (<i>k</i> &gt;= fromIndex)
         * @endcode
         * is true. In either case, if no such character occurs in this
         * string at or after position @c fromIndex, then
         * @c -1 is returned.
         *
         * <p>
         * There is no restriction on the value of @c fromIndex. If it
         * is negative, it has the same effect as if it were zero: this entire
         * string may be searched. If it is greater than the length of this
         * string, it has the same effect as if it were equal to the length of
         * this string: @c -1 is returned.
         *
         * <p>All indices are specified in @c char values
         * (Unicode code units).
         *
         * @param   ch          a character (Unicode code point).
         * @param   fromIndex   the index to start the search from.
         * @return  the index of the first occurrence of the character in the
         *          character sequence represented by this object that is greater
         *          than or equal to @c fromIndex, or @c -1
         *          if the character does not occur.
         */
        gint indexOf(gint ch, gint fromIndex) const;

        /**
         * Returns the index within this string of the last occurrence of
         * the specified character. For values of @c ch in the
         * range from 0 to 0xFFFF (inclusive), the index (in Unicode code
         * units) returned is the largest value <i>k</i> such that:
         * @code{c++}
         * this.charAt(<i>k</i>) == ch
         * @endcode
         * is true. For other values of @c ch, it is the
         * largest value <i>k</i> such that:
         * @code{c++}
         * this.codePointAt(<i>k</i>) == ch
         * @endcode
         * is true.  In either case, if no such character occurs in this
         * string, then @c -1 is returned.  The
         * @c String is searched backwards starting at the last
         * character.
         *
         * @param   ch   a character (Unicode code point).
         * @return  the index of the last occurrence of the character in the
         *          character sequence represented by this object, or
         *          @c -1 if the character does not occur.
         */
        gint lastIndexOf(gint ch) const;

        /**
         * Returns the index within this string of the last occurrence of
         * the specified character, searching backward starting at the
         * specified index. For values of @c ch in the range
         * from 0 to 0xFFFF (inclusive), the index returned is the largest
         * value <i>k</i> such that:
         * @code{c++}
         * (this.charAt(<i>k</i>) == ch) @c && (<i>k</i> &lt;= fromIndex)
         * @endcode
         * is true. For other values of @c ch, it is the
         * largest value <i>k</i> such that:
         * @code{c++}
         * (this.codePointAt(<i>k</i>) == ch) @c && (<i>k</i> &lt;= fromIndex)
         * @endcode
         * is true. In either case, if no such character occurs in this
         * string at or before position @c fromIndex, then
         * @c -1 is returned.
         *
         * <p>All indices are specified in @c char values
         * (Unicode code units).
         *
         * @param   ch          a character (Unicode code point).
         * @param   fromIndex   the index to start the search from. There is no
         *          restriction on the value of @c fromIndex. If it is
         *          greater than or equal to the length of this string, it has
         *          the same effect as if it were equal to one less than the
         *          length of this string: this entire string may be searched.
         *          If it is negative, it has the same effect as if it were -1:
         *          -1 is returned.
         * @return  the index of the last occurrence of the character in the
         *          character sequence represented by this object that is less
         *          than or equal to @c fromIndex, or @c -1
         *          if the character does not occur before that point.
         */
        gint lastIndexOf(gint ch, gint fromIndex) const;

        /**
         * Returns the index within this string of the first occurrence of the
         * specified substring.
         *
         * <p>The returned index is the smallest value @c k for which:
         * <pre>@c @code
         * this.startsWith(str, k)
         * @endcode</pre>
         * If no such value of @c k exists, then @c -1 is returned.
         *
         * @param   str   the substring to search for.
         * @return  the index of the first occurrence of the specified substring,
         *          or @c -1 if there is no such occurrence.
         */
        gint indexOf(String const &str) const;

        /**
         * Returns the index within this string of the first occurrence of the
         * specified substring, starting at the specified index.
         *
         * <p>The returned index is the smallest value @c k for which:
         * <pre>@c @code
         *     k >= Math.min(fromIndex, this.length()) &&
         *                   this.startsWith(str, k)
         * @endcode</pre>
         * If no such value of @c k exists, then @c -1 is returned.
         *
         * @param   str         the substring to search for.
         * @param   fromIndex   the index from which to start the search.
         * @return  the index of the first occurrence of the specified substring,
         *          starting at the specified index,
         *          or @c -1 if there is no such occurrence.
         */
        gint indexOf(String const &str, gint fromIndex) const;

        /**
         * Returns the index within this string of the last occurrence of the
         * specified substring.  The last occurrence of the empty string ""
         * is considered to occur at the index value @c this.length().
         *
         * <p>The returned index is the largest value @c k for which:
         * <pre>@c @code
         * this.startsWith(str, k)
         * @endcode</pre>
         * If no such value of @c k exists, then @c -1 is returned.
         *
         * @param   str   the substring to search for.
         * @return  the index of the last occurrence of the specified substring,
         *          or @c -1 if there is no such occurrence.
         */
        gint lastIndexOf(String const &str) const;

        /**
         * Returns the index within this string of the last occurrence of the
         * specified substring, searching backward starting at the specified index.
         *
         * <p>The returned index is the largest value @c k for which:
         * <pre>@c @code
         *     k <= Math.min(fromIndex, this.length()) &&
         *                   this.startsWith(str, k)
         * @endcode</pre>
         * If no such value of @c k exists, then @c -1 is returned.
         *
         * @param   str         the substring to search for.
         * @param   fromIndex   the index to start the search from.
         * @return  the index of the last occurrence of the specified substring,
         *          searching backward from the specified index,
         *          or @c -1 if there is no such occurrence.
         */
        gint lastIndexOf(String const &str, gint fromIndex) const;

        /**
         * Returns a string that is a substring of this string. The
         * substring begins with the character at the specified index and
         * extends to the end of this string. <p>
         * Examples:
         * @code{c++}
         * "unhappy".subString(2) returns "happy"
         * "Harbison".subString(3) returns "bison"
         * "emptiness".subString(9) returns "" (an empty string)
         * @endcode
         *
         * @param      beginIndex   the beginning index, inclusive.
         * @return     the specified substring.
         * @throws     IndexOutOfBoundsException  if
         *             @c beginIndex is negative or larger than the
         *             length of this @c String object.
         */
        String subString(gint beginIndex) const;

        /**
         * Returns a string that is a substring of this string. The
         * substring begins at the specified @c beginIndex and
         * extends to the character at index @c endIndex - 1.
         * Thus the length of the substring is @c endIndex-beginIndex.
         * <p>
         * Examples:
         * @code{c++}
         * "hamburger".subString(4, 8) returns "urge"
         * "smiles".subString(1, 5) returns "mile"
         * @endcode
         *
         * @param      beginIndex   the beginning index, inclusive.
         * @param      endIndex     the ending index, exclusive.
         * @return     the specified substring.
         * @throws     IndexOutOfBoundsException  if the
         *             @c beginIndex is negative, or
         *             @c endIndex is larger than the length of
         *             this @c String object, or
         *             @c beginIndex is larger than
         *             @c endIndex.
         */
        String subString(gint beginIndex, gint endIndex) const;

        /**
         * Returns a character sequence that is a subsequence of this sequence.
         *
         * <p> An invocation of this method of the form
         *
         * @code{c++}
         * str.subSequence(begin,&nbsp;end)@endcode
         *
         * behaves in exactly the same way as the invocation
         *
         * @code{c++}
         * str.subString(begin,&nbsp;end)@endcode
         *
         * @apiNote
         * This method is defined so that the @c String class can implement
         * the @c CharSequence interface.
         *
         * @param   beginIndex   the begin index, inclusive.
         * @param   endIndex     the end index, exclusive.
         * @return  the specified subsequence.
         *
         * @throws  IndexOutOfBoundsException
         *          if @c beginIndex or @c endIndex is negative,
         *          if @c endIndex is greater than @c length(),
         *          or if @c beginIndex is greater than @c endIndex
         *
         *
         */
        CharSequence &subSequence(gint startIndex, gint endIndex) const override;

        /**
         * Concatenates the specified string to the end of this string.
         * <p>
         * If the length of the argument string is @c 0, then this
         * @c String object is returned. Otherwise, a
         * @c String object is returned that represents a character
         * sequence that is the concatenation of the character sequence
         * represented by this @c String object and the character
         * sequence represented by the argument string.
         * <p>
         * Examples:
         * @code
         *  "cares".concat("s"); // returns "caress".
         *  "to".concat("get").concat("her"); // returns "together"
         * @endcode
         *
         * @param   str   the @c String that is concatenated to the end
         *                of this @c String.
         * @return  a string that represents the concatenation of this object's
         *          characters followed by the string argument's characters.
         */
        String concat(String const &str) const;

        /**
         * Returns a string resulting from replacing all occurrences of
         * @c oldChar in this string with @c newChar.
         * <p>
         * If the character @c oldChar does not occur in the
         * character sequence represented by this @c String object,
         * then a reference to this @c String object is returned.
         * Otherwise, a @c String object is returned that
         * represents a character sequence identical to the character sequence
         * represented by this @c String object, except that every
         * occurrence of @c oldChar is replaced by an occurrence
         * of @c newChar.
         * <p>
         * Examples:
         * @code{c++}
         * "mesquite in your cellar".replace('e', 'o')
         *         returns "mosquito in your collar"
         * "the war of baronets".replace('r', 'y')
         *         returns "the way of bayonets"
         * "sparring with a purple porpoise".replace('p', 't')
         *         returns "starring with a turtle tortoise"
         * "JonL".replace('q', 'x') returns "JonL" (no change)
         * @endcode
         *
         * @param   oldChar   the old character.
         * @param   newChar   the new character.
         * @return  a string derived from this string by replacing every
         *          occurrence of @c oldChar with @c newChar.
         */
        String replace(gchar oldChar, gchar newChar) const;

        /**
         * Returns true if and only if this string contains the specified
         * sequence of char values.
         *
         * @param s the sequence to search for
         * @return true if this string contains @c s, false otherwise
         *
         */
        gbool contains(CharSequence const &s) const;

        /**
         * Replaces each substring of this string that matches the literal target
         * sequence with the specified literal replacement sequence. The
         * replacement proceeds from the beginning of the string to the end, for
         * example, replacing "aa" with "b" in the string "aaa" will result in
         * "ba" rather than "ab".
         *
         * @param  target The sequence of char values to be replaced
         * @param  replacement The replacement sequence of char values
         * @return  The resulting string
         *
         */
        String replace(CharSequence const &target, CharSequence const &replacement) const;

        /**
         * Converts all of the characters in this @c String to lower
         * case using the rules of the default locale. This method is equivalent to
         * @c toLowerCase(Locale.getDefault()).
         * <p>
         * @c Note: This method is locale sensitive, and may produce unexpected
         * results if used for strings that are intended to be interpreted locale
         * independently.
         * Examples are programming language identifiers, protocol keys, and HTML
         * tags.
         * For instance, @c "TITLE"::toLowerCase() in a Turkish locale
         * returns @c "t\\u0131tle", where '\\u0131' is the
         * LATIN SMALL LETTER DOTLESS I character.
         * To obtain correct results for locale insensitive strings, use
         * @c toLowerCase(Locale.ROOT).
         *
         * @return  the @c String, converted to lowercase.
         */
        String toLowerCase() const;

        /**
         * Converts all of the characters in this @c String to upper
         * case using the rules of the default locale. This method is equivalent to
         * @c toUpperCase(Locale.getDefault()).
         * <p>
         * @c Note: This method is locale sensitive, and may produce unexpected
         * results if used for strings that are intended to be interpreted locale
         * independently.
         * Examples are programming language identifiers, protocol keys, and HTML
         * tags.
         * For instance, @c "title"::toUpperCase() in a Turkish locale
         * returns @c "T\\u0130TLE", where '\\u0130' is the
         * LATIN CAPITAL LETTER I WITH DOT ABOVE character.
         * To obtain correct results for locale insensitive strings, use
         * @c toUpperCase(Locale.ROOT).
         *
         * @return  the @c String, converted to uppercase.
         */
        String toUpperCase() const;

        /**
         * Returns a string whose value is this string, with all leading
         * and trailing space removed, where space is defined
         * as any character whose codepoint is less than or equal to
         * @c 'U+0020' (the space character).
         * <p>
         * If this @c String object represents an empty character
         * sequence, or the first and last characters of character sequence
         * represented by this @c String object both have codes
         * that are not space (as defined above), then a
         * reference to this @c String object is returned.
         * <p>
         * Otherwise, if all characters in this string are space (as
         * defined above), then a  @c String object representing an
         * empty string is returned.
         * <p>
         * Otherwise, let <i>k</i> be the index of the first character in the
         * string whose code is not a space (as defined above) and let
         * <i>m</i> be the index of the last character in the string whose code
         * is not a space (as defined above). A @c String
         * object is returned, representing the substring of this string that
         * begins with the character at index <i>k</i> and ends with the
         * character at index <i>m</i>-that is, the result of
         * @c this.subString(k, m + 1).
         * <p>
         * This method may be used to trim space (as defined above) from
         * the beginning and end of a string.
         *
         * @return  a string whose value is this string, with all leading
         *          and trailing space removed, or this string if it
         *          has no leading or trailing space.
         */
        String trim() const;

        /**
         * Returns a string whose value is this string, with all leading
         * and trailing @a whitespace removed.
         * <p>
         * If this @c String object represents an empty string,
         * or if all code points in this string are
         * @a whitespace, then an empty string
         * is returned.
         * <p>
         * Otherwise, returns a substring of this string beginning with the first
         * code point that is not a @a whitespace
         * up to and including the last code point that is not a
         * @a whitespace.
         * <p>
         * This method may be used to strip
         * @a whitespace from
         * the beginning and end of a string.
         *
         * @return  a string whose value is this string, with all leading
         *          and trailing whitespace removed
         */
        String strip() const;

        /**
         * Returns a string whose value is this string, with all leading
         * @a whitespace removed.
         * <p>
         * If this @c String object represents an empty string,
         * or if all code points in this string are
         * @a whitespace, then an empty string
         * is returned.
         * <p>
         * Otherwise, returns a substring of this string beginning with the first
         * code point that is not a @a whitespace
         * up to and including the last code point of this string.
         * <p>
         * This method may be used to trim
         * @a whitespace from
         * the beginning of a string.
         *
         * @return  a string whose value is this string, with all leading white
         *          space removed
         */
        String stripLeading() const;

        /**
         * Returns a string whose value is this string, with all trailing
         * @a whitespace removed.
         * <p>
         * If this @c String object represents an empty string,
         * or if all characters in this string are
         * @a whitespace, then an empty string
         * is returned.
         * <p>
         * Otherwise, returns a substring of this string beginning with the first
         * code point of this string up to and including the last code point
         * that is not a @a whitespace.
         * <p>
         * This method may be used to trim
         * @a whitespace from
         * the end of a string.
         *
         * @return  a string whose value is this string, with all trailing white
         *          space removed
         */
        String stripTrailing() const;

        /**
         * Returns @c true if the string is empty or contains only
         * @a whitespace codepoints,
         * otherwise @c false.
         *
         * @return @c true if the string is empty or contains only
         *         @a whitespace codepoints,
         *         otherwise @c false
         */
        gbool isBlank() const;

        /**
         * Returns a string whose value is this string, with escape sequences
         * translated as if in a string literal.
         * <p>
         * Escape sequences are translated as follows;
         * <table class="striped">
         *   <caption style="display:none">Translation</caption>
         *   <thead>
         *   <tr>
         *     <th scope="col">Escape</th>
         *     <th scope="col">Name</th>
         *     <th scope="col">Translation</th>
         *   </tr>
         *   </thead>
         *   <tbody>
         *   <tr>
         *     <th scope="row">@c \\b</th>
         *     <td>backspace</td>
         *     <td>@c U+0008</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\t</th>
         *     <td>horizontal tab</td>
         *     <td>@c U+0009</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\n</th>
         *     <td>line feed</td>
         *     <td>@c U+000A</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\f</th>
         *     <td>form feed</td>
         *     <td>@c U+000C</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\r</th>
         *     <td>carriage return</td>
         *     <td>@c U+000D</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\s</th>
         *     <td>space</td>
         *     <td>@c U+0020</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\"</th>
         *     <td>double quote</td>
         *     <td>@c U+0022</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\'</th>
         *     <td>single quote</td>
         *     <td>@c U+0027</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\\\</th>
         *     <td>backslash</td>
         *     <td>@c U+005C</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\0 - \\377</th>
         *     <td>octal escape</td>
         *     <td>code point equivalents</td>
         *   </tr>
         *   <tr>
         *     <th scope="row">@c \\<line-terminator></th>
         *     <td>continuation</td>
         *     <td>discard</td>
         *   </tr>
         *   </tbody>
         * </table>
         *
         * @note
         * This method does <em>not</em> translate Unicode escapes such as "@c \\u2022".
         *
         * @throws IllegalArgumentException when an escape sequence is malformed.
         *
         * @return String with escape sequences translated.
         */
        String translateEscapes() const;

        /**
         * This object (which is already a string!) is itself returned.
         *
         * @return  the string itself.
         */
        String toString() const override;

        /**
         * Converts this string to a new character array.
         *
         * @return  a newly allocated character array whose length is the length
         *          of this string and whose contents are initialized to contain
         *          the character sequence represented by this string.
         */
        CharArray toChars() const;

        /**
         * Returns the string representation of the @c Object argument.
         *
         * @param   obj   an @c Object.
         * @return  if the argument is @c null, then a string equal to
         *          @c "null"; otherwise, the value of
         *          @c obj::toString() is returned.
         */
        static String valueOf(Object const &obj);

        /**
         * Returns the string representation of the @c char array
         * argument. The contents of the character array are copied; subsequent
         * modification of the character array does not affect the returned
         * string.
         *
         * @param   data     the character array.
         * @return  a @c String that contains the characters of the
         *          character array.
         */
        static String valueOf(CharArray const &data);

        /**
         * Returns the string representation of a specific subarray of the
         * @c char array argument.
         * <p>
         * The @c offset argument is the index of the first
         * character of the subarray. The @c count argument
         * specifies the length of the subarray. The contents of the subarray
         * are copied; subsequent modification of the character array does not
         * affect the returned string.
         *
         * @param   data     the character array.
         * @param   offset   initial offset of the subarray.
         * @param   count    length of the subarray.
         * @return  a @c String that contains the characters of the
         *          specified subarray of the character array.
         * @throws    IndexOutOfBoundsException if @c offset is
         *          negative, or @c count is negative, or
         *          @c offset+count is larger than
         *          @c data.length.
         */
        static String valueOf(CharArray const &data, gint offset, gint count);

        /**
         * Returns the string representation of the @c boolean argument.
         *
         * @param   b   a @c boolean.
         * @return  if the argument is @c true, a string equal to
         *          @c "true" is returned; otherwise, a string equal to
         *          @c "false" is returned.
         */
        static String valueOf(gbool b);

        /**
         * Returns the string representation of the @c char
         * argument.
         *
         * @param   c   a @c char.
         * @return  a string of length @c 1 containing
         *          as its single character the argument @c c.
         */
        static String valueOf(gchar c);

        /**
         * Returns the string representation of the @c int argument.
         * <p>
         * The representation is exactly the one returned by the
         * @c Integer::toString method of one argument.
         *
         * @param   i   an @c int.
         * @return  a string representation of the @c int argument.
         */
        static String valueOf(gint i);

        /**
         * Returns the string representation of the @c long argument.
         * <p>
         * The representation is exactly the one returned by the
         * @c Long::toString method of one argument.
         *
         * @param   l   a @c long.
         * @return  a string representation of the @c long argument.
         */
        static String valueOf(glong l);

        /**
         * Returns the string representation of the @c float argument.
         * <p>
         * The representation is exactly the one returned by the
         * @c Float::toString method of one argument.
         *
         * @param   f   a @c float.
         * @return  a string representation of the @c float argument.
         */
        static String valueOf(gfloat f);

        /**
         * Returns the string representation of the @c double argument.
         * <p>
         * The representation is exactly the one returned by the
         * @c Double::toString method of one argument.
         *
         * @param   d   a @c double.
         * @return  a  string representation of the @c double argument.
         */
        static String valueOf(gdouble d);

        /**
         * Returns a string whose value is the concatenation of this
         * string repeated @c count times.
         * <p>
         * If this string is empty or count is zero then the empty
         * string is returned.
         *
         * @param   count number of times to repeat
         *
         * @return  A string composed of this string repeated
         *          @c count times or the empty string if this
         *          string is empty or count is zero
         *
         * @throws  IllegalArgumentException if the @c count is
         *          negative.
         *
         *
         */
        String repeat(gint count) const;

        ~String() override;

        template<class Str,
                ClassOf(1)::OnlyIf< Class< Str >::isString() && Class< Str >::isArray() > = 1,
                class CharT = typename Class< Str >::ArrayElement>
        String operator+(Str &&str) const
        {
            // Find number of chars
            glong n = Class< Str >::MEMORY_SIZE / Class< CharT >::MEMORY_SIZE;
            if (n < 0) {
                // Overflow: Required length exceed implementation limit.
                n = 0x7FFFFFFF;
            }

            // Remove the last null character
            if (n > 0 && n <= CharArray::SOFT_MAX_LENGTH && str[n - 1] == 0) {
                n -= 1;
            }

            gint count = (gint) n;

            // Launch Concat operation.
            return (Class< CharT >::MEMORY_SIZE == 1)
                   ? mixedConcat(CORE_CAST(BYTES, str), count)
                   : (Class< CharT >::MEMORY_SIZE == 2) ? mixedConcat(CORE_CAST(CHARS, str), count)
                                                        : mixedConcat(CORE_CAST(INTS, str), count);
        }

        template<class Str,
                ClassOf(1)::OnlyIf< Class< Str >::isString() && Class< Str >::isPointer() > = 1,
                class CharT = typename Class< Str >::PointerTarget>
        String operator+(Str &&str) const
        {
            // Find number of chars
            glong n = -1;
            while (str[++n] != 0)
                ;

            if (n < 0) {
                // Overflow: Required length exceed implementation limit.
                n = 0x7FFFFFFF;
            }

            gint count = (gint) n;

            // Launch Concat operation.
            return (Class< CharT >::MEMORY_SIZE == 1)
                   ? mixedConcat(CORE_CAST(BYTES, str), count)
                   : (Class< CharT >::MEMORY_SIZE == 2) ? mixedConcat(CORE_CAST(CHARS, str), count)
                                                        : mixedConcat(CORE_CAST(INTS, str), count);
        }

    private:
        String mixedConcat(BYTES bytes, gint count2) const;

        String mixedConcat(CHARS chars, gint count2) const;

        String mixedConcat(INTS codePoints, gint count2) const;
    };

} // core

#endif // CORE24_STRING_H
