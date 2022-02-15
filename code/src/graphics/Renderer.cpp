#ifndef RENDERER_CPP
#define RENDERER_CPP

#include"Renderer.h"

Renderer::Renderer(World& _w, Player& _p) : w{_w}, p{_p} {

    vb = {&(w.getAllVertecies()[0]), 8 * 4 * sizeof(float)};

    layout.push<float>(3);
    va.bindVb(vb, layout);

    unsigned int tmpIndeces[] = {
        0, 1, 2,
        2, 3, 1,
        
        2, 3, 7,
        7, 6, 2,

        1, 3, 7,
        7, 5, 1,

        0, 1, 5,
        5, 4, 0,

        0, 2, 6, 
        6, 4, 0,

        4, 6, 7,
        5, 7, 4
    };

    eb = {tmpIndeces, 36};

    // TODO solve this problem with the copy of the shader (do not know why but the bind goes away)
    //shader = {"../code/program.shader"};


}

Renderer::~Renderer() {}

/*
void Renderer::draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const {

    shader.bind();
    va.bind();
    ib.bind(); 
    
    // And for now only triangles
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

    //GLCall(glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}
*/

void Renderer::draw() {

    Shader shader("../code/program.shader");
    shader.bind();
    va.bind();
    eb.bind();

    //Texture texture("../minion.jpg");
    //texture.bind();

    // Send a integer uniform to the shader and it is the id we want to sample
    //shader.setUnifor1i("uTexture", 0);
    shader.setUniform4Matrix("view", p.getViewMatrix());

    glm::mat4 proj = glm::perspective(glm::radians(p.fov), 640.0f/ 480.0f, 0.1f, 100.0f);
    shader.setUniform4Matrix("projection", p.getViewMatrix());

    GLCall(glDrawElements(GL_TRIANGLES, eb.getCount(), GL_UNSIGNED_INT, nullptr));
}

#endif
