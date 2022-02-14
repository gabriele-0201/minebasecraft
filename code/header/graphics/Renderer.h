#ifndef RENDERER_H
#define RENDERER_H

#include<GL/glew.h>
#include<iostream>

#include "GLC.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

// The renderer should take all the stuff to be drawing and draw it to the screen

class Renderer {

    public:
       void draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const;

};

#endif
