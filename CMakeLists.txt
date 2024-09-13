cmake_minimum_required(VERSION 3.0)

project(sorting CXX ASM)
add_executable(sorting 
	shell.S
	insertion.S
	selection.S
	sorting.C
	utils.C
	sorting.h
	utils.h
)
set_property(TARGET sorting PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -Werror")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-znoexecstack")

add_subdirectory(tests)
