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
    std::string vertex_shader = "../lesson02/assets/" + path + ".vs";
    std::string fragment_shader = "../lesson02/assets/" + path + ".fs";

    this->program = glCreateProgram();
    this->load_shader(vertex_shader, GL_VERTEX_SHADER);
    this->load_shader(fragment_shader, GL_FRAGMENT_SHADER);
    this->create_program();
}

void Shader::load_shader(const std::string& path, GLenum shader_type) {
    unsigned int shader_id = 0;
    if(shader_type == GL_VERTEX_SHADER) {
        shader_id = 0;
    } else if(shader_type == GL_FRAGMENT_SHADER) {
        shader_id = 1;
    } else {
        throw std::runtime_error("Unknown shader type requested.");
    }

    this->shaders[shader_id] = glCreateShader(shader_type);

    if(this->shaders[shader_id] == 0) {
        std::cerr << "Error: Shader creation failed!" << std::endl;
    }

    std::cout << "Loading " << path << "\t" << shader_id << std::endl;

    const GLchar* shader_source_strings[1];
    GLint shader_source_strings_length[1];

    std::string text = this->load_shader_code(path);

    shader_source_strings[0] = text.c_str();
    shader_source_strings_length[0] = text.length();

    glShaderSource(this->shaders[shader_id], 1, shader_source_strings, shader_source_strings_length);
    glCompileShader(this->shaders[shader_id]);

    this->check_shader_error(this->shaders[shader_id], GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
}

void Shader::create_program() {
    glAttachShader(this->program, this->shaders[0]);
    glAttachShader(this->program, this->shaders[1]);

    glLinkProgram(this->program);
    check_shader_error(program, GL_LINK_STATUS, true, "Program linking failed: ");

    glValidateProgram(this->program);
    this->check_shader_error(this->program, GL_VALIDATE_STATUS, true, "Program validation failed: ");
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

std::string Shader::load_shader_code(const std::string& path) {
    std::ifstream file(path);

    std::string output;
    std::string line;

    if(file.is_open()) {
        while(file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << path << std::endl;
    }

    return output;
}
