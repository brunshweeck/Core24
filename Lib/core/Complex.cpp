//
// Created by brunshweeck on 3 juin 2024.
//

#include <core/Complex.h>
#include <core/Double.h>
#include <core/String.h>

namespace core
{
    Complex::Complex(gdouble real, gdouble imag) : re(real), im(imag)
    {
    }

    Complex::Complex(gdouble real) : Complex(real, 0.0)
    {

    }

    Complex::Complex(misc::__cplex32_t const &cplex) : Complex(0.0, 0.0)
    {
        struct ComplexF
        {
        public:
            gfloat _Val[2];
        };

        CORE_ALIAS(Complex32, Class< ComplexF >::Pointer);

        Complex32 z = CORE_CAST(Complex32, &cplex);

        re = z->_Val[0];
        im = z->_Val[1];
    }

    Complex::Complex(misc::__cplex64_t const &cplex) : Complex(0.0, 0.0)
    {
        struct ComplexD
        {
        public:
            gdouble _Val[2];
        };

        CORE_ALIAS(Complex64, Class< ComplexD >::Pointer);

        Complex64 z = CORE_CAST(Complex64, &cplex);

        re = z->_Val[0];
        im = z->_Val[1];
    }

    Complex::Complex(misc::__cplex64x_t const &cplex) : Complex(0.0, 0.0)
    {
        struct ComplexL
        {
        public:
            long double _Val[2];
        };

        CORE_ALIAS(Complex128, Class< ComplexL >::Pointer);

        Complex128 z = CORE_CAST(Complex128, &cplex);

        re = (gdouble) z->_Val[0];
        im = (gdouble) z->_Val[1];
    }

    gbool Complex::isNaN() const
    {
        return Double::isNaN(re) || Double::isNaN(im);
    }

    gbool Complex::isInfinite() const
    {
        return Double::isInfinite(re) || Double::isInfinite(im);
    }

    gbool Complex::isFinite() const
    {
        return Double::isFinite(re) && Double::isFinite(im);
    }

    gbool Complex::isReal() const
    {
        return im == 0.0;
    }

    gbool Complex::isImag() const
    {
        return re == 0.0;
    }

    Complex Complex::valueOf(String const &str0)
    {
        String str = str0.strip();
    }

    Complex Complex::valueOf(gdouble real)
    {
        return real;
    }

    String Complex::toString() const
    {
        String str;
        if (re == 0) {
            if (isFinite()) {
                str = Double::toString(im) + "i"_S;
            }
            else if (isNaN()) {
                str = "(NaN)i"_S;
            }
            else {
                str = (im > 0) ? "(inf)i"_S : "-(inf)i"_S;
            }
        }
        else {
            str = Double::toString(re);
            if (im != 0) {
                if (isFinite()) {
                    if (re > 0) {
                        str += "+"_S;
                    }
                    str += Double::toString(im) + "i"_S;
                }
                else if (isNaN()) {
                    str += "+(NaN)i"_S;
                }
                else {
                    str += (im > 0) ? "+(inf)i"_S : "-(inf)i"_S;
                }
            }
        }
        return str;
    }

    gdouble Complex::real() const
    {
        return re;
    }

    gdouble Complex::imag() const
    {
        return im;
    }

    gint Complex::intValue() const
    {
        return (gint) real();
    }

    glong Complex::longValue() const
    {
        return (glong) real();
    }

    gfloat Complex::floatValue() const
    {
        return (gfloat) real();
    }

    gdouble Complex::doubleValue() const
    {
        return real();
    }

    gbyte Complex::byteValue() const
    {
        return (gbyte) intValue();
    }

    gshort Complex::shortValue() const
    {
        return (gshort) intValue();
    }

    Complex Complex::reverse() const
    {
        return Complex(im, re);
    }

    Complex Complex::conjugate() const
    {
        return Complex(re, -im);
    }

    Complex Complex::negate() const
    {
        return Complex(-re, -im);
    }

    gbool Complex::equals(Object const &obj) const
    {
        return this == &obj || Class< Complex >::hasInstance(obj) && compareTo(CORE_XCAST(Complex const, obj)) == 0;
    }

    gint Complex::hash() const
    {
        return Double::hash(re) * 31 + Double::hash(im);
    }

    gint Complex::compareTo(Complex const &anotherComplex) const
    {
        gint r = Double::compare(re, anotherComplex.re);
        if (re == 0) {
            r = Double::compare(im, anotherComplex.im);
        }
        return r;
    }

    Complex Complex::sum(Complex const &z1, Complex const &z2)
    {
        return Complex(z1.re + z2.re, z1.im + z2.im);
    }

