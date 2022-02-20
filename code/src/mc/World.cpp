#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win}{

    // For now only one piece 
    terrain[{0,0}] = PieceOfWorld({0,0});
    //terrain[{0,1}] = PieceOfWorld({0,1});


    // HOW could I manage all the piece of the worlds?

}

std::vector<std::shared_ptr<VertexArray> > World::getAllVertexArrays() {

    std::vector<std::shared_ptr<VertexArray>> arrays{};

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
        arrays.push_back((itr -> second).getVertexArray());
    }

    return arrays;

}

std::vector<std::shared_ptr<ElementBuffer> > World::getAllElementBuffers() {

    std::vector<std::shared_ptr<ElementBuffer>> arrays{};

    // someway reduce the chunks that will be calculed
    for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
        arrays.push_back((itr -> second).getElementBuffer());
    }

    return arrays;

}



/*
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
*/

// This will update also the chunks that will be rendered each frame
void World::updatePos() {
    
}

bool World::isBlock(glm::vec3 pos) {
    // if I see some trouble mean that i do not render properly the piece of world
    // the [] operator add the element to the map if it is no present but all the elmente I will check should be present in the map
    if(pos.y < 0) {
        // std::cout << "there is some trouble with the position for check blocks" <<std::endl;
        return false;
    }
    // TODO put those in a funtion
    int sizeSide = nBlockSide * Block::DIMBLOCK;
    int xWorld = floor(pos.x / sizeSide);
    int zWorld = floor(pos.z / sizeSide);
    int xPieceOfWorld = (int)floor(pos.x) % nBlockSide;
    int zPieceOfWorld = (int)floor(pos.z) % sizeSide;
    int yPieceOfWorld = (int)floor(pos.y) ;
    return terrain[{xWorld, zWorld}].isBlock(xPieceOfWorld, yPieceOfWorld, zPieceOfWorld);
}

void World::breakBlock(glm::vec3 pos) {
    int sizeSide = nBlockSide * Block::DIMBLOCK;
    int xWorld = floor(pos.x / sizeSide);
    int zWorld = floor(pos.z / sizeSide);
    int xPieceOfWorld = (int)floor(pos.x) % nBlockSide;
    int zPieceOfWorld = (int)floor(pos.z) % sizeSide;
    int yPieceOfWorld = (int)floor(pos.y) ;
    terrain[{xWorld, zWorld}].breakBlock(xPieceOfWorld, yPieceOfWorld, zPieceOfWorld);
}

void World::addBlock(TypeOfBlock) {

}

#endif