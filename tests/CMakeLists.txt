find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
# add_executable(tests test.cpp)
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

file(GLOB
	lib_source "../lib/*.cpp")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(tests_lib STATIC 
	${lib_source})

# These tests need their own main
add_executable(tests test-main.cpp ${lib_source})
target_link_libraries(tests PRIVATE Catch2::Catch2)
