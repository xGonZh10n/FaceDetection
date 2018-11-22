# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 设置native目录
set(NATIVE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)

# 设置dlib
include(${NATIVE_DIR}/dlib/cmake)

# 设置opencv include文件夹
include_directories(${NATIVE_DIR}/opencv/jni/include)

# 设置opencv so库
add_library(
        libopencv_java3
        SHARED
        IMPORTED)

set_target_properties(
        libopencv_java3
        PROPERTIES
        IMPORTED_LOCATION
        ${NATIVE_DIR}/opencv/libs/${ANDROID_ABI}/libopencv_java3.so)

# 将jni_common目录中所有文件名，存至SRC_LIST中
AUX_SOURCE_DIRECTORY(${NATIVE_DIR}/jni_common SRC_LIST)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).

        ${SRC_LIST}
        src/main/cpp/face_detector.h
        src/main/cpp/face_detector.cpp
        src/main/cpp/native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        dlib
        libopencv_java3
        jnigraphics
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

# 指定release编译选项
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s -O3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -O3 -Wall")