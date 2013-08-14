# Detects whether a preprocessor symbol is defined by the current C compiler
function(is_symbol_defined output_variable symbol)
    enable_language(C)

set(is_symbol_defined_code "
#if defined(${symbol})
int main() { return 0; }
#endif
")

    file(WRITE "${CMAKE_BINARY_DIR}/is_symbol_defined.c" "${is_symbol_defined_code}")

    try_compile(is_symbol_defined_result "${CMAKE_BINARY_DIR}" "${CMAKE_BINARY_DIR}/is_symbol_defined.c")

    if(is_symbol_defined_result)
        set(${output_variable} TRUE PARENT_SCOPE)
    else()
        set(${output_variable} FALSE PARENT_SCOPE)
    endif()
endfunction()
