set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES_SRC 
    Src/Log.hpp
    Src/MarkdownIndex.hpp Src/MarkdownIndex.cpp
)

add_subdirectory(PerfTools)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_lib CustomPerfTools)
