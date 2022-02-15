#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Enums.h"

namespace Block {
    constexpr unsigned int DIMBLOCK = 10;
    // MAYBE A LOT STUPID
    // if I store the vertex of a face in clockwise order and all consecutive THAN i could find a patter
    // but this is not our case, I will not have consecutive vertecies
    constexpr unsigned int indeces[] = {
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
}

#endif