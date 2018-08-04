# Solutions to exercises
Below are the solutions to the exercises.

## Exercise 01: Changing c-style arrays to std::vector
Change the c-style arrays to
```
std::vector<float> vertices = {-0.6f, -0.4f, 0.6f, -0.4f, 0.f,  0.6f};
std::vector<float> colors = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
std::vector<unsigned int> indices = {0,1,2};
```

and the `glBufferData` statements to

```
// bind vertices
glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

// bind colors
glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), &colors[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

// bind indices
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
glBindVertexArray(0);
```

and the draw call to

```
glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
```

Note that using this method, you do not have to explicitly track the size of the arrays. You could in principle add entries to the `std::vector` and the `size()` instructions would update automatically. (You would still need to do this consistently though in order to get proper results.)

## Exercise 02: Changing the colors
You can either change the colors array to
```
static const float colors[9] = {1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
```

or change the GLSL instructions of the fragment shader to

```
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 outcol;\n"
"void main()\n"
"{\n"
"    outcol = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";
```

The first method actually changes the color values for the vertices, whereas the latter method overrules any color values that were set in the first place.

## Exercise 03: Make a square

Change the vertices as follows

```
static const float vertices[8] = {-0.6f, -0.4f, 0.6f, -0.4f, 0.6,  0.4f, -0.6, 0.4};
static const float colors[12] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
static const unsigned int indices[6] = {0,1,2,0,2,3};
```

and adjust the `glBufferData` statements accordingly (note the change of the second parameter)

```
// bind vertices
glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float) * 3, &vertices[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

// bind colors
glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float) * 3, &colors[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

// bind indices
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
glBindVertexArray(0);
```

Finally, the draw call becomes:
```
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

Note that we only added a single vertex and corresponding color to the arrays and used the indices array to "recycle" two points.

## Exercise 04: Make a tetrahedron

Change the vertex arrays to:
```
static const float vertices[12] = {1.0f, 0.0f, -1.0f/std::sqrt(2.0f), -1.0f, 0.0f, -1.0f/std::sqrt(2.0f), 0.0f, 1.0f, 1.0f/std::sqrt(2.0f), 0.0f, -1.0f, 1.0f/std::sqrt(2.0f)};
static const float colors[12] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};
static const unsigned int indices[12] = {1,3,2,0,2,3,0,1,3,0,2,1};
```

The bind command becomes:
```
glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
```

and

```
glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), &colors[0], GL_STATIC_DRAW);
```

and the draw command is changed to
```
glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
```

You will see that there is some weird overlapping of the triangles. This is because a triangle that is closer to the camera (lower z-value), is not necessarily drawn on top of a triangle that is further away from the camera (larger z-value). This is termed [z-fighting](https://en.wikipedia.org/wiki/Z-fighting).

You can fix this by setting the following two lines

```
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```
