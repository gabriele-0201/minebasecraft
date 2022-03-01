#ifndef PIECEOFWORLD_H
#define PIECEOFWORLD_H

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <libnoise/noise.h>
#include <future>
#include <chrono>

#include "noiseutils.h"

#include "Enums.h"
#include "Block.h"
#include "HashTuples.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "GLC.h"

constexpr int nBlockSide = 16;
constexpr int nBlockHeight = 256;
constexpr unsigned int ind[] = {
    0, 1, 2,
    2, 3, 1,
    
    2, 3, 7,
    7, 6, 2,

    1, 3, 7,
    7, 5, 1,

    0, 1, 5,
    5, 4, 0,

    0, 2, 6, 
    6, 4, 0,

    4, 6, 7,
    5, 7, 4
};

constexpr unsigned int indOfFaces[] = {
    0, 1, 2,
    2, 3, 1,
};

class PieceOfWorld {

    private:

        std::pair<int, int> pos;
        float xoffset;
        float zoffset;
        int xBlockOffset;
        int zBlockOffset;

        float halfDim;

        //std::shared_future<std::unordered_map<std::tuple<int, int, int>, TypeOfBlock, HashTuples::hash3tuple>> futTerrain;
        std::shared_future<void> futTerrain;
        //bool generatedTerrain;
        //std::future<std::tuple<std::vector<float>, std::vector<unsigned int>, unsigned int>> futBuffers;
        std::future<void> futBuffers;
        bool generatingBuffer;
        bool firstGeneration;

        // Remember all the block, all the not specified block is
        std::map<std::tuple<int, int, int>, TypeOfBlock> blocks;

        std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple>* terrainBlocks;

        std::vector<float> vaData;
        std::vector<unsigned int> ebData;
        unsigned int vertexCounter;

        //std::vector<float> getVerteciesOfAFace(unsigned int, unsigned int, unsigned int, glm::vec3 dir, TypeOfBlock type);
        //std::vector<unsigned int> getIndecesOfAFace(int counter) const;

        std::shared_ptr<VertexArray> va;
        std::shared_ptr<VertexBuffer> vb;
        std::shared_ptr<VertexBufferLayout> layout;
        std::shared_ptr<ElementBuffer> eb;

        //void updateBuffers();
        glm::vec3 cameraPos;

        void bindBuffers();

        template<class T>
        bool isReady(std::future<T> const& f);

        template<class T>
        bool isReady(std::shared_future<T> const& f);
    public:

        // Some way to get NOISE
        PieceOfWorld();
        PieceOfWorld(std::pair<int, int>, noise::module::Perlin& finalTerrain, std::unordered_set<std::tuple<int, int, int>, HashTuples::hash3tuple>* _terrainBlocks);

        //std::vector<float> getVertecies() const;
        //std::vector<unsigned int> getIndecies() const;

        std::pair<int, int> inline getPos() { return pos; };

        std::shared_ptr<VertexArray> getVertexArray();
        std::shared_ptr<ElementBuffer> getElementBuffer();

        /**
         * Check if in a determinate position there is a block or not
         */
        bool isBlock(unsigned int x, unsigned int y, unsigned int z);

        /**
         * Remove the block in the specified position
         */
        void breakBlock(unsigned int x, unsigned int y, unsigned int z);

        void addBlock(unsigned int x, unsigned int y, unsigned int z, TypeOfBlock type);
};

#endif