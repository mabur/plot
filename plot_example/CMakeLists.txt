cmake_minimum_required(VERSION 3.5)
project(plot_example)
add_subdirectory(.. plot_build)
FILE(GLOB source "*.c" "*.h")
add_executable(plot_example ${source})

include(FetchContent)
FetchContent_Declare(
        carma
        GIT_REPOSITORY https://github.com/mabur/carma.git
        GIT_TAG f7123af2ea253dea297f30d22536e1aa0ee079b8
)
FetchContent_MakeAvailable(carma)
target_include_directories(plot_example PRIVATE
        ${carma_SOURCE_DIR}
)

target_link_libraries(plot_example PRIVATE carma plot)
target_include_directories(plot_example PRIVATE ..)
#target_compile_features(plot_example PRIVATE cxx_std_17)
target_compile_options(plot_example PRIVATE -std=c2x)
