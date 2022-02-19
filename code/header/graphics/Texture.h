#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLC.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
    private:

        unsigned int id;
        std::string filePath;
        unsigned char* localBuffer;
        int width, height, BPP;

    public:
        Texture(const std::string& path);
        ~Texture();

        Texture(const Texture&) = delete;
        void operator=(const Texture&) = delete;


        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int getWidth() const { return width; };
        inline int getHeight() const { return height; };
        inline int getId() const { return id; }
};

#endif