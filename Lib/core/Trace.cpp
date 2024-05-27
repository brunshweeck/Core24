//
// Created by bruns on 14/05/2024.
//

#include <core/Trace.h>

namespace core
{
    Trace::Trace(String moduleName, String moduleVersion,
                 String declaringClass, String methodName, String fileName, gint lineNumber) :
            module(CORE_CAST(String &&, moduleName)),
            version(CORE_CAST(String &&, moduleVersion)),
            declaringClass(CORE_CAST(String &&, declaringClass)),
            method(CORE_CAST(String &&, methodName)),
            file(CORE_CAST(String &&, fileName)),
            line(lineNumber)
    {
    }

    Trace::Trace(String declaringClass, String methodName, String fileName, gint lineNumber) :
            declaringClass(CORE_CAST(String &&, declaringClass)),
            method(CORE_CAST(String &&, methodName)),
            file(CORE_CAST(String &&, fileName)),
            line(lineNumber)
    {
    }

    Trace::Trace(String functionName, String fileName, gint lineNumber) :
            method(CORE_CAST(String &&, functionName)),
            file(CORE_CAST(String &&, fileName)),
            line(lineNumber)
    {
    }

    String Trace::moduleName() const
    {
        return module;
    }

    String Trace::moduleVersion() const
    {
        return version;
    }

    String Trace::className() const
    {
        return declaringClass;
    }

    String Trace::methodName() const
    {
        return method;
    }

    String Trace::functionName() const
    {
        return methodName();
    }

    String Trace::fileName() const
    {
        return file;
    }

    gint Trace::lineNumber() const
    {
        return line;
    }

    gbool Trace::isNativeMethod() const
    {
        return line == -2;
    }

    String Trace::toString() const
    {
        if (!module.isEmpty()) {
        }

        return ""_S;
    }

    gbool Trace::equals(Object const &obj) const
    {
        if (this == &obj) return true;

        if (!Class<Trace>::hasInstance(obj)) return false;

        Trace const &trace = CORE_XCAST(Trace const, obj);
        return module.equals(trace.module) &&
               version.equals(trace.version) &&
               declaringClass.equals(trace.declaringClass) &&
               method.equals(trace.method) &&
               file.equals(trace.file) &&
               line == trace.line;
    }

    gint Trace::hash() const
    {
        gint hash = 31 * module.hash() + version.hash();
        hash = 31 * hash + declaringClass.hash();
        hash = 31 * hash + method.hash();
        hash = 31 * hash + file.hash();
        hash = 31 * hash + line;

        return hash;
    }
} // core
