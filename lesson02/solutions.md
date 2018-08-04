# Solutions to exercises
Below are the solutions to the exercises.

## Exercise 01: Field of View
The rotating cube becomes smaller as your fov increases.

## Exercise 02: Orthographic projection
Change the projection matrix to

```
glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.01f, 10.0f);
```

also have a look at the [script of lesson 01](../lesson01/main.cpp).

## Exercise 03: Scaling the object
Change the scaling matrix to

```
glm::mat4 scale = glm::scale(glm::vec3(1.0f, std::pow((float)std::sin(glfwGetTime()), 2.0f) + 1.0f, 1.0f));
```

## Exercise 04: Moving the camera
```
glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
glm::mat4 rotate = glm::rotate((float) glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));
glm::mat4 translate = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
glm::mat4 model = glm::mat4(1.0f);
glm::vec3 pos = glm::vec3(0.0f, std::sin((float) glfwGetTime()) * 2.0f, std::cos((float) glfwGetTime()) * 2.0f);
glm::vec3 out = glm::vec3(0.0f, -std::sin((float) glfwGetTime()), -std::cos((float) glfwGetTime()));
glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 up = glm::cross(right, out);
glm::mat4 view = glm::lookAt(pos, glm::vec3(0,0,0), up);
glm::mat4 projection = glm::perspective(glm::quarter_pi<float>(), ratio, 0.01f, 10.0f);
glm::mat4 mvp = projection * view * model;
```
