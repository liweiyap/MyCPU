include_directories("${PROJECT_SOURCE_DIR}/headers")

add_library(catch catch.cpp)
add_library(test_helper test_helper.cpp)

set(TESTS
    sample
)

foreach(TEST ${TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_compile_features(${TEST} PRIVATE cxx_lambdas)
    target_link_libraries(${TEST} std_input_parser)
    target_link_libraries(${TEST} disassembly)
    target_link_libraries(${TEST} stack)
    target_link_libraries(${TEST} stack_execute)
    target_link_libraries(${TEST} simulation)
    target_link_libraries(${TEST} catch)
    target_link_libraries(${TEST} test_helper)
endforeach()