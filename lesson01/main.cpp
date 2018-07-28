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
 * vertices and colors
 */
static const float vertices[6] = {-0.6f, -0.4f, 0.6f, -0.4f, 0.f,  0.6f};
static const float colors[9] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
static const unsigned int indices[3] = {0,1,2};

/*
 * Vertex shader program
 */
static const char* vertex_shader_text =
"#version 330 core\n"
"uniform mat4 mvp;\n"
"in vec3 col;\n"
"in vec2 pos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = mvp * vec4(pos, 0.0, 1.0);\n"
"    color = col;\n"
"}\n";

/*
 * fragment shader program
 */
static const char* fragment_shader_text =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 outcol;\n"
"void main()\n"
"{\n"
"    outcol = vec4(color, 1.0);\n"
"}\n";

static void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message) {
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(is_program) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }

    if(success == GL_FALSE) {
        if(is_program) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << error_message << ": '" << error << "'" << std::endl;
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
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

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

    // declare variables
    GLuint vao, vbo[3], vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    // load shape into buffer
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(3, vbo);

    // bind vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float) * 3, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // bind colors
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float) * 3, &colors[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // bind indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);

    // load vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    check_shader_error(vertex_shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    // load fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    check_shader_error(fragment_shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    // construct program and attach shaders
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    check_shader_error(program, GL_LINK_STATUS, true, "Program linking failed: ");
    glValidateProgram(program);
    check_shader_error(program, GL_VALIDATE_STATUS, true, "Program validation failed: ");

    // set uniform variables in shader
    mvp_location = glGetUniformLocation(program, "mvp");
    glBindAttribLocation(program, 0, "pos");
    glBindAttribLocation(program, 1, "col");

    // start loop
    while (!glfwWindowShouldClose(window)) {
        // get width window width and height
        int width = 640;
        int height = 480;
        float ratio = width / (float) height;
        glfwGetFramebufferSize(window, &width, &height);

        // set the viewport to match width and height
        glViewport(0, 0, width, height);

        // clear the buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // white background
        glClear(GL_COLOR_BUFFER_BIT);

        // add draw calls
        glm::mat4 model = glm::rotate((float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 projection = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 0.01f, 10.0f);
        glm::mat4 mvp = projection * view * model;
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
