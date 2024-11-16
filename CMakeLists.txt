cmake_minimum_required(VERSION 3.5)
project(plot)
FILE(GLOB source "plot/*.h" "plot/*.c")
add_library(plot STATIC ${source})
include(FetchContent)
FetchContent_Declare(
        carma
        GIT_REPOSITORY https://github.com/mabur/carma.git
        GIT_TAG f7123af2ea253dea297f30d22536e1aa0ee079b8
)
FetchContent_MakeAvailable(carma)
target_include_directories(plot PRIVATE
        ${carma_SOURCE_DIR}
)
target_link_libraries(plot PRIVATE
        carma
)
