#ifndef PIECEOFWORLD_H
#define PIECEOFWORLD_H

//#include <unordered_map>
#include <map>
#include <vector>

#include "Enums.h"
#include "Block.h"
#include "HashPair.h"

constexpr int nBlockSide = 32;
constexpr int nBlockHeight = 3;

class PieceOfWorld {

    private:

        std::pair<int, int> pos;
        // Remember all the block, all the not specified block is
        std::map<std::tuple<int, int, int>, TypeOfBlock> blocks;

        //std::vector<float> getVertecies(float xCenter, float yCenter, float zCenter) const;
        std::vector<float> getVertecies(unsigned int, unsigned int, unsigned int) const;

    public:

        // Some way to get NOISE
        PieceOfWorld();
        PieceOfWorld(std::pair<int, int>);

        std::vector<float> getData() const;


};

#endif