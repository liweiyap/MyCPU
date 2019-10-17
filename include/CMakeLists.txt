include_directories("${PROJECT_SOURCE_DIR}/headers")

set(LIBS
    std_input_parser
    disassembly
    stack
    stack_execute
    simulation
)

foreach(LIB ${LIBS})
    add_library(${LIB} ${LIB}.cpp)
endforeach()