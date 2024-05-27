# Install script for directory: E:/CLionProjects/Core24

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "Cmake/VisualStudio2019/Install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2024.1.1/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE STATIC_LIBRARY FILES "E:/CLionProjects/Core24/.vscode/cmake/libCore24.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  include("E:/CLionProjects/Core24/.vscode/cmake/CMakeFiles/Core24.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE EXECUTABLE FILES "E:/CLionProjects/Core24/.vscode/cmake/Main.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install/Main.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install/Main.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Program Files/JetBrains/CLion 2024.1.1/bin/mingw/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install/Main.exe")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  include("E:/CLionProjects/Core24/.vscode/cmake/CMakeFiles/Main.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE FILE PERMISSIONS OWNER_READ FILES
    "E:/CLionProjects/Core24/Lib/core/Boolean.cpp"
    "E:/CLionProjects/Core24/Lib/core/Boolean.h"
    "E:/CLionProjects/Core24/Lib/core/BooleanArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/BooleanArray.h"
    "E:/CLionProjects/Core24/Lib/core/Byte.cpp"
    "E:/CLionProjects/Core24/Lib/core/Byte.h"
    "E:/CLionProjects/Core24/Lib/core/ByteArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/ByteArray.h"
    "E:/CLionProjects/Core24/Lib/core/CharArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/CharArray.h"
    "E:/CLionProjects/Core24/Lib/core/CharSequence.cpp"
    "E:/CLionProjects/Core24/Lib/core/CharSequence.h"
    "E:/CLionProjects/Core24/Lib/core/Class.cpp"
    "E:/CLionProjects/Core24/Lib/core/Class.h"
    "E:/CLionProjects/Core24/Lib/core/Comparable.cpp"
    "E:/CLionProjects/Core24/Lib/core/Comparable.h"
    "E:/CLionProjects/Core24/Lib/core/DoubleArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/DoubleArray.h"
    "E:/CLionProjects/Core24/Lib/core/FloatArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/FloatArray.h"
    "E:/CLionProjects/Core24/Lib/core/IntArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/IntArray.h"
    "E:/CLionProjects/Core24/Lib/core/Integer.cpp"
    "E:/CLionProjects/Core24/Lib/core/Integer.h"
    "E:/CLionProjects/Core24/Lib/core/Long.cpp"
    "E:/CLionProjects/Core24/Lib/core/Long.h"
    "E:/CLionProjects/Core24/Lib/core/LongArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/LongArray.h"
    "E:/CLionProjects/Core24/Lib/core/Number.cpp"
    "E:/CLionProjects/Core24/Lib/core/Number.h"
    "E:/CLionProjects/Core24/Lib/core/Object.cpp"
    "E:/CLionProjects/Core24/Lib/core/Object.h"
    "E:/CLionProjects/Core24/Lib/core/Short.cpp"
    "E:/CLionProjects/Core24/Lib/core/Short.h"
    "E:/CLionProjects/Core24/Lib/core/ShortArray.cpp"
    "E:/CLionProjects/Core24/Lib/core/ShortArray.h"
    "E:/CLionProjects/Core24/Lib/core/String.cpp"
    "E:/CLionProjects/Core24/Lib/core/String.h"
    "E:/CLionProjects/Core24/Lib/core/Throwable.cpp"
    "E:/CLionProjects/Core24/Lib/core/Throwable.h"
    "E:/CLionProjects/Core24/Lib/core/Trace.cpp"
    "E:/CLionProjects/Core24/Lib/core/Trace.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Compiler.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Compiler.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Literals.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Literals.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Nil.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Nil.h"
    "E:/CLionProjects/Core24/Lib/core/misc/OS.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/OS.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Precondition.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Precondition.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Templates.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Templates.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Types.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Types.h"
    "E:/CLionProjects/Core24/Lib/meta/StringUtils.cpp"
    "E:/CLionProjects/Core24/Lib/meta/StringUtils.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/CLionProjects/Core24/.vscode/cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
