cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_digiin2 LANGUAGES MikroC)
else()
    project(example_digiin2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_digiin2
        main.c
    
)


############################ example_digiin2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_digiin2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_digiin2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_digiin2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_digiin2)
target_link_libraries(example_digiin2 PUBLIC Click.DIGIIN2)
############################ example_digiin2 GENERATED CODE END ###########################

