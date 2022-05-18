set(BINARY ${CMAKE_PROJECT_NAME})

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES_SRC 
    Log.hpp
    Utils.hpp   Utils.cpp
    MdTypes.hpp MdTypes.cpp
    Slugger.hpp Slugger.cpp
    MarkdownIndex.hpp MarkdownIndex.cpp
)

add_subdirectory(PerfTools)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME}_lib CustomPerfTools)
