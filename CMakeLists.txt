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
        Lib/core/XString.cpp
        Lib/core/XString.h
        Lib/core/Complex.cpp
        Lib/core/Complex.h)

ADD_EXECUTABLE(Main Exe/Main.cpp)

TARGET_LINK_LIBRARIES(Main PRIVATE Core24)

INSTALL(TARGETS Core24 EXPORT Core2024 DESTINATION ${CMAKE_INSTALL_PREFIX} EXCLUDE_FROM_ALL)
INSTALL(TARGETS Main EXPORT Core2024 DESTINATION ${CMAKE_INSTALL_PREFIX} EXCLUDE_FROM_ALL)
INSTALL(FILES ${LIB_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX} PERMISSIONS OWNER_READ EXCLUDE_FROM_ALL)

SET(Python_EXECUTABLE "PyGen/PyEnv/Scripts/python.exe")
SET(Python3_EXECUTABLE $Python_EXECUTABLE)