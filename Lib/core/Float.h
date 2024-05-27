//
// Created by brunshweeck on 25 mai 2024.
//

#ifndef CORE24_FLOAT_H
#define CORE24_FLOAT_H

#include "Integer.h"

namespace core
{

    /**
     * The <b>Float</b> class wraps a value of primitive type
     * <b>float</b> in an object. An object of type
     * <b>Float</b> contains a single field whose type is
     * <b>float</b>.
     *
     * @see <a href="https://standards.ieee.org/ieee/754/6210/">
     *      <cite>IEEE Standard for Floating-Point Arithmetic</cite></a>
     */
    class Float final : public virtual Number, public virtual Comparable<Float>
    {
    public:
        /**
         * A constant holding the positive infinity of type
         * <b>float</b>. It is equal to the value returned by
         * <b>Float.fromIntBits(0x7f800000)</b>.
         */
        static CORE_FAST gfloat const POSITIVE_INFINITY = (gfloat) 1.0e+1000L;

        /**
         * A constant holding the negative infinity of type
         * <b>float</b>. It is equal to the value returned by
         * <b>Float.fromIntBits(0xff800000)</b>.
         */
        static CORE_FAST gfloat const NEGATIVE_INFINITY = (gfloat) 1.0e+1000L;

        /**
         * A constant holding a Not-a-Number (NaN) value of type
         * <b>float</b>.  It is equivalent to the value returned by
         * <b>Float.fromIntBits(0x7fc00000)</b>.
         */
        static gfloat const NaN;

        /**
         * A constant holding the largest positive finite value of type
         * <b>float</b>, (2-2<sup>-23</sup>)&middot;2<sup>127</sup>.
         * It is equal to the hexadecimal floating-point literal
         * <b>0x1.fffffeP+127f</b> and also equal to
         * <b>Float.fromIntBits(0x7f7fffff)</b>.
         */
        static CORE_FAST gfloat MAX_VALUE = 0x1.FFFFFEP+127F; // 3.4028235e+38f

        /**
         * A constant holding the smallest positive normal value of type
         * <b>float</b>, 2<sup>-126</sup>.  It is equal to the
         * hexadecimal floating-point literal <b>0x1.0p-126f</b> and also
         * equal to <b>Float.fromIntBits(0x00800000)</b>.
         *
         *
         */
        static CORE_FAST gfloat MIN_NORMAL = 0x1.0P-126F; // 1.17549435E-38f

        /**
         * A constant holding the smallest positive nonzero value of type
         * <b>float</b>, 2<sup>-149</sup>. It is equal to the
         * hexadecimal floating-point literal <b>0x0.000002P-126f</b>
         * and also equal to <b>Float.fromIntBits(0x1)</b>.
         */
        static CORE_FAST gfloat MIN_VALUE = 0x0.000002P-126F; // 1.4e-45f

        /**
         * The number of bits used to represent a <b>float</b> value.
         *
         *
         */
        static CORE_FAST gint SIZE = 32;

        /**
         * The number of bits in the significand of a <b>float</b> value.
         * This is the parameter N in section {@jls 4.2.3</b> of
         * <cite>The Java Language Specification</cite>.
         *
         *
         */
        static CORE_FAST gint PRECISION = 24;

        /**
         * Maximum exponent a finite <b>float</b> variable may have.  It
         * is equal to the value returned by <b>
         * Math.getExponent(Float.MAX_VALUE)</b>.
         *
         *
         */
        static CORE_FAST gint MAX_EXPONENT = (1 << (SIZE - PRECISION - 1)) - 1; // 127

        /**
         * Minimum exponent a normalized <b>float</b> variable may have.
         * It is equal to the value returned by <b>
         * Math.getExponent(Float.MIN_NORMAL)</b>.
         *
         *
         */
        static CORE_FAST gint MIN_EXPONENT = 1 - MAX_EXPONENT; // -126

        /**
         * The number of bytes used to represent a <b>float</b> value.
         *
         *
         */
        static CORE_FAST gint BYTES = SIZE / Byte::SIZE;

