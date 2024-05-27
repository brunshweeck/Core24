//
// Created by brunshweeck on 25 mai 2024.
//

#include "MathUtils.h"

extern "C" gdouble sin(gdouble);
extern "C" gdouble cos(gdouble);
extern "C" gdouble tan(gdouble);
extern "C" gdouble asin(gdouble);
extern "C" gdouble acos(gdouble);
extern "C" gdouble atan(gdouble);
extern "C" gdouble sinh(gdouble);
extern "C" gdouble cosh(gdouble);
extern "C" gdouble tanh(gdouble);
extern "C" gdouble log(gdouble);
extern "C" gdouble log10(gdouble);
extern "C" gdouble log1p(gdouble);
extern "C" gdouble expm1(gdouble);
extern "C" gdouble sqrt(gdouble);
extern "C" gdouble atan2(gdouble, gdouble);
extern "C" gdouble remainder(gdouble, gdouble);
extern "C" gdouble fma(gdouble, gdouble, gdouble);

namespace core
{
    MathUtils::MathUtils()
    {
    }

    gdouble MathUtils::sin(gdouble a)
    {
        return ::sin(a);
    }

    gdouble MathUtils::cos(gdouble a)
    {
        return ::cos(a);
    }

    gdouble MathUtils::tan(gdouble a)
    {
        return ::tan(a);
    }

    gdouble MathUtils::asin(gdouble a)
    {
        return ::asin(a);
    }

    gdouble MathUtils::acos(gdouble a)
    {
        return ::acos(a);
    }

    gdouble MathUtils::atan(gdouble a)
    {
        return ::atan(a);
    }

    gdouble MathUtils::log(gdouble a)
    {
        return ::log(a);
    }

    gdouble MathUtils::log10(gdouble a)
    {
        return ::log10(a);
    }

    gdouble MathUtils::sqrt(gdouble a)
    {
        return ::sqrt(a);
    }

    gdouble MathUtils::IEEEremainder(gdouble f1, gdouble f2)
    {
        return ::remainder(f1, f2);
    }

    gdouble MathUtils::atan2(gdouble y, gdouble x)
    {
        return ::atan2(y, x);
    }

    gdouble MathUtils::sinh(gdouble x)
    {
        return ::sinh(x);
    }

    gdouble MathUtils::cosh(gdouble x)
    {
        return ::cosh(x);
    }

    gdouble MathUtils::tanh(gdouble x)
    {
        return ::tanh(x);
    }

    gdouble MathUtils::expm1(gdouble x)
    {
        return ::expm1(x);
    }

    gdouble MathUtils::log1p(gdouble x)
    {
        return ::log1p(x);
    }

    gfloat MathUtils::fma(gfloat a, gfloat b, gfloat c)
    {
        return (gfloat) ::fma(a, b, c);
    }

    gdouble MathUtils::fma(gdouble a, gdouble b, gdouble c)
    {
        return ::fma(a, b, c);
    }
} // core