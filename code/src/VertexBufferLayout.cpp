#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include"VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : stride{0} {}

template<class T>
void VertexBufferLayout::push(unsigned int count) {
    ASSERT(false);
}

//template specialization

template<>
void VertexBufferLayout::push<float> (unsigned int count) {
    elements.push_back( {GL_FLOAT, count, GL_FALSE} );
    stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

/*
template<>
void VertexBufferLayout::push<unsigned int> (unsigned int count) {
    elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char> (unsigned int count) {
    elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
*/

#endif