#ifndef VERTEXBUFFER_CPP
#define VERTEXBUFFER_CPP

#include"VertexBuffer.h"


VertexBuffer::VertexBuffer() {

    //float* dataflaot = (float*) data;
    //for(int i = 0; i < size/sizeof(float); ++i)
        //std::cout << dataflaot[i] <<std::endl;

    GLCall(glGenBuffers(1, &id));
}

void VertexBuffer::updateData(const void* data, unsigned int size) {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data,  GL_DYNAMIC_DRAW));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}


void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer() {
    if(!defCostruct)
        GLCall(glDeleteBuffers(1, &id));
}

#endif