        /**
         * Returns a string representation of the <b>float</b>
         * argument. All characters mentioned below are ASCII characters.
         * <ul>
         * <li>If the argument is NaN, the result is the string
         * "<b>NaN</b>".
         * <li>Otherwise, the result is a string that represents the sign and
         *     magnitude (absolute value) of the argument. If the sign is
         *     negative, the first character of the result is
         *     '<b>-</b>' (<b>'&#92;u002D'</b>); if the sign is
         *     positive, no sign character appears in the result. As for
         *     the magnitude <i>m</i>:
         * <ul>
         * <li>If <i>m</i> is infinity, it is represented by the characters
         *     <b>"Infinity"</b>; thus, positive infinity produces
         *     the result <b>"Infinity"</b> and negative infinity
         *     produces the result <b>"-Infinity"</b>.
         * <li>If <i>m</i> is zero, it is represented by the characters
         *     <b>"0.0"</b>; thus, negative zero produces the result
         *     <b>"-0.0"</b> and positive zero produces the result
         *     <b>"0.0"</b>.
         *
         * <li> Otherwise <i>m</i> is positive and finite.
         * It is converted to a string in two stages:
         * <ul>
         * <li> <em>Selection of a decimal</em>:
         * A well-defined decimal <i>d</i><sub><i>m</i></sub>
         * is selected to represent <i>m</i>.
         * This decimal is (almost always) the <em>shortest</em> one that
         * rounds to <i>m</i> according to the round to nearest
         * rounding policy of IEEE 754 floating-point arithmetic.
         * <li> <em>Formatting as a string</em>:
         * The decimal <i>d</i><sub><i>m</i></sub> is formatted as a string,
         * either in plain or in computerized scientific notation,
         * depending on its value.
         * </ul>
         * </ul>
         * </ul>
         *
         * <p>A <em>decimal</em> is a number of the form
         * <i>s</i>&times;10<sup><i>i</i></sup>
         * for some (unique) integers <i>s</i> &gt; 0 and <i>i</i> such that
         * <i>s</i> is not a multiple of 10.
         * These integers are the <em>significand</em> and
         * the <em>exponent</em>, respectively, of the decimal.
         * The <em>length</em> of the decimal is the (unique)
         * positive integer <i>n</i> meeting
         * 10<sup><i>n</i>-1</sup> &le; <i>s</i> &lt; 10<sup><i>n</i></sup>.
         *
         * <p>The decimal <i>d</i><sub><i>m</i></sub> for a finite positive <i>m</i>
         * is defined as follows:
         * <ul>
         * <li>Let <i>R</i> be the set of all decimals that round to <i>m</i>
         * according to the usual <em>round to nearest</em> rounding policy of
         * IEEE 754 floating-point arithmetic.
         * <li>Let <i>p</i> be the minimal length over all decimals in <i>R</i>.
         * <li>When <i>p</i> &ge; 2, let <i>T</i> be the set of all decimals
         * in <i>R</i> with length <i>p</i>.
         * Otherwise, let <i>T</i> be the set of all decimals
         * in <i>R</i> with length 1 or 2.
         * <li>Define <i>d</i><sub><i>m</i></sub> as the decimal in <i>T</i>
         * that is closest to <i>m</i>.
         * Or if there are two such decimals in <i>T</i>,
         * select the one with the even significand.
         * </ul>
         *
         * <p>The (uniquely) selected decimal <i>d</i><sub><i>m</i></sub>
         * is then formatted.
         * Let <i>s</i>, <i>i</i> and <i>n</i> be the significand, exponent and
         * length of <i>d</i><sub><i>m</i></sub>, respectively.
         * Further, let <i>e</i> = <i>n</i> + <i>i</i> - 1 and let
         * <i>s</i><sub>1</sub>&hellip;<i>s</i><sub><i>n</i></sub>
         * be the usual decimal expansion of <i>s</i>.
         * Note that <i>s</i><sub>1</sub> &ne; 0
         * and <i>s</i><sub><i>n</i></sub> &ne; 0.
         * Below, the decimal point <b>'.'</b> is <b>'&#92;u002E'</b>
         * and the exponent indicator <b>'E'</b> is <b>'&#92;u0045'</b>.
         * <ul>
         * <li>Case -3 &le; <i>e</i> &lt; 0:
         * <i>d</i><sub><i>m</i></sub> is formatted as
         * <code>0.0</code>&hellip;<code>0</code><!--
         * --><i>s</i><sub>1</sub>&hellip;<i>s</i><sub><i>n</i></sub>,
         * where there are exactly -(<i>n</i> + <i>i</i>) zeroes between
         * the decimal point and <i>s</i><sub>1</sub>.
         * For example, 123 &times; 10<sup>-4</sup> is formatted as
         * <b>0.0123</b>.
         * <li>Case 0 &le; <i>e</i> &lt; 7:
         * <ul>
         * <li>Subcase <i>i</i> &ge; 0:
         * <i>d</i><sub><i>m</i></sub> is formatted as
         * <i>s</i><sub>1</sub>&hellip;<i>s</i><sub><i>n</i></sub><!--
         * --><code>0</code>&hellip;<code>0.0</code>,
         * where there are exactly <i>i</i> zeroes
         * between <i>s</i><sub><i>n</i></sub> and the decimal point.
         * For example, 123 &times; 10<sup>2</sup> is formatted as
         * <b>12300.0</b>.
         * <li>Subcase <i>i</i> &lt; 0:
         * <i>d</i><sub><i>m</i></sub> is formatted as
         * <i>s</i><sub>1</sub>&hellip;<!--
         * --><i>s</i><sub><i>n</i>+<i>i</i></sub><code>.</code><!--
         * --><i>s</i><sub><i>n</i>+<i>i</i>+1</sub>&hellip;<!--
         * --><i>s</i><sub><i>n</i></sub>,
         * where there are exactly -<i>i</i> digits to the right of
         * the decimal point.
         * For example, 123 &times; 10<sup>-1</sup> is formatted as
         * <b>12.3</b>.
         * </ul>
         * <li>Case <i>e</i> &lt; -3 or <i>e</i> &ge; 7:
         * computerized scientific notation is used to format
         * <i>d</i><sub><i>m</i></sub>.
         * Here <i>e</i> is formatted as by <b style="color:orange;">Integer#toString(int)</b>.
         * <ul>
         * <li>Subcase <i>n</i> = 1:
         * <i>d</i><sub><i>m</i></sub> is formatted as
         * <i>s</i><sub>1</sub><code>.0E</code><i>e</i>.
         * For example, 1 &times; 10<sup>23</sup> is formatted as
         * <b>1.0E23</b>.
         * <li>Subcase <i>n</i> &gt; 1:
         * <i>d</i><sub><i>m</i></sub> is formatted as
         * <i>s</i><sub>1</sub><code>.</code><i>s</i><sub>2</sub><!--
         * -->&hellip;<i>s</i><sub><i>n</i></sub><code>E</code><i>e</i>.
         * For example, 123 &times; 10<sup>-21</sup> is formatted as
         * <b>1.23E-19</b>.
         * </ul>
         * </ul>
         *
         * <p>To create localized string representations of a floating-point
         * value, use subclasses of <b style="color:orange;">java.text.NumberFormat</b>.
         *
         * @param   f   the <b>float</b> to be converted.
         * @return a string representation of the argument.
         */
        static String toString(gfloat f);

