#ifndef PIECEOFWORLD_H
#define PIECEOFWORLD_H

#include <unordered_map>
#include <vector>

#include "Enums.h"
#include "Block.h"
#include "HashTuples.h"

constexpr int nBlockSide = 32;
constexpr int nBlockHeight = 3;

class PieceOfWorld {

    private:

        std::pair<int, int> pos;
        // Remember all the block, all the not specified block is
        std::unordered_map<std::tuple<int, int, int>, TypeOfBlock, HashTuples::hash3tuple> blocks;
        //std::map<std::tuple<int, int, int>, int, HashTuples::hash3tuple> faces;

        // THOSE are stabilized vector, there is not embty space in it
        std::vector<float> currentVisibleVertecies;
        std::vector<bool> activeVertecies;

        std::vector<unsigned int> indeces;

        //std::vector<float> getVertecies(float xCenter, float yCenter, float zCenter) const;
        std::vector<float> getVertecies(unsigned int, unsigned int, unsigned int) const;

    public:

        // Some way to get NOISE
        PieceOfWorld();
        PieceOfWorld(std::pair<int, int>);

        std::vector<float> getVertecies() const;
        std::vector<unsigned int> getIndecies() const;

        std::pair<int, int> inline getPos() { return pos; }


};

#endif