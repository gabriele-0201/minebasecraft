#ifndef PIECEOFWORLD_CPP
#define PIECEOFWORLD_CPP

#include "PieceOfWorld.h"

PieceOfWorld::PieceOfWorld() {

}

PieceOfWorld::PieceOfWorld(std::pair<int, int> _pos) : pos{_pos} {

    for(int z = 0; z < nBlockHeight; ++z) {

        for(int x = 0; x < nBlockSide; ++x) {

            for(int y = 0; y < nBlockSide; ++y) {

                blocks[{x, y, z}] = TypeOfBlock::GRASS;

            }
        }

    }

}

std::vector<float> PieceOfWorld::getData () const {
    std::vector<float> data{};

    for(int z = 0; z < nBlockHeight; ++z) {

        for(int x = 0; x < nBlockSide; ++x) {

            for(int y = 0; y < nBlockSide; ++y) {


                std::vector<float> vertecies = getVertecies(x, y, z);

                data.insert(data.end(), vertecies.begin(), vertecies.end());
            }
        }
    }
    return data;
}


//std::vector<float> PieceOfWorld::getVertecies(float xCenter, float yCenter, float zCenter) const {
std::vector<float> PieceOfWorld::getVertecies(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock) const {

    float halfDim = (float)(Block::DIMBLOCK / 2);
    float xCenter = (float)(Block::DIMBLOCK * xBlock) + halfDim;
    float yCenter = (float)(Block::DIMBLOCK * yBlock) + halfDim;
    float zCenter = (float)(Block::DIMBLOCK * zBlock) + halfDim;

    std::vector<float> vertecies{};
    for(int y = 1; y >= -1; y -= 2) {

        for(int z = -1; z <= 1; z += 2) {

            for(int x = -1; x <= 1; x += 2) {

                vertecies.push_back(xCenter + (float)(halfDim * x));
                vertecies.push_back(yCenter + (float)(halfDim * y));
                vertecies.push_back(zCenter + (float)(halfDim * z));

            }
        }
    }

    return vertecies;
}

/**
 * Starting point
 * 0 0 0
 * 
 * -1  1 -1 - 1
 *  1  1 -1 - 2
 * -1  1  1 - 3
 *  1  1  1 - 4
 * -1 -1 -1 - 5
 *  1 -1 -1 - 6
 * -1 -1  1 - 7
 *  1 -1  1 - 8
*/


#endif