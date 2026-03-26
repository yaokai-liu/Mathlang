cmake_minimum_required(VERSION 4.1)
project(Mathlang C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    set(TARGET_PREFIX "")
else ()
    set(TARGET_PREFIX "Mathlang_")
endif ()

#add_compile_options("-O3" "-Os")
add_compile_options("-funsigned-char")
add_compile_options("-Wall" "-Wextra" "-Werror")
if (WIN32)
    add_compile_options("-Wno-format")
endif ()

if (ENABLE_TEST_COV)
    add_compile_options("-fprofile-arcs" "-ftest-coverage")
endif ()
if (ENABLE_GPROF)
    add_compile_options("-pg")
    add_link_options("-pg")
endif ()

if (WIN32)
    find_program(POWERSHELL_PATH
            NAMES pwsh powershell.exe
            PATHS "C:/Program Files/PowerShell"
            "C:/Windows/System32/WindowsPowerShell")
    set(EXECUTOR_PATH ${POWERSHELL_PATH})
    set(CMD_HINT "-command")
else()
    find_program(SHELL_PATH NAMES bash)
    set(EXECUTOR_PATH ${SHELL_PATH})
    set(CMD_HINT "-c")
endif()
find_package(Python 3.8 REQUIRED)

set(AUTOMATON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/json")
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/grammar/generated")
set(SCR_CODEGEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src-codegen")
set(SRC_TEMPLATE_DIR "${SCR_CODEGEN_DIR}/template")
set(SRC_SYNTAX_DIR "${SCR_CODEGEN_DIR}/syntax")
set(SRC_RENDER_DIR "${SCR_CODEGEN_DIR}/render")

list(APPEND PROJECT_AUTOMATONS "Mathlang")
list(APPEND AUTOMATON_FILES
        "automaton.json"
        "first_set.json"
        "folded_states.json"
        "follow_set.json"
        "lr_items.json"
        "rules.json"
        "tokens.json")
# create automaton and source directories
foreach(AUTOMATON IN LISTS PROJECT_AUTOMATONS)
    if (NOT EXISTS "${AUTOMATON_DIR}/${AUTOMATON}")
        message(STATUS "${AUTOMATON}'s automaton directory does not exist, make the directory.")
        file(MAKE_DIRECTORY "${AUTOMATON_DIR}/${AUTOMATON}")
    else()
        message(STATUS "${AUTOMATON}'s automaton directory exists, skip.")
    endif ()
    if (NOT EXISTS "${GENERATED_DIR}/${AUTOMATON}")
        message(STATUS "${AUTOMATON}'s automaton source directory does not exist, make the directory.")
        file(MAKE_DIRECTORY "${GENERATED_DIR}/${AUTOMATON}")
    else()
        message(STATUS "${AUTOMATON}'s automaton source directory exists, skip.")
    endif ()
endforeach()
# generate automaton files
set(GRAMMARS
        "Mathlang.xnf:MathEntry:$,MathEntry"
)
foreach(GRAMMAR_TRIPLE IN LISTS GRAMMARS)
    string(FIND "${GRAMMAR_TRIPLE}" ":" pos)
    string(SUBSTRING "${GRAMMAR_TRIPLE}" 0 "${pos}" GRAMMAR_FILE)
    math(EXPR pos "${pos} + 1")  # Skip the separator
    string(SUBSTRING "${GRAMMAR_TRIPLE}" "${pos}" -1 GRAMMAR_PAIR)

    string(FIND "${GRAMMAR_PAIR}" ":" pos)
    string(SUBSTRING "${GRAMMAR_PAIR}" 0 "${pos}" GRAMMAR_ENTRY)
    math(EXPR pos "${pos} + 1")  # Skip the separator
    string(SUBSTRING "${GRAMMAR_PAIR}" "${pos}" -1 GRAMMAR_ENVS)

    string(FIND "${GRAMMAR_FILE}" ".xnf" pos)
    string(SUBSTRING "${GRAMMAR_FILE}" 0 "${pos}" GRAMMAR_NAME)

    execute_process(COMMAND ${Python_EXECUTABLE}
            "${SRC_SYNTAX_DIR}/generate.py"
            "${SRC_SYNTAX_DIR}/${GRAMMAR_FILE}"
            "${GRAMMAR_ENTRY}"
            "--environments=${GRAMMAR_ENVS}"
            "--output-directory=${AUTOMATON_DIR}/${GRAMMAR_NAME}"
            RESULT_VARIABLE PS_RESULT
            OUTPUT_VARIABLE PS_OUTPUT
            ERROR_VARIABLE PS_ERROR
            OUTPUT_STRIP_TRAILING_WHITESPACE
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    if (NOT "${PS_OUTPUT}" STREQUAL "")
        message("   ${PS_OUTPUT}")
    endif()
    if (NOT "${PS_ERROR}" STREQUAL "")
        message(SEND_ERROR "${PS_ERROR}")
    endif()
endforeach ()
# generate source files
execute_process(COMMAND ${Python_EXECUTABLE}
        "${SRC_RENDER_DIR}/codegen.py" "${AUTOMATON_DIR}" "${SRC_TEMPLATE_DIR}" "${GENERATED_DIR}"
        RESULT_VARIABLE PS_RESULT
        OUTPUT_VARIABLE PS_OUTPUT
        ERROR_VARIABLE PS_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
if (NOT "${PS_OUTPUT}" STREQUAL "")
    message("   ${PS_OUTPUT}")
endif()
if (NOT "${PS_ERROR}" STREQUAL "")
    message(SEND_ERROR "${PS_ERROR}")
endif()

if (NOT TARGET meman)
    include_directories(meman)
    aux_source_directory(meman MEMAN_SRC)
    add_library(meman STATIC ${MEMAN_SRC})
    link_libraries(meman)
endif ()

include_directories(include)

file(GLOB_RECURSE MATHLANG_GRAMMAR_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} grammar/*.c grammar/*.h)
add_library(${TARGET_PREFIX}grammar STATIC ${MATHLANG_GRAMMAR_SRC})
target_link_libraries(${TARGET_PREFIX}grammar PRIVATE m)
target_include_directories(${TARGET_PREFIX}grammar PRIVATE grammar)

add_executable(${TARGET_PREFIX}debug test/debug.c)
target_link_libraries(${TARGET_PREFIX}debug PRIVATE ${TARGET_PREFIX}grammar)
target_include_directories(${TARGET_PREFIX}debug PRIVATE grammar)

if (BUILD_MATHLANG_TEST)
    add_compile_definitions("MATHLANG_BUILD_TEST=1")
    aux_source_directory(test/test TEST_UTILS_SRC)
    aux_source_directory(test/tokenize TOKENIZE_TEST_SRC)
    add_executable(${TARGET_PREFIX}test-tokenize ${TEST_UTILS_SRC} ${TOKENIZE_TEST_SRC})
    target_link_libraries(${TARGET_PREFIX}test-tokenize PRIVATE ${TARGET_PREFIX}grammar)
    target_include_directories(${TARGET_PREFIX}test-tokenize PRIVATE grammar test)
endif ()