        /**
         * Returns a hexadecimal string representation of the
         * <b>float</b> argument. All characters mentioned below are
         * ASCII characters.
         *
         * <ul>
         * <li>If the argument is NaN, the result is the string
         *     "<b>NaN</b>".
         * <li>Otherwise, the result is a string that represents the sign and
         * magnitude (absolute value) of the argument. If the sign is negative,
         * the first character of the result is '<b>-</b>'
         * (<b>'&#92;u002D'</b>); if the sign is positive, no sign character
         * appears in the result. As for the magnitude <i>m</i>:
         *
         * <ul>
         * <li>If <i>m</i> is infinity, it is represented by the string
         * <b>"Infinity"</b>; thus, positive infinity produces the
         * result <b>"Infinity"</b> and negative infinity produces
         * the result <b>"-Infinity"</b>.
         *
         * <li>If <i>m</i> is zero, it is represented by the string
         * <b>"0x0.0p0"</b>; thus, negative zero produces the result
         * <b>"-0x0.0p0"</b> and positive zero produces the result
         * <b>"0x0.0p0"</b>.
         *
         * <li>If <i>m</i> is a <b>float</b> value with a
         * normalized representation, sub-strings are used to represent the
         * significand and exponent fields.  The significand is
         * represented by the characters <b>"0x1."</b>
         * followed by a lowercase hexadecimal representation of the rest
         * of the significand as a fraction.  Trailing zeros in the
         * hexadecimal representation are removed unless all the digits
         * are zero, in which case a single zero is used. Next, the
         * exponent is represented by <b>"p"</b> followed
         * by a decimal string of the unbiased exponent as if produced by
         * a call to <b style="color:orange;">Integer#toString(int) Integer.toString</b> on the
         * exponent value.
         *
         * <li>If <i>m</i> is a <b>float</b> value with a subnormal
         * representation, the significand is represented by the
         * characters <b>"0x0."</b> followed by a
         * hexadecimal representation of the rest of the significand as a
         * fraction.  Trailing zeros in the hexadecimal representation are
         * removed. Next, the exponent is represented by
         * <b>"p-126"</b>.  Note that there must be at
         * least one nonzero digit in a subnormal significand.
         *
         * </ul>
         *
         * </ul>
         *
         * <table class="striped">
         * <caption>Examples</caption>
         * <thead>
         * <tr><th scope="col">Floating-point Value</th><th scope="col">Hexadecimal String</th>
         * </thead>
         * <tbody>
         * <tr><th scope="row"><b>1.0</b></th> <td><b>0x1.0p0</b></td>
         * <tr><th scope="row"><b>-1.0</b></th>        <td><b>-0x1.0p0</b></td>
         * <tr><th scope="row"><b>2.0</b></th> <td><b>0x1.0p1</b></td>
         * <tr><th scope="row"><b>3.0</b></th> <td><b>0x1.8p1</b></td>
         * <tr><th scope="row"><b>0.5</b></th> <td><b>0x1.0p-1</b></td>
         * <tr><th scope="row"><b>0.25</b></th>        <td><b>0x1.0p-2</b></td>
         * <tr><th scope="row"><b>Float.MAX_VALUE</b></th>
         *     <td><b>0x1.fffffep127</b></td>
         * <tr><th scope="row"><b>Minimum Normal Value</b></th>
         *     <td><b>0x1.0p-126</b></td>
         * <tr><th scope="row"><b>Maximum Subnormal Value</b></th>
         *     <td><b>0x0.fffffep-126</b></td>
         * <tr><th scope="row"><b>Float.MIN_VALUE</b></th>
         *     <td><b>0x0.000002p-126</b></td>
         * </tbody>
         * </table>
         * @param   f   the <b>float</b> to be converted.
         * @return a hex string representation of the argument.
         *
         * @author Joseph D. Darcy
         */
        static String toHexString(gfloat f);

