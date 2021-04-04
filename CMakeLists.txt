cmake_minimum_required(VERSION 3.17)
project(RecipeLib)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib)
add_subdirectory(extern)
add_executable(RecipeLib main.cpp)
target_link_libraries(RecipeLib PRIVATE resourcelib)
#target_compile_options(RecipeLib PUBLIC -std=c++20 -stdlib=libc++ -fcoroutines-ts)