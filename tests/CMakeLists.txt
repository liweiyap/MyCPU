include_directories("${PROJECT_SOURCE_DIR}/headers")

set(TESTS
    catch
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
endforeach()