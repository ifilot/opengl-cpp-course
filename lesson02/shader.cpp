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

#include "shader.h"

Shader::Shader(const std::string& path) {

}

void Shader::check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message) {
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