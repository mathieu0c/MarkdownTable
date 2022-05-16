cmake_minimum_required (VERSION 3.8)

set(LIB_NAME "CustomPerfTools")

project(${LIB_NAME})

set(SOURCE_FILES
    ScopeTimer.h    ScopeTimer.cpp
    Utils.h         Utils.cpp
)

# We declare the project as a static library and add all the source code files to it.
add_library(${LIB_NAME} STATIC ${SOURCE_FILES})