cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME_CUSTOM MarkdownTable)
project(${PROJECT_NAME_CUSTOM} VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    add_compile_definitions(COMPILE_DEBUG)
    message("debug mode")
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

# add_subdirectory(Src/PerfTools)
add_subdirectory(Src)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}_lib)

add_executable(TEMP_TEST_EXE
    main2.cpp
)
target_link_libraries(TEMP_TEST_EXE ${CMAKE_PROJECT_NAME}_lib)


set(CPACK_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(Tests)


string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-D_FILE_=(__FILE__ + ${SOURCE_PATH_SIZE})")
target_compile_definitions(${CMAKE_PROJECT_NAME}_lib PUBLIC _FILE_="(__FILE__ + ${SOURCE_PATH_SIZE})")