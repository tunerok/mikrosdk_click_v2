cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hallcurrent19 LANGUAGES MikroC)
else()
    project(lib_hallcurrent19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hallcurrent19 STATIC
        src/hallcurrent19.c
        include/hallcurrent19.h
)
add_library(Click.HallCurrent19  ALIAS lib_hallcurrent19)



target_include_directories(lib_hallcurrent19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hallcurrent19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hallcurrent19 PUBLIC MikroSDK.Driver)

