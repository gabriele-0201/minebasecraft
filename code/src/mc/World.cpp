#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win}{

    // For now only one piece 
    terrain[{0,0}] = PieceOfWorld({0,0});
    terrain[{0,1}] = PieceOfWorld({0,1});

}

std::vector<std::shared_ptr<VertexArray> > World::getAllVertexArrays() {

    std::vector<std::shared_ptr<VertexArray>> arrays{};
    //buffers.push_back(std::vector<float> {});

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
        arrays.push_back((itr -> second).getVertexArray());
    }

    return arrays;

}

std::vector<std::shared_ptr<ElementBuffer> > World::getAllElementBuffers() {

    std::vector<std::shared_ptr<ElementBuffer>> arrays{};
    //buffers.push_back(std::vector<float> {});

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
        arrays.push_back((itr -> second).getElementBuffer());
    }

    return arrays;

}



std::vector<float> World::getAllVertecies() {

    std::vector<float> buffers{};
    //buffers.push_back(std::vector<float> {});

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {

        std::vector<float> vertecies = (itr -> second).getVertecies();

        buffers.insert(buffers.end(), vertecies.begin(), vertecies.end());
    }

    return buffers;
}

std::vector<std::vector<unsigned int>> World::getAllIndicies() {

    std::vector<std::vector<unsigned int>> buffers{};
    buffers.push_back(std::vector<unsigned int> {});

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
       buffers.push_back((itr -> second).getIndecies());
    }

    return buffers;
}

// This will update also the chunks that will be rendered each frame
void World::updatePos() {
    
}

void World::breakBlock() {

}

void World::addBlock(TypeOfBlock) {

}

#endif