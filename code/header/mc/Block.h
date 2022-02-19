#ifndef BLOCK_H
#define BLOCK_H

#include "Enums.h"

namespace Block {
    constexpr float DIMBLOCK = 1.0f;
    constexpr float DIMTEXBLOCK = 0.0624f;
    // MAYBE A LOT STUPID
    // if I store the vertex of a face in clockwise order and all consecutive THAN i could find a patter
    // but this is not our case, I will not have consecutive vertecies
//    constexpr unsigned int indecesOfCube[] = {
//        0, 1, 2,
//        2, 3, 1,
//        
//        2, 3, 7,
//        7, 6, 2,
//
//        1, 3, 7,
//        7, 5, 1,
//
//        0, 1, 5,
//        5, 4, 0,
//
//        0, 2, 6, 
//        6, 4, 0,
//
//        4, 6, 7,
//        5, 7, 4
//    };

    std::pair<int, int> getRowColumn(TypeOfBlock type) {
        
        std::pair<int, int> pos;

        switch (type) {
            case TypeOfBlock::GRASS:
                pos.first = 1;
                pos.second = 1;
                break;
       
            default:
                break;
        } 
        return pos;
    }

    std::pair<float, float> getTexCoordTopLeft(TypeOfBlock type) { 


        std::pair<int, int> pos = getRowColumn(type);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first - 1)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second - 1)) * DIMTEXBLOCK;
        return tex;

    }

    std::pair<float, float> getTexCoordTopRight(TypeOfBlock type) { 


        std::pair<int, int> pos = getRowColumn(type);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second - 1)) * DIMTEXBLOCK;
        return tex;

    }

    std::pair<float, float> getTexCoordBottomLeft(TypeOfBlock type) { 


        std::pair<int, int> pos = getRowColumn(type);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first - 1)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second)) * DIMTEXBLOCK;
        return tex;

    }

    std::pair<float, float> getTexCoordBottomRight(TypeOfBlock type) { 


        std::pair<int, int> pos = getRowColumn(type);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second)) * DIMTEXBLOCK;
        return tex;

    }
    
    std::pair<float, float> getTexCoord (int i, int j, TypeOfBlock type) {
        if(i == -1 && j == -1)
            return getTexCoordBottomLeft(type);
        else if ( ... )
    }

}

#endif