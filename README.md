# OpenGL C++ Course

__!! Please not that this repository is under construction !!__

## Purpose and expectations
This repository contains the source code for the OpenGL C++ course. The course teaches students how to effectively use C++ in conjunction with OpenGL to build graphical programs. The course is made in a concise manner and we refer often to external resources which we expect the student to read (or at least glance through). The learning strategy employed here is "Learning by example" and "Learning by doing". This means that example code is provided and the student is given the opportunity to practice with the material in the form of exercises.

We assume that the student is relatively comfortable reading C++ code and has some previous experience with it. The exercises are constructed in such a way that the student only has to change a few lines of code. Furthermore, we expect that the reader is familiar with matrix-vector multiplication and has some understanding of mathematics. Finally, we expect that the user is a bit familiar using the Windows command prompt.

This course focuses on running OpenGL in a Windows environment. In principle, OpenGL and the libraries we are using are cross-platform and thus work on Windows, Mac OS X as well as Linux. Nevertheless, tackling all the different platforms in a single course makes the code bulky and explaining the differences between the operating systems only adds to the complexity.

Feedback on this course is always much appreciated if provided in a constructive manner. Feel free to use the Issues system on Github for this purpose.

## Lesson overview
1. [Compiling and running an OpenGL program](lesson01/README.md)
2. [Model, View, Perspective](lesson02/README.md)
3. [Creating a Shader class](lesson03/README.md)

## Prerequisite software
In order to compile the software, you need to download and install the following packages.

* [CMake](https://cmake.org/download/) - During the installation, you need to **add cmake to the $PATH**. Do not forget to tag the corresponding box.
* [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/downloads/) - Use the 2017 version
* [Git](https://git-scm.com/download/win)
* [Python](https://www.python.org/downloads/) - Use the latest Python 2 version!

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
