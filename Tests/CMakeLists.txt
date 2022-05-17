set (CMAKE_CXX_STANDARD 20)

link_libraries(${CMAKE_PROJECT_NAME}_lib)

#pass
# add_executable(firstTest_bin firstTest.cpp)
# add_test(firstTest firstTest_bin)

#fail
# add_executable(secondTest_bin secondTest.cpp)
# add_test(secondTest secondTest_bin)

add_executable(test_md_parseLine_bin test_md_parseLine.cpp)
add_test(test_md_parseLine test_md_parseLine_bin)
add_executable(test_md_parseStr_bin test_md_parseStr.cpp)
add_test(test_md_parseStr test_md_parseStr_bin)
add_executable(test_md_parseFile_bin test_md_parseFile.cpp)
add_test(test_md_parseFile test_md_parseFile_bin)

add_executable(test_md_insertTableInFile_bin test_md_insertTableInFile.cpp)
add_test(test_md_insertTableInFile test_md_insertTableInFile_bin)