    Complex Complex::multiply(Complex const &z1, Complex const &z2)
    {
        return Complex(z1.re * z2.re - z1.im * z2.im, z1.im * z2.re + z1.re * z2.im);
    }

    Complex Complex::divide(Complex const &z1, Complex const &z2)
    {
        if (z2.im == 0) {
            return Complex(z1.re / z2.re, z1.im / z2.re);
        }
        if (z2.re == 0) {
            return Complex(-z1.im * z2.im / z2.im, z1.re * z2.im / z2.im);
        }
        gdouble norm2 = z2.re * z2.re + z2.im * z2.im;
        return Complex((z1.re * z2.re - z1.im * z2.im) / norm2, (z1.im * z2.re + z1.re * z2.im) / norm2);
    }

    gdouble Complex::norm() const
    {
        return Math::sqrt(re * re + im * im);
    }

    gdouble Complex::phase() const
    {
        if (!isNaN()) {
            return Math::NaN;
        }

        if (isReal()) {

            return re < 0
                   /// &pi;
                   ? Math::PI
                   /// 2&pi; = 0
                   : 0.0;
        }

        if (isImag()) {
            return im < 0
                   /// -&pi;/2
                   ? -Math::PI / 2.0
                   /// &pi;/2
                   : Math::PI / 2.0;
        }

        if (isInfinite()) {
            if (Double::isInfinite(re)) {
                if (Double::isInfinite(im)) {
                    if (re > 0 && im > 0) {
                        /// &pi;/4
                        return Math::PI / 4;
                    }
                    else if (re > 0 && im < 0) {
                        /// -&pi;/4
                        return -Math::PI / 4;
                    }
                    else if (re < 0 && im > 0) {
                        /// 3&pi;/4
                        return Math::PI * (3.0 / 4.0);
                    }
                    else {
                        /// 5&pi;/4
                        return Math::PI * (5.0 / 4.0);
                    }
                }
                else {
                    return re < 0
                           /// &pi;
                           ? Math::PI
                           /// 2&pi; = 0
                           : 0.0;
                }
            }
            else {
                return im < 0
                       /// -&pi;/2
                       ? -Math::PI / 2
                       /// &pi;/2
                       : Math::PI / 2;
            }
        }

        if (Math::abs(re) == Math::abs(im)) {
            if (re > 0 && im > 0) {
                /// &pi;/4
                return Math::PI / 4;
            }
            else if (re > 0 && im < 0) {
                /// -&pi;/4
                return -Math::PI / 4;
            }
            else if (re < 0 && im > 0) {
                /// 3&pi;/4
                return Math::PI * (3.0 / 4.0);
            }
            else {
                /// 5&pi;/4
                return Math::PI * (5.0 / 4.0);
            }
        }

        gdouble a = Math::abs(re);

        gdouble r = norm();
        gdouble cos = a / r;

        gdouble phi = Math::acos(a);

        if (re > 0 && im > 0) {
            /// &phi;
            return phi;
        }
        else if (re > 0 && im < 0) {
            /// -&phi;
            return -phi;
        }
        else if (re < 0 && im > 0) {
            /// &pi;-&phi;
            return Math::PI - phi;
        }
        else {
            /// &pi;+&phi;
            return Math::PI + phi;
        }
    }

