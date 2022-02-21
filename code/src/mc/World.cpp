#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win}{

    // For now only one piece 
    //terrain[{0,0}] = PieceOfWorld({0,0});
    //terrain[{0,1}] = PieceOfWorld({0,1});

    // Create the 9 starting pieces
    // for(int i = -1; i < 2; ++i) {
    //     for(int j = -1; j < 2; ++j) {
    //         terrain[{i,j}] = PieceOfWorld({i,j});
    //     }
    // }

    currentPos = {0,0};

    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(0, 0);
    for(auto n: nears) {
        //std::cout << n.first << " " << n.second << std::endl;
        terrain[{n.first, n.second}] = PieceOfWorld({n.first, n.second});
    }

    // HOW could I manage all the piece of the worlds?

}

std::vector<std::pair<int, int>> World::getNearPieceOfWorld(int x, int z) {

    int renderingPieces = 10;
    std::vector<std::pair<int, int>> nears {};

    for(int i = x - renderingPieces; i <= x + renderingPieces; ++i) {
        for(int j = z - renderingPieces; j <= z + renderingPieces; ++j) {
            nears.push_back({i, j});
        }
    }

    return nears;
}

std::vector<std::shared_ptr<VertexArray> > World::getAllVertexArrays() {

    std::vector<std::shared_ptr<VertexArray>> arrays{};

    // someway reduce the chunks that will be calculed

    //std::cout <<" RENDERING " <<std::endl;
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second);
    for(auto n: nears) {

        //std::cout << n.first << " " << n.second << std::endl;

        arrays.push_back(terrain[{n.first, n.second}].getVertexArray());


        //if(terrain.find({n.first, n.second}) != terrain.end())
            //terrain[n.first, n.second] = PieceOfWorld({n.first, n.second});

    }

    //for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
        //arrays.push_back((itr -> second).getVertexArray());
    //}

    return arrays;

}

std::vector<std::shared_ptr<ElementBuffer> > World::getAllElementBuffers() {

    std::vector<std::shared_ptr<ElementBuffer>> arrays{};

    // someway reduce the chunks that will be calculed
    //for(auto itr = terrain.begin(); itr != terrain.end(); ++itr) {
    //    arrays.push_back((itr -> second).getElementBuffer());
    //}
    
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second);
    for(auto n: nears) {


        arrays.push_back(terrain[{n.first, n.second}].getElementBuffer());


        //if(terrain.find({n.first, n.second}) != terrain.end())
            //terrain[n.first, n.second] = PieceOfWorld({n.first, n.second});

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
void World::updatePos(int x, int z) {

    currentPos.first = x;
    currentPos.second = z;
    
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second);
    for(auto n: nears) {

        if(terrain.find({n.first, n.second}) == terrain.end()){
            terrain[{n.first, n.second}] = PieceOfWorld({n.first, n.second});
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