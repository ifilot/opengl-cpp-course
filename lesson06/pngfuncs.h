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

#ifndef _UTIL_PNG_H
#define _UTIL_PNG_H

#include <fstream>
#include <iostream>
#include <vector>
#include <png.h>

namespace PNG {

    void write_image_buffer_to_png(const std::string& filename, const std::vector<uint8_t>& buffer, unsigned int width, unsigned int height, unsigned int col);
    void load_image_buffer_from_png(const std::string& filename, std::vector<uint8_t>& buffer, png_uint_32* width, png_uint_32* height, int* col, int* bit_depth, bool invert = false);

    void read_file_callback(png_structp png_ptr, png_bytep out, png_size_t count);
    void write_file_callback(png_structp png_ptr, png_bytep data, png_size_t count);
}

#endif //_UTIL_PNG_H