        /**
         * Returns a <b>Float</b> object holding the
         * <b>float</b> value represented by the argument string
         * <b>s</b>.
         *
         * <p>If <b>s</b> is <b>null</b>, then a
         * <b>NullPointerException</b> is thrown.
         *
         * <p>Leading and trailing whitespace characters in <b>s</b>
         * are ignored.  Whitespace is removed as if by the <b style="color:orange;">
         * String#trim</b> method; that is, both ASCII space and control
         * characters are removed. The rest of <b>s</b> should
         * constitute a <i>FloatValue</i> as described by the lexical
         * syntax rules:
         *
         * <blockquote>
         * <dl>
         * <dt><i>FloatValue:</i>
         * <dd><i>Sign<sub>opt</sub></i> <b>NaN</b>
         * <dd><i>Sign<sub>opt</sub></i> <b>Infinity</b>
         * <dd><i>Sign<sub>opt</sub> FloatingPointLiteral</i>
         * <dd><i>Sign<sub>opt</sub> HexFloatingPointLiteral</i>
         * <dd><i>SignedInteger</i>
         * </dl>
         *
         * <dl>
         * <dt><i>HexFloatingPointLiteral</i>:
         * <dd> <i>HexSignificand BinaryExponent FloatTypeSuffix<sub>opt</sub></i>
         * </dl>
         *
         * <dl>
         * <dt><i>HexSignificand:</i>
         * <dd><i>HexNumeral</i>
         * <dd><i>HexNumeral</i> <b>.</b>
         * <dd><b>0x</b> <i>HexDigits<sub>opt</sub>
         *     </i><b>.</b><i> HexDigits</i>
         * <dd><b>0X</b><i> HexDigits<sub>opt</sub>
         *     </i><b>.</b> <i>HexDigits</i>
         * </dl>
         *
         * <dl>
         * <dt><i>BinaryExponent:</i>
         * <dd><i>BinaryExponentIndicator SignedInteger</i>
         * </dl>
         *
         * <dl>
         * <dt><i>BinaryExponentIndicator:</i>
         * <dd><b>p</b>
         * <dd><b>P</b>
         * </dl>
         *
         * </blockquote>
         *
         * where <i>Sign</i>, <i>FloatingPointLiteral</i>,
         * <i>HexNumeral</i>, <i>HexDigits</i>, <i>SignedInteger</i> and
         * <i>FloatTypeSuffix</i> are as defined in the lexical structure
         * sections of
         * <cite>The Java Language Specification</cite>,
         * except that underscores are not accepted between digits.
         * If <b>s</b> does not have the form of
         * a <i>FloatValue</i>, then a <b>NumberFormatException</b>
         * is thrown. Otherwise, <b>s</b> is regarded as
         * representing an exact decimal value in the usual
         * "computerized scientific notation" or as an exact
         * hexadecimal value; this exact numerical value is then
         * conceptually converted to an "infinitely precise"
         * binary value that is then rounded to type <b>float</b>
         * by the usual round-to-nearest rule of IEEE 754 floating-point
         * arithmetic, which includes preserving the sign of a zero
         * value.
         *
         * Note that the round-to-nearest rule also implies overflow and
         * underflow behaviour; if the exact value of <b>s</b> is large
         * enough in magnitude (greater than or equal to (<b style="color:orange;">
         * #MAX_VALUE</b> + <b style="color:orange;">Math#ulp(float) ulp(MAX_VALUE)</b>/2),
         * rounding to <b>float</b> will result in an infinity and if the
         * exact value of <b>s</b> is small enough in magnitude (less
         * than or equal to <b style="color:orange;">#MIN_VALUE</b>/2), rounding to float will
         * result in a zero.
         *
         * Finally, after rounding a <b>Float</b> object representing
         * this <b>float</b> value is returned.
         *
         * <p>To interpret localized string representations of a
         * floating-point value, use subclasses of <b style="color:orange;">
         * java.text.NumberFormat</b>.
         *
         * <p>Note that trailing format specifiers, specifiers that
         * determine the type of a floating-point literal
         * (<b>1.0f</b> is a <b>float</b> value;
         * <b>1.0d</b> is a <b>double</b> value), do
         * <em>not</em> influence the results of this method.  In other
         * words, the numerical value of the input string is converted
         * directly to the target floating-point type.  In general, the
         * two-step sequence of conversions, string to <b>double</b>
         * followed by <b>double</b> to <b>float</b>, is
         * <em>not</em> equivalent to converting a string directly to
         * <b>float</b>.  For example, if first converted to an
         * intermediate <b>double</b> and then to
         * <b>float</b>, the string<br>
         * <b>"1.00000017881393421514957253748434595763683319091796875001d"</b><br>
         * results in the <b>float</b> value
         * <b>1.0000002f</b>; if the string is converted directly to
         * <b>float</b>, <code>1.000000<b>1</b>f</code> results.
         *
         * <p>To avoid calling this method on an invalid string and having
         * a <b>NumberFormatException</b> be thrown, the documentation
         * for <b style="color:orange;">Double#valueOf Double.valueOf</b> lists a regular
         * expression which can be used to screen the input.
         *
         * @param   s   the string to be parsed.
         * @return  a <b>Float</b> object holding the value
         *          represented by the <b>String</b> argument.
         * @throws  NumberFormatException  if the string does not contain a
         *          parsable number.
         */
        static Float valueOf(String const &s);

