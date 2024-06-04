//
// Created by brunshweeck on 3 juin 2024.
//

#ifndef CORE24_COMPLEX_H
#define CORE24_COMPLEX_H

#include <core/Byte.h>
#include <core/Math.h>

namespace core
{

    class Complex final : public virtual Number, public Comparable< Complex >
    {
        static CORE_FAST gint SIZE_MASK = Class< misc::__cplex64x_t >::MEMORY_SIZE |
                                          Class< misc::__cplex64_t >::MEMORY_SIZE |
                                          Class< misc::__cplex32_t >::MEMORY_SIZE;
    public:
        /**
         * Construct new @c Complex object with given real part and imaginary part.
         *
         * @param real The real part
         * @param imag The imaginary part
         */
        CORE_EXPLICIT Complex(gdouble real, gdouble imag);

        /**
         * Construct newly allocated @c Complex object that
         * represent the native @c gdouble argument as real
         * part.
         *
         * @note The imaginary will be set to zero.
         *
         * @param real The real part
         */
        CORE_IMPLICIT Complex(gdouble real);

        /**
         * Construct newly allocated @c Complex object that
         * represent the native @c __cplex32_t (complex of 32 bits) argument.
         *
         * @note The imaginary will be set to zero.
         *
         * @param real The real part
         */
        CORE_IMPLICIT Complex(misc::__cplex32_t const &);

        /**
         * Construct newly allocated @c Complex object that
         * represent the native @c __cplex64_t (complex of 64 bits) argument.
         *
         * @note The imaginary will be set to zero.
         *
         * @param real The real part
         */
        CORE_IMPLICIT Complex(misc::__cplex64_t const &);

        /**
         * Construct newly allocated @c Complex object that
         * represent the native @c __cplex64x_t (complex of 64 bits) argument.
         *
         * @note The imaginary will be set to zero.
         *
         * @param real The real part
         */
        CORE_IMPLICIT Complex(misc::__cplex64x_t const &);

        /**
         * Returns @c true if this @c Complex value is
         * a Not-a-Number (NaN), @c false otherwise.
         *
         * @note Complex object is Not-a-Number (NaN) if any
         * part of this object is Not-a-Number.
         */
        gbool isNaN() const;

        /**
         * Returns @c true if this @c Complex value is
         * a infinite, @c false otherwise.
         *
         * @note Complex object is infinite if any
         * part of this object is infinite.
         */
        gbool isInfinite() const;

        /**
         * Returns @c true if this @c Complex value is
         * a finite, @c false otherwise.
         *
         * @note Complex object is finite if all
         * parts of this object is finite.
         */
        gbool isFinite() const;

        /**
         * Returns @c true if this @c Complex value is
         * a pure real, @c false otherwise.
         *
         * @note Complex object is pure real if the
         * imaginary part is set to value zero.
         */
        gbool isReal() const;

        /**
         * Returns @c true if this @c Complex value is
         * a pure imaginary, @c false otherwise.
         *
         * @note Complex object is pure imaginary if the
         * real part is set to value zero.
         */
        gbool isImag() const;

