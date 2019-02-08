cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-Wall -g")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(main main.cc queue.cc hashtab.cc)
target_link_libraries(main ${GTEST_LIBRARIES} pthread)

add_executable(queue_test queue_test.cc queue.cc)
target_link_libraries(queue_test ${GTEST_LIBRARIES} pthread)

add_executable(hashtab_test hashtab_test.cc hashtab.cc)
target_link_libraries(hashtab_test ${GTEST_LIBRARIES} pthread)

add_executable(main_test main_test.cc main.cc queue.cc hashtab.cc)
target_link_libraries(main_test ${GTEST_LIBRARIES} pthread)



