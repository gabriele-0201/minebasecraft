#ifndef PIECEOFWORLD_CPP
#define PIECEOFWORLD_CPP

#include "PieceOfWorld.h"

PieceOfWorld::PieceOfWorld() {

}

PieceOfWorld::PieceOfWorld(std::pair<int, int> _pos) : pos{_pos} {

    // OFFEST ON THE RENDERING
    xoffset = pos.first * nBlockSide * Block::DIMBLOCK;
    zoffset = pos.second * nBlockSide * Block::DIMBLOCK;

    halfDim = (float)(Block::DIMBLOCK / 2);

    int hGrass = 1;

    for(int x = 0; x < nBlockSide; ++x) {

        for(int z = 0; z < nBlockSide; ++z) {

            // in the future hGrass is the result of a noise function
            for(int y = 0; y < hGrass; ++y) {
                blocks[{x, y, z}] = TypeOfBlock::GRASS;
                //std::cout <<x << " : " << y << " : " <<z <<std::endl;
            }

            for(int y = hGrass; y < nBlockHeight; ++y) {
                blocks[{x, y, z}] = TypeOfBlock::SKY;
                //std::cout <<x << " : " << y << " : " <<z <<std::endl;
            }
        }
    }
    
    blocks[{0, 1, 0}] = TypeOfBlock::GRASS;

    va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    vb = std::shared_ptr<VertexBuffer>{ new VertexBuffer{} };
    eb = std::shared_ptr<ElementBuffer>{ new ElementBuffer{nullptr, 0} };
    
    layout = std::shared_ptr<VertexBufferLayout> { new VertexBufferLayout{} };
    layout -> push<float>(3);

    updateBuffers();
}

void PieceOfWorld::updateBuffers() {

    std::vector<float> vertecies{};
    std::vector<unsigned int> indeces{};
    int counter = 0;

    for(auto itr = blocks.begin(); itr != blocks.end(); ++itr) {

        if((itr -> second) == TypeOfBlock::SKY)
            continue;
            
        // work on vertecies
        std::tuple<int, int, int> coordinates = itr -> first;
        //std::cout << "blocks " <<std::endl;
        std::cout << std::get<0>(coordinates) << " " << std::get<1>(coordinates) << " " << std::get<2>(coordinates) << " " << std::endl;
        //std::cout << " FINE" <<std::endl;

        //std::vector<float> blockCoords = getVerteciesOfBlock(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates));

        // Get vertecies of only the usefull faces

        for(int i = 0; i < 3; ++i) {
            for(int j = -1; j <= 1; j += 2) {

                glm::vec3 dir (0.0f, 0.0f, 0.0f);

                switch (i)  {
                    case 0:
                        dir.x = (float)j;
                        break;
                    case 1:
                        dir.y = (float)j;
                        break;
                    case 2:
                        dir.z = (float)j;
                        break;
                }


                // [] operator is not const
                auto checkValue = blocks.find({std::get<0>(coordinates) + dir.x, std::get<1>(coordinates) + dir.y, std::get<2>(coordinates) + dir.z});
                if(checkValue == blocks.end() || checkValue -> second != TypeOfBlock::SKY)
                    continue;

                //std::cout << dir.x << " " << dir.y << " " << dir.z << " " << std::endl;

                std::vector<float> blockCoords = getVerteciesOfAFace(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates), dir);
                
                vertecies.insert(vertecies.end(), blockCoords.begin(), blockCoords.end());

                // work on indeces
                std::vector<unsigned int> blockInds = getIndecesOfAFace(counter);
                indeces.insert(indeces.end(), blockInds.begin(), blockInds.end());
                counter++;

            }
        }


        // vertecies.insert(vertecies.end(), blockCoords.begin(), blockCoords.end());

        // work on indeces
        //std::vector<unsigned int> blockInds = getIndecesOfBlock(counter);

        //indeces.insert(indeces.end(), blockInds.begin(), blockInds.end());

        //counter++;
    }

    // Degub
    for(auto i : vertecies)
       std::cout << i << " " <<std::endl;
    for(auto i : indeces)
       std::cout << i << " " <<std::endl;

    vb -> updateData(&(vertecies[0]), (counter * 8) * 3 * sizeof(float));
    va -> bindVb(*vb, *layout);

    // update also the idex buffer in the future (when I will render more than one cube)
    eb -> updateData(&(indeces[0]), counter * 36);
}

std::vector<float> PieceOfWorld::getVerteciesOfAFace(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock, glm::vec3 dir) {

    //std::cout << "half dim " << halfDim <<std::endl;

    float xCenter = ((float)(Block::DIMBLOCK * xBlock)) + halfDim;
    float yCenter = ((float)(Block::DIMBLOCK * yBlock)) + halfDim;
    float zCenter = ((float)(Block::DIMBLOCK * zBlock)) + halfDim;

    std::vector<float> vertecies{};

    //std::cout << xBlock << " " << yBlock << " " << zBlock << " " << std::endl;
    // std::cout << "centro oo" << std::endl;
    // std::cout << xCenter << " " << yCenter << " " << zCenter << " " << std::endl;

    for(int i = -1; i <= 1; i += 2) {

        for(int j = -1; j <= 1; j += 2) {

            if(dir.x != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * dir.x));
                vertecies.push_back(yCenter + (float)(halfDim * i));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * j));

            } else if (dir.y != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * i));
                vertecies.push_back(yCenter + (float)(halfDim * dir.y));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * j));

            } else if (dir.z != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * i));
                vertecies.push_back(yCenter + (float)(halfDim * j));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * dir.z));

            }

        }
    }

    return vertecies;
}

std::vector<unsigned int> PieceOfWorld::getIndecesOfAFace(int counter) const {
    std::vector<unsigned int> data;
    for(int i = 0; i < 6; ++i) 
        data.push_back(indOfFaces[i] + counter * 4);
    return data;
}
/*
std::vector<float> PieceOfWorld::getVertecies() const {
    std::vector<float> data{};

    for(auto itr = blocks.begin(); itr != blocks.end(); ++itr) {

        if((itr -> second) == TypeOfBlock::SKY)
            continue;
            
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
*/

std::vector<unsigned int> PieceOfWorld::getIndecesOfBlock(int counter) const {
    std::vector<unsigned int> data;
    for(int i = 0; i < 36; ++i) 
        data.push_back(ind[i] + counter * 8);
    return data;
}


//std::vector<float> PieceOfWorld::getVertecies(float xCenter, float yCenter, float zCenter) const {
std::vector<float> PieceOfWorld::getVerteciesOfBlock(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock) const {

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