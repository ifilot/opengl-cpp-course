# Solutions to exercises
Below are the solutions to the exercises.

### Exercise 01: Field of View
The rotating cube becomes smaller as your fov increases.

### Exercise 02: Orthographic projection
Change the projection matrix to

```
glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.01f, 10.0f);
```

also have a look at the [script of lesson 01](../lesson01/main.cpp).

### Exercise 03: Scaling the object
Change the scaling matrix to

```
glm::mat4 scale = glm::scale(glm::vec3(1.0f, std::pow((float)std::sin(glfwGetTime()), 2.0f) + 1.0f, 1.0f));
```
