cmake_minimum_required(VERSION 3.11...3.28 FATAL_ERROR)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(RASM_ROOT_PROJECT ON)
endif()

if(NOT CMAKE_BUILD_TYPE OR (CMAKE_BUILD_TYPE STREQUAL Debug) OR
  (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo))
    set(RASM_DEBUG 1)
else()
  set(RASM_DEBUG 0)
endif()


project(rasm)

include(GNUInstallDirs)


set(RASM_HEADERS
  "librasm/rasm.h"
  "librasm/lib/error.h"
  "librasm/lib/riscv.h"
  "librasm/lib/number.h"
  "librasm/lib/debug.h"
  "librasm/lib/charconv.h"
  "librasm/lib/charconv/base.h"
  "librasm/lib/charconv/float.h"
  "librasm/lib/charconv/table.h"
  "librasm/lib/syntax.h"
  "librasm/lib/input.h"
  "librasm/lib/string.h"
  "librasm/lib/source.h"
  "librasm/lib/token.h"
  "librasm/lib/token/scan.h")

set(RASM_SOURCES
  "librasm/lib/rasm.c"
  "librasm/lib/riscv.c"
  "librasm/lib/error.c"
  "librasm/lib/charconv/base.c"
  "librasm/lib/charconv/table.c"
  "librasm/lib/charconv/size.c"
  "librasm/lib/charconv/ssize.c"
  "librasm/lib/charconv/float16.c"
  "librasm/lib/string.c"
  "librasm/lib/source.c"
  "librasm/lib/token.c"
  "librasm/lib/token/scan_symbol.c"
  "librasm/lib/token/scan_string.c"
  "librasm/lib/token/scan_number.c")

add_library(rasm_lib)

set_target_properties(rasm_lib
  PROPERTIES
    DEBUG_POSTFIX "d"
    OUTPUT_NAME "rasm"
    COMPILE_PDB_NAME "rasm"
    COMPILE_PDF_NAME_DEBUG "rasmd")

target_compile_features(rasm_lib PRIVATE c_std_90)

target_compile_definitions(rasm_lib
  PRIVATE
    "RASM_LIB"
  PUBLIC
    $<$<BOOL:RASM_DEBUG>: "RASM_DEBUG" >
    $<$<PLATFORM_ID:Windows>: "_CRT_SECURE_NO_WARNINGS" >)

target_include_directories(rasm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(rasm_lib PRIVATE ${RASM_SOURCES} ${RASM_HEADERS})

add_library(rasm::lib ALIAS rasm_lib)

add_executable(rasm)

target_compile_options(rasm
  PRIVATE
    $<$<C_COMPILER_ID:Clang>:
      "-Weverything"
      "-Wno-unsafe-buffer-usage"
      "-Wno-missing-noreturn"
      "-Wno-implicit-fallthrough"
      "-Wno-switch"
    >)

target_link_libraries(rasm PRIVATE rasm::lib)

target_sources(rasm PRIVATE "rasm/main.c")

add_executable(rasm::rasm ALIAS rasm)

if(RASM_ROOT_PROJECT AND RASM_DEBUG)
  add_executable(charconv.test "librasm/test/charconv.test.c")
  target_link_libraries(charconv.test PRIVATE rasm::lib)
endif()
