#ifndef VERTEXARRAY_CPP
#define VERTEXARRAY_cpp

#include "VertexArray.h"

VertexArray::VertexArray(){
    GLCall(glGenVertexArrays(1, &id));
}

VertexArray::~VertexArray(){
    GLCall(glDeleteVertexArrays(1, &id));
}

/**
 * Maybe usefull but when some change but I do not want to recreate the entire vertex array
 */
void VertexArray::bindVb(VertexBuffer vb, VertexBufferLayout layout){
    GLCall();
    vb.bind();

    unsigned int offset = 0;
    unsigned int index = 0;
    for(VertexBufferElement elem : layout.getElements()) {
        GLCall(glEnableVertexAttribArray(index++));
        GLCall(glVertexAttribPointer(index, elem.count, elem.type, elem.normalized, layout.getStride(), (const void*)offset));
        offset += elem.count * VertexBufferElement::getSizeOfType(elem.type);
    }

}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(id));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}

#endif