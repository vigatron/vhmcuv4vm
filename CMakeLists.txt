cmake_minimum_required(VERSION 3.10)

set(PRJNAME v4vm)

project(${PRJNAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILE_OBJECT "${CMAKE_C_COMPILE_OBJECT} -Wa,-alh=<OBJECT>.lst")

set(PATH_VHPCK21 /home/vigatron/VHSources/VHPCK)

file(GLOB_RECURSE srclist_src       src/*.cpp src/*.hpp src/*.h src/*.c )


add_executable(${PRJNAME}
    ${srclist_src}
)

target_include_directories(${PRJNAME}
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PATH_VHPCK21}/misc>
)