        /**
         * Returns a <b>Float</b> instance representing the specified
         * <b>float</b> value.
         * If a new <b>Float</b> instance is not required, this method
         * should generally be used in preference to the constructor
         * <b style="color:orange;">#Float(float)</b>, as this method is likely to yield
         * significantly better space and time performance by caching
         * frequently requested values.
         *
         * @param  f a float value.
         * @return a <b>Float</b> instance representing <b>f</b>.
         *
         */
        static Float valueOf(gfloat f);

        /**
         * Returns a new <b>float</b> initialized to the value
         * represented by the specified <b>String</b>, as performed
         * by the <b>valueOf</b> method of class <b>Float</b>.
         *
         * @param  s the string to be parsed.
         * @return the <b>float</b> value represented by the string
         *         argument.
         *
         * @throws NumberFormatException if the string does not contain a
         *               parsable <b>float</b>.
         * @see    Float#valueOf(String)
         *
         */
        static gfloat parseFloat(String const &s);

        /**
         * Returns <b>true</b> if the specified number is a
         * Not-a-Number (NaN) value, <b>false</b> otherwise.
         *
         * @apiNote
         * This method corresponds to the isNaN operation defined in IEEE
         * 754.
         *
         * @param   v   the value to be tested.
         * @return  <b>true</b> if the argument is NaN;
         *          <b>false</b> otherwise.
         */
        static gbool isNaN(gfloat v);

        /**
         * Returns <b>true</b> if the specified number is infinitely
         * large in magnitude, <b>false</b> otherwise.
         *
         * @apiNote
         * This method corresponds to the isInfinite operation defined in
         * IEEE 754.
         *
         * @param   v   the value to be tested.
         * @return  <b>true</b> if the argument is positive infinity or
         *          negative infinity; <b>false</b> otherwise.
         */
        static gbool isInfinite(gfloat v);


        /**
         * Returns <b>true</b> if the argument is a finite floating-point
         * value; returns <b>false</b> otherwise (for NaN and infinity
         * arguments).
         *
         * @apiNote
         * This method corresponds to the isFinite operation defined in
         * IEEE 754.
         *
         * @param f the <b>float</b> value to be tested
         * @return <b>true</b> if the argument is a finite
         * floating-point value, <b>false</b> otherwise.
         *
         */
        static gbool isFinite(gfloat f);

    private:
        /**
         * The value of the Float.
         *
         * @serial
         */
        gfloat value;

    public:

        /**
         * Constructs a newly allocated <b>Float</b> object that
         * represents the primitive <b>float</b> argument.
         *
         * @param   value   the value to be represented by the <b>Float</b>.
         *
         * @deprecated
         * It is rarely appropriate to use this constructor. The static factory
         * <b style="color:orange;">#valueOf(float)</b> is generally a better choice, as it is
         * likely to yield significantly better space and time performance.
         */
        CORE_IMPLICIT Float(gfloat value);

        /**
         * Constructs a newly allocated <b>Float</b> object that
         * represents the argument converted to type <b>float</b>.
         *
         * @param   value   the value to be represented by the <b>Float</b>.
         *
         * @deprecated
         * It is rarely appropriate to use this constructor. Instead, use the
         * static factory method <b style="color:orange;">#valueOf(float)</b> method as follows:
         * <b>Float.valueOf((float)value)</b>.
         */
        CORE_IMPLICIT Float(gdouble value);

        /**
         * Constructs a newly allocated <b>Float</b> object that
         * represents the floating-point value of type <b>float</b>
         * represented by the string. The string is converted to a
         * <b>float</b> value as if by the <b>valueOf</b> method.
         *
         * @param   s   a string to be converted to a <b>Float</b>.
         * @throws      NumberFormatException if the string does not contain a
         *              parsable number.
         *
         * @deprecated
         * It is rarely appropriate to use this constructor.
         * Use <b style="color:orange;">#parseFloat(String)</b> to convert a string to a
         * <b>float</b> primitive, or use <b style="color:orange;">#valueOf(String)</b>
         * to convert a string to a <b>Float</b> object.
         */
        CORE_EXPLICIT Float(String const &s);

        /**
         * Returns <b>true</b> if this <b>Float</b> value is a
         * Not-a-Number (NaN), <b>false</b> otherwise.
         *
         * @return  <b>true</b> if the value represented by this object is
         *          NaN; <b>false</b> otherwise.
         */
        gbool isNaN() const;

        /**
         * Returns <b>true</b> if this <b>Float</b> value is
         * infinitely large in magnitude, <b>false</b> otherwise.
         *
         * @return  <b>true</b> if the value represented by this object is
         *          positive infinity or negative infinity;
         *          <b>false</b> otherwise.
         */
        gbool isInfinite() const;

        /**
         * Returns a string representation of this <b>Float</b> object.
         * The primitive <b>float</b> value represented by this object
         * is converted to a <b>String</b> exactly as if by the method
         * <b>toString</b> of one argument.
         *
         * @return  a <b>String</b> representation of this object.
         * @see Float#toString(float)
         */
        String toString() const override;

        /**
         * Returns the value of this <b>Float</b> as a <b>byte</b> after
         * a narrowing primitive conversion.
         *
         * @return  the <b>float</b> value represented by this object
         *          converted to type <b>byte</b>
         * @jls 5.1.3 Narrowing Primitive Conversion
         */
        gbyte byteValue() const override;

