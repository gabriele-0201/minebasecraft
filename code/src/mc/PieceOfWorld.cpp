#ifndef PIECEOFWORLD_CPP
#define PIECEOFWORLD_CPP

#include "PieceOfWorld.h"

using namespace std::chrono_literals;

// MAP
//static std::shared_mutex _lockMap;
//static std::unique_lock< Lock > WriteLock;
//static std::shared_lock< Lock > ReadLock;

// Vectors
static std::mutex _lock;

std::atomic_bool finishTerrain = false;

void genTerrain (ThreadSafeMap<std::tuple<int, int, int>, TypeOfBlock>* blocks, std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple>* terrainBlocks,int xBlockOffest, int zBockOffset, noise::module::Perlin& finalTerrain) {

    //std::unordered_map<std::tuple<int, int, int>, TypeOfBlock, HashTuples::hash3tuple> blocks;

    // get upgradable access
    //std::upgrade_lock<std::shared_mutex> lock(_lockMap);

    for(int x = 0; x < nBlockSide; ++x) {

        for(int z = 0; z < nBlockSide; ++z) {

            int xWorld, zWorld;
            xWorld = x + xBlockOffest;
            zWorld = z + zBockOffset;

            int heightCol = (finalTerrain.GetValue(xWorld * 0.001, zWorld * 0.001, 0.0f) + 1) * (256.0f / 2.0f);

            //std::lock_guard<std::mutex> locker(_lock);
            // get exclusive access
            //std::upgrade_to_unique_lock<std::shared_mutex> uniqueLock(lock);

            for(int y = 0; y < heightCol; ++y) {

                // if (y < 70) blocks[{x, y, z}] = TypeOfBlock::STONE;
                // else if (y < 80) blocks[{x, y, z}] = TypeOfBlock::SAND;
                // else if (y < 130) blocks[{x, y, z}] = TypeOfBlock::SOIL;
                // else if (y < 170) blocks[{x, y, z}] = TypeOfBlock::STONE;
                // else blocks[{x, y, z}] = TypeOfBlock::SNOW;

                //std::lock_guard<std::shared_mutex> g(_lockMap);
                _lock.lock();
                if (y < 70) blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::STONE));
                else if (y < 80) blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::SAND));
                else if (y < 130) blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::SOIL));
                else if (y < 170) blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::STONE));
                else blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::SNOW));

                terrainBlocks -> insert({xWorld, y, zWorld});
                _lock.unlock();

            }

            //std::lock_guard<std::shared_mutex> g(_lockMap);

            _lock.lock();
            for(int y = heightCol; y < 70; ++y)
                blocks -> insert(std::make_pair(std::make_tuple(x, y, z), TypeOfBlock::WATER));
                //blocks.operator[] ({x, y, z}) = TypeOfBlock::WATER;

            if(blocks -> find(std::make_tuple(x, heightCol - 1, z)) -> second == TypeOfBlock::STONE || blocks -> find(std::make_tuple(x, heightCol - 1, z)) -> second == TypeOfBlock::SOIL)
                blocks -> insert(std::make_pair(std::make_tuple(x, heightCol - 1, z), TypeOfBlock::GRASS));
                //blocks.operator[] ({x, heightCol - 1, z}) = TypeOfBlock::GRASS;
            _lock.unlock();

        }
    }
    std::cout << blocks -> size() << " dim del terreno generato" <<std::endl;
    finishTerrain = true;
    return;
}

