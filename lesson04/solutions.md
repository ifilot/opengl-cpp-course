# Solutions to exercises
Below are the solutions to the exercises.

### Exercise 01: Drawing multiple monkeys
Create an array holding the positions of the four objects.

```
static const glm::vec3 positions[4] = {glm::vec3(1.0f, 0.0f, 1.0f),
                                       glm::vec3(1.0f, 0.0f, -1.0f),
                                       glm::vec3(-1.0f, 0.0f, -1.0f),
                                       glm::vec3(-1.0f, 0.0f, 1.0f)};
```

Next, change within the loop functions the draw calls to something like the following. Note that the matrices that do not change when looping over the draw calls are set before the `for` loop. Within the `for` loop, we only calculate those matrices that change for every model.

```
// construct mvp matrix
glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
glm::mat4 rotate = glm::rotate((float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glm::mat4 projection = glm::perspective(45.0f, ratio, 0.01f, 10.0f);

// load program and copy mvp matrix
shader.use();

for(unsigned int i=0; i<4; i++) {
    glm::mat4 translate = glm::translate(positions[i]);
    glm::mat4 model = translate * rotate * scale;
    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

    // draw monkey
    monkey.draw();
}
```
