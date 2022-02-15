#ifndef VERTEXBUFFER_CPP
#define VERTEXBUFFER_CPP

#include"VertexBuffer.h"

VertexBuffer::VertexBuffer() {

}

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data,  GL_STATIC_DRAW));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}


void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &id));
}

#endif