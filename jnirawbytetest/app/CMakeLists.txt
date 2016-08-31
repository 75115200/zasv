cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)

add_library( # Sets the name of the library.
             native_lib

             SHARED

             src/main/cpp/JavaJniPerformanceCompare.cpp )

find_library( log-lib
              log )

target_link_libraries( native_lib
                       log
                       )



# ============ audio ===============
set(jniLibs_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})

set(cpp_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)

if (${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set(kge_so_postfix _v7a)
else()
    set(kge_so_postfix )
endif()

add_library(lib_audio_base SHARED IMPORTED)
set_target_properties(lib_audio_base PROPERTIES IMPORTED_LOCATION
    ${jniLibs_DIR}/libaudiobase${kge_so_postfix}.so)

add_library(lib_audio_process SHARED IMPORTED)
set_target_properties(lib_audio_process PROPERTIES IMPORTED_LOCATION
    ${jniLibs_DIR}/libwebrtc_audio_preprocessing${kge_so_postfix}.so)

include_directories(${cpp_DIR}/kge/include)

file(GLOB KALA_SRC
             ${cpp_DIR}/kge/src/*.cpp
             )

add_library( audio_test

             SHARED

             ${KALA_SRC}
             )

target_link_libraries( audio_test
                       log
                       lib_audio_base
                       lib_audio_process
                       )

