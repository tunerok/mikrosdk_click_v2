cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss16 LANGUAGES MikroC)
else()
    project(lib_gnss16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss16 STATIC
        src/gnss16.c
        include/gnss16.h
)
add_library(Click.GNSS16  ALIAS lib_gnss16)



target_include_directories(lib_gnss16 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss16 PUBLIC MikroSDK.Driver)