        /**
         * Returns the value of this <b>Float</b> as a <b>short</b>
         * after a narrowing primitive conversion.
         *
         * @return  the <b>float</b> value represented by this object
         *          converted to type <b>short</b>
         * @jls 5.1.3 Narrowing Primitive Conversion
         *
         */
        gshort shortValue() const override;

        /**
         * Returns the value of this <b>Float</b> as an <b>int</b> after
         * a narrowing primitive conversion.
         *
         * @return  the <b>float</b> value represented by this object
         *          converted to type <b>int</b>
         * @jls 5.1.3 Narrowing Primitive Conversion
         */
        gint intValue() const override;

        /**
         * Returns value of this <b>Float</b> as a <b>long</b> after a
         * narrowing primitive conversion.
         *
         * @return  the <b>float</b> value represented by this object
         *          converted to type <b>long</b>
         * @jls 5.1.3 Narrowing Primitive Conversion
         */
        glong longValue() const override;

        /**
         * Returns the <b>float</b> value of this <b>Float</b> object.
         *
         * @return the <b>float</b> value represented by this object
         */
        gfloat floatValue() const override;

        /**
         * Returns the value of this <b>Float</b> as a <b>double</b>
         * after a widening primitive conversion.
         *
         * @apiNote
         * This method corresponds to the convertFormat operation defined
         * in IEEE 754.
         *
         * @return the <b>float</b> value represented by this
         *         object converted to type <b>double</b>
         * @jls 5.1.2 Widening Primitive Conversion
         */
        gdouble doubleValue() const override;

        /**
         * Returns a hash code for this <b>Float</b> object. The
         * result is the integer bit representation, exactly as produced
         * by the method <b style="color:orange;">#toIntBits(float)</b>, of the primitive
         * <b>float</b> value represented by this <b>Float</b>
         * object.
         *
         * @return a hash code value for this object.
         */
        gint hash() const override;

        /**
         * Returns a hash code for a <b>float</b> value; compatible with
         * <b>Float.hashCode()</b>.
         *
         * @param value the value to hash
         * @return a hash code value for a <b>float</b> value.
         *
         */
        static gint hash(gfloat value);

        /**
         * Compares this object against the specified object.  The result
         * is <b>true</b> if and only if the argument is not
         * <b>null</b> and is a <b>Float</b> object that
         * represents a <b>float</b> with the same value as the
         * <b>float</b> represented by this object. For this
         * purpose, two <b>float</b> values are considered to be the
         * same if and only if the method <b style="color:orange;">#toIntBits(float)</b>
         * returns the identical <b>int</b> value when applied to
         * each.
         *
         * @apiNote
         * This method is defined in terms of <b style="color:orange;">
         * #toIntBits(float)</b> rather than the <b>==</b> operator on
         * <b>float</b> values since the <b>==</b> operator does
         * <em>not</em> define an equivalence relation and to satisfy the
         * <b style="color:green;">Object#equals equals contract</b> an equivalence
         * relation must be implemented; see <a
         * href="">this discussion</a> for
         * details of floating-point equality and equivalence.
         *
         * @param obj the object to be compared
         * @return  <b>true</b> if the objects are the same;
         *          <b>false</b> otherwise.
         * @see Float#toIntBits(float)
         * @jls 15.21.1 Numerical Equality Operators == and !=
         */
        gbool equals(Object const &obj) const override;

        /**
         * Returns a representation of the specified floating-point value
         * according to the IEEE 754 floating-point "single format" bit
         * layout.
         *
         * <p>Bit 31 (the bit that is selected by the mask
         * <b>0x80000000</b>) represents the sign of the floating-point
         * number.
         * Bits 30-23 (the bits that are selected by the mask
         * <b>0x7f800000</b>) represent the exponent.
         * Bits 22-0 (the bits that are selected by the mask
         * <b>0x007fffff</b>) represent the significand (sometimes called
         * the mantissa) of the floating-point number.
         *
         * <p>If the argument is positive infinity, the result is
         * <b>0x7f800000</b>.
         *
         * <p>If the argument is negative infinity, the result is
         * <b>0xff800000</b>.
         *
         * <p>If the argument is NaN, the result is <b>0x7fc00000</b>.
         *
         * <p>In all cases, the result is an integer that, when given to the
         * <b style="color:orange;">#fromIntBits(int)</b> method, will produce a floating-point
         * value the same as the argument to <b>toIntBits</b>
         * (except all NaN values are collapsed to a single
         * "canonical" NaN value).
         *
         * @param   value   a floating-point number.
         * @return the bits that represent the floating-point number.
         */
        static gint toIntBits(gfloat value);

