# GLFW Helloworld Windows

## Purpose and expectations
This repository contains the source code for the OpenGL C++ course. The course teaches students how to effectively use C++ in conjunction with OpenGL to build graphical programs. The course is made in a concise manner and we refer often to external resources which we expect the student to read (or at least glance through). The learning strategy employed here is "Learning by example" and "Learning by doing". This means that example code is provided and the student is given the opportunity to practice with the material in the form of exercises.

## Lesson overview
1. [Compiling and running an OpenGL program](lesson01/README.md)
2. [Model, View, Perspective](lesson02/README.md)
3. [Creating a Shader class](lesson03/README.md)

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