        /**
         * Return the @c Complex object holding the
         * @c __cplex64_t value represented by the
         * argument string @c str.
         * All whitespace characters in
         * given string are ignored. Whitespace is removed
         * as if by @c String::strip method; that is, both
         * ascii space and control characters are removed.
         * The rest of string should constitute a @a value
         * (single or double) as described by the lexical
         * syntax rules:
         *
         * <blockquote>
         * <dl>
         * <dt> @a Single-Value: </dt>
         * <dd>Sign<sub>opt</sub> @c NaN </dd>
         * <dd>Sign<sub>opt</sub> @c inf </dd>
         * <dd>Sign<sub>opt</sub> @c infinity </dd>
         * <dd>Sign<sub>opt</sub> @c FloatingPointLiteral  </dd>
         * <dd>Sign<sub>opt</sub> @c HexFloatingPointLiteral  </dd>
         * <dd> @c SignedInteger  </dd>
         * <dd>Sign<sub>opt</sub> @c NaNi </dd>
         * <dd>Sign<sub>opt</sub> @c NaNj </dd>
         * <dd>Sign<sub>opt</sub> @c (NaN)i </dd>
         * <dd>Sign<sub>opt</sub> @c (NaN)j </dd>
         * <dd>Sign<sub>opt</sub> @c infi </dd>
         * <dd>Sign<sub>opt</sub> @c infj </dd>
         * <dd>Sign<sub>opt</sub> @c (inf)i </dd>
         * <dd>Sign<sub>opt</sub> @c (inf)j </dd>
         * <dd>Sign<sub>opt</sub> @c (infinity)j </dd>
         * <dd>Sign<sub>opt</sub> @c (infinity)j </dd>
         * <dd>Sign<sub>opt</sub> @c FloatingPointLiteral i </dd>
         * <dd>Sign<sub>opt</sub> @c FloatingPointLiteral j </dd>
         * <dd>Sign<sub>opt</sub> @c HexFloatingPointLiteral i </dd>
         * <dd>Sign<sub>opt</sub> @c HexFloatingPointLiteral j </dd>
         * <dd>@c SignedInteger i </dd>
         * <dd>Sign<sub>opt</sub> @c SignedInteger j </dd>
         * <dt> @a Double-Values: </dt>
         * <dd>@a SingleValue Sign @a SingleValue i</dd>
         * <dd>@a SingleValue Sign @a SingleValue j</dd>
         * </dl>
         * </blockquote>
         *
         * Example:
         * @code
         *  auto z1=Complex::valueOf("2")
         *  auto z1=Complex::valueOf("5i")
         *  auto z1=Complex::valueOf("2+5i")
         *  auto z2=Complex::valueOf("2+NaNi")
         *  auto z3=Complex::valueOf("2+infi")
         *  auto z4=Complex::valueOf("2+infinityi")//error
         *  auto z5=Complex::valueOf("2+(inf)i")
         *  auto z6=Complex::valueOf("2+(NaN)i")
         *  auto z7=Complex::valueOf("2+(infinity)i")
         * @endcode
         *
         * @param str The String to be parsed
         * @throw NumberFormatException If the string do not
         *          contain a parsable number.
         *
         * @sa Double::parseDouble
         */
        static Complex valueOf(String const &str);

        /**
         * Return a @c Complex object representing the specified
         * @c gdouble value
         *
         * @param real
         */
        static Complex valueOf(gdouble real);

        /**
         * Return the @c String representing this @c Complex object.
         *
         * The native @c gdouble values represented by parts of this
         * object is converted to a string exactly as if by the
         * @c Double::toString method of one argument.
         *
         * @note If one part only is set to zero, this part will be
         * ignored
         *
         * @sa Double::toString
         */
        String toString() const override;

    private:
        /**
         * The field representing the real part of
         * this complex
         */
        gdouble re;

        /**
         * The field representing the imaginary part of
         * this complex
         */
        gdouble im;

    public:
        /**
         * Return the real part of this @c Complex.
         *
         * @return the real part of this number.
         */
        gdouble real() const;

        /**
         * Return the imaginary part of this @c Complex.
         *
         * @return the imaginary part of this number.
         */
        gdouble imag() const;

        /**
         * Returns the real part of this number as an @c gint.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c gint
         */
        gint intValue() const override;

        /**
         * Returns the real part of this number as an @c glong.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c glong
         */
        glong longValue() const override;

        /**
         * Returns the real part of this number as an @c gfloat.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c gfloat
         */
        gfloat floatValue() const override;

        /**
         * Returns the real part of this number as an @c gdouble.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c gdouble
         */
        gdouble doubleValue() const override;

        /**
         * Returns the real part of this number as an @c gbyte.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c gbyte
         */
        gbyte byteValue() const override;

        /**
         * Returns the real part of this number as an @c gshort.
         *
         * @return The numeric value represented real part of this object
         * after conversion to type @c gshort
         */
        gshort shortValue() const override;

        /**
         * Return the reverse form of this complex.
         * <p>
         * This operation is equivalent to
         * @c ~(z*1i) for all complex @c z.
         *
         * @note After this operation the real part will be
         * a imaginary part and vice-versa.
         *
         * @return the reverse form of this number.
         */
        Complex reverse() const;

        /**
         *
         * Return the conjugate form of this complex. For
         * simplify this operation you have possibility to
         * use @a complement operator @c (~), such as:
         * @code
         *     Complex z = 2+3i;
         *     Complex z2 = z.conjugate();
         *     Complex z3 = ~z;
         * @endcode
         *
         * @note After this operation, the sign of
         * imaginary part will be changed by it opposite
         *
         * @return the conjugate form of this complex.
         */
        Complex conjugate() const;

