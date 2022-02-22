#ifndef PIECEOFWORLD_CPP
#define PIECEOFWORLD_CPP

#include "PieceOfWorld.h"

using namespace std::chrono_literals;


PieceOfWorld::PieceOfWorld() {

}

PieceOfWorld::PieceOfWorld(std::pair<int, int> _pos, module::Turbulence& finalTerrain) : pos{_pos} {

    // OFFEST ON THE RENDERING
    xoffset = pos.first * nBlockSide * Block::DIMBLOCK;
    zoffset = pos.second * nBlockSide * Block::DIMBLOCK;

    halfDim = (float)(Block::DIMBLOCK / 2);

    /*
    int xBlockoffset = pos.first * nBlockSide;
    int zBlockoffset = pos.second * nBlockSide;

     if(pos.first == 0)
        xBlockoffset = 0;
    else
        xBlockoffset = pos.first * nBlockSide;

     if(pos.second == 0)
        zBlockoffset = 0;
    else
        zBlockoffset = pos.second * nBlockSide;

    int waterLevel = 80;
    int hSoil = 5;
    int hGrass = 1;

    int hLowSand = 75;
    int hHighSand = 85;

    for(int x = 0; x < nBlockSide; ++x) {

        for(int z = 0; z < nBlockSide; ++z) {


            int xWorld, zWorld;
            xWorld = x + xBlockoffset;
            zWorld = z + zBlockoffset;

            int heightCol = (finalTerrain.GetValue(xWorld * 0.001, zWorld * 0.001, 0.0f) + 1) * (256.0f / 2.0f);

            for(int y = 0; y < heightCol; ++y) {
                
                if(y <= hHighSand && y >= hLowSand)
                    blocks[{x, y, z}] = TypeOfBlock::SAND;
                
                if(y >= hHighSand - hGrass)
                    blocks[{x, y, z}] = TypeOfBlock::GRASS;
                else if(y >= hHighSand - hGrass - hSoil) 
                    blocks[{x, y, z}] = TypeOfBlock::SOIL;
                else            
                    blocks[{x, y, z}] = TypeOfBlock::STONE;
            }

            //for(int y = heightCol; y < waterLevel; ++y) {
                //blocks[{x, y, z}] = TypeOfBlock::WATER;
            //}


        }
    }
    */

    future = generated.get_future();
    std::thread t(&PieceOfWorld::genTerrain, this, finalTerrain);

    
    //blocks[{0, 15, 0}] = TypeOfBlock::GRASS;

    va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    vb = std::shared_ptr<VertexBuffer>{ new VertexBuffer{} };
    eb = std::shared_ptr<ElementBuffer>{ new ElementBuffer{nullptr, 0} };
    
    layout = std::shared_ptr<VertexBufferLayout> { new VertexBufferLayout{} };
    layout -> push<float>(3);
    layout -> push<float>(2);

    //updateBuffers();
}

void PieceOfWorld::genTerrain(module::Turbulence& finalTerrain) {
    
    //std::unordered_map<std::tuple<int, int, int>, TypeOfBlock, HashTuples::hash3tuple> blocks;

    int xBlockoffset = pos.first * nBlockSide;
    int zBlockoffset = pos.second * nBlockSide;

     if(pos.first == 0)
        xBlockoffset = 0;
    else
        xBlockoffset = pos.first * nBlockSide;

     if(pos.second == 0)
        zBlockoffset = 0;
    else
        zBlockoffset = pos.second * nBlockSide;

    int waterLevel = 80;
    int hSoil = 5;
    int hGrass = 1;

    int hLowSand = 75;
    int hHighSand = 85;

    for(int x = 0; x < nBlockSide; ++x) {

        for(int z = 0; z < nBlockSide; ++z) {


            int xWorld, zWorld;
            xWorld = x + xBlockoffset;
            zWorld = z + zBlockoffset;

            int heightCol = (finalTerrain.GetValue(xWorld * 0.001, zWorld * 0.001, 0.0f) + 1) * (256.0f / 2.0f);

            for(int y = 0; y < heightCol; ++y) {
                
                if(y <= hHighSand && y >= hLowSand)
                    blocks[{x, y, z}] = TypeOfBlock::SAND;
                
                if(y >= hHighSand - hGrass)
                    blocks[{x, y, z}] = TypeOfBlock::GRASS;
                else if(y >= hHighSand - hGrass - hSoil) 
                    blocks[{x, y, z}] = TypeOfBlock::SOIL;
                else            
                    blocks[{x, y, z}] = TypeOfBlock::STONE;
            }

            //for(int y = heightCol; y < waterLevel; ++y) {
                //blocks[{x, y, z}] = TypeOfBlock::WATER;
            //}


        }
    }

    updateBuffers();

    generated.set_value(true);

}

