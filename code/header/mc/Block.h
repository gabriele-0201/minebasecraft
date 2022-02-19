#ifndef BLOCK_H
#define BLOCK_H

#include "Enums.h"
#include <glm/glm.hpp>
#include <utility>

namespace Block {
    constexpr float DIMBLOCK = 1.0f;
    constexpr float DIMTEXBLOCK = 0.0624f;

    static std::pair<int, int> getRowColumn(TypeOfBlock type, glm::vec3 dir) {
        
        std::pair<int, int> pos;

        switch (type) {
            case TypeOfBlock::GRASS:
                
                pos.first = 16;

                if(dir.y == 1) 
                    pos.second = 1;
                else if(dir.y == -1) 
                    pos.second = 3;
                else 
                    pos.second = 2;

                break;
            case TypeOfBlock::SAND:
                pos.first = 15;
                pos.second = 1;
                break;
            case TypeOfBlock::STONE:
                pos.first = 16;
                pos.second = 4;
                break;
            default:
                break;
        } 
        return pos;
    }

    static std::pair<float, float> getTexCoordTopLeft(TypeOfBlock type, glm::vec3 dir) { 


        std::pair<int, int> pos = getRowColumn(type, dir);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second - 1)) * DIMTEXBLOCK;
        return tex;

    }

    static std::pair<float, float> getTexCoordTopRight(TypeOfBlock type, glm::vec3 dir) { 


        std::pair<int, int> pos = getRowColumn(type, dir);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second)) * DIMTEXBLOCK;
        return tex;

    }

    static std::pair<float, float> getTexCoordBottomLeft(TypeOfBlock type, glm::vec3 dir) { 


        std::pair<int, int> pos = getRowColumn(type, dir);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second - 1)) * DIMTEXBLOCK;
        return tex;

    }

    static std::pair<float, float> getTexCoordBottomRight(TypeOfBlock type, glm::vec3 dir) { 


        std::pair<int, int> pos = getRowColumn(type, dir);
        std::pair<float, float> tex;
        tex.first = ((float)(pos.first - 1)) * DIMTEXBLOCK;
        tex.second = ((float)(pos.second)) * DIMTEXBLOCK;
        return tex;

    }
    
    static std::pair<float, float> getTexCoord (int i, int j, TypeOfBlock type, glm::vec3 dir) {
        if(i == -1 && j == -1)
            return getTexCoordBottomLeft(type, dir);
        else if(i == -1 && j == 1)
            return getTexCoordTopLeft(type, dir);
        else if(i == 1 && j == -1)
            return getTexCoordBottomRight(type, dir);
        //else if(i == 1 && j == 1)
        else
            return getTexCoordTopRight(type, dir);
    }

}

#endif