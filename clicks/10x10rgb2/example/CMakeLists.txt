cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c10x10rgb2 LANGUAGES MikroC)
else()
    project(example_c10x10rgb2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c10x10rgb2
        main.c
    
)


############################ example_c10x10rgb2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c10x10rgb2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c10x10rgb2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c10x10rgb2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_c10x10rgb2)
target_link_libraries(example_c10x10rgb2 PUBLIC Click.10x10RGB2)
############################ example_c10x10rgb2 GENERATED CODE END ###########################

