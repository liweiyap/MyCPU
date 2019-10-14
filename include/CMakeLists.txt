include_directories("${PROJECT_SOURCE_DIR}/headers")

set(LIBS
    std_input_parser
    disassembly
)

foreach(LIB ${LIBS})
    add_library(${LIB} ${LIB}.cpp)
endforeach()