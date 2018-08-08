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

#ifndef _TEXTURE_MANAGER
#define _TEXTURE_MANAGER

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <iostream>
#include <string>

#include "pngfuncs.h"

class TextureFactory {
private:
    std::unordered_map<std::string, GLuint> textures;

public:
    /**
     * @brief       sprite manager constructor
     *
     * @return      sprite manager instance
     */
    TextureFactory();

    GLuint get_texture(const std::string& name);

    ~TextureFactory();

private:
    void add_texture(const std::string& name);

    GLuint load_texture(const std::string& filename);
};

#endif // _TEXTURE_MANAGER