int PieceOfWorld::noise(int x, int y, noise::module::Perlin& noiseObj) {
    // Scale from -1 : 1 to 0 : 255
    // noise : 1 = x : 256
    //double nx = x/nBlockSide;
    //double ny = y/nBlockSide;
    double nx = x + 0.001;
    double ny = y + 0.001;
    double freq = 1.2;
    double noiseResult = noiseObj.GetValue(nx, ny, 0) / 2.0 + 0.5;
    return floor(noiseResult * 256.0f);
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


                // TEST not assign SKY type, if is not in the map so it is sky
                // [] operator is not const

                // Check out of bounds: (n=only for now)

                if(std::get<0>(coordinates) + dir.x < 0 || std::get<0>(coordinates) + dir.x >= nBlockSide)
                    continue;
                if(std::get<1>(coordinates) + dir.y < 0)
                    continue;
                if(std::get<2>(coordinates) + dir.z < 0 || std::get<2>(coordinates) + dir.z >= nBlockSide)
                    continue;

                auto checkValue = blocks.find({std::get<0>(coordinates) + dir.x, std::get<1>(coordinates) + dir.y, std::get<2>(coordinates) + dir.z});
                // THIS solution is only for now, because I'm rendering all the freaking faces beteween chunks
                // RENDER also the side of the the face to other chunks
                if(checkValue != blocks.end() && checkValue -> second != TypeOfBlock::SKY)
                    continue;

                //std::cout << std::get<0>(coordinates) << " " << std::get<1>(coordinates) << " " << std::get<2>(coordinates) << " " << std::endl;
                //std::cout << dir.x << " " << dir.y << " " << dir.z << " " << std::endl;

                std::vector<float> blockCoords = getVerteciesOfAFace(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates), dir, itr -> second);
                
                // std::vector<float> test {0.0f, 0.0f, 0.0f};
                // if(blockCoords == test)
                //     std::cout << counter <<std::endl;
                
                vertecies.insert(vertecies.end(), blockCoords.begin(), blockCoords.end());

                // work on indeces
                std::vector<unsigned int> blockInds = getIndecesOfAFace(counter);
                indeces.insert(indeces.end(), blockInds.begin(), blockInds.end());
                counter++;

            }
        }
    }

    //std::cout << counter << std::endl;

    // Degub
    // for(auto i : vertecies)
    //    std::cout << i << " " <<std::endl;
    // std::cout << " Fine vertici " <<std::endl;
    // for(auto i : indeces)
    //    std::cout << i << " " <<std::endl;

    vb -> updateData(&(vertecies[0]), (counter * 4) * 5 * sizeof(float));
    va -> bindVb(*vb, *layout);

    // update also the idex buffer in the future (when I will render more than one cube)
    // SIX indeces for each face
    eb -> updateData(&(indeces[0]), counter * 6);
}

std::vector<float> PieceOfWorld::getVerteciesOfAFace(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock, glm::vec3 dir, TypeOfBlock type) {

    //std::cout << "half dim " << halfDim <<std::endl;

    float xCenter = ((float)(Block::DIMBLOCK * xBlock)) + halfDim;
    float yCenter = ((float)(Block::DIMBLOCK * yBlock)) + halfDim;
    float zCenter = ((float)(Block::DIMBLOCK * zBlock)) + halfDim;

    std::vector<float> vertecies{};

    //std::cout << xBlock << " " << yBlock << " " << zBlock << " " << std::endl;
    // std::cout << "centro oo" << std::endl;
    // std::cout << xCenter << " " << yCenter << " " << zCenter << " " << std::endl;
    // std::cout << "dir " <<std::endl;
    // std::cout << dir.x << " " << dir.y << " " << dir.z << " " << std::endl;

    // Create the vertecies fot the faces and add also the texCoord in funtion to the vertecies we are calculating
    for(int i = -1; i <= 1; i += 2) {

        for(int j = -1; j <= 1; j += 2) {


            if(dir.x != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * dir.x));
                //vertecies.push_back(yCenter + (float)(halfDim * i));
                //vertecies.push_back(zoffset + zCenter + (float)(halfDim * j));
                vertecies.push_back(yCenter + (float)(halfDim * j));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * i));

            } else if (dir.y != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * i));
                vertecies.push_back(yCenter + (float)(halfDim * dir.y));
                // INVERT THAT FOR NOW, see that will work
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * (j * (-1))));

            } else if (dir.z != 0) {

                vertecies.push_back(xoffset + xCenter + (float)(halfDim * i));
                vertecies.push_back(yCenter + (float)(halfDim * j));
                vertecies.push_back(zoffset + zCenter + (float)(halfDim * dir.z));

            }

            // TODO understand how get the corner from i and j
            std::pair<float, float> texCoord = Block::getTexCoord(i, j, type, dir);
            // std::cout << "TEX COORD for " << i << " - " <<j <<" coord: " << texCoord.first << " " << texCoord.second << std::endl;
            vertecies.push_back(texCoord.first);
            vertecies.push_back(texCoord.second);

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

bool PieceOfWorld::isBlock(unsigned int x, unsigned int y, unsigned int z) {
    return blocks.find({x, y, z}) != blocks.end();
}

void PieceOfWorld::breakBlock(unsigned int x, unsigned int y, unsigned int z) {
    //std::cout << "Blocco da rimuovere: " << x << " " << y << " " << z << std::endl;
    blocks.erase({x, y, z});
    updateBuffers();
}

void PieceOfWorld::addBlock(unsigned int x, unsigned int y, unsigned int z, TypeOfBlock type) {
    //std::cout << "Blocco da aggiungere : " << x << " " << y << " " << z << std::endl;
    blocks[{x, y, z}] = type;
    updateBuffers();
}

std::shared_ptr<VertexArray> PieceOfWorld::getVertexArray() {
    status == future.wait_for(0ms);
    if (status == std::future_status::ready)
        return va;
    else 
        return {nullptr};
}

std::shared_ptr<ElementBuffer> PieceOfWorld::getElementBuffer() {
    status == future.wait_for(0ms);
    if (status == std::future_status::ready)
        return eb;
    else 
        return {nullptr};
}
/**
 * Starting point
 * 0 0 0
 * 
 * Vertecies for a cube:
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