#ifndef RENDERER_CPP
#define RENDERER_CPP

#include"Renderer.h"

Renderer::Renderer(World& _w, Player& _p) : 
        w{_w}, p{_p}
        //vb{&(w.getAllVertecies()), 8 * 3 * sizeof(float)},
        //shader{"../code/program.shader"}
        //eb{tmpIndeces, 36}
        {

    shader = std::unique_ptr<Shader>{ new Shader{"../code/program.shader"} };


    proj = glm::perspective(glm::radians(p.fov), 1200.0f/ 900.0f, 0.1f, 100.0f);

}

Renderer::~Renderer() {}

void Renderer::draw() {
    // DO SOME STUFF USING PIECE OF WORLDS

    shader -> bind();

    shader -> setUniform4Matrix("view", p.getViewMatrix());

    shader -> setUniform4Matrix("projection", proj);

    std::vector<std::shared_ptr<VertexArray>> vas = w.getAllVertexArrays();
    std::vector<std::shared_ptr<ElementBuffer>> ebs = w.getAllElementBuffers();

    for(int i = 0; i < vas.size(); ++i) {

        vas[i] -> bind();
        ebs[i] -> bind();

        GLCall(glDrawElements(GL_TRIANGLES, ebs[i] -> getCount(), GL_UNSIGNED_INT, nullptr));

        vas[i] -> unbind();
        ebs[i] -> unbind();
    }

    //Texture texture("../minion.jpg");
    //texture.bind();

    // Send a integer uniform to the shader and it is the id we want to sample
    //shader.setUnifor1i("uTexture", 0);

    // I will use an integer in the buffer data to say witch texture

}


void Renderer::winSizeCb(float width, float height) {

    proj = glm::perspective(glm::radians(p.fov), width / height, 0.1f, 100.0f);

    glViewport(0, 0, width, height);
}
#endif
