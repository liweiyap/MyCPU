cmake_minimum_required(VERSION 2.8)
project(MYCPU)

set(CMAKE_CXX_STANDARD 11)

set(TESTS
    test
)

foreach(TEST ${TESTS})
    add_executable(${TEST} EXCLUDE_FROM_ALL ${TEST}.cpp ${TMP})
    target_compile_features(${TEST} PRIVATE cxx_lambdas)  # use C++11
    set_target_properties(${TEST} PROPERTIES COMPILE_FLAGS -g)
endforeach()