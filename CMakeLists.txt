cmake_minimum_required(VERSION 3.5)
project(plot)
FILE(GLOB source "plot/*.hpp" "plot/*.cpp")
add_library(plot STATIC ${source})
