#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win}{

    // For now only one piece 
    terrain[{0,0}] = PieceOfWorld({0,0});

    //for(float f : terrain[{0, 0}].getData())
        //std::cout << f <<std::endl;

    
    VertexArray va{};

    VertexBuffer vb{pos, 4 * 4 * sizeof(float)};

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.addBuffer(vb, layout);
    //to be insered in the main loop, chek the code of the cherno

    IndexBuffer ib {indeces, 6};
    //IndexBuffer ib {indeces2, 6};

    Shader shader ("../program.shader");
    shader.bind();

    Texture texture("../minion.jpg");
    texture.bind();

    // Send a integer uniform to the shader and it is the id we want to sample
    shader.setUnifor1i("uTexture", 0);

    va.unbind();
    shader.unbind();
    vb.unbind();
    ib.unbind();

    Renderer renderer {};

    float r = 0.0f;
    float incr = 0.01f;

}

void World::render() {

    

}

// This will update also the chunks that will be rendered each frame
void World::updatePos() {
    
}

void World::breakBlock() {

}

void World::addBlock(TypeOfBlock) {

}

#endif