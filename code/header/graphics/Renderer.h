#ifndef RENDERER_H
#define RENDERER_H

#include<GL/glew.h>
#include<iostream>

#include "VertexArray.h"
#include "Shader.h"
#include "World.h"
#include "Player.h"

// The renderer should take all the stuff to be drawing and draw it to the screen

class Renderer {

    private:

        World& w;
        Player& p;

        VertexArray va;
        VertexBuffer vb;
        VertexBufferLayout layout;
        ElementBuffer eb;

    public:
    
        Renderer(World& w, Player& p);
        ~Renderer();

        //void draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const;

        void draw();

};

#endif
