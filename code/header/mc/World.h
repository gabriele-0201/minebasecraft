#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "Enums.h"
#include "PieceOfWorld.h"
#include "HashTuples.h"
#include "GLC.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "ElementBuffer.h"
  
class World { 

    private:

        GLFWwindow* win;

        // Someway store chunkssss
        std::unordered_map<std::tuple<int, int>, PieceOfWorld, HashTuples::hash2tuple> terrain;

    public:

        World(GLFWwindow* win, unsigned int seed);

        void render();

        /**
         * Return a vector containing two vectors:
         * 1 - contains all the vertex to be used in the buffer
         * 2 - contains all the indeces that is used to draw the stuff int the same index buffer
         */
        std::vector<std::vector<float>> getAllVertecies();
        std::vector<std::vector<unsigned int>> getAllIndicies();

        // This will update also the chunks that will be rendered each frame
        void updatePos();

        void breakBlock();

        void addBlock(TypeOfBlock);

};

#endif