    Complex Complex::cos(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::acos(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::cosh(Complex const &z)
    {
        /// cosh(z) = (e^z + e^(-z))/2 <br>
        /// cosh(z) = (e^z + 1/e^z)/2 <br>
        Complex eZ = exp(z);
        return (eZ + 1 / eZ) / 2;
    }

    Complex Complex::acosh(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::sin(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::asin(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::sinh(Complex const &z)
    {
        /// sinh(z) = (e^z - e^(-z))/2  <br>
        /// sinh(z) = (e^z - 1/e^z)/2 <br>
        Complex eZ = exp(z);
        return (eZ - 1 / eZ) / 2;
    }

    Complex Complex::asinh(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::tan(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::atan(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::tanh(Complex const &z)
    {
        /// tanh(z) = (e^z + e^(-z))/(e^z - e^(-z)) <br>
        /// tanh(z) = (e^z + 1/e^z)/(e^z - 1/e^z) <br>
        /// tanh(z) = (e^2z + 1)/(e^2z - 1) <br>
        Complex eZ = exp(2 * z);
        return (eZ + 1) / (eZ - 1);
    }

    Complex Complex::atanh(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::exp(Complex const &z)
    {
        /// z = a+ib <br>
        /// e^z= e^(a+bi) <br>
        /// e^z= (e^a)&times;(e^(bi))
        if (z.isReal()) {
            return Math::exp(z.re);
        }
        return rect(Math::exp(z.re), z.im);
    }

    Complex Complex::log(Complex const &z)
    {
        if (z == 1.0) {
            return 0.0;
        }
        if (z == Math::E) {
            return 1.0;
        }

        if (z.isReal()) {
            return Math::log(z.re);
        }

        return Complex(0, 0);
    }

    Complex Complex::log(Complex const &z, Complex const &base)
    {
        if (base == 0) {
            return Math::NaN;
        }
        if (base == Math::E) {
            return log(z);
        }
        else if (base == 10.0) {
            return log10(z);
        }
        else if (base == z) {
            return z / base;
        }
        return log(z) / log(base);
    }

    Complex Complex::log10(Complex const &z)
    {
        if (z == 1.0) {
            return 0.0;
        }
        if (z == 10.0) {
            return 1.0;
        }

        if (z.isReal()) {
            return Math::log10(z.re);
        }

        return Complex(0, 0);
    }

    Complex Complex::rect(gdouble r, gdouble phi)
    {
        return Complex(r * Math::cos(phi), r * Math::sin(phi));
    }

    Complex Complex::norm(Complex const &z)
    {
        return Complex(0, 0);
    }

    Complex Complex::phase(Complex const &z)
    {
        return z.phase();
    }

    gbool Complex::isNaN(Complex const &z)
    {
        return z.isNaN();
    }

    gbool Complex::isFinite(Complex const &z)
    {
        return z.isInfinite();
    }

    gbool Complex::isInfinite(Complex const &z)
    {
        return z.isInfinite();
    }

    Complex Complex::pow(Complex const &z1, Complex const &z2)
    {
        /// z1 = r&times;e^(&phi;i) <br>
        /// z2 = a+ib <br>
        /// z1^z2=(r&times;e^(&phi;i))^z2 = (r^z2)&times;e^(&phi;i&times;z2) <br>
        /// z1^z2= (r^a)&times;(r^bi)&times;e^(&phi;i&times;a)&times;e^(&phi;i&times;bi) <br>
        /// z1^z2= (r^a)&times;e^(&phi;i&times;a)&times;(r^bi)&times;e^(-&phi;&times;b)
        if (z2.isReal()) {
            /// z1 = r&times;e^(&phi;i) <br>
            /// z2 = a <br>
            /// z1^z2=(r&times;e^(&phi;i))^z2 = (r^z2)&times;e^(&phi;i&times;z2) <br>
            /// z1^z2= (r^a)&times;e^(&phi;i&times;a) <br>
            gdouble d = z2.re;
            gdouble r = z1.norm();
            gdouble phi = z1.phase();
            r = Math::pow(r, d);
            phi = phi * d;
            return rect(r, phi);
        }
        else if (z2.isImag()) {
            /// z1 = r&times;e^(&phi;i) <br>
            /// z2 = +ib <br>
            /// z1^z2=(r&times;e^(&phi;i))^z2 = (r^z2)&times;e^(&phi;i&times;z2) <br>
            /// z1^z2= (r^bi)&times;e^(&phi;i&times;bi) <br>
            /// z1^z2= (r^bi)&times;e^(-&phi;&times;b) <br>

            gdouble r = z1.norm();
            gdouble phi = z1.phase();
            return Math::exp(-phi * z2.im);
        }
        else {
            return pow(z1, z2.re) * pow(z1, Complex(0, z2.im));
        }
    }

    Complex Complex::sqrt(Complex &z)
    {
        /// z = r&times;e^(&phi;i) <br>
        /// sqrt(z)=sqrt(r&times;e^(&phi;i)) = sqrt(r)&times;sqrt(e^(&phi;i)) <br>
        /// sqrt(z)= sqrt(r)&times;e^(&phi;i/2) <br>
        gdouble r = z.norm();
        gdouble phi = z.phase();
        r = Math::sqrt(r);
        phi = phi / 2;
        return rect(r, phi);
    }

    Complex Complex::cbrt(Complex &z)
    {

        /// z = r&times;e^(&phi;i) <br>
        /// cbrt(z)=cbrt(r&times;e^(&phi;i)) = cbrt(r)&times;cbrt(e^(&phi;i)) <br>
        /// cbrt(z)= cbrt(r)&times;e^(&phi;i/3) <br>
        gdouble r = z.norm();
        gdouble phi = z.phase();
        r = Math::cbrt(r);
        phi = phi / 3;
        return rect(r, phi);
    }
} // core