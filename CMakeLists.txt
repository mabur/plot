cmake_minimum_required(VERSION 3.5)
project(plot)
FILE(GLOB source "plot/*.h" "plot/*.c")
add_library(plot STATIC ${source})
