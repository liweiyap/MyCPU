include_directories("${PROJECT_SOURCE_DIR}/headers")

add_library(catch catch.cpp)
add_library(test_helper test_helper.cpp)

add_executable(myCPU_tests myCPU_tests.cpp)
target_compile_features(myCPU_tests PRIVATE cxx_lambdas)
target_link_libraries(myCPU_tests std_input_parser)
target_link_libraries(myCPU_tests disassembly)
target_link_libraries(myCPU_tests stack)
target_link_libraries(myCPU_tests stack_execute)
target_link_libraries(myCPU_tests simulation)
target_link_libraries(myCPU_tests catch)
target_link_libraries(myCPU_tests test_helper)