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
#ifdef WIN32
    #pragma comment (lib, "glew32s.lib")
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

class Shader {
private:

public:
	Shader(const std::string& path);

private:
	void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_message);
};

#endif // _SHADER_H