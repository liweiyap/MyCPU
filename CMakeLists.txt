cmake_minimum_required(VERSION 2.8)
project(MYCPU)

set(CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(include)

set(TESTS
    myCPU
)

foreach(TEST ${TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_compile_features(${TEST} PRIVATE cxx_lambdas)  # use C++11
    set_target_properties(${TEST} PROPERTIES COMPILE_FLAGS -g)
    target_link_libraries(${TEST} std_input_parser)  # tried foreach() but linking error
    target_link_libraries(${TEST} disassembly)
    target_link_libraries(${TEST} stack)
    target_link_libraries(${TEST} stack_execute)
    target_link_libraries(${TEST} simulation)
endforeach()