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

#include "pngfuncs.h"

void PNG::write_image_buffer_to_png(const std::string& filename, const std::vector<uint8_t>& buffer, unsigned int width, unsigned int height, unsigned int col) {
    png_structp png_ptr;
    png_infop info_ptr;

    /* create file */
    std::ofstream ofile(filename.c_str(), std::ios::binary);

    if (!ofile.is_open() ) {
        std::cerr << "[write_png_file] File " << filename.c_str() << " could not be opened for reading" << std::endl;
        exit(-1);
    }

    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr) {
        std::cerr << "[write_png_file] png_create_write_struct failed" << std::endl;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "[write_png_file] png_create_info_struct failed" << std::endl;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "[write_png_file] Error during init_io";
    }

    png_set_write_fn(png_ptr, (void *)&ofile, write_file_callback, NULL);

    /* write header */
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "[write_png_file] Error during writing header" << std::endl;
    }

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 8, col, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "[write_png_file] Error during writing bytes" << std::endl;
    }

    png_bytep *row_pointers;
    if(col == PNG_COLOR_TYPE_GRAY) {
        row_pointers = new png_bytep[height];
        for(unsigned int i=0; i<height; i++) {
            row_pointers[i] = new unsigned char[width];
            for(unsigned int j=0; j<width; j++) {
                row_pointers[i][j] = buffer[i * width + j];
            }
        }
    } else {
        static const unsigned int coldepth = 4;
        row_pointers = new png_bytep[height];
        for(unsigned int i=0; i<height; i++) {
            row_pointers[i] = new unsigned char[width * coldepth];
            for(unsigned int j=0; j<width; j++) {
                for(unsigned int p=0; p<coldepth; p++) {
                    // note that height needs to inverted for correct image capture
                    row_pointers[i][j * coldepth + p] = buffer[((height - i - 1) * width + j) * coldepth + p];
                }
            }
        }
    }
    png_write_image(png_ptr, row_pointers);

    /* end write */
    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "[write_png_file] Error during end of write" << std::endl;
    }

    png_write_end(png_ptr, NULL);

    for(unsigned int i=0; i<height; i++) {
        delete[] row_pointers[i];
    }
    delete[] row_pointers;

    png_destroy_write_struct(&png_ptr, &info_ptr);

    ofile.close();
}

void PNG::load_image_buffer_from_png(const std::string& filename, std::vector<uint8_t>& buffer, png_uint_32* width, png_uint_32* height, int* col, int* bit_depth, bool invert) {
    png_structp png_ptr;
    png_infop info_ptr;

    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    std::ifstream ifile(filename.c_str(), std::ios::binary);

    if (!ifile.is_open() ) {
        std::cerr << "[read_png_file] File " << filename.c_str() << " could not be opened for reading" << std::endl;
        exit(-1);
    }

    ifile.read(&header[0], 8 * sizeof(char));
    if (!png_check_sig((png_bytep)header, 8)) {
        std::cerr << "[read_png_file] File " << filename.c_str() << " is not recognized as a PNG file" << std::endl;
        exit(-1);
    }

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

    if (!png_ptr) {
        std::cerr << "[read_png_file] png_create_read_struct failed for file " << filename.c_str() << std::endl;
        exit(-1);
    }

    info_ptr = png_create_info_struct(png_ptr);

    if (!info_ptr) {
        std::cerr << "[read_png_file] png_create_info_struct failed for file " << filename.c_str() << std::endl;
        exit(-1);
    }

    png_set_read_fn(png_ptr, (void*)&ifile, read_file_callback);

    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)width, (png_uint_32*)height, bit_depth, col, 0, 0, 0);

    if (*col == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
    }

    // allocate space for storing texture
    png_bytepp row_pointers = new png_bytep[(*height)];
    for (unsigned int y=0; y<(*height); y++) {
        row_pointers[y] = new png_byte[png_get_rowbytes(png_ptr,info_ptr)];
    }

    png_read_image(png_ptr, row_pointers);
    png_read_end(png_ptr, info_ptr);

    unsigned int channels = 0;
    switch(*col) {
        case PNG_COLOR_TYPE_RGB_ALPHA:
            channels = 4;
        break;
        case PNG_COLOR_TYPE_RGB:
            channels = 3;
        break;
        case PNG_COLOR_TYPE_PALETTE:
            channels = 3;
        break;
        case PNG_COLOR_TYPE_GRAY:
            channels = 1;
        break;
        default:
            channels = 1;
        break;
    }

    // transfer data to std::vector
    const unsigned int w = *width;
    const unsigned int h = *height;

    buffer.resize(w * h * channels, 0);
    for(unsigned int i=0; i<h; i++) {
        for(unsigned int j=0; j<w; j++) {
            for(unsigned int p=0; p<channels; p++) {
                if(invert) {
                    buffer[((h - i - 1) * w + j) * channels + p] = row_pointers[i][j * channels + p];
                } else {
                    buffer[i * w * channels + j * channels + p] = row_pointers[i][j * channels + p];
                }
            }
        }
    }

    ifile.close();

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    for(unsigned int i=0; i<*height; i++) {
        delete[] row_pointers[i];
    }
    delete[] row_pointers;
}

void PNG::read_file_callback( png_structp png_ptr, png_bytep out, png_size_t count ) {
    png_voidp io_ptr = png_get_io_ptr( png_ptr );

    if( io_ptr == 0 ) {
        return;
    }

    std::ifstream &ifs = *(std::ifstream*)io_ptr;

    ifs.read( (char*)out, count );
}

void PNG::write_file_callback(png_structp png_ptr, png_bytep data, png_size_t count) {
    std::ofstream *outfile = (std::ofstream*)png_get_io_ptr(png_ptr);
    outfile->write((char*)data, count);
}
