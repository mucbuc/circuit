cmake_minimum_required(VERSION 3.27)

project(Example)

add_subdirectory(lib/circuit)

add_executable(Example src/example.cpp)

target_link_libraries(Example INTERFACE asserter)
target_link_libraries(Example PRIVATE circuit)

set_target_properties(Example PROPERTIES
    CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	COMPILE_WARNING_AS_ERROR ON
)

target_include_directories(Example SYSTEM PUBLIC ${CMAKE_SOURCE_DIR})
