//
// Created by brunshweeck on 26 mai 2024.
//

#ifndef CORE24_FOREIGN_H
#define CORE24_FOREIGN_H

#include <core/String.h>
#include <core/misc/Precondition.h>
#include "core/Throwable.h"

namespace core
{
    namespace misc
    {

        class Foreign final : public Object
        {
        private:
            CORE_EXPLICIT Foreign();

            static String strLatin1(glong ptr, glong offset, glong count);

            static String strUtf8(glong ptr, glong offset, glong count);

            static String strUtf16(glong ptr, glong offset, glong count);

            static String strUtf32(glong ptr, glong offset, glong count);

            static String i2str(gint i, gint radix, gbool unsignedNumber);

            static String l2str(glong i, gint radix, gbool unsignedNumber);

            static String f2str(gfloat i, gint precision);

            static String d2str(gdouble i, gint precision);

        public:
            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isArray()> = 1,
                    class ChrT = typename Class<Str>::ArrayElement,
                    ClassOf(1)::OnlyIf<Class<ChrT>::isCharacter() && Class<ChrT>::MEMORY_SIZE == 1> = 1>
            static String str(Str &&str, gbool isLatin1)
            {
                gint count = Class<Str>::MEMORY_SIZE;
                if (count > 0 && str[count - 1] == 0) {
                    // remove string ending mark
                    count -= 1;
                }
                return isLatin1
                       ? strLatin1(CORE_CAST(glong, str), 0, count)
                       : strUtf8(CORE_CAST(glong, str), 0, count);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isArray()> = 1,
                    class ChrT = typename Class<Str>::ArrayElement,
                    ClassOf(1)::OnlyIf<Class<ChrT>::isCharacter() && sizeof(ChrT) == 1> = 1>
            static String str(Str &&str, gint offset, gint count, gbool isLatin1)
            {
                gint count0 = Class<Str>::MEMORY_SIZE;
                try {
                    Precondition::checkIndexFromSize(offset, count, count0);
                    return isLatin1
                           ? strLatin1(CORE_CAST(glong, str), 0, count)
                           : strUtf8(CORE_CAST(glong, str), 0, count);
                } catch (Throwable const &ex) {
                    ex.throws(Trace("core::misc::Foreign"_S, str(CORE_FUNCTION), str(CORE_FILE), CORE_LINE));
                }
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isString() && Class<Str>::isArray()> = 1,
                    class CharT = typename Class<Str>::ArrayElement
            >
            static String str(Str &&str)
            {
                gint count = Class<Str>::MEMORY_SIZE;
                if (count > 0 && str[count - 1] == 0) {
                    // remove string ending mark
                    count -= 1;
                }
                return Class<CharT>::MEMORY_SIZE == 2
                       ? strUtf16(CORE_CAST(glong, str), 0, count * 2LL)
                       : strUtf32(CORE_CAST(glong, str), 0, count * 4LL);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isString() && Class<Str>::isArray()> = 1,
                    class CharT = typename Class<Str>::ArrayElement
            >
            static String str(Str &&str, gint offset, gint count)
            {
                gint count0 = Class<Str>::MEMORY_SIZE;
                Precondition::checkIndexFromSize(offset, count, count0);
                return Class<CharT>::MEMORY_SIZE == 2
                       ? strUtf16(CORE_CAST(glong, str), offset * 2LL, count * 2LL)
                       : strUtf32(CORE_CAST(glong, str), offset * 4LL, count * 4LL);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isPointer()> = 1,
                    class ChrT = typename Class<Str>::PointerTarget,
                    ClassOf(1)::OnlyIf<Class<ChrT>::isCharacter() && sizeof(ChrT) == 1> = 1>
            static String str(Str &&str, gbool isLatin1)
            {
                gint count = 0;
                while (str[count] != 0) count++;
                return isLatin1
                       ? strLatin1(CORE_CAST(glong, str), 0, count)
                       : strUtf8(CORE_CAST(glong, str), 0, count);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isPointer()> = 1,
                    class ChrT = typename Class<Str>::PointerTarget,
                    ClassOf(1)::OnlyIf<Class<ChrT>::isCharacter() && sizeof(ChrT) == 1> = 1>
            static String str(Str &&str, gint offset, gint count, gbool isLatin1)
            {
                return isLatin1
                       ? strLatin1(CORE_CAST(glong, str), offset, count)
                       : strUtf8(CORE_CAST(glong, str), offset, count);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isString() && Class<Str>::isPointer()> = 1,
                    class CharT = typename Class<Str>::ArrayElement
            >
            static String str(Str &&str)
            {
                gint count = 0;
                while (str[count] != 0) count++;
                return Class<CharT>::MEMORY_SIZE == 2
                       ? strUtf16(CORE_CAST(glong, str), 0, count * 2LL)
                       : strUtf32(CORE_CAST(glong, str), 0, count * 4LL);
            }

            template<class Str,
                    ClassOf(1)::OnlyIf<Class<Str>::isString() && Class<Str>::isPointer()> = 1,
                    class CharT = typename Class<Str>::ArrayElement
            >
            static String str(Str &&str, gint offset, gint count)
            {
                return Class<CharT>::MEMORY_SIZE == 2
                       ? strUtf16(CORE_CAST(glong, str), offset * 2LL, count * 2LL)
                       : strUtf32(CORE_CAST(glong, str), offset * 4LL, count * 4LL);
            }

            template<class Num, ClassOf(1)::OnlyIf<Class<Num>::isInteger()> = 1>
            static String str(Num num)
            {
                return Class<Num>::MEMORY_SIZE == 2
                       ? i2str(num & 0xffff, 10, Class<Num>::template isSame<unsigned short>())
                       : Class<Num>::MEMORY_SIZE <= 4
                         ? i2str((gint) num, 10, Class<Num>::template isSame<unsigned int>()
                                                 | Class<Num>::template isSame<unsigned long>())
                         : l2str((glong) num, 10, Class<Num>::template isSame<unsigned long>()
                                                  | Class<Num>::template isSame<unsigned long long>());
            }

            template<class Num, ClassOf(1)::OnlyIf<Class<Num>::isInteger()> = 1>
            static String str(Num num, gint radix)
            {
                return Class<Num>::MEMORY_SIZE == 2
                       ? i2str(num & 0xffff, radix, Class<Num>::template isSame<unsigned short>())
                       : Class<Num>::MEMORY_SIZE <= 4
                         ? i2str((gint) num, radix, Class<Num>::template isSame<unsigned int>()
                                                    | Class<Num>::template isSame<unsigned long>())
                         : l2str((glong) num, radix, Class<Num>::template isSame<unsigned long>()
                                                     | Class<Num>::template isSame<unsigned long long>());
            }

            template<class Num, ClassOf(1)::OnlyIf<Class<Num>::isFloating()> = 1>
            static String str(Num num)
            {
                return Class<Num>::MEMORY_SIZE <= 4
                       ? f2str((gfloat) num, -1)
                       : d2str((gdouble) num, -1);
            }

            template<class Num, ClassOf(1)::OnlyIf<Class<Num>::isFloating()> = 1>
            static String str(Num num, gint precision)
            {
                return Class<Num>::MEMORY_SIZE <= 4
                       ? f2str((gfloat) num, precision)
                       : d2str((gdouble) num, precision);
            }

        };

    } // misc
} // core

#endif //CORE24_FOREIGN_H
