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
add_subdirectory(LittleArgsParser)


add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME}_lib CustomPerfTools LittleArgsParser)

#----- Used to get the current filename

# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-D_FILE_=(__FILE__ + ${SOURCE_PATH_SIZE})")
target_compile_definitions(${CMAKE_PROJECT_NAME}_lib PUBLIC _FILE_="(__FILE__ + ${SOURCE_PATH_SIZE})")