#ifndef RENDERER_CPP
#define RENDERER_CPP

#include"Renderer.h"

void Renderer::draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const {

    shader.bind();
    va.bind();
    ib.bind(); 
    
    // And for now only triangles
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

    //GLCall(glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

#endif
