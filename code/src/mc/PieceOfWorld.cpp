#ifndef PIECEOFWORLD_CPP
#define PIECEOFWORLD_CPP

#include "PieceOfWorld.h"

PieceOfWorld::PieceOfWorld() {

}

PieceOfWorld::PieceOfWorld(std::pair<int, int> _pos) : pos{_pos} {

    // OFFEST ON THE RENDERING
    xoffset = pos.first * nBlockSide * Block::DIMBLOCK;
    zoffset = pos.second * nBlockSide * Block::DIMBLOCK;

    for(int y = 0; y < nBlockHeight; ++y) {

        for(int x = 0; x < nBlockSide; ++x) {

            for(int z = 0; z < nBlockSide; ++z) {

                blocks[{x, y, z}] = TypeOfBlock::GRASS;

            }
        }
    }

    va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    std::cout <<" cacca"<<std::endl;

    vb = std::shared_ptr<VertexBuffer>{ new VertexBuffer{} };

    eb = std::shared_ptr<ElementBuffer>{ new ElementBuffer{nullptr, 0} };
    //eb -> bind();
    
    layout = std::shared_ptr<VertexBufferLayout> { new VertexBufferLayout{} };
    layout -> push<float>(3);

    updateBuffers();
}

void PieceOfWorld::updateBuffers() {

    vb -> updateData(&(getVertecies()[0]), (blocks.size() * 8) * 3 * sizeof(float));
    va -> bindVb(*vb, *layout);

    // update also the idex buffer in the future (when I will render more than one cube)
    eb -> updateData(&(getIndecies()[0]), blocks.size() * 36);
}

std::vector<float> PieceOfWorld::getVertecies() const {
    std::vector<float> data{};

    for(auto itr = blocks.begin(); itr != blocks.end(); ++itr) {
            
        std::tuple<int, int, int> coordinates = itr -> first;
        std::vector<float> vertecies = getVerteciesOfBlock(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates));

        data.insert(data.end(), vertecies.begin(), vertecies.end());
    }

    //for(auto i : data)
        //std::cout << i << " " <<std::endl;

    return data;
}

std::vector<unsigned int> PieceOfWorld::getIndecies() const {
    std::vector<unsigned int> data{};

    int counter = 0;

    while(counter < blocks.size()) {
        std::vector<unsigned int> vertecies = getIndecesOfBlock(counter);

        data.insert(data.end(), vertecies.begin(), vertecies.end());

        counter++;
    }

    //for(auto i : data)
        //std::cout << i << " " <<std::endl;

    return data;
}

std::vector<unsigned int> PieceOfWorld::getIndecesOfBlock(int counter) const {
    std::vector<unsigned int> data;
    for(int i = 0; i < 36; ++i) 
        data.push_back(ind[i] + counter * 8);
    return data;
}


//std::vector<float> PieceOfWorld::getVertecies(float xCenter, float yCenter, float zCenter) const {
std::vector<float> PieceOfWorld::getVerteciesOfBlock(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock) const {

    float halfDim = (float)(Block::DIMBLOCK / 2);
    float xCenter = (float)(Block::DIMBLOCK * xBlock) + halfDim;
    float yCenter = (float)(Block::DIMBLOCK * yBlock) + halfDim;
    float zCenter = (float)(Block::DIMBLOCK * zBlock) + halfDim;

    std::vector<float> vertecies{};
    for(int y = 1; y >= -1; y -= 2) {

        for(int z = -1; z <= 1; z += 2) {

            for(int x = -1; x <= 1; x += 2) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * x));
                vertecies.push_back(yCenter + (float)(halfDim * y));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * z));

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