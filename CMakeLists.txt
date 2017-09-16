cmake_minimum_required(VERSION 2.8.9)
project (Palloc)

file(GLOB SOURCES "src/*.c")
add_executable(Palloc ${SOURCES})
