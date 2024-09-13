cmake_minimum_required(VERSION 3.0)

project(test_selection CXX ASM)
add_executable(test_selection
	../../selection.S
	../../utils.C
	test_selection.C
	
)
set_property(TARGET test_selection PROPERTY CXX_STANDARD 20)
target_include_directories(test_selection PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -Werror")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-znoexecstack")
