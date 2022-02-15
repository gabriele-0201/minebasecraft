#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win}{

    // For now only one piece 
    terrain[{0,0}] = PieceOfWorld({0,0});

    //for(float f : terrain[{0, 0}].getData())
        //std::cout << f <<std::endl;

    

}


std::vector<std::vector<float>> World::getAllVertecies() {

    std::vector<std::vector<float>> buffers{};
    buffers.push_back(std::vector<float> {});

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
       buffers.push_back((itr -> second).getVertecies());
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