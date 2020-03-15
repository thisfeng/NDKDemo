# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

#指定 Cmake构建版本
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#添加 .so库文件
add_library( # Sets the name of the library.
             Hello

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             Hello.c )#当前目录可直接指定

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

#添加NDK API ，找到 NDK 库并将其路径存储为一个变量。您可以使用此变量在构建脚本的其他部分引用 NDK 库
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#为了让您的原生库能够调用 log 库中的函数，您需要使用 CMake 构建脚本中的 target_link_libraries() 命令来关联这些库：
target_link_libraries( # Specifies the target library.
                       Hello

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )