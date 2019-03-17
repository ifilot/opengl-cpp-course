/**************************************************************************
 *                                                                        *
 *   Author: Ivo Filot <ivo@ivofilot.nl>                                  *
 *                                                                        *
 *   This file is distributed under the Academic Free License 3.0         *
 *   in the hope that it will be useful, but WITHOUT ANY WARRANTY;        *
 *   without even the implied warranty of MERCHANTABILITY or FITNESS      *
 *   FOR A PARTICULAR PURPOSE.                                            *
 *                                                                        *
 **************************************************************************/

#ifdef WIN32
    #pragma comment (lib, "glew32s.lib")
    #define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>

#include "shader.h"
#include "model.h"

static const std::string lesson_id = "lesson07";

/*
 * execute this function is an error is encountered
 */
static void error_callback(int error, const char* description) {
    std::cerr << "Error: "<< description << std::endl;
}

/*
 * execute this function every time a key is pressed
 */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

/*
 * WinMain enables us to launch a Windows application that immediately returns to the prompt
 */
int main() {
    std::cout << "Start program" << std::endl;

    // create pointer to new window
    GLFWwindow* window;

    // set error callback function
    glfwSetErrorCallback(error_callback);

    // try to initialize glfw
    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw, exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create a new window
    window = glfwCreateWindow(640, 480, "Lesson 07 - Anaglyph", NULL, NULL);

    // check if the window was succesfully created
    if (!window) {
        std::cerr << "Could not build window, exiting..." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set a key callback function
    glfwSetKeyCallback(window, key_callback);

    // make the created windows the active context
    glfwMakeContextCurrent(window);

    // initialize GLEW
    // remember to initialize GLEW after you have made the current window
    // in context
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Could not initialize GLEW" << std::endl;
    }

    // set swap interval
    glfwSwapInterval(1);

    // load object
    Model monkey("../"+ lesson_id + "/assets/models/monkey.obj");

    // load shader
    Shader shader("../"+ lesson_id + "/assets/shaders/phong");
    shader.add_attribute("position");
    shader.add_attribute("normal");
    shader.build();

    // set uniform variables
    GLuint mvp_location = shader.get_uniform_location("mvp");
    GLuint camera_location = shader.get_uniform_location("camerapos");
    GLuint model_location = shader.get_uniform_location("model");
    GLuint view_location = shader.get_uniform_location("view");
    GLuint color_location = shader.get_uniform_location("color");
    GLuint lightcolor_location = shader.get_uniform_location("lightcolor");
    GLuint lightpos_location = shader.get_uniform_location("lightpos");

    // set object color and position of camera
    shader.use();
    glUniform3f(lightcolor_location, 1.0f, 1.0f, 1.0f);
    glUniform3f(color_location, 1.0f, 1.0f, 1.0f);
    glUniform3f(lightpos_location, 0.0f, -5.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    // start loop
    while (!glfwWindowShouldClose(window)) {
        // get width window width and height
        int width = 640;
        int height = 480;

        glfwGetFramebufferSize(window, &width, &height);
        float ratio = (float)width / (float) height;

        // set the viewport to match width and height
        glViewport(0, 0, width, height);

        // clear the buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // convergence plane
        static const float dist = 4.0f;
        static const float eye_sep = dist / 30.0f; // rule of thumb: intra-ocular separation should be distance to convergence plane divided by 30
        glm::vec3 camera_pos_ctr = glm::vec3(0.0f, -3.0f, 0.0f);

        // model matrix
        glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
        glm::mat4 rotate = glm::rotate((float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translate = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 model = translate * rotate * scale;

        // view - automatically calculate camera settings using distance and intra-ocular separation
        glm::vec3 camerapos1 = camera_pos_ctr - glm::vec3(eye_sep / 2.0f, 0.0f, 0.0f);
        glm::vec3 camerapos2= camera_pos_ctr + glm::vec3(eye_sep / 2.0f, 0.0f, 0.0f);
        glm::mat4 view1 = glm::lookAt(camerapos1, camera_pos_ctr + glm::vec3(0.0f, dist, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 view2 = glm::lookAt(camerapos2, camera_pos_ctr + glm::vec3(0.0f, dist, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        // projection
        glm::mat4 projection = glm::perspective(glm::quarter_pi<float>(), ratio, 0.01f, 10.0f);

        // construct mvp matrix
        glm::mat4 mvp1 = projection * view1 * model;
        glm::mat4 mvp2 = projection * view2 * model;

        // load program and copy uniform variables
        shader.use();

        glUniformMatrix4fv(model_location, 1, GL_FALSE, &model[0][0]);

        // perform two rendering calls (one for each eye); assume red/cyan anaglyph stereographics

        // left eye
        glColorMask(true, false, false, false); // place left eye data on red channel
        glUniform3fv(camera_location, 1, &camerapos1[0]);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp1[0][0]);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, &view1[0][0]);
        monkey.draw();

        glClear(GL_DEPTH_BUFFER_BIT);

        // right eye
        glColorMask(false, true, true, false); // place right eye data on blue and green channels (= cyan)
        glUniform3fv(camera_location, 1, &camerapos2[0]);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp2[0][0]);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, &view2[0][0]);
        monkey.draw();
        glColorMask(true, true, true, true);

        // swap buffers
        glfwSwapBuffers(window);

        // poll for any events
        glfwPollEvents();
    }

    // destroy the window and clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
