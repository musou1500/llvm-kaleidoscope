cmake_minimum_required(VERSION 3.1)
project (llvm-kaleidoscope)

find_package(LLVM 3.9 REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

include_directories(./src)
add_executable(llvm-kaleidoscope ./src/main.cpp)

# Use C++11 to compile our pass (i.e., supply -std=c++11).
target_compile_features(llvm-kaleidoscope PRIVATE cxx_range_for cxx_auto_type)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(llvm-kaleidoscope PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
