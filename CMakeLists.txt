cmake_minimum_required(VERSION 2.8)
project(MYCPU)

set(CMAKE_CXX_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(include)

add_executable(myCPU myCPU.cpp)
target_compile_features(myCPU PRIVATE cxx_lambdas)    # use C++11
target_link_libraries(myCPU std_input_parser)         # tried foreach() but linking error
target_link_libraries(myCPU disassembly)
target_link_libraries(myCPU stack)
target_link_libraries(myCPU stack_execute)
target_link_libraries(myCPU simulation)

add_subdirectory(tests)