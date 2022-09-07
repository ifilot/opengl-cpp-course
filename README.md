# OpenGL C++ Course

**Update**
I made some changes to the code by which everything should now work for MSVC 2019 using Boost 1.74.0.

## Purpose and expectations
This repository contains the source code for the OpenGL C++ course. The course teaches students how to effectively use C++ in conjunction with OpenGL to build graphical programs. The course is made in a concise manner and we refer often to external resources which we expect the student to read (or at least glance through). The learning strategy employed here is "Learning by example" and "Learning by doing". This means that example code is provided and the student is given the opportunity to practice with the material in the form of exercises.

We assume that the student is relatively comfortable reading C++ code and has some previous experience with it. The exercises are constructed in such a way that the student only has to change a few lines of code. Furthermore, we expect that the reader is familiar with matrix-vector multiplication and has some understanding of mathematics. Finally, we expect that the user is a bit familiar using the Windows command prompt.

This course focuses on running OpenGL in a Windows environment, although it should also run under Linux (we have tested it for Linux Debian). If you want to compile the programs on Linux, please read [below](#compilation-instructions-for-linux) as the instructions for CMake differ slightly. OpenGL and the libraries we are using are cross-platform and thus work on Windows, Mac OS X as well as Linux.

Feedback on this course is always much appreciated if provided in a constructive manner. Feel free to use the Issues system on Github for this purpose.

## Lesson overview
1. [Compiling and running an OpenGL program](lesson01/README.md)
2. [Model, View, Perspective](lesson02/README.md)
3. [Creating a Shader class](lesson03/README.md)
4. [Models](lesson04/README.md)
5. [Lighting](lesson05/README.md)
6. [Textures](lesson06/README.md)
7. [Anaglyph](lesson07/README.md)

## Prerequisite software
In order to compile the software, you need to download and install the following packages.

* [CMake](https://cmake.org/download/) - During the installation, you need to select **Add CMAKE to the system PATH for all users**.
* [Microsoft Visual Studio Community Edition](https://visualstudio.microsoft.com/downloads/) - Use the 2019 version. Under 'Workloads', you only need to select 'Desktop Development with C++'
* [Git](https://git-scm.com/download/win) - You can use the default settings during the installation procedure.
* [Python](https://www.python.org/downloads/) - Use the latest Python 3 version!

## Dependencies
* GLFW
* Boost
* Glew
* GLM

You can easily download these dependencies by double-clicking on `download_dep.py` in the `vendor` folder. This might take a while though! Especially the compiled Boost libraries are relatively big (~300MB).

## Compilation instructions for Windows
Open the `Native x64 Native Tools Command Prompt` and go to the repository root folder.

Create a build directory and execute CMake; note that you need to change `XX` to the lesson of interest.

```
mkdir build
cd build
cmake ..\lessonXX -G "NMake Makefiles"
nmake
```

## Compilation instructions for Linux
Open a terminal, go to the root folder of the repository and use the following commands.

```
mkdir build
cd build
cmake ..\lessonXX
make -j5
```

## Troubleshooting

### Framerate is very low
If you are working with Intel Integrated Graphics, open the Intel (U)HD Graphics Control Panel. Go to `3D` and add the executable to the `Select Application` window using the `Browse` button. Then under `Vertical Sync`, select `Use Driver Settings`.

Alternatively, try disabling the following line:

```
// set swap interval
glfwSwapInterval(1);
```