bool faceToDraw(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock, float xoffset, float zoffset, float halfDim, glm::vec3 dir, glm::vec3 cameraPos) {

    float xCenter = ((float)(Block::DIMBLOCK * xBlock)) + halfDim;
    float yCenter = ((float)(Block::DIMBLOCK * yBlock)) + halfDim;
    float zCenter = ((float)(Block::DIMBLOCK * zBlock)) + halfDim;

    // center of the face:
    glm::vec3 centerFace;
    if(dir.x != 0)
        centerFace = glm::vec3 (xoffset + xCenter + (float)(halfDim * dir.x), yCenter, zoffset + zCenter);
    else if (dir.y != 0)
        centerFace = glm::vec3 (xoffset + xCenter, yCenter + (float)(halfDim * dir.y), zoffset + zCenter);
    else if (dir.z != 0) 
        centerFace = glm::vec3 (xoffset + xCenter, yCenter, zoffset + zCenter + (float)(halfDim * dir.z));

    // maybe opposite
    glm::vec3 direction = cameraPos - centerFace;

    glm::vec3 pointToCheck = centerFace + (direction * 0.2f);

    int sizeSide = nBlockSide * Block::DIMBLOCK;
    int x = (int)floor(pointToCheck.x) % sizeSide;
    int y = (int)floor(pointToCheck.y);
    int z = (int)floor(pointToCheck.z) % sizeSide;

    // TEST
    if(x < 0)
        x += nBlockSide;
    if(z < 0)
        z += nBlockSide;

    //std::cout << "Blocchi: " << std::endl;
    //std::cout << "XBlock: " << xBlock << " YBlock: " << yBlock << " ZBlock: " << zBlock <<std::endl;
    //std::cout << "Dir: " << dir.x << " " << dir.y << " " << dir.z << std::endl;
    //std::cout << "x: " << x << " y: " << y << " z: " << z <<std::endl;

    if(x == xBlock && y == yBlock && z == zBlock) {
        std::cout << " fuck lui non lo disegna" <<std::endl;
        return false;
    }

    std::cout << "Ok, lo dovrebbe disegnare" <<std::endl;
    return true;
}

std::vector<float> getVerteciesOfAFace(unsigned int xBlock, unsigned int yBlock, unsigned int zBlock, float halfDim, float xoffset, float zoffset, glm::vec3 dir, TypeOfBlock type, glm::vec3 cameraPos) {

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

std::vector<unsigned int> getIndecesOfAFace(unsigned int counter) {
    std::vector<unsigned int> data;
    for(int i = 0; i < 6; ++i) 
        data.push_back(indOfFaces[i] + counter * 4);
    return data;
}

void genBuffers(ThreadSafeMap<std::tuple<int, int, int>, TypeOfBlock>* blocks, std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple>* terrainBlocks, float halfDim, float xoffset, float zoffset, int xBlockOffset, int zBlockOffset, glm::vec3 cameraPos, std::shared_future<void> futTerrain, std::vector<float>* vertecies, std::vector<unsigned int>* indeces, unsigned int* counter) {

    //if(futTerrain.valid())
        //futTerrain.get();
    while(!finishTerrain);

    (*counter) = 0;

    //std::shared_lock<std::shared_mutex> lock(_lockMap);

    for(auto itr = blocks -> begin(); itr != blocks -> end(); ++itr) {

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

                // USEFULL if I draw the vertex only once
                // if(!faceToDraw(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates), xoffset, zoffset, halfDim, dir, cameraPos))
                //     continue;

                if((std::get<0>(coordinates) + dir.x < 0 || std::get<0>(coordinates) + dir.x >= nBlockSide ||
                    std::get<1>(coordinates) + dir.y < 0 ||
                    std::get<2>(coordinates) + dir.z < 0 || std::get<2>(coordinates) + dir.z >= nBlockSide)) {

                    int xWorld, zWorld, yWorld;
                    xWorld = std::get<0>(coordinates) + xBlockOffset;
                    zWorld = std::get<2>(coordinates) + zBlockOffset;
                    yWorld = std::get<1>(coordinates);

                    std::lock_guard<std::mutex> locker(_lock);
                    if(terrainBlocks -> find({xWorld + dir.x, yWorld + dir.y, zWorld + dir.z}) != terrainBlocks -> end())
                        continue;

                } else {
                
                    //auto checkValue = blocks -> find({std::get<0>(coordinates) + dir.x, std::get<1>(coordinates) + dir.y, std::get<2>(coordinates) + dir.z});
                    //if(checkValue != blocks -> end())
                    //    continue;
                    auto checkValue = blocks -> find(std::make_tuple(std::get<0>(coordinates) + dir.x, std::get<1>(coordinates) + dir.y, std::get<2>(coordinates) + dir.z));
                    if(checkValue != blocks -> end())
                        continue;

                }

                //std::cout << std::get<0>(coordinates) << " " << std::get<1>(coordinates) << " " << std::get<2>(coordinates) << " " << std::endl;
                //std::cout << dir.x << " " << dir.y << " " << dir.z << " " << std::endl;

                std::lock_guard<std::mutex> locker(_lock);
                std::vector<float> blockCoords = getVerteciesOfAFace(std::get<0>(coordinates), std::get<1>(coordinates), std::get<2>(coordinates), halfDim, xoffset, zoffset, dir, itr -> second, cameraPos);
                
                vertecies -> insert(vertecies -> end(), blockCoords.begin(), blockCoords.end());

                // work on indeces
                std::vector<unsigned int> blockInds = getIndecesOfAFace(*counter);
                indeces -> insert(indeces -> end(), blockInds.begin(), blockInds.end());
                (*counter)++;

            }
        }
    }

    //return {vertecies, indeces, counter};
    std::cout << "Dovrei aver finito di generare i bufffers" <<std::endl;
}


