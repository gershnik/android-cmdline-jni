#
# Copyright 2020 Eugene Gershnik
#
# Use of this source code is governed by a BSD-style
# license that can be found in the LICENSE file or at
# https://github.com/gershnik/android-cmdline-jni/blob/main/LICENSE
#

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(hello)

add_executable(hello
    main.cpp
)

target_link_options(hello PRIVATE

    "$<$<PLATFORM_ID:Android>:-Wl,--export-dynamic>"
)

set(RUN_COMMAND "")

if (${CMAKE_SYSTEM_NAME} STREQUAL Android)

    set(ANDROID_RUN_DIR /data/local/tmp/hellodir)
    set(ANDROID_SDK_DIR ${CMAKE_ANDROID_NDK}/../..)
    set(ADB ${ANDROID_SDK_DIR}/platform-tools/adb)

    if(${CMAKE_ANDROID_ARCH} STREQUAL x86 OR ${CMAKE_ANDROID_ARCH} STREQUAL arm)
        set(ANDROID_LD_LIBRARY_PATH /apex/com.android.art/lib)
    else()
        set(ANDROID_LD_LIBRARY_PATH /apex/com.android.art/lib64)
    endif()

    list(APPEND RUN_COMMAND COMMAND ${ADB} shell mkdir -p ${ANDROID_RUN_DIR})
    list(APPEND RUN_COMMAND COMMAND ${ADB} push hello ${ANDROID_RUN_DIR})
    list(APPEND RUN_COMMAND COMMAND echo ${ANDROID_LD_LIBRARY_PATH})
    list(APPEND RUN_COMMAND COMMAND ${ADB} shell ls ${ANDROID_LD_LIBRARY_PATH})
    list(APPEND RUN_COMMAND COMMAND ${ADB} shell LD_LIBRARY_PATH=${ANDROID_LD_LIBRARY_PATH} ${ANDROID_RUN_DIR}/hello)

else()
    list(APPEND RUN_COMMAND COMMAND hello)
endif()

add_custom_target(run
    DEPENDS hello
    ${RUN_COMMAND}
)