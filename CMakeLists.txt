cmake_minimum_required(VERSION 3.18)

project(big_integer)

# set the C++ standard
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(public_header lib/${PROJECT_NAME}.h)
set(sources lib/${PROJECT_NAME}.cpp)

add_library(${PROJECT_NAME}_lib ${sources} ${public_header})

add_executable(${PROJECT_NAME}.exe main.cpp ${sources})

target_link_libraries(${PROJECT_NAME}.exe ${PROJECT_NAME}_lib)
