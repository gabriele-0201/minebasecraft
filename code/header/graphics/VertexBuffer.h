#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "GLC.h"

class VertexBuffer {

    private:
        // Keep track if the Object is created with a default constructor
        bool defCostruct;

        /* 
        * OpenGL need an ID for every type of object we create
        * This is an unique ID that will specify the right object
        */
        unsigned int id;

    public:

        VertexBuffer();
        ~VertexBuffer();

        void updateData(const void* data, unsigned int size);
        VertexBuffer(const VertexBuffer&) = delete;
        void operator=(const VertexBuffer&) = delete;

        void bind() const;
        void unbind() const;

};

#endif