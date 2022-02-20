#ifndef VERTEXARRAY_CPP
#define VERTEXARRAY_cpp

#include "VertexArray.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &id));
}



VertexArray::~VertexArray(){
    GLCall(glDeleteVertexArrays(1, &id));
}



/**
 * Maybe usefull but when some change but I do not want to recreate the entire vertex array
 */
void VertexArray::bindVb(const VertexBuffer& vb, const VertexBufferLayout& layout){
    bind();
    vb.bind();

    //get all the elements in the layout
    const auto& elements = layout.getElements();
    //for each have to set up the layouit
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i) {

        const auto& element = elements[i];
    
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.getStride(), (const void*)offset));
    
        //we need to know the size of each type 
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const {
    GLCall(glBindVertexArray(id));
}

void VertexArray::unbind() const {
    GLCall(glBindVertexArray(0));
}

#endif