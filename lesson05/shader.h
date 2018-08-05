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

#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#ifdef WIN32
    #pragma comment (lib, "glew32s.lib")
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

/**
 * @brief      Shader class
 *
 * Handles loading GLSL programs
 */
class Shader {
private:
	GLuint program;        //!< id of the program
	GLuint shaders[2];     //!< hold shader references

    std::vector<std::string> attributes;    //!< attribute names

public:
	/**
     * @brief      Constructs Shader object.
     *
     * @param[in]  path  path to the shader files
     */
    Shader(const std::string& path);

    /**
     * @brief      add an attribute name
     *
     * @param[in]  name  attribute name
     */
    void add_attribute(const std::string& name);

    /**
     * @brief      build shader
     */
    void build();

    /**
     * @brief      Gets the uniform location.
     *
     * @param[in]  name  uniform name
     *
     * @return     The uniform location.
     */
    inline GLuint get_uniform_location(const std::string& name) {
        return glGetUniformLocation(this->program, name.c_str());
    }

    /**
     * @brief      use the program
     */
    inline void use() {
        glUseProgram(this->program);
    }

    /**
     * @brief      get the Shader reference
     *
     * @return     the reference
     */
    inline GLuint get_id() const {
        return this->program;
    }

private:
	/**
     * @brief      check shader for error
     *
     * @param[in]  shader         shader reference
     * @param[in]  flag           which flag to check
     * @param[in]  is_program     whether to check linking or validation
     * @param[in]  error_message  The error message
     */
    void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message);

    /**
     * @brief      load a shader
     *
     * @param[in]  path         path to the shader
     * @param[in]  shader_type  shader type
     */
    void load_shader(const std::string& path, GLenum shader_type);

    /**
     * @brief      load shader code from file
     *
     * @param[in]  path  path to file
     *
     * @return     shader code
     */
    std::string load_shader_code(const std::string& path);
};

#endif // _SHADER_H
