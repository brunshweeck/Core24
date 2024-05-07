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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE STATIC_LIBRARY FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/Debug/Core24.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE STATIC_LIBRARY FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/Release/Core24.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE STATIC_LIBRARY FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/MinSizeRel/Core24.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE STATIC_LIBRARY FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/RelWithDebInfo/Core24.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Core24.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Core24.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Core24.dir/install-cxx-module-bmi-MinSizeRel.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Core24.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE EXECUTABLE FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/Debug/Main.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE EXECUTABLE FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/Release/Main.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE EXECUTABLE FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/MinSizeRel/Main.exe")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE EXECUTABLE FILES "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/RelWithDebInfo/Main.exe")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Main.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Main.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Main.dir/install-cxx-module-bmi-MinSizeRel.cmake" OPTIONAL)
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    include("E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/CMakeFiles/Main.dir/install-cxx-module-bmi-RelWithDebInfo.cmake" OPTIONAL)
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Cmake/VisualStudio2019/Install" TYPE FILE PERMISSIONS OWNER_READ FILES
    "E:/CLionProjects/Core24/Lib/core/Class.cpp"
    "E:/CLionProjects/Core24/Lib/core/Class.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Compiler.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Compiler.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Literals.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Literals.h"
    "E:/CLionProjects/Core24/Lib/core/misc/OS.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/OS.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Templates.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Templates.h"
    "E:/CLionProjects/Core24/Lib/core/misc/Types.cpp"
    "E:/CLionProjects/Core24/Lib/core/misc/Types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/CLionProjects/Core24/Cmake/VisualStudio2019/Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