PieceOfWorld::PieceOfWorld() {

}

PieceOfWorld::PieceOfWorld(std::pair<int, int> _pos, noise::module::Perlin& finalTerrain, std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple>* _terrainBlocks) : pos{_pos}, terrainBlocks{_terrainBlocks} {

    // OFFEST ON THE RENDERING
    xoffset = pos.first * nBlockSide * Block::DIMBLOCK;
    zoffset = pos.second * nBlockSide * Block::DIMBLOCK;

    halfDim = (float)(Block::DIMBLOCK / 2);
    
    xBlockOffset = pos.first * nBlockSide;
    zBlockOffset = pos.second * nBlockSide;
 
    futTerrain = std::async(std::launch::async, genTerrain, &blocks, terrainBlocks, xBlockOffset, zBlockOffset, std::ref(finalTerrain));
    
    //va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    va = std::shared_ptr<VertexArray>{ nullptr };
    vb = std::shared_ptr<VertexBuffer>{ new VertexBuffer{} };
    eb = std::shared_ptr<ElementBuffer>{ new ElementBuffer{nullptr, 0} };
    
    layout = std::shared_ptr<VertexBufferLayout> { new VertexBufferLayout{} };
    layout -> push<float>(3);
    layout -> push<float>(2);
    
    generatingBuffer = false;
    firstGeneration = false;
    //updateBuffers();
    
    futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset, xBlockOffset, zBlockOffset, cameraPos, futTerrain, &vaData, &ebData, &vertexCounter);

    std::cout << "il costruttore dovrebbe aver finito il suo compito" <<std::endl;
}

void PieceOfWorld::bindBuffers() {

    vb -> updateData(&(vaData[0]), (vertexCounter * 4) * 5 * sizeof(float));
    va -> bindVb(*vb, *layout);

    // update also the idex buffer in the future (when I will render more than one cube)
    // SIX indeces for each face
    eb -> updateData(&(ebData[0]), vertexCounter * 6);

}

bool PieceOfWorld::isBlock(unsigned int x, unsigned int y, unsigned int z) {
    return blocks.find({x, y, z}) != blocks.end();
}

void PieceOfWorld::breakBlock(unsigned int x, unsigned int y, unsigned int z) {
    //std::cout << "Blocco da rimuovere: " << x << " " << y << " " << z << std::endl;
    blocks.erase(std::make_tuple(x, y, z));
    //updateBuffers();

    /*
    if(!generatingBuffer) {
        futBuffers = std::async(std::launch::async, genBuffers, &blocks, halfDim, xoffset, zoffset);
        generatingBuffer = true;
    }
    */
    if(!futBuffers.valid()) {
        futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset, xBlockOffset, zBlockOffset, cameraPos, futTerrain, &vaData, &ebData, &vertexCounter);
    }
}

