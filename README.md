# Red Framework

Open source collection of C++ modules built to interest a wide variety of programming focuses. The modules provide high and low level abstractions to make software development smoother, leaving the platform-dependent and management code to the library. This project is not a replacement for more developed libraries such as Boost, but it makes attempts at providing unique and useful constructs for programmers.

[![Code Coverage](https://codecov.io/gh/XenonicDev/Red/branch/master/graph/badge.svg)](https://codecov.io/gh/XenonicDev/Red)

| Build Status          | System         |
| ------------- | ------------------------------------------ |
| [![Build Status Windows](https://ci.appveyor.com/api/projects/status/uaoee0lwjm5qfx5t?svg=true)](https://ci.appveyor.com/project/XenonicDev/red) | Windows 10 (MSVS 2017) |
| [![Build Status Linux](https://travis-ci.org/XenonicDev/Red.svg?branch=master)](https://travis-ci.org/XenonicDev/Red) | Ubuntu 14.04.3 (gcc 4.8.4/clang 5.0.0) OSX (XCode 8.3 clang) |

## Building
Building is simplified into platform specific build scripts. For Windows systems, execute Build.bat, while on *nix systems, use Build.sh. These will generate a Build folder in the project root to store all intermediates and binaries. Running these scripts without any arguments will default to 64 bit builds without debugging information.
### Customizing the Build
You can customize the build with the following set of commandline arguments. *Note: If you want to specify one of these arguments, you must specify all preceding arguments. Any arguments not specified after will resort to defaults. Order does matter.*
> [**Argument 1**] Release | Debug

Changes whether or not debugging information should be included in the build.
> [**Argument 2**] x86 | x64

Changes the target system architecture.
> [**Argument 3\***] coverage

Changes whether or not code coverage data should be included in the build.
> [**Argument 3\*\***] HASNUGET

**\*** *\*nix build script only, used mainly by CI for code coverage statistics.*

**\*\*** *Windows build script only, use this if you have NuGet in your PATH and don't need to download it.*
### Requirements
#### Windows
* [Microsoft Visual Studio 2017 15.2 or Later](https://www.visualstudio.com/downloads/)
#### \*nix
* [CMake 3.1 or Later](https://cmake.org/download/)
* Compiler With C++14 or Later Support

## Contributing
This is an open source project that is open to any public submissions that fall within the loosely held style guide of the project. Until an official guide is written, potential contributors can look over the code provided and do their best to get a sense of the structure and style. As for work environments, Microsoft Visual Studio is the native development suite for work on the library and will always be supported. It is unknown whether or not other IDEs will be natively supported in the future.
