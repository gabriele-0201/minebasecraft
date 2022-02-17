#ifndef PIECEOFWORLD_H
#define PIECEOFWORLD_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "Enums.h"
#include "Block.h"
#include "HashTuples.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "GLC.h"

constexpr int nBlockSide = 32;
constexpr int nBlockHeight = 1;
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

class PieceOfWorld {

    private:

        std::pair<int, int> pos;
        float xoffset;
        float zoffset;
        // Remember all the block, all the not specified block is
        std::unordered_map<std::tuple<int, int, int>, TypeOfBlock, HashTuples::hash3tuple> blocks;
        //std::map<std::tuple<int, int, int>, int, HashTuples::hash3tuple> faces;

        // THOSE are stabilized vector, there is not embty space in it
        std::vector<float> currentVisibleVertecies;
        std::vector<bool> activeVertecies;

        std::vector<unsigned int> indeces;

        std::vector<float> getVerteciesOfBlock(unsigned int, unsigned int, unsigned int) const;
        std::vector<unsigned int> getIndecesOfBlock(int counter) const;
        std::shared_ptr<VertexArray> va;
        std::shared_ptr<VertexBuffer> vb;
        std::shared_ptr<VertexBufferLayout> layout;
        std::shared_ptr<ElementBuffer> eb;

        void updateBuffers();

    public:

        // Some way to get NOISE
        PieceOfWorld();
        PieceOfWorld(std::pair<int, int>);

        std::vector<float> getVertecies() const;
        std::vector<unsigned int> getIndecies() const;

        std::pair<int, int> inline getPos() { return pos; };

        inline std::shared_ptr<VertexArray> getVertexArray() { return va; };
        inline std::shared_ptr<ElementBuffer> getElementBuffer() { return eb; };

};

#endif