cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_relay6 LANGUAGES MikroC)
else()
    project(lib_relay6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_relay6 STATIC
        src/relay6.c
        include/relay6.h
)
add_library(Click.Relay6  ALIAS lib_relay6)



target_include_directories(lib_relay6 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_relay6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_relay6 PUBLIC MikroSDK.Driver)