void PieceOfWorld::addBlock(unsigned int x, unsigned int y, unsigned int z, TypeOfBlock type) {
    //std::cout << "Blocco da aggiungere : " << x << " " << y << " " << z << std::endl;
    //blocks[{x, y, z}] = type;
    //blocks.set(std::make_tuple(x, y, z), type);
    blocks.insert(std::make_pair(std::make_tuple(x, y, z), type));
    //updateBuffers();

    /*
    if(!generatingBuffer) {
        futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset);
        generatingBuffer = true;
    }
    */
    if(!futBuffers.valid()) {
        futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset, xBlockOffset, zBlockOffset, cameraPos, futTerrain, &vaData, &ebData, &vertexCounter);
    }
}

std::shared_ptr<VertexArray> PieceOfWorld::getVertexArray() {

    // if(va == nullptr) {
    //     va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    //     blocks = fut.get();
    //     //std::cout << "start update " <<std::endl;
    //     updateBuffers();
    // }

    if(!futTerrain.valid() || isReady(futTerrain)) {
    //if(finishedTerrain) {
    
        // Just finisched generatin the terrain
        // if(va == nullptr && !futBuffers.valid()) {

        //     blocks = futTerrain.get();
        //     futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset, xBlockOffset, zBlockOffset, cameraPos);
        //     generatingBuffer = true;

        // }

        // the future of the buffers has to be valid and finished
        if(futBuffers.valid() && isReady(futBuffers)) {
            
                //futBuffers.get();

                if(va == nullptr)
                    va = std::shared_ptr<VertexArray>{ new VertexArray{} };

                bindBuffers();

        }
        // otherwise do nothing and use the old va

    }

    return va;


    /*
    if(!futTerrain.valid() || isReady(futTerrain)) {

        if(!firstGeneration) {
            blocks = futTerrain.get();
            futBuffers = std::async(std::launch::async, genBuffers, &blocks, terrainBlocks, halfDim, xoffset, zoffset);
            generatingBuffer = true;
            firstGeneration = true;
        }

        if(!futBuffers.valid() || isReady(futBuffers)) {
            if(generatingBuffer) {
                if(va == nullptr)
                    va = std::shared_ptr<VertexArray> { new VertexArray{} };
                generatingBuffer = false;
                auto buffsData = futBuffers.get();
                vaData = std::get<0>(buffsData);
                ebData = std::get<1>(buffsData);
                vertexCounter = std::get<2>(buffsData);
                bindBuffers();
            }
        }
        else {

            //if(!generatingBuffer) {
            //    futBuffers = std::async(std::launch::async, genBuffers, &blocks, halfDim, xoffset, zoffset);
            //    generatingBuffer = true;
            //}

        }

        if(va != nullptr)
            return va;
    }

    return { nullptr };
    */
}

std::shared_ptr<ElementBuffer> PieceOfWorld::getElementBuffer() {

    // if(va == nullptr) {
    //     va = std::shared_ptr<VertexArray>{ new VertexArray{} };
    //     blocks = fut.get();
    //     updateBuffers();
    // }

    // return eb;

    /*
    if(!futTerrain.valid() || isReady(futTerrain)) {

        if(!futBuffers.valid() || isReady(futBuffers)) {
            // Theorically do not need this, I always call before getVa
            //bindBuffers();
            return eb;
        }

    }

    return { nullptr };
    */
    return eb;
}

template<typename T>
bool PieceOfWorld::isReady(std::future<T> const& f) { 
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; 
}

template<typename T>
bool PieceOfWorld::isReady(std::shared_future<T> const& f) { 
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready; 
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