CMAKE_MINIMUM_REQUIRED(VERSION 3.20 FATAL_ERROR)

PROJECT(
        Core24
        VERSION 2024.0.0.1
        DESCRIPTION "THE NEW APPEARANCE OF CXX"
        HOMEPAGE_URL "https://www.coder237.com/Projects/CXX/${PROJECT_NAME}"
        LANGUAGES C CXX ASM
)

SET(CMAKE_C_STANDARD 14)
SET(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_INSTALL_PREFIX "Cmake/VisualStudio2019/Install")

FILE(GLOB LIB_FILES
        "Lib/*/*.cpp" #[[Lib/core/*.cpp and Lib/meta/*.cpp]]
        "Lib/*/*.h"  #[[Lib/core/*.cpp and Lib/meta/*.cpp]]
        "Lib/*/*/*.cpp" #[[Lib/core/*/*.cpp and Lib/meta/*/*.cpp]]
        "Lib/*/*/*.h"  #[[Lib/core/*/*.cpp and Lib/meta/*/*.cpp]]
)

INCLUDE_DIRECTORIES("Lib")


IF (WIN32)
    FILE(GLOB NATIVE_FILES
            "Native/Win32/*/*.cpp"
            "Native/Win32/*/*.h"
            "Native/Win32/*/*/*.cpp"
            "Native/Win32/*/*/*.h"
    )

    INCLUDE_DIRECTORIES("Native/Win32")
ENDIF (WIN32)

ADD_LIBRARY(Core24 ${LIB_FILES} ${NATIVE_FILES}
        Lib/core/DoubleArray.cpp
        Lib/core/DoubleArray.h
        Lib/core/ShortArray.cpp
        Lib/core/ShortArray.h
        Lib/core/BooleanArray.cpp
        Lib/core/BooleanArray.h)

ADD_EXECUTABLE(Main Exe/Main.cpp)

TARGET_LINK_LIBRARIES(Main PRIVATE Core24)

INSTALL(TARGETS Core24 EXPORT Core2024 DESTINATION ${CMAKE_INSTALL_PREFIX} EXCLUDE_FROM_ALL)
INSTALL(TARGETS Main EXPORT Core2024 DESTINATION ${CMAKE_INSTALL_PREFIX} EXCLUDE_FROM_ALL)
INSTALL(FILES ${LIB_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX} PERMISSIONS OWNER_READ EXCLUDE_FROM_ALL)

ADD_LIBRARY(LibFiles OBJECT
        Lib/core/Class.cpp
        Lib/core/Class.h
        Lib/core/Object.cpp
        Lib/core/Object.h
        Lib/core/misc/Nil.cpp
        Lib/core/misc/Nil.h
        Lib/core/Comparable.cpp
        Lib/core/Comparable.h
        Lib/core/Number.cpp
        Lib/core/Number.h
        Lib/core/CharSequence.cpp
        Lib/core/CharSequence.h
        Lib/core/CharArray.cpp
        Lib/core/CharArray.h
        Lib/core/ByteArray.cpp
        Lib/core/ByteArray.h
        Lib/core/IntArray.cpp
        Lib/core/IntArray.h
        Lib/core/LongArray.cpp
        Lib/core/LongArray.h
        Lib/core/FloatArray.cpp
        Lib/core/FloatArray.h
        Lib/core/String.cpp
        Lib/core/String.h
        Lib/meta/StringUtils.cpp
        Lib/meta/StringUtils.h
        Lib/core/misc/Precondion.cpp
        Lib/core/misc/Precondition.h
        Lib/core/Boolean.cpp
        Lib/core/Boolean.h
        Lib/core/Integer.cpp
        Lib/core/Integer.h
        Lib/core/Long.cpp
        Lib/core/Long.h
        Lib/core/Byte.cpp
        Lib/core/Byte.h
        Lib/core/Short.cpp
        Lib/core/Short.h
)