        /**
         * Returns a representation of the specified floating-point value
         * according to the IEEE 754 floating-point "single format" bit
         * layout, preserving Not-a-Number (NaN) values.
         *
         * <p>Bit 31 (the bit that is selected by the mask
         * <b>0x80000000</b>) represents the sign of the floating-point
         * number.
         * Bits 30-23 (the bits that are selected by the mask
         * <b>0x7f800000</b>) represent the exponent.
         * Bits 22-0 (the bits that are selected by the mask
         * <b>0x007fffff</b>) represent the significand (sometimes called
         * the mantissa) of the floating-point number.
         *
         * <p>If the argument is positive infinity, the result is
         * <b>0x7f800000</b>.
         *
         * <p>If the argument is negative infinity, the result is
         * <b>0xff800000</b>.
         *
         * <p>If the argument is NaN, the result is the integer representing
         * the actual NaN value.  Unlike the <b>toIntBits</b>
         * method, <b>toRawIntBits</b> does not collapse all the
         * bit patterns encoding a NaN to a single "canonical"
         * NaN value.
         *
         * <p>In all cases, the result is an integer that, when given to the
         * <b style="color:orange;">#fromIntBits(int)</b> method, will produce a
         * floating-point value the same as the argument to
         * <b>toRawIntBits</b>.
         *
         * @param   value   a floating-point number.
         * @return the bits that represent the floating-point number.
         *
         */
        static gint toRawIntBits(gfloat value);

        /**
         * Returns the <b>float</b> value corresponding to a given
         * bit representation.
         * The argument is considered to be a representation of a
         * floating-point value according to the IEEE 754 floating-point
         * "single format" bit layout.
         *
         * <p>If the argument is <b>0x7f800000</b>, the result is positive
         * infinity.
         *
         * <p>If the argument is <b>0xff800000</b>, the result is negative
         * infinity.
         *
         * <p>If the argument is any value in the range
         * <b>0x7f800001</b> through <b>0x7fffffff</b> or in
         * the range <b>0xff800001</b> through
         * <b>0xffffffff</b>, the result is a NaN.  No IEEE 754
         * floating-point operation provided by Java can distinguish
         * between two NaN values of the same type with different bit
         * patterns.  Distinct values of NaN are only distinguishable by
         * use of the <b>Float.toRawIntBits</b> method.
         *
         * <p>In all other cases, let <i>s</i>, <i>e</i>, and <i>m</i> be three
         * values that can be computed from the argument:
         *
         * <b> @code
         * int s = ((bits >> 31) == 0) ? 1 : -1;
         * int e = ((bits >> 23) & 0xff);
         * int m = (e == 0) ?
         *                 (bits & 0x7fffff) << 1 :
         *                 (bits & 0x7fffff) | 0x800000;
         * @endcode </b>
         *
         * Then the floating-point result equals the value of the mathematical
         * expression <i>s</i>&middot;<i>m</i>&middot;2<sup><i>e</i>-150</sup>.
         *
         * <p>Note that this method may not be able to return a
         * <b>float</b> NaN with exactly same bit pattern as the
         * <b>int</b> argument.  IEEE 754 distinguishes between two
         * kinds of NaNs, quiet NaNs and <i>signaling NaNs</i>.  The
         * differences between the two kinds of NaN are generally not
         * visible in Java.  Arithmetic operations on signaling NaNs turn
         * them into quiet NaNs with a different, but often similar, bit
         * pattern.  However, on some processors merely copying a
         * signaling NaN also performs that conversion.  In particular,
         * copying a signaling NaN to return it to the calling method may
         * perform this conversion.  So <b>fromIntBits</b> may
         * not be able to return a <b>float</b> with a signaling NaN
         * bit pattern.  Consequently, for some <b>int</b> values,
         * <b>toRawIntBits(fromIntBits(start))</b> may
         * <i>not</i> equal <b>start</b>.  Moreover, which
         * particular bit patterns represent signaling NaNs is platform
         * dependent; although all NaN bit patterns, quiet or signaling,
         * must be in the NaN range identified above.
         *
         * @param   bits   an integer.
         * @return  the <b>float</b> floating-point value with the same bit
         *          pattern.
         */
        static gfloat fromIntBits(gint bits);

        /**
         * {@return the <b>float</b> value closest to the numerical value
         * of the argument, a floating-point binary16 value encoded in a
         * <b>short</b></b> The conversion is exact; all binary16 values can
         * be exactly represented in <b>float</b>.
         *
         * Special cases:
         * <ul>
         * <li> If the argument is zero, the result is a zero with the
         * same sign as the argument.
         * <li> If the argument is infinite, the result is an infinity
         * with the same sign as the argument.
         * <li> If the argument is a NaN, the result is a NaN.
         * </ul>
         *
         * <h4><a id=binary16Format>IEEE 754 binary16 format</a></h4>
         * The IEEE 754 standard defines binary16 as a 16-bit format, along
         * with the 32-bit binary32 format (corresponding to the <b>
         * float</b> type) and the 64-bit binary64 format (corresponding to
         * the <b>double</b> type). The binary16 format is similar to the
         * other IEEE 754 formats, except smaller, having all the usual
         * IEEE 754 values such as NaN, signed infinities, signed zeros,
         * and subnormals. The parameters (JLS {@jls 4.2.3</b>) for the
         * binary16 format are N = 11 precision bits, K = 5 exponent bits,
         * <i>E</i><sub><i>max</i></sub> = 15, and
         * <i>E</i><sub><i>min</i></sub> = -14.
         *
         * @apiNote
         * This method corresponds to the convertFormat operation defined
         * in IEEE 754 from the binary16 format to the binary32 format.
         * The operation of this method is analogous to a primitive
         * widening conversion (JLS {@jls 5.1.2</b>).
         *
         * @param floatBinary16 the binary16 value to convert to <b>float</b>
         *
         */
        static gfloat fromFloat16(gshort floatBinary16);

