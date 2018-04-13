cmake_minimum_required(VERSION 3.0)
project(seminar08)

add_library(queue STATIC "queue.c")

add_executable(playground08 "playground.c")
target_link_libraries(playground08 queue)

add_executable(tests08 "tests.c")
target_link_libraries(tests08 queue)

add_executable(tests-debug08 "tests.c")
target_compile_definitions(tests-debug08 PRIVATE DEBUG)
target_link_libraries(tests-debug08 queue)

# Configure compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES Clang OR ${CMAKE_C_COMPILER_ID} STREQUAL GNU)
  # using regular Clang, AppleClang or GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -ggdb3 -Wall -Wextra -pedantic")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  target_compile_definitions(tests08 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(tests-debug08 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  target_compile_definitions(playground08 PRIVATE _CRT_SECURE_NO_DEPRECATE)
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
endif()

if(MINGW)
    target_compile_definitions(tests08 PRIVATE __USE_MINGW_ANSI_STDIO=1)
    target_compile_definitions(tests-debug08 PRIVATE __USE_MINGW_ANSI_STDIO=1)
    target_compile_definitions(playground08 PRIVATE __USE_MINGW_ANSI_STDIO=1)
endif()


