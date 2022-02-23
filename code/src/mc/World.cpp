#ifndef WORLD_CPP
#define WORLD_CPP

#include "World.h"

World::World(GLFWwindow* _win, unsigned int seed) : win{_win} {

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

    srand(time(NULL));

    baseFlatTerrain.SetFrequency (2.0);

    flatTerrain.SetSourceModule (0, baseFlatTerrain);
    flatTerrain.SetScale (0.125);
    flatTerrain.SetBias (-0.75);

    terrainType.SetFrequency (0.5);
    terrainType.SetPersistence (0.25);

    terrainSelector.SetSourceModule (0, flatTerrain);
    terrainSelector.SetSourceModule (1, mountainTerrain);
    terrainSelector.SetControlModule (terrainType);
    terrainSelector.SetBounds (0.0, 1000.0);
    terrainSelector.SetEdgeFalloff (0.125);

    finalTerrain.SetSourceModule (0, terrainSelector);
    finalTerrain.SetFrequency (4.0);
    finalTerrain.SetPower (0.125);
    
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(0, 0);
    for(auto n: nears) {
        //std::cout << n.first << " " << n.second << std::endl;

        terrain[{n.first, n.second}] = PieceOfWorld({n.first, n.second}, finalTerrain);
    }

}

std::vector<std::pair<int, int>> World::getNearPieceOfWorld(int x, int z) {

    int renderingPieces = 3;
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

// This will update also the chunks that will be rendered each frame
void World::updatePos(int x, int z) {

    currentPos.first = x;
    currentPos.second = z;
    
    std::vector<std::pair<int, int>> nears = getNearPieceOfWorld(currentPos.first, currentPos.second);
    for(auto n: nears) {

        if(terrain.find({n.first, n.second}) == terrain.end()){

            terrain[{n.first, n.second}] = PieceOfWorld({n.first, n.second}, finalTerrain);
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