#ifndef ELEMENTBUFFER_CPP
#define ELEMENTBUFFER_CPP

#include "ElementBuffer.h"

ElementBuffer::ElementBuffer () : defCostruct{true} {

}

ElementBuffer::ElementBuffer(unsigned int* data, unsigned int _count) : count{_count}, defCostruct{true}  {
    GLCall(glGenBuffers(1, &id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
};

void ElementBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}


void ElementBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

ElementBuffer::~ElementBuffer() {
    // NOT delete the buffer if I did not created it (default constructor used)
    if(!defCostruct)
        GLCall(glDeleteBuffers(1, &id));
};

#endif