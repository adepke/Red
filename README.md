# Red Framework

Open source collection of C++ modules built to interest a wide variety of programming focuses. The modules provide high and low level abstractions to make software development smoother, leaving the platform-dependent and management code to the library. This project is not a replacement for more developed libraries such as Boost, but it makes attempts at providing unique and useful constructs for programmers.

[![Code Coverage](https://codecov.io/gh/XenonicDev/Red/branch/master/graph/badge.svg)](https://codecov.io/gh/XenonicDev/Red)

| Build Status          | System         |
| ------------- | ------------------------------------------ |
| [![Build Status Windows](https://ci.appveyor.com/api/projects/status/uaoee0lwjm5qfx5t?svg=true)](https://ci.appveyor.com/project/XenonicDev/red) | Windows 10 (MSVS 2017) |
| [![Build Status Linux](https://travis-ci.org/XenonicDev/Red.svg?branch=master)](https://travis-ci.org/XenonicDev/Red) | Ubuntu 14.04.3 (gcc 4.8.4/clang 5.0.0) OSX (XCode 8.3 clang) |

## Building
Building is simplified into platform specific build scripts. For Windows systems, execute Build.bat, while on Unix systems, use Build.sh. These will generate a Build folder in the project root to store all intermediates and binaries. Build script parameters are in the immediate roadmap.
