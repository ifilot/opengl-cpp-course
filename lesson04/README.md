# Lesson 04 : Models

## Learning goals
* Load models from Wavefront files into OpenGL
* Understand vertex normals

## Compilation instructions
```
mkdir build
cd build
cmake ..\lesson04 -G "NMake Makefiles"
nmake
```

## Explanation
In the [previous lesson](../lesson03/README.md), we created a separate class to handle the Shader. To continue on this path, in this lesson we use a separate class to handle objects. The objects are loaded from [wavefront .obj files](https://en.wikipedia.org/wiki/Wavefront_.obj_file). Such files can be exported using a program such as [Blender](https://www.blender.org/).

Loading the model has basically become a one-liner

```
Model monkey("../" + lesson_id + "/assets/models/monkey.obj");
```

What the class does is open the file [monkey.obj](assets/models/monkey.obj), read the contents, construct a vao and several vbo and place the contents of the object in the corresponding buffers. In detail, this means that vertex and normal data is copied to the buffers and the indices are created that form the triangles.

To draw the object, simply call the `draw` function within the loop as follows

```
monkey.draw();
```

## Running the program
```
occ-lesson-04
```

![Normal projection](images/lesson04_normal_projection.jpg "Lesson 04 - Normal projection")

## Loading models

![Coordinate system](images/coordinate_system.png "Lesson 04 - Coordinate system")

## Exercises

### Exercise 01: Drawing multiple monkeys
Alter the program in such a way that not one, but four monkeys are being drawn. Note that you do *not* have to create a separate object for each monkey, you can simply call the draw command again. Try to explain why simply calling the draw command is sufficient.

To further practice with the learning goals of this lesson. A series of exercises are introduced as can be found below. Solution to these exercises are given [here](solutions.md).
