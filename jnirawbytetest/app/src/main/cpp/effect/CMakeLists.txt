cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_VERBOSE_MAKEFILE on)

#sample for build script
set(cpp_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)

#################### super sound #################
include_directories(
        ${cpp_DIR}/supersound/include
)

file(GLOB SUPER_SOUND_JNI_SRC
             ${cpp_DIR}/supersound/src/*.cpp
             )


add_library( super_sound

             SHARED

             ${SUPER_SOUND_JNI_SRC}
             )

add_library(lib_super_sound_static STATIC IMPORTED)
set_target_properties(lib_super_sound_static PROPERTIES IMPORTED_LOCATION
                        ${cpp_DIR}/supersound/lib/armeabi/libSuperSound.a)

target_link_libraries( super_sound
                       log
                       lib_super_sound_static
                       )