        /**
         *
         * Return the negate form of this complex. For
         * simplify this operation you have possibility to
         * use a prefixed @a minus operator @c (-), such as:
         * @code
         *     Complex z = 2+3i;
         *     Complex z2 = z.negate();
         *     Complex z3 = -z;
         * @endcode
         *
         * @note After this operation, the sign of
         * all parts will be changed by it opposite
         *
         * @return the conjugate form of this complex.
         */
        Complex negate() const;

        /**
         * Return true if the given Complex number equals
         * to this Complex number.s
         */
        gbool equals(Object const &obj) const override;

        /**
         * Return the hash code value of this @c Complex
         * number
         *
         * @return the hash code value of this complex
         */
        gint hash() const override;

        gint compareTo(Complex const &anotherComplex) const override;

        static Complex sum(Complex const &z1, Complex const &z2);

        static Complex multiply(Complex const &z1, Complex const &z2);

        static Complex divide(Complex const &z1, Complex const &z2);

        /**
         * Return the norm of this complex number.
         *
         * @return the distance of this complex number from zero.
         */
        gdouble norm() const;

        /**
         * Return argument, alsa known as the phase angle, of
         * this @c Complex number.
         *
         * @return the phase angle of this complex.
         */
        gdouble phase() const;

        /**
         * Return cosine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex cos(Complex const &z);

        /**
         * Return arc cosine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex acos(Complex const &z);

        /**
         * Return hyperbolic cosine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex cosh(Complex const &z);

        /**
         * Return arc hyperbolic cosine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex acosh(Complex const &z);

        /**
         * Return sine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex sin(Complex const &z);

        /**
         * Return arc sine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex asin(Complex const &z);

        /**
         * Return hyperbolic sine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex sinh(Complex const &z);

        /**
         * Return arc hyperbolic sine of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex asinh(Complex const &z);

        /**
         * Return tangent of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex tan(Complex const &z);

        /**
         * Return arc tangent of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex atan(Complex const &z);

        /**
         * Return hyperbolic tangent of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex tanh(Complex const &z);

        /**
         * Return arc hyperbolic tangent of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex atanh(Complex const &z);

        /**
         * Return exponential of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex exp(Complex const &z);

        /**
         * Return logarithm of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex log(Complex const &z);

        /**
         * Return logarithm of given @c Complex number
         * to given base.
         *
         * @param z the complex number.
         * @param base the logarithm base
         */
        static Complex log(Complex const &z, Complex const& base);

        /**
         * Return decimal logarithm of given @c Complex number
         *
         * @param z the complex number.
         */
        static Complex log10(Complex const &z);

        /**
         * Returns the value of the first argument raised to
         * the power of the second argument
         *
         * @param z1 the first complex number.
         * @param z2 the second complex number.
         */
         static Complex pow(Complex const &z1, Complex const& z2);

         /**
          * Return the square-root of given @c Complex number
          *
          * @param z the complex number
          */
          static Complex sqrt(Complex &z);

         /**
          * Return the cubic-root of given @c Complex number
          *
          * @param z the complex number
          */
          static Complex cbrt(Complex &z);

        /**
         * Obtain newly created @c Complex object with
         * given polar coordinates.
         *
         * @param r the distance from zero (norm).
         * @param phi the phase angle.
         *
         * @sa Complex::norm
         * @sa Complex::phase
         */
        static Complex rect(gdouble r, gdouble phi);

        /**
         * Return the norm this @c Complex number.
         * In other worlds this methods return the
         * distance from zero.
         *
         * @param z the complex number.
         * @return the distance of z from @c 0.
         */
        static Complex norm(Complex const &z);

        /**
         * Return the argument this @c Complex number.
         * In other worlds this methods return the
         * phase angle.
         *
         * @param z the complex number.
         * @return the phase angle.
         */
        static Complex phase(Complex const &z);

        /**
         * Returns @c true if given @c Complex number is
         * a Not-a-Number (NaN), @c false otherwise.
         *
         * @note Complex object is Not-a-Number (NaN) if any
         * part of this object is Not-a-Number.
         */
        static gbool isNaN(Complex const &z);

        /**
         * Returns @c true if given @c Complex number is
         * a infinite, @c false otherwise.
         *
         * @note Complex object is infinite if any
         * part of this object is infinite.
         */
        static gbool isInfinite(Complex const &z);

        /**
         * Returns @c true if given @c Complex number is
         * a finite, @c false otherwise.
         *
         * @note Complex object is finite if all
         * parts of this object is finite.
         */
        static gbool isFinite(Complex const &z);
    };

} // core

#endif //CORE24_COMPLEX_H
