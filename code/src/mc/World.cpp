#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win} {

    renderingBlockDistance = 10;
    viewBlockDistance = 8;
    currentPos = {0,0};

    srand(time(NULL));

    perl.SetSeed(rand() % 100);
    perl.SetOctaveCount (10);
    perl.SetFrequency (2.0);
    perl.SetPersistence (0.5); 

    updatePos(0, 0, glm::vec3());

}

std::vector<std::pair<int, int>> World::getNearPieceOfWorld(int x, int z, int distance) {

    //int renderingPieces = 2;
    std::vector<std::pair<int, int>> nears {};

    //for(int i = x - renderingPieces; i <= x + renderingPieces; ++i) {
        //for(int j = z - renderingPieces; j <= z + renderingPieces; ++j) {
    for(int i = x - distance; i <= x + distance; ++i) {
        for(int j = z - distance; j <= z + distance; ++j) {
            nears.push_back({i, j});
        }
    }

    return nears;
}

std::vector<std::shared_ptr<VertexArray> > World::getAllVertexArrays() {

    std::vector<std::shared_ptr<VertexArray>> arrays{};
    
    //std::cout << "Currently " << currentPos.first << " - " << currentPos.second << std::endl;

    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second, viewBlockDistance);
    for(auto n: nears) {
        auto v = terrain[{n.first, n.second}].getVertexArray();
        if(v != nullptr) {
            arrays.push_back(v);
            //std::cout << "Nears visible " << n.first << " - " << n.second << std::endl;
        } else {
            //std::cout << " questo non e' presente" <<std::endl;
        }
    }
    return arrays;
}

std::vector<std::shared_ptr<ElementBuffer> > World::getAllElementBuffers() {

    std::vector<std::shared_ptr<ElementBuffer>> arrays{};
    
    // See chunk
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second, viewBlockDistance);
    for(auto n: nears)  {
        auto e = terrain[{n.first, n.second}].getElementBuffer();
        if(e != nullptr)
            arrays.push_back(e);
    }

    return arrays;

}

// This will update also the chunks that will be rendered each frame
void World::updatePos(int x, int z, glm::vec3 _cameraPos) {

    cameraPos = _cameraPos;

    currentPos.first = x;
    currentPos.second = z;
    
    // neatest for rendering
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second, renderingBlockDistance);
    for(auto n: nears) {

        if(terrain.find({n.first, n.second}) == terrain.end()){

            terrain[{n.first, n.second}] = PieceOfWorld({n.first, n.second}, perl, &terrainBlocks);
            //std::cout << "New Piece: " << n.first << " " << n.second <<std::endl;
        }

    }
}

bool World::isBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock) {
    // if I see some trouble mean that i do not render properly the piece of world
    // the [] operator add the element to the map if it is no present but all the elmente I will check should be present in the map
    return terrain[{posOfPiece.x, posOfPiece.y}].isBlock(posOfBlock.x, posOfBlock.y, posOfBlock.z);
}

void World::breakBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock) {
    terrain[{posOfPiece.x, posOfPiece.y}].breakBlock(posOfBlock.x, posOfBlock.y, posOfBlock.z);
}

void World::addBlock(glm::vec2 posOfPiece, glm::vec3 posOfBlock, TypeOfBlock type) {
    terrain[{posOfPiece.x, posOfPiece.y}].addBlock(posOfBlock.x, posOfBlock.y, posOfBlock.z, type);
}


#endif