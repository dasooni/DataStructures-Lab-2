cmake_minimum_required(VERSION 3.13.0...3.20)
project(TND004-Lab-2 VERSION 1.0.0 DESCRIPTION "TND004 Lab 2" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Lab2 lab2.cpp set.cpp set.h node.h)

enable_warnings(Lab2)
