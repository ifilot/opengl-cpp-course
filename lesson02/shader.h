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
#include <iostream>
#include <fstream>
#ifdef WIN32
    #pragma comment (lib, "glew32s.lib")
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

class Shader {
private:
	GLuint program;
	GLuint shaders[2];

public:
	Shader(const std::string& path);

    inline void link() {
        glLinkProgram(this->program);
    }

    inline void use() {
        glUseProgram(this->program);
    }

    inline GLuint get_id() const {
        return this->program;
    }

private:
	void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message);

    void load_shader(const std::string& path, GLenum shader_type);

    void create_program();

    std::string load_shader_code(const std::string& path);
};

#endif // _SHADER_H
