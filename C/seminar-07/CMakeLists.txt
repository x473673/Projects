cmake_minimum_required(VERSION 3.0)
project(seminar07)

set(LIST_SOURCES list.c list_utils.c)
add_library(dllist STATIC ${LIST_SOURCES})

add_executable(playground07 main.c)
target_link_libraries(playground07 dllist)

add_executable(tests07 tests/test_utils.c tests/tests.c)
target_include_directories(tests07 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(tests07 dllist)

add_executable(bonus_tests07 tests/test_utils.c tests/bonus_tests.c)
target_include_directories(bonus_tests07 PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(bonus_tests07 dllist)

# disable forking mode in Debug mode
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

# configure compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES Clang OR ${CMAKE_C_COMPILER_ID} STREQUAL GNU)
  # using regular Clang, AppleClang or GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -Wextra -pedantic")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  target_compile_definitions(playground07 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(tests07 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(bonus_tests07 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
endif()

if(MINGW)
    target_compile_definitions(playground07 PRIVATE __USE_MINGW_ANSI_STDIO=1)
    target_compile_definitions(tests07 PRIVATE __USE_MINGW_ANSI_STDIO=1)
    target_compile_definitions(bonus_tests07 PRIVATE __USE_MINGW_ANSI_STDIO=1)
endif()
