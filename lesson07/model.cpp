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

#include "model.h"

/**
 * @brief      Construct model object
 *
 * @param[in]  path  Path to object file
 */
Model::Model(const std::string& path) {
    this->load_data(path);
}

/**
 * @brief      Draw the model
 */
void Model::draw() {
    this->load();
    glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
}

/**
 * @brief      Load the VAO of the model
 */
void Model::load() {
    glBindVertexArray(this->vao);
}

/**
 * @brief      Destroys the object.
 */
Model::~Model() {
    glDeleteBuffers(3, this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

/**
 * @brief      Load object data from hard drive
 *
 * @param[in]  path  Path to object file
 */
void Model::load_data(const std::string& path) {
    std::ifstream file(path);

    if(file.is_open()) {
        // set regex patterns
        static const boost::regex v_line("v\\s+([0-9.-]+)\\s+([0-9.-]+)\\s+([0-9.-]+).*");
        static const boost::regex vn_line("vn\\s+([0-9.-]+)\\s+([0-9.-]+)\\s+([0-9.-]+).*");
        static const boost::regex f_line("f\\s+([0-9]+)\\/\\/([0-9]+)\\s+([0-9]+)\\/\\/([0-9]+)\\s+([0-9]+)\\/\\/([0-9]+).*");

        // construct holders
        std::vector<glm::vec3> _positions;
        std::vector<glm::vec3> _normals;
        std::vector<unsigned int> position_indices;
        std::vector<unsigned int> normal_indices;

        std::string line;

        // skip first three lines
        for(unsigned int i=0; i<3; i++) {
            std::getline(file, line);
        }

        // start reading
        while(std::getline(file, line)) {
             boost::smatch what1;

            if (boost::regex_match(line, what1, v_line)) {
                glm::vec3 pos(boost::lexical_cast<float>(what1[1]),
                              boost::lexical_cast<float>(what1[2]),
                              boost::lexical_cast<float>(what1[3]));
                _positions.push_back(pos);
            }

            if (boost::regex_match(line, what1, vn_line)) {
                glm::vec3 normal(boost::lexical_cast<float>(what1[1]),
                                 boost::lexical_cast<float>(what1[2]),
                                 boost::lexical_cast<float>(what1[3]));
                _normals.push_back(normal);
            }

            if (boost::regex_match(line, what1, f_line)) {
                position_indices.push_back(boost::lexical_cast<unsigned int>(what1[1]) - 1);
                position_indices.push_back(boost::lexical_cast<unsigned int>(what1[3]) - 1);
                position_indices.push_back(boost::lexical_cast<unsigned int>(what1[5]) - 1);

                normal_indices.push_back(boost::lexical_cast<unsigned int>(what1[2]) - 1);
                normal_indices.push_back(boost::lexical_cast<unsigned int>(what1[4]) - 1);
                normal_indices.push_back(boost::lexical_cast<unsigned int>(what1[6]) - 1);
            }
        }

        // restructure data
        for(unsigned int i=0; i<position_indices.size(); i++) {
            this->positions.push_back(_positions[position_indices[i]]);
            this->normals.push_back(_normals[normal_indices[i]]);
            this->indices.push_back(i);
        }

        std::cout << "Loaded " + path + ", which contains " << this->indices.size() / 3 << " faces." << std::endl;

        // load into buffer
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);
        glGenBuffers(3, this->vbo);

        // bind vertices
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, this->positions.size() * 3 * sizeof(float), &this->positions[0][0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // bind normals
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, this->normals.size() * 3 * sizeof(float), &this->normals[0][0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // bind indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);
        glBindVertexArray(0);
    } else {
        std::cerr << "Cannot open file " + path << std::endl;
    }
}
