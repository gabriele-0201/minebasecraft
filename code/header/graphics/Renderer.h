#ifndef RENDERER_H
#define RENDERER_H

#include<GL/glew.h>
#include<iostream>
#include<memory>

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "World.h"
#include "Player.h"

// The renderer should take all the stuff to be drawing and draw it to the screen

class Renderer {

    private:

        World& w;
        Player& p;
        glm::mat4 proj;
        float distanceOfView;

        //std::unique_ptr<VertexArray> va;
        //std::unique_ptr<VertexBuffer> vb;
        //std::unique_ptr<VertexBufferLayout> layout;
        //std::unique_ptr<ElementBuffer> eb;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;

        //VertexArray va;
        //VertexBuffer vb;
        //VertexBufferLayout layout;
        //ElementBuffer eb;
        //Shader shader;

    public:
    
        Renderer(World& w, Player& p);
        ~Renderer();

        void draw();

        /**
         * Window update size
         */
        void winSizeCb(float width, float height);

};

#endif
