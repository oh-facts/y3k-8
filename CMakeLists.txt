cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(fcpu)

#--------target--------#

include_directories(src)
set(src "src/arena.c" "src/app.c")

add_executable(${PROJECT_NAME} "src/main.c" ${src})
