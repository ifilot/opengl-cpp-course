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

#include "texture_factory.h"

TextureFactory::TextureFactory() {

}

GLuint TextureFactory::get_texture(const std::string& name){
    auto search = this->textures.find(name);
    if(search != this->textures.end()) {
        return search->second;
    } else {
        this->add_texture(name);
        return this->get_texture(name);
    }
}

void TextureFactory::add_texture(const std::string& name) {
    GLuint texture_id = this->load_texture(name);
    this->textures.emplace(name, texture_id);
}

GLuint TextureFactory::load_texture(const std::string& filename) {
    glActiveTexture(GL_TEXTURE0);

    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    std::vector<uint8_t> pixels;
    png_uint_32 width, height;
    int col, bit_depth;

    PNG::load_image_buffer_from_png(filename,
                                    pixels,
                                    &width,
                                    &height,
                                    &col,
                                    &bit_depth,
                                    true);  // automatically invert the image

    switch(col) {
        case PNG_COLOR_TYPE_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
        break;
    }

    std::cout << "Loading " << filename << ": " << width << "x" << height << " px." << std::endl;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture_id;
}

TextureFactory::~TextureFactory() {
    for(auto& item : this->textures) {
        glDeleteTextures(1, &item.second);
    }
}
