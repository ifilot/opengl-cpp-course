# GLFW Helloworld Windows

## Purpose
This repository contains the source code for the OpenGL C++ course.

## Prerequisite software
* [CMake](https://cmake.org/download/)
* [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/downloads/) - Use the 2017 version
* [Git](https://git-scm.com/download/win)
* [Python](https://www.python.org/downloads/) - Use the latest Python 2 version.

## Dependencies
* GLFW
* Boost
* Glew
* GLM

You can easily download these dependencies by double-clicking on `download_dep.py` in the `vendor` folder. This might take a while though!

## Compilation instructions
Open the `Native x64 Native Tools Command Prompt` and go to the repository root folder.

Create a build directory and execute CMake; note that you need to change `XX` to the lesson of interest.

```
mkdir build
cd build
cmake ..\lessonXX -G "NMake Makefiles"
nmake
```

## Lesson overview
1. [Compiling and running an OpenGL program](lesson01/README.md)
2. [Creating a Shader class](lesson02/README.md)
