//
// Created by bruns on 08/05/2024.
//

#ifndef Core24_OBJECT_H
#define Core24_OBJECT_H

#include <core/misc/Literals.h>

namespace core
{
    /**
     * The class @c Object is a root of class hierachy
     */
    class Object
    {
    protected:
        /**
         * The @c Object constructor is only accessible via inherited class
         */
        CORE_IMPLICIT Object();

    public:
        /**
         * Destroy this object
         */
        virtual ~Object();

        /**
         * Indicates whether some other object is "equal to" this one.
         *
         * The @c equals method implements an equivalence relation
         * on non-null object references:
         * @li It is @a reflexive : For any reference value @c x,
         *     @c x.equals(x) should return @c true.
         * @li It is @a symetric : For any reference values @c x and @c y,
         *     @c x.equals(y) should return @c true if and only if @c y.equals(x)
         *     return @c true.
         * @li It is @a transitive : For any reference values @c x, @c y and @c z,
         *     if @c x.equals(y) return @c true, and @c y.equals(z) return @c true,
         *     then @c x.equals(z) should be return @c true
         * @li It is @a consistant : For any reference value @c x and @c y,
         *     mutliple invocation of @c x.equals(y) consistently return @c true,
         *     or consistently return @c false provided no information used in
         *     @c equals  comparisons on the objects is modified.
         *
         * @param obj The object to be compared
         * @return @c true if object instance equals to given object.
         */
        virtual gbool equals(Object const& obj) const;

        /**
         * Returns a hash code value for the object. This method is
         * supported for the benefit of hash tables such as those provided by
         * @c core::util::HashTable.
         *
         * The general contract of @c hash is:
         * @li Whenever it is invoked on the same object more than once during
         *     an execution of a application, the @c hash method
         *     must consistently return the same integer, provided no information
         *     used in @c equals comparisons on the object is modified.
         *     This integer need not remain consistent from one execution of an
         *     application to another execution of the same application.
         * @li If two objects are equal according to the @c equals
         *     method, then calling the @c hash
         *     method on each of the two objects must produce the
         *     same integer result.
         * @li It is @a not required that if two objects are unequal
         *     according to the @c equals method, then calling the
         *     @c hash method on each of the two objects must produce
         *     distinct integer results.  However, the programmer
         *     should be aware that producing distinct integer results for
         *     unequal objects may improve the performance of hash tables.
         *
         * @note
         *     As far as is reasonably practical, the @c hash method defined
         *     by class @c Object returns distinct integers for distinct objects.
         *
         * @return The hash code value for this object
         */
        virtual gint hash() const;
    };

    namespace misc
    {
        class NIL;
    }

    extern misc::NIL& null;
} // core

#endif // Core24_OBJECT_H
