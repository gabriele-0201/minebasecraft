#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "GLC.h"

class VertexBuffer {

    private:
        /* 
        * OpenGL need an ID for every type of object we create
        * This is an unique ID that will specify the right object
        */
        unsigned int id;

    public:

        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

};

#endif