        /**
         * {@return the floating-point binary16 value, encoded in a <b>
         * short</b>, closest in value to the argument</b>
         * The conversion is computed under the <b style="color:green;">
         * round to nearest even rounding mode</b>.
         *
         * Special cases:
         * <ul>
         * <li> If the argument is zero, the result is a zero with the
         * same sign as the argument.
         * <li> If the argument is infinite, the result is an infinity
         * with the same sign as the argument.
         * <li> If the argument is a NaN, the result is a NaN.
         * </ul>
         *
         * The <a href="">binary16 format</a> is discussed in
         * more detail in the <b style="color:orange;">#float16ToFloat</b> method.
         *
         * @apiNote
         * This method corresponds to the convertFormat operation defined
         * in IEEE 754 from the binary32 format to the binary16 format.
         * The operation of this method is analogous to a primitive
         * narrowing conversion (JLS {@jls 5.1.3</b>).
         *
         * @param f the <b>float</b> value to convert to binary16
         *
         */
        static gshort toFloat16(gfloat f);

        /**
         * Compares two <b>Float</b> objects numerically.
         *
         * This method imposes a total order on <b>Float</b> objects
         * with two differences compared to the incomplete order defined by
         * the Java language numerical comparison operators (<b><, <=,
         * ==, >=, ></b>) on <b>float</b> values.
         *
         * <ul><li> A NaN is <em>unordered</em> with respect to other
         *          values and unequal to itself under the comparison
         *          operators.  This method chooses to define <b>
         *          Float.NaN</b> to be equal to itself and greater than all
         *          other <b>double</b> values (including <b>
         *          Float.POSITIVE_INFINITY</b>).
         *
         *      <li> Positive zero and negative zero compare equal
         *      numerically, but are distinct and distinguishable values.
         *      This method chooses to define positive zero (<b>+0.0f</b>),
         *      to be greater than negative zero (<b>-0.0f</b>).
         * </ul>
         *
         * This ensures that the <i>natural ordering</i> of <b>Float</b>
         * objects imposed by this method is <i>consistent with
         * equals</i>; see <a href="">this
         * discussion</a> for details of floating-point comparison and
         * ordering.
         *
         *
         * @param   anotherFloat   the <b>Float</b> to be compared.
         * @return  the value <b>0</b> if <b>anotherFloat</b> is
         *          numerically equal to this <b>Float</b>; a value
         *          less than <b>0</b> if this <b>Float</b>
         *          is numerically less than <b>anotherFloat</b>;
         *          and a value greater than <b>0</b> if this
         *          <b>Float</b> is numerically greater than
         *          <b>anotherFloat</b>.
         *
         * @jls 15.20.1 Numerical Comparison Operators <b><</b>, <b><=</b>, <b>></b>, and <b>>=</b>
         *
         */
        gint compareTo(Float const &other) const override;

        /**
         * Compares the two specified <b>float</b> values. The sign
         * of the integer value returned is the same as that of the
         * integer that would be returned by the call:
         * <pre>
         *    Float.valueOf(f1).compareTo(Float.valueOf(f2))
         * </pre>
         *
         * @param   f1        the first <b>float</b> to compare.
         * @param   f2        the second <b>float</b> to compare.
         * @return  the value <b>0</b> if <b>f1</b> is
         *          numerically equal to <b>f2</b>; a value less than
         *          <b>0</b> if <b>f1</b> is numerically less than
         *          <b>f2</b>; and a value greater than <b>0</b>
         *          if <b>f1</b> is numerically greater than
         *          <b>f2</b>.
         *
         */
        static gint compare(gfloat f1, gfloat f2);

        /**
         * Adds two <b>float</b> values together as per the + operator.
         *
         * @apiNote This method corresponds to the addition operation
         * defined in IEEE 754.
         *
         * @param a the first operand
         * @param b the second operand
         * @return the sum of <b>a</b> and <b>b</b>
         * @jls 4.2.4 Floating-Point Operations
         *
         */
        static gfloat sum(gfloat a, gfloat b);

        /**
         * Returns the greater of two <b>float</b> values
         * as if by calling <b style="color:orange;">Math#max(float, float) Math.max</b>.
         *
         * @apiNote
         * This method corresponds to the maximum operation defined in
         * IEEE 754.
         *
         * @param a the first operand
         * @param b the second operand
         * @return the greater of <b>a</b> and <b>b</b>
         *
         */
        static gfloat max(gfloat a, gfloat b);

        /**
         * Returns the smaller of two <b>float</b> values
         * as if by calling <b style="color:orange;">Math#min(float, float) Math.min</b>.
         *
         * @apiNote
         * This method corresponds to the minimum operation defined in
         * IEEE 754.
         *
         * @param a the first operand
         * @param b the second operand
         * @return the smaller of <b>a</b> and <b>b</b>
         *
         */
        static gfloat min(gfloat a, gfloat b);
    };

} // core

#endif //CORE24_FLOAT_H
