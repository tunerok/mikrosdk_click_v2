cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_current12 LANGUAGES MikroC)
else()
    project(example_current12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_current12
        example/main.c
    
)


############################ example_current12 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_current12 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_current12 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_current12 PUBLIC MikroSDK.Log)
add_subdirectory(lib_current12)
target_link_libraries(example_current12 PUBLIC Click.Current12)
############################ example_current12 GENERATED CODE END ###########################

