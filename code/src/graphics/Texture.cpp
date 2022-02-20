#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include "Texture.h"

Texture::Texture (const std::string& path) 
    : id{0}, filePath{path}, width{0}, height{0}, localBuffer{nullptr} {

        GLCall(glGenTextures(1, &id));
        GLCall(glBindTexture(GL_TEXTURE_2D, id));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        stbi_set_flip_vertically_on_load(1);
        localBuffer = stbi_load(filePath.c_str(), &width, &height, &BPP, 4);

        if(localBuffer) {
            GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
            GLCall(glBindTexture(GL_TEXTURE_2D, 0));
        }
        else {
            std::cout << "FAILED TO LOAD IMAGE!" <<std::endl;
        }

        stbi_image_free(localBuffer);

}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &id));
}

void Texture::bind(unsigned int slot) const {
    // We have to select the active texture
    //GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::unbind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

#endif