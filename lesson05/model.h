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

#ifndef _MODEL_H
#define _MODEL_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#ifdef WIN32
    #pragma comment (lib, "glew32s.lib")
    #define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Model {
private:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    GLuint vao;
    GLuint vbo[3];

public:
    Model(const std::string& path);

    void draw();

    void load();

    ~Model();

private:
    void load_data(const std::string& path);
};

#endif // _MODEL_H
